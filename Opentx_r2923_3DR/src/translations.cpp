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

#define ISTR(x) LEN_##x TR_##x


 // The non-0-terminated-strings
const pm_char STR_OPEN9X[] PROGMEM =
    ISTR(OFFON)
    ISTR(MMMINV)
    ISTR(NCHANNELS)
#if !defined(GRAPHICS)
    ISTR(VBEEPLEN)
#endif
    ISTR(VBEEPMODE)
#if defined(ROTARY_ENCODERS)
    ISTR(VRENAVIG)
#endif
#if defined(ROTARY_ENCODER_NAVIGATION)
    ISTR(VRENCODERS)
#endif
    ISTR(TRNMODE)
    ISTR(TRNCHN)
    ISTR(VTRIMINC)
    ISTR(RETA123)
    ISTR(VPROTOS)
    ISTR(POSNEG)
    ISTR(VBLMODE)
    ISTR(VCURVEFUNC)
    ISTR(VMLTPX)
    ISTR(VMLTPX2)
    ISTR(VMIXTRIMS)
    ISTR(VCSWFUNC)
    ISTR(VFSWFUNC)
    ISTR(VFSWRESET)
    ISTR(FUNCSOUNDS)
    ISTR(VTELEMCHNS)
#if defined(FRSKY) || defined(CPUARM)
  #if defined(CPUARM)
    ISTR(VTELEMUNIT_IMP)
    ISTR(VTELEMUNIT_NORM)
  #else
    ISTR(VTELEMUNIT)
  #endif
    ISTR(VALARM)
    ISTR(VALARMFN)
    ISTR(VTELPROTO)
    ISTR(GPSFORMAT)
    ISTR(VOLTSRC)
    ISTR(VARIOSRC)
    ISTR(VSCREEN)
#endif
#if defined(TEMPLATES)
    ISTR(VTEMPLATES)
#endif
#if defined(HELI)
    ISTR(VSWASHTYPE)
#endif
    ISTR(VKEYS)
    ISTR(VSWITCHES)
    ISTR(VSRCRAW)
    ISTR(VTMRMODES)
#if defined(CPUM2560) || defined(CPUARM)
    ISTR(DATETIME)
#endif
#if defined(CPUARM)
    ISTR(VLCD)
    ISTR(VUNITSSYSTEM)
#endif
#if defined(PXX)
    ISTR(COUNTRYCODES)
    ISTR(VFAILSAFE)
#endif
#if defined(PCBTARANIS)
    ISTR(VTRAINERMODES)
#endif
#if defined(MAVLINK)
	ISTR(MAVLINK_BAUDS)
	ISTR(MAVLINK_AC_MODES)
	ISTR(MAVLINK_AP_MODES)
#endif
    ;

