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

#ifndef pulses_arm_h
#define pulses_arm_h

#if NUM_MODULES == 2
  #define MODULES_INIT(...) __VA_ARGS__, __VA_ARGS__
#else
  #define MODULES_INIT(...) __VA_ARGS__
#endif

extern uint8_t s_current_protocol[NUM_MODULES];
extern uint8_t s_pulses_paused;
extern uint32_t failsafeCounter[NUM_MODULES];

void setupPulses(unsigned int port);
void setupPulsesDSM2(unsigned int port);
void setupPulsesPXX(unsigned int port);
void setupPulsesPPM(unsigned int port);

#if defined(HUBSAN)
void Hubsan_Init();
#endif

inline void startPulses()
{
  s_pulses_paused = false;

#if defined(PCBTARANIS)
  setupPulses(INTERNAL_MODULE);
  setupPulses(EXTERNAL_MODULE);
#else
  setupPulses(0);
#endif

#if defined(HUBSAN)
  Hubsan_Init();
#endif
}

inline bool pulsesStarted() { return s_current_protocol[0] != 255; }
inline void pausePulses() { s_pulses_paused = true; }
inline void resumePulses() { s_pulses_paused = false; }

#define SEND_FAILSAFE_NOW(idx) failsafeCounter[idx] = 1

inline void SEND_FAILSAFE_1S()
{
  for (int i=0; i<NUM_MODULES; i++)
    failsafeCounter[i] = 100;
}

#endif
