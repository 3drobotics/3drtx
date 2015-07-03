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

uint8_t currentTrainerMode;
uint16_t * TrainerPulsePtr;
extern uint16_t ppmStream[NUM_MODULES+1][20];

#define setupTrainerPulses() setupPulsesPPM(TRAINER_MODULE)

// Trainer PPM oputput PC9, Timer 3 channel 4, (Alternate Function 2)
void init_trainer_ppm()
{
  setupTrainerPulses() ;
  TrainerPulsePtr = ppmStream[TRAINER_MODULE];

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN ;           // Enable portC clock
  configure_pins( PIN_TR_PPM_OUT, PIN_PERIPHERAL | PIN_PORTC | PIN_PER_2 | PIN_OS25 | PIN_PUSHPULL ) ;
  configure_pins( PIN_TR_PPM_IN, PIN_PORTA | PIN_INPUT ) ;
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;            // Enable clock

  TIM3->ARR = *TrainerPulsePtr++ ;
  TIM3->PSC = (PERI1_FREQUENCY * TIMER_MULT_APB1) / 2000000 - 1 ;               // 0.5uS
  TIM3->CCER = TIM_CCER_CC4E ;
  if(!g_model.moduleData[TRAINER_MODULE].ppmPulsePol)
    TIM3->CCER |= TIM_CCER_CC4P;
  TIM3->CCMR2 = TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE ;                   // PWM mode 1
  TIM3->CCR4 = (g_model.moduleData[TRAINER_MODULE].ppmDelay*50+300)*2;
  TIM3->BDTR = TIM_BDTR_MOE ;
  TIM3->EGR = 1 ;
  // TIM3->DIER = TIM_DIER_UDE ;

  TIM3->SR &= ~TIM_SR_UIF ;                               // Clear flag
  TIM3->SR &= ~TIM_SR_CC2IF ;                             // Clear flag
  TIM3->DIER |= TIM_DIER_CC2IE ;
  TIM3->DIER |= TIM_DIER_UIE ;

  TIM3->CR1 = TIM_CR1_CEN ;
  NVIC_EnableIRQ(TIM3_IRQn) ;
  NVIC_SetPriority(TIM3_IRQn, 7);
}

// TODO - testing
void stop_trainer_ppm()
{
  configure_pins( PIN_TR_PPM_OUT, PIN_INPUT | PIN_PORTC ) ; // Pin as input
  TIM3->CR1 &= ~TIM_CR1_CEN ;                             // Stop counter
  TIM3->DIER &= ~TIM_DIER_CC2IE ;                      // Stop Interrupt
  TIM3->DIER &= ~TIM_DIER_UIE ;                        // Stop Interrupt
  NVIC_DisableIRQ(TIM3_IRQn) ;                         // Stop Interrupt
}

// Trainer capture, PC8, Timer 3 channel 3
void init_trainer_capture()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN ; // Enable portC clock
  configure_pins (PIN_TR_PPM_IN, PIN_PERIPHERAL | PIN_PORTC | PIN_PER_2) ;
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ; // Enable clock

  TIM3->ARR = 0xFFFF ;
  TIM3->PSC = (PERI1_FREQUENCY * TIMER_MULT_APB1) / 2000000 - 1 ;               // 0.5uS
  TIM3->CR2 = 0 ;
  TIM3->CCMR2 = TIM_CCMR2_IC3F_0 | TIM_CCMR2_IC3F_1 | TIM_CCMR2_CC3S_0 ;
  TIM3->CCER = TIM_CCER_CC3E ;
  TIM3->SR &= ~TIM_SR_CC3IF & ~TIM_SR_CC2IF & ~TIM_SR_UIF ;  // Clear flags
  TIM3->DIER |= TIM_DIER_CC3IE ;
  TIM3->CR1 = TIM_CR1_CEN ;
  NVIC_EnableIRQ(TIM3_IRQn) ;
  NVIC_SetPriority(TIM3_IRQn, 7);
}

void stop_trainer_capture()
{
  TIM3->CR1 &= ~TIM_CR1_CEN ;                          // Stop counter
  TIM3->DIER &= ~TIM_DIER_CC3IE ;                      // Stop Interrupt
  NVIC_DisableIRQ(TIM3_IRQn) ;                         // Stop Interrupt
}

extern "C" void TIM3_IRQHandler()
{
  uint16_t capture ;
  static uint16_t lastCapt ;
  uint16_t val ;

  // What mode? in or out?
  if ( (TIM3->DIER & TIM_DIER_CC3IE ) && ( TIM3->SR & TIM_SR_CC3IF ) ) {
    // capture mode
    capture = TIM3->CCR3 ;

    val = (uint16_t)(capture - lastCapt) / 2 ;
    lastCapt = capture;

    // We prcoess g_ppmInsright here to make servo movement as smooth as possible
    //    while under trainee control
    if ((val>4000) && (val < 19000)) { // G: Prioritize reset pulse. (Needed when less than 8 incoming pulses)
      ppmInState = 1; // triggered
    }
    else {
      if (ppmInState && (ppmInState<=8)) {
        if ((val>800) && (val<2200)) {
          g_ppmIns[ppmInState++ - 1] = (int16_t)(val - 1500)*(g_eeGeneral.PPM_Multiplier+10)/10; //+-500 != 512, but close enough.
        }
        else {
          ppmInState = 0; // not triggered
        }
      }
    }
  }

  // PPM out compare interrupt
  if ( ( TIM3->DIER & TIM_DIER_CC2IE ) && ( TIM3->SR & TIM_SR_CC2IF ) ) {
    // compare interrupt
    TIM3->SR &= ~TIM_SR_CC2IF ;                             // Clear flag
    TIM3->DIER &= ~TIM_DIER_CC2IE ;         // stop this interrupt
    TIM3->SR &= ~TIM_SR_CC2IF ;                             // Clear flag

    setupTrainerPulses() ;

    TrainerPulsePtr = ppmStream[TRAINER_MODULE];
    TIM3->DIER |= TIM_DIER_UDE ;
    TIM3->SR &= ~TIM_SR_UIF ;                                       // Clear this flag
    TIM3->DIER |= TIM_DIER_UIE ;                            // Enable this interrupt
  }

  // PPM out update interrupt
  if ( (TIM3->DIER & TIM_DIER_UIE) && ( TIM3->SR & TIM_SR_UIF ) ) {
    TIM3->SR &= ~TIM_SR_UIF ;                               // Clear flag
    TIM3->ARR = *TrainerPulsePtr++ ;
    if ( *TrainerPulsePtr == 0 ) {
      TIM3->SR &= ~TIM_SR_CC2IF ;                     // Clear this flag
      TIM3->DIER |= TIM_DIER_CC2IE ;  // Enable this interrupt
    }
  }
}

