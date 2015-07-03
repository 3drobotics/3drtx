/*
 * Authors (alphabetical order)
 * - Andre Bernet <bernet.andre@gmail.com>
 * - Andreas Weitl
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 * - Cameron Weeks <th9xer@gmail.com>
 * - Erez Raviv
 * - Gabriel Birkus
 * - Jean-Pierre Parisy
 * - Karl Szmutny
 * - Michael Blandford
 * - Michal Hlavinka
 * - Pat Mackenzie
 * - Philip Moss
 * - Rob Thomson
 * - Romolo Manfredini <romolo.manfredini@gmail.com>
 * - Thomas Husterer
 *
 * opentx is based on code named
 * gruvin9x by Bryan J. Rentoul: http://code.google.com/p/gruvin9x/,
 * er9x by Erez Raviv: http://code.google.com/p/er9x/,
 * and the original (and ongoing) project by
 * Thomas Husterer, th9x: http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "../../opentx.h"

#ifndef SIMU
inline void boardInit()            // Done 2013.10.09 : trims, keyboard, LCD, ID1+2 SW     warning PORTF-3 (1.2V ADC_ref)
{
  // Set up I/O port data directions and initial states
  DDRA = 0b11111111;  PORTA = 0b00000000; // LCD data
  DDRB = 0b11000111;  PORTB = 0b00111111; // 7:SPKR, 6:PPM_OUT, 5:TrainSW, 4:xxxxx, SDCARD[3:MISO 2:MOSI 1:SCK 0:CS]
  DDRC = 0b11111100;  PORTC = 0b00000011; // LCD[7,6,5,4,3], 2:BackLight, 1:ID2_Sw, 0:ID1_Sw
  DDRD = 0b11000000;  PORTD = 0b11111100; // 7:VIB, 6:LED BL, 5:RENC2_PUSH, 4:RENC1_PUSH, 3:RENC2_B, 2:RENC2_A, 1:I2C_SDA, 0:I2C_SCL
  DDRE = 0b00001010;  PORTE = 0b11110100; // 7:PPM_IN, 6: RENC1_B, 5:RENC1_A, 4:USB_DNEG, 3:BUZZER, 2:USB_DPOS, 1:TELEM_TX, 0:TELEM_RX(pull-up off)
//DDRF = 0b00000000;  PORTF = 0b00000000; // 7-4:JTAG, 3:ADC_REF_1.2V input, 2-0:ADC_SPARE_2-0
  DDRF = 0b00000000;  PORTF = 0b11111111; // 7-0:Trim switch inputs
  
  DDRG = 0b00010000;  PORTG = 0b00111111; // 7-6:N/A, 5:GearSW, 4: Sim_Ctrl[out], 3:xxxxx, 2:TCut_Sw, 1:RF_Power[in], 0: RudDr_Sw
  DDRH = 0b10111000;  PORTH = 0b11010111; // [7:0 DSM/PPM TX-caddy control. 1=PPM, 0=DSM ]
                                          // [6:SOMO14D-BUSY 5:SOMO14D-DATA 4:SOMO14D-CLK 3:SOMO14D-RESET]
                                          // [2:VIB_OPTION -- setting to input for now]
                                          // [1:TxD 0:RxD Spare serial port]
//DDRJ = 0b00000000;  PORTJ = 0b11111111; // 7-0:Trim switch inputs
  DDRK = 0b00000000;  PORTK = 0b00000000; // Analogic input (no pull-ups)
  DDRL = 0b10000000;  PORTL = 0b11111111; // 7: Hold_PWR_On (1=On, default Off), 6:Jack_Presence_TTL, 5-0: Keyboard inputs

  ADMUX=ADC_VREF_TYPE;
  ADCSRA=0x85; // ADC enabled, pre-scaler division=32 (no interrupt, no auto-triggering)
  ADCSRB=(1<<MUX5);

  /**** Set up timer/counter 0 ****/
  /** Move old 64A Timer0 functions to Timer2 and use WGM on OC0(A) (PB7) for spkear tone output **/

  // TCNT0  10ms = 16MHz/1024/156(.25) periodic timer (100ms interval)
  //        cycles at 9.984ms but includes 1:4 duty cycle correction to /157 to average at 10.0ms
  TCCR2B  = (0b111 << CS20); // Norm mode, clk/1024 (differs from ATmega64 chip)
  OCR2A   = 156;
  TIMSK2 |= (1<<OCIE2A) |  (1<<TOIE2); // Enable Output-Compare and Overflow interrrupts

  // Set up Phase correct Waveform Gen. mode, at clk/64 = 250,000 counts/second
  // (Higher speed allows for finer control of frquencies in the audio range.)
  // Used for audio tone generation
  TCCR0B  = (1<<WGM02) | (0b011 << CS00);
  TCCR0A  = (0b01<<WGM00);

  /***************************************************/
  /* Rotary encoder interrupt set-up                 */
  EIMSK = 0; // disable ALL external interrupts.
  // encoder 1
  EICRB = (1<<ISC60) | (1<<ISC50); // 01 = interrupt on any edge
  EIFR = (3<<INTF5); // clear the int. flag in case it got set when changing modes
  // encoder 2
  EICRA = (1<<ISC30) | (1<<ISC20); // do the same for encoder 1
  EIFR = (3<<INTF2);
  EIMSK = (3<<INT5) | (3<<INT2); // enable the two rot. enc. ext. int. pairs.
  /***************************************************/