// The 0-terminated-strings
const pm_char STR_POPUPS[] PROGMEM = TR_POPUPS;
const pm_char STR_MENUWHENDONE[] PROGMEM = TR_MENUWHENDONE;
const pm_char STR_FREE[] PROGMEM = TR_FREE;
const pm_char STR_DELETEMODEL[] PROGMEM = TR_DELETEMODEL;
const pm_char STR_COPYINGMODEL[] PROGMEM = TR_COPYINGMODEL;
const pm_char STR_MOVINGMODEL[] PROGMEM = TR_MOVINGMODEL;
const pm_char STR_LOADINGMODEL[] PROGMEM = TR_LOADINGMODEL;
const pm_char STR_NAME[] PROGMEM = TR_NAME;
const pm_char STR_BITMAP[] PROGMEM = TR_BITMAP;
const pm_char STR_TIMER[] PROGMEM = TR_TIMER;
const pm_char STR_ELIMITS[] PROGMEM = TR_ELIMITS;
const pm_char STR_ETRIMS[] PROGMEM = TR_ETRIMS;
const pm_char STR_TRIMINC[] PROGMEM = TR_TRIMINC;
const pm_char STR_TTRACE[] PROGMEM = TR_TTRACE;
const pm_char STR_TTRIM[] PROGMEM = TR_TTRIM;
const pm_char STR_BEEPCTR[] PROGMEM = TR_BEEPCTR;
const pm_char STR_PROTO[] PROGMEM = TR_PROTO;
const pm_char STR_PPMFRAME[] PROGMEM = TR_PPMFRAME;
const pm_char STR_MS[] PROGMEM = TR_MS;
const pm_char STR_SWITCH[] PROGMEM = TR_SWITCH;
const pm_char STR_TRIMS[] PROGMEM = TR_TRIMS;
const pm_char STR_FADEIN[] PROGMEM = TR_FADEIN;
const pm_char STR_FADEOUT[] PROGMEM = TR_FADEOUT;
const pm_char STR_DEFAULT[] PROGMEM = TR_DEFAULT;
const pm_char STR_CHECKTRIMS[] PROGMEM = TR_CHECKTRIMS;
#ifdef HELI
const pm_char STR_SWASHTYPE[] PROGMEM = TR_SWASHTYPE;
const pm_char STR_COLLECTIVE[] PROGMEM = TR_COLLECTIVE;
const pm_char STR_SWASHRING[] PROGMEM = TR_SWASHRING;
const pm_char STR_ELEDIRECTION[] PROGMEM = TR_ELEDIRECTION;
const pm_char STR_AILDIRECTION[] PROGMEM = TR_AILDIRECTION;
const pm_char STR_COLDIRECTION[] PROGMEM = TR_COLDIRECTION;
#endif
const pm_char STR_MODE[] PROGMEM = TR_MODE;
#if defined(AUDIO) && defined(BUZZER)
const pm_char STR_SPEAKER[] PROGMEM = TR_SPEAKER;
const pm_char STR_BUZZER[] PROGMEM = TR_BUZZER;
#endif
const pm_char STR_NOFREEEXPO[] PROGMEM = TR_NOFREEEXPO;
const pm_char STR_NOFREEMIXER[] PROGMEM = TR_NOFREEMIXER;
const pm_char STR_INSERTMIX[] PROGMEM = TR_INSERTMIX;
const pm_char STR_EDITMIX[] PROGMEM = TR_EDITMIX;
const pm_char STR_SOURCE[] PROGMEM = TR_SOURCE;
const pm_char STR_WEIGHT[] PROGMEM = TR_WEIGHT;
const pm_char STR_EXPO[] PROGMEM = TR_EXPO;
const pm_char STR_SIDE[] PROGMEM = TR_SIDE;
const pm_char STR_DIFFERENTIAL[] PROGMEM = TR_DIFFERENTIAL;
const pm_char STR_OFFSET[] PROGMEM = TR_OFFSET;
const pm_char STR_TRIM[] PROGMEM = TR_TRIM;
const pm_char STR_DREX[] PROGMEM = TR_DREX;
const pm_char STR_CURVE[] PROGMEM = TR_CURVE;
const pm_char STR_FLMODE[] PROGMEM = TR_FLMODE;
const pm_char STR_MIXWARNING[] PROGMEM = TR_MIXWARNING;
const pm_char STR_OFF[] PROGMEM = TR_OFF;
const pm_char STR_MULTPX[] PROGMEM = TR_MULTPX;
const pm_char STR_DELAYDOWN[] PROGMEM = TR_DELAYDOWN;
const pm_char STR_DELAYUP[] PROGMEM = TR_DELAYUP;
const pm_char STR_SLOWDOWN[] PROGMEM = TR_SLOWDOWN;
const pm_char STR_SLOWUP[] PROGMEM = TR_SLOWUP;
const pm_char STR_MIXER[] PROGMEM = TR_MIXER;
const pm_char STR_CV[] PROGMEM = TR_CV;
const pm_char STR_GV[] PROGMEM = TR_GV;
const pm_char STR_ACHANNEL[] PROGMEM = TR_ACHANNEL;
const pm_char STR_RANGE[] PROGMEM = TR_RANGE;
const pm_char STR_BAR[] PROGMEM = TR_BAR;
const pm_char STR_ALARM[] PROGMEM = TR_ALARM;
const pm_char STR_USRDATA[] PROGMEM = TR_USRDATA;
const pm_char STR_BLADES[] PROGMEM = TR_BLADES;
const pm_char STR_SCREEN[] PROGMEM = TR_SCREEN;
const pm_char STR_SOUND_LABEL[] PROGMEM = TR_SOUND_LABEL;
const pm_char STR_LENGTH[] PROGMEM = TR_LENGTH;
#if defined(AUDIO)
const pm_char STR_SPKRPITCH[] PROGMEM = TR_SPKRPITCH;
#endif
#if defined(HAPTIC)
const pm_char STR_HAPTIC_LABEL[] PROGMEM = TR_HAPTIC_LABEL;
const pm_char STR_HAPTICSTRENGTH[] PROGMEM = TR_HAPTICSTRENGTH;
#endif
const pm_char STR_CONTRAST[] PROGMEM = TR_CONTRAST;
const pm_char STR_ALARMS_LABEL[] PROGMEM = TR_ALARMS_LABEL;
#if defined(BATTGRAPH) || defined(PCBTARANIS)
const pm_char STR_BATTERY_RANGE[] PROGMEM = TR_BATTERY_RANGE;
#endif
const pm_char STR_BATTERYWARNING[] PROGMEM = TR_BATTERYWARNING;
const pm_char STR_INACTIVITYALARM[] PROGMEM = TR_INACTIVITYALARM;
const pm_char STR_MEMORYWARNING[] PROGMEM = TR_MEMORYWARNING;
const pm_char STR_ALARMWARNING[] PROGMEM = TR_ALARMWARNING;
#if defined(ROTARY_ENCODERS)
const pm_char STR_RENAVIG[] PROGMEM = TR_RENAVIG;
#endif
const pm_char STR_THROTTLEREVERSE[] PROGMEM = TR_THROTTLEREVERSE;
const pm_char STR_MINUTEBEEP[] PROGMEM = TR_MINUTEBEEP;
const pm_char STR_BEEPCOUNTDOWN[] PROGMEM = TR_BEEPCOUNTDOWN;
const pm_char STR_PERSISTENT[] PROGMEM = TR_PERSISTENT;
const pm_char STR_BACKLIGHT_LABEL[] PROGMEM = TR_BACKLIGHT_LABEL;
const pm_char STR_BLDELAY[] PROGMEM = TR_BLDELAY;

