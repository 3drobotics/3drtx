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

#include "../opentx.h"

#if defined(PCBTARANIS)
uint16_t dsm2Stream[400];                         // Likely more than we need
uint16_t *dsm2StreamPtr;
uint16_t dsm2Value;
#else
uint8_t  dsm2Stream[64];                          // Likely more than we need
uint8_t *dsm2StreamPtr;
uint8_t  dsm2SerialByte ;
uint8_t  dsm2SerialBitCount;
#endif

// DSM2 control bits
#define DSM2_CHANS           6
#define FRANCE_BIT           0x10
#define DSMX_BIT             0x08
#define BAD_DATA             0x47

#define BITLEN_DSM2          (8*2) //125000 Baud => 8uS per bit

#if defined(PCBTARANIS)
uint8_t dsm2Index = 0;
void _send_1(uint8_t v)
{
  if (dsm2Index == 0)
    v -= 2;
  else
    v += 2;

  dsm2Value += v;
  *dsm2StreamPtr++ = dsm2Value;

  dsm2Index = (dsm2Index+1) % 2;
}

void sendByteDsm2(uint8_t b) //max 10 changes 0 10 10 10 10 1
{
    bool    lev = 0;
    uint8_t len = BITLEN_DSM2; //max val: 9*16 < 256
    for (uint8_t i=0; i<=8; i++) { //8Bits + Stop=1
        bool nlev = b & 1; //lsb first
        if (lev == nlev) {
          len += BITLEN_DSM2;
        }
        else {
          _send_1(len); // _send_1(nlev ? len-5 : len+3);
          len  = BITLEN_DSM2;
          lev  = nlev;
        }
        b = (b>>1) | 0x80; //shift in stop bit
    }
    _send_1(len+BITLEN_DSM2); // _send_1(len+BITLEN_DSM2+3); // 2 stop bits
}
void putDsm2Flush()
{
  dsm2StreamPtr--; //remove last stopbits and
  *dsm2StreamPtr++ = 44010;             // Past the 44000 of the ARR
}
#else
void putDsm2SerialBit(uint8_t bit)
{
  dsm2SerialByte >>= 1;
  if (bit & 1) {
    dsm2SerialByte |= 0x80;
  }
  if (++dsm2SerialBitCount >= 8) {
    *dsm2StreamPtr++ = dsm2SerialByte;
    dsm2SerialBitCount = 0;
  }
}
void sendByteDsm2(uint8_t b)     // max 10changes 0 10 10 10 10 1
{
  putDsm2SerialBit(0);           // Start bit
  for (uint8_t i=0; i<8; i++) {  // 8 data Bits
    putDsm2SerialBit(b & 1);
    b >>= 1;
  }

  putDsm2SerialBit(1);           // Stop bit
  putDsm2SerialBit(1);           // Stop bit
}
void putDsm2Flush()
{
  for (int i=0; i<16; i++) {
    putDsm2SerialBit(1);         // 16 extra stop bits
  }
}
#endif

// This is the data stream to send, prepare after 19.5 mS
// Send after 22.5 mS

//static uint8_t *Dsm2_pulsePtr = pulses2MHz.pbyte ;
void setupPulsesDSM2(unsigned int port)
{
  static uint8_t dsmDat[2+6*2]={0xFF,0x00, 0x00,0xAA, 0x05,0xFF, 0x09,0xFF, 0x0D,0xFF, 0x13,0x54, 0x14,0xAA};

#if defined(PCBSKY9X)
  dsm2SerialByte = 0 ;
  dsm2SerialBitCount = 0 ;
#else
  dsm2Value = 0;
  dsm2Index = 1;
#endif

  dsm2StreamPtr = dsm2Stream;

#if defined(PCBTARANIS)
  dsm2Value = 100;
  *dsm2StreamPtr++ = dsm2Value;
#endif

  switch(s_current_protocol[port]) {
    case PROTO_DSM2_LP45:
      dsmDat[0] = 0x00;
      break;
    case PROTO_DSM2_DSM2:
      dsmDat[0] = 0x10;
      break;
    default: // DSMX
      dsmDat[0] = 0x18;
      break;
  }

#if !defined(PCBTARANIS)
  if (s_bind_allowed) s_bind_allowed--;
  if (s_bind_allowed && switchState(SW_DSM2_BIND))
    dsm2Flag = DSM2_BIND_FLAG;
  else
    dsm2Flag &= ~DSM2_BIND_FLAG;
#endif

  dsmDat[0] |= dsm2Flag;
  dsmDat[1] = g_model.header.modelId; // DSM2 Header second byte for model match

  for (int i=0; i<DSM2_CHANS; i++) {
    uint16_t pulse = limit(0, ((channelOutputs[g_model.moduleData[port].channelsStart+i]*13)>>5)+512, 1023);
    dsmDat[2+2*i] = (i<<2) | ((pulse>>8)&0x03);
    dsmDat[3+2*i] = pulse & 0xff;
  }

  for (int i=0; i<14; i++) {
    sendByteDsm2(dsmDat[i]);
  }

  putDsm2Flush();
}
