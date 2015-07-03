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

#include "opentx.h"
#include "FatFs/ff.h"

FIL g_oLogFile = {0};
const pm_char * g_logError = NULL;
uint8_t logDelay;

#if defined(PCBTARANIS)
  #define get2PosState(sw) (switchState(SW_ ## sw ## 0) ? -1 : 1)
#else
  #define get2PosState(sw) (switchState(SW_ ## sw) ? -1 : 1)
#endif

#define get3PosState(sw) (switchState(SW_ ## sw ## 0) ? -1 : (switchState(SW_ ## sw ## 2) ? 1 : 0))

const pm_char * openLogs()
{
  // Determine and set log file filename
  FRESULT result;
  DIR folder;
  char filename[34]; // /LOGS/modelnamexxx-2013-01-01.log

  if (!sdMounted())
    return STR_NO_SDCARD;

  strcpy_P(filename, STR_LOGS_PATH);

  result = f_opendir(&folder, filename);
  if (result != FR_OK) {
    if (result == FR_NO_PATH)
      result = f_mkdir(filename);
    if (result != FR_OK)
      return SDCARD_ERROR(result);
  }

  filename[sizeof(LOGS_PATH)-1] = '/';
  memcpy(&filename[sizeof(LOGS_PATH)], g_model.header.name, sizeof(g_model.header.name));
  filename[sizeof(LOGS_PATH)+sizeof(g_model.header.name)] = '\0';

  uint8_t i = sizeof(LOGS_PATH)+sizeof(g_model.header.name)-1;
  uint8_t len = 0;
  while (i>sizeof(LOGS_PATH)-1) {
    if (!len && filename[i])
      len = i+1;
    if (len) {
      if (filename[i])
        filename[i] = idx2char(filename[i]);
      else
        filename[i] = '_';
    }
    i--;
  }

  if (len == 0) {
    uint8_t num = g_eeGeneral.currModel + 1;
    strcpy_P(&filename[sizeof(LOGS_PATH)], STR_MODEL);
    filename[sizeof(LOGS_PATH) + PSIZE(TR_MODEL)] = (char)((num / 10) + '0');
    filename[sizeof(LOGS_PATH) + PSIZE(TR_MODEL) + 1] = (char)((num % 10) + '0');
    len = sizeof(LOGS_PATH) + PSIZE(TR_MODEL) + 2;
  }

#if defined(RTCLOCK)
  filename[len] = '-';
  struct gtm utm;
  gettime(&utm);
  div_t qr = div(utm.tm_year+1900, 10);
  filename[len+4] = '0' + qr.rem;
  qr = div(qr.quot, 10);
  filename[len+3] = '0' + qr.rem;
  qr = div(qr.quot, 10);
  filename[len+2] = '0' + qr.rem;
  filename[len+1] = '0' + qr.quot;
  filename[len+5] = '-';
  qr = div(utm.tm_mon+1, 10);
  filename[len+7] = '0' + qr.rem;
  filename[len+6] = '0' + qr.quot;
  filename[len+8] = '-';
  qr = div(utm.tm_mday, 10);
  filename[len+10] = '0' + qr.rem;
  filename[len+9] = '0' + qr.quot;
#endif

  strcpy_P(&filename[len+11], STR_LOGS_EXT);

  result = f_open(&g_oLogFile, filename, FA_OPEN_ALWAYS | FA_WRITE);
  if (result != FR_OK) {
    return SDCARD_ERROR(result);
  }

  if (f_size(&g_oLogFile) == 0) {
#if defined(RTCLOCK)
    f_puts("Date,Time,", &g_oLogFile);
#else
    f_puts("Time,", &g_oLogFile);
#endif

#if defined(FRSKY_SPORT)
    f_puts("SWR,RSSI,A1,A2,", &g_oLogFile);
#elif defined(FRSKY)
    f_puts("Buffer,RX,TX,A1,A2,", &g_oLogFile);
#endif

#if defined(FRSKY_HUB)
    if (IS_USR_PROTO_FRSKY_HUB())
      f_puts("GPS Date,GPS Time,Long,Lat,Course,GPS Speed,GPS Alt,Baro Alt,Vertical Speed,Temp1,Temp2,RPM,Fuel,Cell volts,Cell 1,Cell 2,Cell 3,Cell 4,Cell 5,Cell 6,Current,Consumption,Vfas,AccelX,AccelY,AccelZ,", &g_oLogFile);
#endif

#if defined(WS_HOW_HIGH)
    if (IS_USR_PROTO_WS_HOW_HIGH())
      f_puts("WSHH Alt,", &g_oLogFile);
#endif

#if defined(PCBTARANIS)
    f_puts("Rud,Ele,Thr,Ail,S1,S2,LS,RS,SA,SB,SC,SD,SE,SF,SG,SH\n", &g_oLogFile);
#else
    f_puts("Rud,Ele,Thr,Ail,P1,P2,P3,THR,RUD,ELE,3POS,AIL,GEA,TRN\n", &g_oLogFile);
#endif
  }
  else {
    result = f_lseek(&g_oLogFile, f_size(&g_oLogFile)); // append
    if (result != FR_OK) {
      return SDCARD_ERROR(result);
    }
  }

  return NULL;
}

tmr10ms_t lastLogTime = 0;