#if defined(PWM_BACKLIGHT)
const pm_char STR_BLONBRIGHTNESS[] PROGMEM = TR_BLONBRIGHTNESS;
const pm_char STR_BLOFFBRIGHTNESS[] PROGMEM = TR_BLOFFBRIGHTNESS;
#endif

const pm_char STR_SPLASHSCREEN[] PROGMEM = TR_SPLASHSCREEN;
const pm_char STR_THROTTLEWARNING[] PROGMEM = TR_THROTTLEWARNING;
const pm_char STR_SWITCHWARNING[] PROGMEM = TR_SWITCHWARNING;
#ifdef FRSKY
const pm_char STR_TIMEZONE[] PROGMEM = TR_TIMEZONE;
const pm_char STR_GPSCOORD[] PROGMEM = TR_GPSCOORD;
const pm_char STR_VARIO[] PROGMEM = TR_VARIO;
#endif
const pm_char STR_RXCHANNELORD[] PROGMEM = TR_RXCHANNELORD;
const pm_char STR_SLAVE[] PROGMEM = TR_SLAVE;
const pm_char STR_MODESRC[] PROGMEM = TR_MODESRC;
const pm_char STR_MULTIPLIER[] PROGMEM = TR_MULTIPLIER;
const pm_char STR_CAL[] PROGMEM = TR_CAL;
const pm_char STR_VTRIM[] PROGMEM = TR_VTRIM;
const pm_char STR_BG[] PROGMEM = TR_BG;
const pm_char STR_MENUTOSTART[] PROGMEM = TR_MENUTOSTART;
const pm_char STR_SETMIDPOINT[] PROGMEM = TR_SETMIDPOINT;
const pm_char STR_MOVESTICKSPOTS[] PROGMEM = TR_MOVESTICKSPOTS;
const pm_char STR_RXBATT[] PROGMEM = TR_RXBATT;
const pm_char STR_TX[] PROGMEM = TR_TXnRX;
const pm_char STR_ACCEL[] PROGMEM = TR_ACCEL;
const pm_char STR_NODATA[] PROGMEM = TR_NODATA;
const pm_char STR_TM1TM2[] PROGMEM = TR_TM1TM2;
const pm_char STR_THRTHP[] PROGMEM = TR_THRTHP;
const pm_char STR_TOT[] PROGMEM = TR_TOT;
const pm_char STR_TMR1LATMAXUS[] PROGMEM = TR_TMR1LATMAXUS;
const pm_char STR_TMR1LATMINUS[] PROGMEM = TR_TMR1LATMINUS;
const pm_char STR_TMR1JITTERUS[] PROGMEM = TR_TMR1JITTERUS;
const pm_char STR_TMIXMAXMS[] PROGMEM = TR_TMIXMAXMS;
#ifdef DEBUG
const pm_char STR_T10MSUS[] PROGMEM = TR_T10MSUS;
#endif
const pm_char STR_FREESTACKMINB[] PROGMEM = TR_FREESTACKMINB;
const pm_char STR_MENUTORESET[] PROGMEM = TR_MENUTORESET;
const pm_char STR_PPM[] PROGMEM = TR_PPM;
const pm_char STR_CH[] PROGMEM = TR_CH;
const pm_char STR_MODEL[] PROGMEM = TR_MODEL;
const pm_char STR_FP[] PROGMEM = TR_FP;
const pm_char STR_MIX[] PROGMEM = TR_MIX;
const pm_char STR_EEPROMLOWMEM[] PROGMEM = TR_EEPROMLOWMEM;
const pm_char STR_ALERT[] PROGMEM = TR_ALERT;
const pm_char STR_PRESSANYKEYTOSKIP[] PROGMEM = TR_PRESSANYKEYTOSKIP;
const pm_char STR_THROTTLENOTIDLE[] PROGMEM = TR_THROTTLENOTIDLE;
const pm_char STR_ALARMSDISABLED[] PROGMEM = TR_ALARMSDISABLED;
const pm_char STR_PRESSANYKEY[] PROGMEM = TR_PRESSANYKEY;
const pm_char STR_BADEEPROMDATA[] PROGMEM = TR_BADEEPROMDATA;
const pm_char STR_EEPROMFORMATTING[] PROGMEM = TR_EEPROMFORMATTING;
const pm_char STR_EEPROMOVERFLOW[] PROGMEM = TR_EEPROMOVERFLOW;
const pm_char STR_TRIMS2OFFSETS[] PROGMEM = TR_TRIMS2OFFSETS;
const pm_char STR_MENURADIOSETUP[] PROGMEM = TR_MENURADIOSETUP;