#if defined (VOICE)
  /*
   * SOMO set-up (V4 board only)
   */
  OCR4A = 0x1F4; //2ms
  TCCR4B = (1 << WGM42) | (0b011 << CS40); // CTC OCR1A, 16MHz / 64 (4us ticks)
  TIMSK4 |= (1<<OCIE4A); // Start the interrupt so the unit reset can occur
#endif

}
#endif // !SIMU

uint8_t pwrCheck()
{
#if !defined(SIMU) && !defined(REV0)
  if ((PING & 0b00000010) && (~PINL & 0b01000000))
  return e_power_off;
#endif
  return e_power_on;
}

void pwrOff()
{
#ifndef REV0
  PORTL = 0x7f;
#endif
}

#if ROTARY_ENCODERS <= 2
#define ROTENC_DOWN() ((~PIND & 0x20) || (~PIND & 0x10))
#else
#define ROTENC_DOWN() (0)
#endif

FORCEINLINE uint8_t keyDown()
{
  return ((~PINL) & 0x3F) || ROTENC_DOWN();
}

bool switchState(EnumKeys enuk)
{
  uint8_t result = 0 ;

  if (enuk < (int)DIM(keys))
    return keys[enuk].state() ? 1 : 0;

  switch(enuk){
    //case SW_ELE:
    //  result = PINC & (1<<INP_C_ElevDR);
    //  break;

    //case SW_AIL:
    //  result = PINC & (1<<INP_C_AileDR);
    //  break;

    case SW_RUD:
      result = PING & (1<<INP_G_RuddDR);
      break;

    //     INP_G_ID1 INP_B_ID2
    // id0    0        1
    // id1    1        1
    // id2    1        0
    case SW_ID0:
      result = !(PINC & (1<<INP_C_ID1));
      break;

    case SW_ID1:
      result = (PINC & (1<<INP_C_ID1))&& (PINC & (1<<INP_C_ID2));
      break;

    case SW_ID2:
      result = !(PINC & (1<<INP_C_ID2));
      break;

#if 0
    case SW_ID3:
      result = (calibratedStick[POT1+EXTRA_3POS-1] < 0);
      break;

    case SW_ID4:
      result = (calibratedStick[POT1+EXTRA_3POS-1] == 0);
      break;

    case SW_ID5:
      result = (calibratedStick[POT1+EXTRA_3POS-1] > 0);
      break;
#endif

    case SW_GEA:
      result = PING & (1<<INP_G_Gear);
      break;

    case SW_THR:
      result = PING & (1<<INP_G_ThrCt);
      break;

    case SW_TRN:
      result = PINB & (1<<INP_B_Trainer);
      break;

    default:
      break;
  }

  return result;
}

FORCEINLINE void readKeysAndTrims()
{
  /* Original keys were connected to PORTB as follows:
  
     Bit  Key
      7   other use
      6   LEFT
      5   RIGHT
      4   UP
      3   DOWN
      2   EXIT
      1   MENU
      0   other use
  */

  uint8_t enuk = KEY_MENU;

  keys[BTN_REa].input(~PIND & 0x20, BTN_REa);
  keys[BTN_REb].input(~PIND & 0x10, BTN_REb);

  uint8_t tin = ~PINL;
  uint8_t in;
  in = (tin & 0x0f) << 3;
  in |= (tin & 0x30) >> 3;

  for (int i=1; i<7; i++)
  {
    //INP_B_KEY_MEN 1  .. INP_B_KEY_LFT 6
    keys[enuk].input(in & (1<<i),(EnumKeys)enuk);
    ++enuk;
  }

  // Trim switches ...
  static const pm_uchar crossTrim[] PROGMEM ={
    1<<INP_F_TRM_LH_DWN,
    1<<INP_F_TRM_LH_UP,
    1<<INP_F_TRM_LV_DWN,
    1<<INP_F_TRM_LV_UP,
    1<<INP_F_TRM_RV_DWN,
    1<<INP_F_TRM_RV_UP,
    1<<INP_F_TRM_RH_DWN,
    1<<INP_F_TRM_RH_UP
  };

  in = ~PINF;

  for (int i=0; i<8; i++) {
    // INP_D_TRM_RH_UP   0 .. INP_D_TRM_LH_UP   7
    keys[enuk].input(in & pgm_read_byte(crossTrim+i),(EnumKeys)enuk);
    ++enuk;
  }
}

ISR(INT2_vect)
{
  uint8_t input = (PIND & 0x0C);
  if (input == 0 || input == 0x0C) incRotaryEncoder(0, -1);
}

ISR(INT3_vect)
{
  uint8_t input = (PIND & 0x0C);
  if (input == 0 || input == 0x0C) incRotaryEncoder(0, +1);
}

ISR(INT5_vect)
{
  uint8_t input = (PINE & 0x60);
  if (input == 0 || input == 0x60) incRotaryEncoder(1, +1);
}

ISR(INT6_vect)
{
  uint8_t input = (PINE & 0x60);
  if (input == 0 || input == 0x60) incRotaryEncoder(1, -1);
}