void closeLogs()
{
  f_close(&g_oLogFile);
  lastLogTime = 0;
}

// TODO test when disk full
void writeLogs()
{
  static const pm_char * error_displayed = NULL;

  if (isFunctionActive(FUNC_LOGS) && logDelay > 0) {
    tmr10ms_t tmr10ms = get_tmr10ms();
    if (lastLogTime == 0 || (tmr10ms_t)(tmr10ms - lastLogTime) >= (tmr10ms_t)logDelay*10) {
      lastLogTime = tmr10ms;

      if (!g_oLogFile.fs) {
        const pm_char * result = openLogs();
        if (result != NULL) {
          if (result != error_displayed) {
            error_displayed = result;
            s_global_warning = result;
          }
          return;
        }
      }

#if defined(RTCLOCK)
      struct gtm utm;
      gettime(&utm);
      f_printf(&g_oLogFile, "%4d-%02d-%02d,%02d:%02d:%02d.%02d0,", utm.tm_year+1900, utm.tm_mon+1, utm.tm_mday, utm.tm_hour, utm.tm_min, utm.tm_sec, g_ms100);
#else
      f_printf(&g_oLogFile, "%d,", tmr10ms);
#endif

#if defined(FRSKY_SPORT)
      f_printf(&g_oLogFile, "%d,%d,", frskyData.rssi[1].value, frskyData.rssi[0].value);
#elif defined(FRSKY)
      f_printf(&g_oLogFile, "%d,%d,%d,", frskyStreaming, frskyData.rssi[0].value, frskyData.rssi[1].value);
#endif

#if defined(FRSKY)
      for (uint8_t i=0; i<2; i++) {
        int16_t converted_value = applyChannelRatio(i, frskyData.analog[i].value);
        f_printf(&g_oLogFile, "%d.%02d,", converted_value/100, converted_value%100);
      }
#endif

#if defined(FRSKY_HUB)
      if (IS_USR_PROTO_FRSKY_HUB()) {
        f_printf(&g_oLogFile, "%4d-%02d-%02d,%02d:%02d:%02d,%03d.%04d%c,%03d.%04d%c,%03d.%02d,%d.%02d,%d.%02d," TELEMETRY_ALT_FORMAT TELEMETRY_VSPEED_FORMAT "%d,%d,%d,%d," TELEMETRY_CELLS_FORMAT TELEMETRY_CURRENT_FORMAT "%d," TELEMETRY_VFAS_FORMAT "%d,%d,%d,",
            frskyData.hub.year+2000,
            frskyData.hub.month,
            frskyData.hub.day,
            frskyData.hub.hour,
            frskyData.hub.min,
            frskyData.hub.sec,
            frskyData.hub.gpsLongitude_bp,
            frskyData.hub.gpsLongitude_ap,
            frskyData.hub.gpsLongitudeEW ? frskyData.hub.gpsLongitudeEW : '-',
            frskyData.hub.gpsLatitude_bp,
            frskyData.hub.gpsLatitude_ap,
            frskyData.hub.gpsLatitudeNS ? frskyData.hub.gpsLatitudeNS : '-',
            frskyData.hub.gpsCourse_bp,
            frskyData.hub.gpsCourse_ap,
            TELEMETRY_GPS_SPEED_BP,
            TELEMETRY_GPS_SPEED_AP,
            TELEMETRY_GPS_ALT_BP,
            TELEMETRY_GPS_ALT_AP,
            TELEMETRY_ALT,
            TELEMETRY_VSPEED,
            frskyData.hub.temperature1,
            frskyData.hub.temperature2,
            frskyData.hub.rpm,
            frskyData.hub.fuelLevel,
            TELEMETRY_CELLS,
            TELEMETRY_CURRENT,
            frskyData.hub.currentConsumption,
            TELEMETRY_VFAS,
            frskyData.hub.accelX,
            frskyData.hub.accelY,
            frskyData.hub.accelZ);
      }
#endif

#if defined(WS_HOW_HIGH)
      if (IS_USR_PROTO_WS_HOW_HIGH()) {
        f_printf(&g_oLogFile, "%d,", TELEMETRY_ALT_BP);
      }
#endif

      for (uint8_t i=0; i<NUM_STICKS+NUM_POTS; i++) {
        f_printf(&g_oLogFile, "%d,", calibratedStick[i]);
      }

#if defined(PCBTARANIS)
      int result = f_printf(&g_oLogFile, "%d,%d,%d,%d,%d,%d,%d,%d\n",
          get3PosState(SA),
          get3PosState(SB),
          get3PosState(SC),
          get3PosState(SD),
          get3PosState(SE),
          get2PosState(SF),
          get3PosState(SG),
          get2PosState(SH));
#else
      int result = f_printf(&g_oLogFile, "%d,%d,%d,%d,%d,%d,%d\n",
          get2PosState(THR),
          get2PosState(RUD),
          get2PosState(ELE),
          get3PosState(ID),
          get2PosState(AIL),
          get2PosState(GEA),
          get2PosState(TRN));
#endif

      if (result<0 && !error_displayed) {
        error_displayed = STR_SDCARD_ERROR;
        s_global_warning = STR_SDCARD_ERROR;
      }
    }
  }
  else {
    error_displayed = NULL;
    if (g_oLogFile.fs)
      closeLogs();
  }
}