#if defined(CPUM2560) || defined(CPUARM)
const pm_char STR_MENUDATEANDTIME[] PROGMEM = TR_MENUDATEANDTIME;
#endif

const pm_char STR_MENUTRAINER[] PROGMEM = TR_MENUTRAINER;
const pm_char STR_MENUVERSION[] PROGMEM = TR_MENUVERSION;
const pm_char STR_MENUDIAG[] PROGMEM = TR_MENUDIAG;
const pm_char STR_MENUANA[] PROGMEM = TR_MENUANA;
const pm_char STR_MENUCALIBRATION[] PROGMEM = TR_MENUCALIBRATION;

const pm_char STR_MENUMODELSEL[] PROGMEM = TR_MENUMODELSEL;
const pm_char STR_MENUSETUP[] PROGMEM = TR_MENUSETUP;
const pm_char STR_MENUFLIGHTPHASE[] PROGMEM = TR_MENUFLIGHTPHASE;
const pm_char STR_MENUFLIGHTPHASES[] PROGMEM = TR_MENUFLIGHTPHASES;

#ifdef HELI
const pm_char STR_MENUHELISETUP[] PROGMEM = TR_MENUHELISETUP;
#endif

const pm_char STR_MENUDREXPO[] PROGMEM = TR_MENUDREXPO;
const pm_char STR_MENULIMITS[] PROGMEM = TR_MENULIMITS;
const pm_char STR_MENUCURVES[] PROGMEM = TR_MENUCURVES;
const pm_char STR_MENUCURVE[] PROGMEM = TR_MENUCURVE;
const pm_char STR_MENUCUSTOMSWITCH[] PROGMEM = TR_MENUCUSTOMSWITCH;
const pm_char STR_MENUCUSTOMSWITCHES[] PROGMEM = TR_MENUCUSTOMSWITCHES;
const pm_char STR_MENUCUSTOMFUNC[] PROGMEM = TR_MENUCUSTOMFUNC;

#if defined(FRSKY)
const pm_char STR_MENUTELEMETRY[] PROGMEM = TR_MENUTELEMETRY;
const pm_char STR_LIMIT[] PROGMEM = TR_LIMIT;
#endif

#if defined(TEMPLATES)
const pm_char STR_MENUTEMPLATES[] PROGMEM = TR_MENUTEMPLATES;
#endif

const pm_char STR_MENUSTAT[] PROGMEM = TR_MENUSTAT;
const pm_char STR_MENUDEBUG[] PROGMEM = TR_MENUDEBUG;
const pm_char STR_MENUGLOBALVARS[] PROGMEM = TR_MENUGLOBALVARS;

#if defined(DSM2) || defined(PXX)
const pm_char STR_RXNUM[] PROGMEM = TR_RXNUM;
#endif

#if defined(PXX)
const pm_char STR_SYNCMENU[] PROGMEM = TR_SYNCMENU;
const pm_char STR_INTERNALRF[] PROGMEM = TR_INTERNALRF;
const pm_char STR_EXTERNALRF[] PROGMEM = TR_EXTERNALRF;
const pm_char STR_COUNTRYCODE[] PROGMEM = TR_COUNTRYCODE;
const pm_char STR_FAILSAFE[] PROGMEM = TR_FAILSAFE;
const pm_char STR_FAILSAFESET[] PROGMEM = TR_FAILSAFESET;
#endif

const pm_char STR_INVERT_THR[] PROGMEM = TR_INVERT_THR;
const pm_char STR_AND_SWITCH[] PROGMEM = TR_AND_SWITCH;
extern const pm_char STR_CF[] PROGMEM = TR_CF;

#if defined(FRSKY_HUB)
const pm_char STR_MINRSSI[] PROGMEM = TR_MINRSSI;
const pm_char STR_LATITUDE[] PROGMEM = TR_LATITUDE;
const pm_char STR_LONGITUDE[] PROGMEM = TR_LONGITUDE;
#endif

#if defined(CPUARM) || defined(CPUM2560)
const pm_char STR_SHUTDOWN[] PROGMEM = TR_SHUTDOWN;
#endif

const pm_char STR_BATT_CALIB[] PROGMEM = TR_BATT_CALIB;

#if defined(CPUARM) || defined(FRSKY)
const pm_char STR_VOLTAGE[] PROGMEM = TR_VOLTAGE;
const pm_char STR_CURRENT[] PROGMEM = TR_CURRENT;
#endif

#if defined(CPUARM)
const pm_char STR_CURRENT_CALIB[] PROGMEM = TR_CURRENT_CALIB;
const pm_char STR_UNITSSYSTEM[]   PROGMEM = TR_UNITSSYSTEM;
const pm_char STR_VOICELANG[] PROGMEM = TR_VOICELANG;
const pm_char STR_MODELIDUSED[] PROGMEM = TR_MODELIDUSED;
const pm_char STR_BEEP_VOLUME[] PROGMEM = INDENT TR_BEEP_VOLUME;
const pm_char STR_WAV_VOLUME[] PROGMEM = INDENT TR_WAV_VOLUME;
const pm_char STR_VARIO_VOLUME[] PROGMEM = INDENT TR_VARIO_VOLUME;
const pm_char STR_BG_VOLUME[] PROGMEM = INDENT TR_BG_VOLUME;
#endif

#if defined(NAVIGATION_MENUS)
const pm_char STR_SELECT_MODEL[] PROGMEM = TR_SELECT_MODEL;
const pm_char STR_CREATE_MODEL[] PROGMEM = TR_CREATE_MODEL;
const pm_char STR_COPY_MODEL[] PROGMEM = TR_COPY_MODEL;
const pm_char STR_MOVE_MODEL[] PROGMEM = TR_MOVE_MODEL;
const pm_char STR_DELETE_MODEL[] PROGMEM = TR_DELETE_MODEL;
const pm_char STR_EDIT[] PROGMEM = TR_EDIT;
const pm_char STR_INSERT_BEFORE[] PROGMEM = TR_INSERT_BEFORE;
const pm_char STR_INSERT_AFTER[] PROGMEM = TR_INSERT_AFTER;
const pm_char STR_COPY[] PROGMEM = TR_COPY;
const pm_char STR_MOVE[] PROGMEM = TR_MOVE;
const pm_char STR_PASTE[] PROGMEM = TR_PASTE;
const pm_char STR_DELETE[] PROGMEM = TR_DELETE;
const pm_char STR_RESET_FLIGHT[] PROGMEM = TR_RESET_FLIGHT;
const pm_char STR_RESET_TIMER1[] PROGMEM = TR_RESET_TIMER1;
const pm_char STR_RESET_TIMER2[] PROGMEM = TR_RESET_TIMER2;
const pm_char STR_RESET_TELEMETRY[] PROGMEM = TR_RESET_TELEMETRY;
const pm_char STR_STATISTICS[] PROGMEM = TR_STATISTICS;
const pm_char STR_ABOUT_US[] PROGMEM = TR_ABOUT_US;
#endif

const pm_char STR_RESET[] PROGMEM = TR_RESET;

#if defined(SDCARD)
const pm_char STR_BACKUP_MODEL[] PROGMEM = TR_BACKUP_MODEL;
const pm_char STR_RESTORE_MODEL[] PROGMEM = TR_RESTORE_MODEL;
const pm_char STR_SDCARD_ERROR[] PROGMEM = TR_SDCARD_ERROR;
const pm_char STR_NO_SDCARD[] PROGMEM = TR_NO_SDCARD;
const pm_char STR_INCOMPATIBLE[] PROGMEM = TR_INCOMPATIBLE;
const pm_char STR_LOGS_PATH[] PROGMEM = LOGS_PATH;
const pm_char STR_LOGS_EXT[] PROGMEM = LOGS_EXT;
const pm_char STR_MODELS_PATH[] PROGMEM = MODELS_PATH;
const pm_char STR_MODELS_EXT[] PROGMEM = MODELS_EXT;
#endif

const pm_char STR_WARNING[] PROGMEM = TR_WARNING;
const pm_char STR_EEPROMWARN[] PROGMEM = TR_EEPROMWARN;
const pm_char STR_THROTTLEWARN[] PROGMEM = TR_THROTTLEWARN;
const pm_char STR_ALARMSWARN[] PROGMEM = TR_ALARMSWARN;
const pm_char STR_SWITCHWARN[] PROGMEM = TR_SWITCHWARN;

const pm_char STR_SPEAKER_VOLUME[] PROGMEM = TR_SPEAKER_VOLUME;
const pm_char STR_LCD[] PROGMEM = TR_LCD;
const pm_char STR_BRIGHTNESS[] PROGMEM = TR_BRIGHTNESS;
const pm_char STR_CPU_TEMP[] PROGMEM = TR_CPU_TEMP;
const pm_char STR_CPU_CURRENT[] PROGMEM = TR_CPU_CURRENT;
const pm_char STR_CPU_MAH[] PROGMEM = TR_CPU_MAH;
const pm_char STR_COPROC[] PROGMEM = TR_COPROC;
const pm_char STR_COPROC_TEMP[] PROGMEM = TR_COPROC_TEMP;
const pm_char STR_TEMPWARNING[] PROGMEM = TR_TEMPWARNING;
const pm_char STR_CAPAWARNING[] PROGMEM = TR_CAPAWARNING;
const pm_char STR_FUNC[] PROGMEM = TR_FUNC;
const pm_char STR_V1[] PROGMEM = TR_V1;
const pm_char STR_V2[] PROGMEM = TR_V2;
const pm_char STR_DURATION[] PROGMEM = TR_DURATION;
const pm_char STR_DELAY[] PROGMEM = TR_DELAY;
const pm_char STR_SD_CARD[] PROGMEM = TR_SD_CARD;
const pm_char STR_SDHC_CARD[] PROGMEM = TR_SDHC_CARD;
const pm_char STR_NO_SOUNDS_ON_SD[] PROGMEM = TR_NO_SOUNDS_ON_SD;
const pm_char STR_NO_MODELS_ON_SD[] PROGMEM = TR_NO_MODELS_ON_SD;
const pm_char STR_NO_BITMAPS_ON_SD[] PROGMEM = TR_NO_BITMAPS_ON_SD;
const pm_char STR_PLAY_FILE[] PROGMEM = TR_PLAY_FILE;
const pm_char STR_ASSIGN_BITMAP[] PROGMEM = TR_ASSIGN_BITMAP;
const pm_char STR_DELETE_FILE[] PROGMEM = TR_DELETE_FILE;
const pm_char STR_COPY_FILE[] PROGMEM = TR_COPY_FILE;
const pm_char STR_RENAME_FILE[] PROGMEM = TR_RENAME_FILE;
const pm_char STR_SD_INFO[] PROGMEM = TR_SD_INFO;
const pm_char STR_SD_FORMAT[] PROGMEM = TR_SD_FORMAT;
const pm_char STR_REMOVED[] PROGMEM = TR_REMOVED;
const pm_char STR_NA[] PROGMEM = TR_NA;
const pm_char STR_HARDWARE[] PROGMEM = TR_HARDWARE;
const pm_char STR_FORMATTING[] PROGMEM = TR_FORMATTING;
const pm_char STR_TEMP_CALIB[] PROGMEM = TR_TEMP_CALIB;
const pm_char STR_TIME[] PROGMEM = TR_TIME;
const pm_char STR_BAUDRATE[] PROGMEM = TR_BAUDRATE;
const pm_char STR_SD_INFO_TITLE[] PROGMEM = TR_SD_INFO_TITLE;
const pm_char STR_SD_TYPE[] PROGMEM = TR_SD_TYPE;
const pm_char STR_SD_SPEED[] PROGMEM = TR_SD_SPEED;
const pm_char STR_SD_SECTORS[] PROGMEM = TR_SD_SECTORS;
const pm_char STR_SD_SIZE[] PROGMEM = TR_SD_SIZE;
const pm_char STR_TYPE[] PROGMEM = TR_TYPE;
const pm_char STR_GLOBAL_VARS[] PROGMEM = TR_GLOBAL_VARS;
const pm_char STR_GLOBAL_VAR[] PROGMEM = TR_GLOBAL_VAR;
const pm_char STR_OWN[] PROGMEM = TR_OWN;
const pm_char STR_ROTARY_ENCODER[] PROGMEM = TR_ROTARY_ENCODER;
const pm_char STR_DATE[] PROGMEM = TR_DATE;
const pm_char STR_CHANNELS_MONITOR[] PROGMEM = TR_CHANNELS_MONITOR;
const pm_char STR_PATH_TOO_LONG[] PROGMEM = "Path too long";

#if LCD_W >= 212
  const pm_char STR_MODELNAME[] PROGMEM = TR_MODELNAME;
  const pm_char STR_PHASENAME[] PROGMEM = TR_PHASENAME;
  const pm_char STR_MIXNAME[] PROGMEM = TR_MIXNAME;
  const pm_char STR_EXPONAME[] PROGMEM = TR_EXPONAME;
#endif

#if LCD_W >= 212
  const char * STR_PHASES_HEADERS[] = TR_PHASES_HEADERS;
  const char * STR_LIMITS_HEADERS[] = TR_LIMITS_HEADERS;
  const char * STR_CSW_HEADERS[] =    TR_CSW_HEADERS;
#endif

#if defined(PCBTARANIS)
  const pm_char STR_BYTES[] PROGMEM = TR_BYTES;
  const pm_char STR_MODULE_BIND[] PROGMEM  = TR_MODULE_BIND;
  const pm_char STR_SET[] PROGMEM = TR_SET;
  const pm_char STR_TRAINER[] PROGMEM = TR_TRAINER;
  const pm_char STR_ANTENNAPROBLEM[] PROGMEM = TR_ANTENNAPROBLEM;
  const pm_char STR_MODULE[] PROGMEM = TR_MODULE;
  const pm_char STR_CHANNELRANGE[] PROGMEM = TR_CHANNELRANGE;
  const pm_char STR_LOWALARM[] PROGMEM = TR_LOWALARM;
  const pm_char STR_CRITICALALARM[] PROGMEM = TR_CRITICALALARM;
#endif

#if defined(PCBTARANIS) || defined(DSM2)
  const pm_char STR_MODULE_RANGE[] PROGMEM = TR_MODULE_RANGE;
#endif

#if defined(MAVLINK)
  const pm_char STR_MAVLINK_RC_RSSI_SCALE_LABEL[] PROGMEM = TR_MAVLINK_RC_RSSI_SCALE_LABEL;
  const pm_char STR_MAVLINK_PC_RSSI_EN_LABEL[] PROGMEM = TR_MAVLINK_PC_RSSI_EN_LABEL;
  const pm_char STR_MAVMENUSETUP_TITLE[] PROGMEM = TR_MAVMENUSETUP_TITLE;
  const pm_char STR_MAVLINK_BAUD_LABEL[] PROGMEM = TR_MAVLINK_BAUD_LABEL;
  const pm_char STR_MAVLINK_INFOS[] PROGMEM = TR_MAVLINK_INFOS;
  const pm_char STR_MAVLINK_MODE[] PROGMEM = TR_MAVLINK_MODE;
  const pm_char STR_MAVLINK_CUR_MODE[] PROGMEM = TR_MAVLINK_CUR_MODE;
  const pm_char STR_MAVLINK_ARMED[] PROGMEM = TR_MAVLINK_ARMED;
  const pm_char STR_MAVLINK_BAT_MENU_TITLE[] PROGMEM = TR_MAVLINK_BAT_MENU_TITLE;
  const pm_char STR_MAVLINK_BATTERY_LABEL[] PROGMEM = TR_MAVLINK_BATTERY_LABEL;
  const pm_char STR_MAVLINK_RC_RSSI_LABEL[] PROGMEM = TR_MAVLINK_RC_RSSI_LABEL;
  const pm_char STR_MAVLINK_PC_RSSI_LABEL[] PROGMEM = TR_MAVLINK_PC_RSSI_LABEL;
  const pm_char STR_MAVLINK_NAV_MENU_TITLE[] PROGMEM = TR_MAVLINK_NAV_MENU_TITLE;
  const pm_char STR_MAVLINK_COURSE[] PROGMEM = TR_MAVLINK_COURSE;
  const pm_char STR_MAVLINK_HEADING[] PROGMEM = TR_MAVLINK_HEADING;
  const pm_char STR_MAVLINK_BEARING[] PROGMEM = TR_MAVLINK_BEARING;
  const pm_char STR_MAVLINK_ALTITUDE[] PROGMEM = TR_MAVLINK_ALTITUDE;
  const pm_char STR_MAVLINK_GPS[] PROGMEM = TR_MAVLINK_GPS;
  const pm_char STR_MAVLINK_NO_FIX[] PROGMEM = TR_MAVLINK_NO_FIX;
  const pm_char STR_MAVLINK_SAT[] PROGMEM = TR_MAVLINK_SAT;
  const pm_char STR_MAVLINK_HDOP[] PROGMEM = TR_MAVLINK_HDOP;
  const pm_char STR_MAVLINK_LAT[] PROGMEM = TR_MAVLINK_LAT;
  const pm_char STR_MAVLINK_LON[] PROGMEM = TR_MAVLINK_LON;
#endif

#if !defined(CPUM64)
  const pm_char STR_ABOUTUS[] PROGMEM = TR_ABOUTUS;
  const pm_char STR_ABOUT_OPENTX_1[] PROGMEM = TR_ABOUT_OPENTX_1;
  const pm_char STR_ABOUT_OPENTX_2[] PROGMEM = TR_ABOUT_OPENTX_2;
  const pm_char STR_ABOUT_OPENTX_3[] PROGMEM = TR_ABOUT_OPENTX_3;
  const pm_char STR_ABOUT_OPENTX_4[] PROGMEM = TR_ABOUT_OPENTX_4;
  const pm_char STR_ABOUT_OPENTX_5[] PROGMEM = TR_ABOUT_OPENTX_5;
  
  const pm_char STR_ABOUT_BERTRAND_1[] PROGMEM = TR_ABOUT_BERTRAND_1;
  const pm_char STR_ABOUT_BERTRAND_2[] PROGMEM = TR_ABOUT_BERTRAND_2;
  const pm_char STR_ABOUT_BERTRAND_3[] PROGMEM = TR_ABOUT_BERTRAND_3;
  
  const pm_char STR_ABOUT_MIKE_1[] PROGMEM = TR_ABOUT_MIKE_1;
  const pm_char STR_ABOUT_MIKE_2[] PROGMEM = TR_ABOUT_MIKE_2;
  const pm_char STR_ABOUT_MIKE_3[] PROGMEM = TR_ABOUT_MIKE_3;
  const pm_char STR_ABOUT_MIKE_4[] PROGMEM = TR_ABOUT_MIKE_4;
  
  const pm_char STR_ABOUT_ROMOLO_1[] PROGMEM = TR_ABOUT_ROMOLO_1;
  const pm_char STR_ABOUT_ROMOLO_2[] PROGMEM = TR_ABOUT_ROMOLO_2;
  const pm_char STR_ABOUT_ROMOLO_3[] PROGMEM = TR_ABOUT_ROMOLO_3;
  
  const pm_char STR_ABOUT_ANDRE_1[] PROGMEM = TR_ABOUT_ANDRE_1;
  const pm_char STR_ABOUT_ANDRE_2[] PROGMEM = TR_ABOUT_ANDRE_2;
  const pm_char STR_ABOUT_ANDRE_3[] PROGMEM = TR_ABOUT_ANDRE_3;
  
  const pm_char STR_ABOUT_ROB_1[] PROGMEM = TR_ABOUT_ROB_1;
  const pm_char STR_ABOUT_ROB_2[] PROGMEM = TR_ABOUT_ROB_2;
  
  const pm_char STR_ABOUT_MARTIN_1[] PROGMEM = TR_ABOUT_MARTIN_1;
  const pm_char STR_ABOUT_MARTIN_2[] PROGMEM = TR_ABOUT_MARTIN_2;
  
  const pm_char STR_ABOUT_HARDWARE_1[] PROGMEM = TR_ABOUT_HARDWARE_1;
  const pm_char STR_ABOUT_HARDWARE_2[] PROGMEM = TR_ABOUT_HARDWARE_2;
  const pm_char STR_ABOUT_HARDWARE_3[] PROGMEM = TR_ABOUT_HARDWARE_3;
  
  const pm_char STR_ABOUT_PARENTS_1[] PROGMEM = TR_ABOUT_PARENTS_1;
  const pm_char STR_ABOUT_PARENTS_2[] PROGMEM = TR_ABOUT_PARENTS_2;
  const pm_char STR_ABOUT_PARENTS_3[] PROGMEM = TR_ABOUT_PARENTS_3;
  const pm_char STR_ABOUT_PARENTS_4[] PROGMEM = TR_ABOUT_PARENTS_4;
#endif

const pm_uchar font_5x7[] PROGMEM = {
#include "font_05x07.lbm"
#if defined(TRANSLATIONS_DE)
#include "font_de_05x07.lbm"
#elif defined(TRANSLATIONS_CZ)
#include "font_cz_05x07.lbm"
#elif defined(TRANSLATIONS_ES)
#include "font_es_05x07.lbm"
#elif defined(TRANSLATIONS_FR)
#include "font_fr_05x07.lbm"
#elif defined(TRANSLATIONS_IT)
#include "font_it_05x07.lbm"
#elif defined(TRANSLATIONS_PT)
#include "font_pt_05x07.lbm"
#elif defined(TRANSLATIONS_SE)
#include "font_se_05x07.lbm"
#endif
};

const pm_uchar font_10x14[] PROGMEM = {
#include "font_10x14_compressed.lbm"
#if defined(CPUARM)
  #if defined(TRANSLATIONS_DE)
  #include "font_de_10x14.lbm"
  #elif defined(TRANSLATIONS_CZ)
  #include "font_cz_10x14.lbm"
  #elif defined(TRANSLATIONS_ES)
  #include "font_es_10x14.lbm"
  #elif defined(TRANSLATIONS_FR)
  #include "font_fr_10x14.lbm"
  #elif defined(TRANSLATIONS_IT)
  #include "font_it_10x14.lbm"
  #elif defined(TRANSLATIONS_PT)
  #include "font_pt_10x14.lbm"
  #elif defined(TRANSLATIONS_SE)
  #include "font_se_10x14.lbm"
  #endif
#endif
};

#if defined(CPUARM)
const pm_uchar font_3x5[] PROGMEM = {
#include "font_03x05.lbm"
};

const pm_uchar font_4x6[] PROGMEM = {
#include "font_04x06.lbm"
#if defined(TRANSLATIONS_DE)
#include "font_de_04x06.lbm"
#elif defined(TRANSLATIONS_CZ)
#include "font_cz_04x06.lbm"
#elif defined(TRANSLATIONS_ES)
#include "font_es_04x06.lbm"
#elif defined(TRANSLATIONS_FR)
#include "font_fr_04x06.lbm"
#elif defined(TRANSLATIONS_IT)
#include "font_it_04x06.lbm"
#elif defined(TRANSLATIONS_PT)
#include "font_pt_04x06.lbm"
#elif defined(TRANSLATIONS_SE)
#include "font_se_04x06.lbm"
#endif
};

const pm_uchar font_8x10[] PROGMEM = {
#include "font_08x10.lbm"
#if defined(TRANSLATIONS_DE)
#include "font_de_08x10.lbm"
#elif defined(TRANSLATIONS_CZ)
#include "font_cz_08x10.lbm"
#elif defined(TRANSLATIONS_ES)
#include "font_es_08x10.lbm"
#elif defined(TRANSLATIONS_FR)
#include "font_fr_08x10.lbm"
#elif defined(TRANSLATIONS_IT)
#include "font_it_08x10.lbm"
#elif defined(TRANSLATIONS_PT)
#include "font_pt_08x10.lbm"
#elif defined(TRANSLATIONS_SE)
#include "font_se_08x10.lbm"
#endif
};

const pm_uchar font_4x6_extra[] PROGMEM = {
#include "font_04x06_extra.lbm"
};

const pm_uchar font_5x7_extra[] PROGMEM = {
#include "font_05x07_extra.lbm"
};

const pm_uchar font_10x14_extra[] PROGMEM = {
#include "font_10x14_extra.lbm"
};

#endif


