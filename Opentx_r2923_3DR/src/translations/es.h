/*
 * Authors (alphabetical order)
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bernet Andre <bernet.andre@gmail.com>
 * - Jose Moreno <josemoreno259@gmail.com>
 * - Kjell Kernen <kjell.kernen@gmail.com>
 * - Martin Hotar <mhotar@gmail.com>
 * - Romolo Manfredini <romolo.manfredini@gmail.com>
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
 *
 * !!!!! DO NOT EDIT es.h - EDIT es.h.txt INSTEAD !!!!!!!
 *
 * In order to make translations easier es.h.txt is parsed and national
 * characters are replaced by bitmap codes. The result is es.h.
 * 
 * See translate.py in the util catalog for the list of character codes  
 *
 * !!!!! DO NOT EDIT es.h - EDIT es.h.txt INSTEAD !!!!!!!   
 */

 
// NON ZERO TERMINATED STRINGS
#define LEN_OFFON              "\003"
#define TR_OFFON               "OFF""ON\0"

#define LEN_MMMINV             "\003"
#define TR_MMMINV              "---""INV"

#define LEN_NCHANNELS          "\004"
#define TR_NCHANNELS           "\0014CH\0016CH\0018CH10CH12CH14CH16CH"

#define LEN_VBEEPMODE          "\005"
#define TR_VBEEPMODE           "Mudo ""Alarm""NoKey""Todo "

#define LEN_VBEEPLEN           "\005"
#define TR_VBEEPLEN            "0====""=0===""==0==""===0=""====0"

#define LEN_VRENAVIG           "\003"
#define TR_VRENAVIG            "No REaREb"

#define LEN_VBLMODE            "\004"
#define TR_VBLMODE             "OFF ""Keys""Stks""Both""ON\0"

#define LEN_TRNMODE            "\003"
#define TR_TRNMODE             "OFF"" +="" :="

#define LEN_TRNCHN             "\003"
#define TR_TRNCHN              "CH1CH2CH3CH4"

#define LEN_DATETIME           "\005"
#define TR_DATETIME            "DATA:""HORA:"

#define LEN_VLCD               "\006"
#define TR_VLCD                "NormalOptrex"

#define LEN_COUNTRYCODES       TR("\002", "\007")
#define TR_COUNTRYCODES        TR("US""JP""EU", "America""Japon\0 ""Europa\0")

#define LEN_VTRIMINC           TR("\006", "\013")
#define TR_VTRIMINC            TR("Expo  ""ExFino""Fino  ""Medio ""Grueso", "Exponencial""Extra Fino ""Fino       ""Medio      ""Grueso     ")

#define LEN_RETA123            "\001"

#if defined(PCBGRUVIN9X)
  #if ROTARY_ENCODERS > 2
    #define TR_RETA123         "RETA123abcd"
  #else
    #define TR_RETA123         "RETA123ab"
  #endif
#elif defined(PCBTARANIS)
  #define TR_RETA123           "RETA12LR"
#else
  #define TR_RETA123           "RETA123"
#endif

#define LEN_VPROTOS            "\006"

#if defined(PXX)
  #define TR_PXX               "PXX\0  "
#elif defined(DSM2) || defined(IRPROTOS)
  #define TR_PXX               "[PXX]\0"
#else
  #define TR_PXX
#endif

#if defined(DSM2)
  #define TR_DSM2              "LP45\0 ""DSM2\0 ""DSMX\0 "
#elif defined(IRPROTOS)
  #define TR_DSM2              "[LP45]""[DSM2]""[DSMX]"
#else
  #define TR_DSM2
#endif

#if defined(IRPROTOS)
  #define TR_IRPROTOS          "SILV  TRAC09PICZ  SWIFT\0"
#else
  #define TR_IRPROTOS
#endif

#if defined(CPUARM)
  #define TR_XPPM
#else
  #define TR_XPPM              "PPM16\0""PPMsim"
#endif

#define TR_VPROTOS             "PPM\0  " TR_XPPM TR_PXX TR_DSM2 TR_IRPROTOS

#define LEN_POSNEG             "\003"
#define TR_POSNEG              "POS""NEG"

#define LEN_VCURVEFUNC         "\003"
#define TR_VCURVEFUNC          "---""x>0""x<0""|x|""f>0""f<0""|f|"

#define LEN_VMLTPX             "\010"
#define TR_VMLTPX              "Agregar ""Multipl.""Cambiar\0"

#define LEN_VMLTPX2            "\002"
#define TR_VMLTPX2             "+=""*="":="

#define LEN_VMIXTRIMS          "\003"
#define TR_VMIXTRIMS           "OFF""ON\0""Dir""Ele""Ace""Ale"

#define LEN_VCSWFUNC           "\005"
#define TR_VCSWFUNC            "---\0 ""a{x\0 ""a>x\0 ""a<x\0 ""|a|>x""|a|<x""AND\0 ""OR\0  ""XOR\0 ""a=b\0 ""a>b\0 ""a<b\0 ""d}x\0 ""|d|}x""TIM\0"

#define LEN_VFSWFUNC           "\012"

#if defined(VARIO)
  #define TR_VVARIO            "Vario\0    "
#else
  #define TR_VVARIO            "[Vario]\0  "
#endif

#if defined(AUDIO)
  #define TR_SOUND             "Oir Sonido"
#else
  #define TR_SOUND             "Beep\0     "
#endif

#if defined(PCBTARANIS)
  #define TR_HAPTIC
#elif defined(HAPTIC)
  #define TR_HAPTIC            "Tactil\0   "
#else
  #define TR_HAPTIC            "[Tactil]\0 "
#endif

#if defined(VOICE)
  #if defined(PCBSKY9X)
    #define TR_PLAY_TRACK      "Oir\0     "
  #else
    #define TR_PLAY_TRACK      "Oir pista\0"
  #endif
  #define TR_PLAY_BOTH         "Oir Ambos\0"
  #define TR_PLAY_VALUE        "Oir valor\0"
#else
  #define TR_PLAY_TRACK        "[OirPista]"
  #define TR_PLAY_BOTH         "[OirAmbos]"
  #define TR_PLAY_VALUE        "[OirValor]"
#endif

#define TR_CFN_VOLUME          "Volumen\0   "
#define TR_CFN_BG_MUSIC        "BgMusica\0  ""BgMusica||"

#if defined(SDCARD)
  #define TR_SDCLOGS           "SD Logs\0  "
#else
  #define TR_SDCLOGS           "[SD Logs]\0"
#endif

#ifdef GVARS
  #define TR_CFN_ADJUST_GVAR   "Ajuste\0  "
#else
  #define TR_CFN_ADJUST_GVAR
#endif

#ifdef DEBUG
  #define TR_CFN_TEST          "Test\0"
#else
  #define TR_CFN_TEST
#endif

#if defined(CPUARM)
  #define TR_VFSWFUNC          "Seguro\0   ""Aprendiz\0 ""Inst. Trim" TR_SOUND TR_HAPTIC "Reset\0    " TR_VVARIO TR_PLAY_TRACK TR_PLAY_VALUE TR_SDCLOGS TR_CFN_VOLUME "Luz fondo\0" TR_CFN_BG_MUSIC TR_CFN_ADJUST_GVAR TR_CFN_TEST
#elif defined(PCBGRUVIN9X)
  #define TR_VFSWFUNC          "Seguro\0   ""Aprendiz\0 ""Inst. Trim" TR_SOUND TR_HAPTIC "Reset\0    " TR_VVARIO TR_PLAY_TRACK TR_PLAY_BOTH TR_PLAY_VALUE TR_SDCLOGS "Luz fondo\0" TR_CFN_ADJUST_GVAR TR_CFN_TEST
#else
  #define TR_VFSWFUNC          "Seguro\0   ""Aprendiz\0 ""Inst. Trim" TR_SOUND TR_HAPTIC "Reset\0    " TR_VVARIO TR_PLAY_TRACK TR_PLAY_BOTH TR_PLAY_VALUE "Luz fondo\0" TR_CFN_ADJUST_GVAR TR_CFN_TEST
#endif

#define LEN_VFSWRESET          TR("\005", "\011")

#if defined(FRSKY)
  #define TR_FSW_RESET_TELEM   TR("Telem", "Telemetria")
#else
  #define TR_FSW_RESET_TELEM
#endif

#if ROTARY_ENCODERS == 2
  #define TR_FSW_RESET_ROTENC  TR("REa\0 ""REb\0 ", "RotEnc A\0""RotEnc B\0")
#elif ROTARY_ENCODERS == 1
  #define TR_FSW_RESET_ROTENC  TR("R.Enc", "RotEnc\0  ")
#else
  #define TR_FSW_RESET_ROTENC
#endif

#define TR_VFSWRESET           TR("Tmr1\0""Tmr2\0""All\0 " TR_FSW_RESET_TELEM TR_FSW_RESET_ROTENC, "Reloj 1  ""Reloj 2  ""Todo     " TR_FSW_RESET_TELEM TR_FSW_RESET_ROTENC)

#define LEN_FUNCSOUNDS         TR("\004", "\006")
#define TR_FUNCSOUNDS          TR("Bp1\0""Bp2\0""Bp3\0""Avs1""Avs2""Chee""Rata""Tick""Sirn""Ring""SciF""Robt""Chrp""Tada""Crck""Alrm", "Beep1 ""Beep2 ""Beep3 ""Aviso1""Aviso2""Cheep ""Ratata""Tick  ""Sirena""Ring  ""SciFi ""Robot ""Chirp ""Tada  ""Crickt""AlmClk")

#define LEN_VTELEMCHNS         "\004"
#if defined(PCBTARANIS)
  #define TR_RSSI_0            "SWR\0"
  #define TR_RSSI_1            "RSSI"
#else
  #define TR_RSSI_0            "Tx\0 "
  #define TR_RSSI_1            "Rx\0 "
#endif
#define TR_VTELEMCHNS          "---\0""Batt""Tmr1""Tmr2" TR_RSSI_0 TR_RSSI_1 "A1\0 ""A2\0 ""Alt\0""Rpm\0""Fuel""T1\0 ""T2\0 ""Spd\0""Dist""GAlt""Cell""Cels""Vfas""Curr""Cnsp""Powr""AccX""AccY""AccZ""Hdg\0""VSpd""A1-\0""A2-\0""Alt-""Alt+""Rpm+""T1+\0""T2+\0""Spd+""Dst+""Cur+""Pwr+""Acc\0""Hora"

#if defined(CPUARM)
  #define LEN_VUNITSSYSTEM     TR("\006", "\010")
  #define TR_VUNITSSYSTEM      TR("Metric""Imper.", "Metric\0 ""Imperial")
  #define LEN_VTELEMUNIT_NORM  "\003"
  #define TR_VTELEMUNIT_NORM   "v\0 ""A\0 ""m/s""-\0 ""kmh""m\0 ""@\0 ""%\0 ""mA\0""mAh""W\0 "
  #define LEN_VTELEMUNIT_IMP   "\003"
  #define TR_VTELEMUNIT_IMP    "v\0 ""A\0 ""m/s""-\0 ""kts""ft\0""@\0 ""%\0 ""mA\0""mAh""W\0 "
#else
  #if defined(IMPERIAL_UNITS)
    #define LENGTH_UNIT        "ft\0"
    #define SPEED_UNIT         "kts"
  #else
    #define LENGTH_UNIT        "m\0 "
    #define SPEED_UNIT         "kmh"
  #endif
  #define LEN_VTELEMUNIT       "\003"
  #define TR_VTELEMUNIT        "v\0 ""A\0 ""m/s""-\0 " SPEED_UNIT LENGTH_UNIT "@\0 ""%\0 ""mA\0""mAh""W\0 "
#endif

#define STR_V                  (STR_VTELEMUNIT+1)
#define STR_A                  (STR_VTELEMUNIT+4)

#define LEN_VALARM             "\003"
#define TR_VALARM              "---""Ama""Nar""Roj"

#define LEN_VALARMFN           "\001"
#define TR_VALARMFN            "<>"

#define LEN_VTELPROTO          "\007"
#define TR_VTELPROTO           "Nada\0  ""Hub\0   ""WSHHigh"

#define LEN_VOLTSRC            "\003"
#define TR_VOLTSRC             "---""A1\0""A2\0""FAS""Cel"

#define LEN_VARIOSRC           "\005"
#if defined(FRSKY_SPORT)
  #define TR_VARIOSRC          "Vario""A1\0  ""A2\0"
#else
  #define TR_VARIOSRC          "Alti\0""Alti+""Vario""A1\0  ""A2\0"
#endif

#define LEN_VSCREEN            "\004"
#define TR_VSCREEN             "Nums""Bars"

#define LEN_GPSFORMAT          "\004"
#define TR_GPSFORMAT           "HMS NMEA"

#define LEN2_VTEMPLATES        13
#define LEN_VTEMPLATES         "\015"
#define TR_VTEMPLATES          "Elim Mezcla\0\0""Simple 4-CH \0""Anular Motor\0""Cola en V   \0""Elevon\\Delta\0""eCCPM       \0""Heli Setup  \0""Servo Test  \0"

#define LEN_VSWASHTYPE         "\004"
#define TR_VSWASHTYPE          "---\0""120\0""120X""140\0""90\0"

#define LEN_VKEYS              "\005"
#define TR_VKEYS               TR(" Menu""Salir""Abajo""Arrib""Dcha.""Izqd.", " Menu""Salir""Enter""Pgna.""Mas  ""Menos")

#define LEN_VRENCODERS         "\003"
#define TR_VRENCODERS          "REa""REb"

#define LEN_VSWITCHES          "\003"
#define LEN_VSRCRAW            "\004"

#if defined(PCBTARANIS)
  #define TR_POTS_VSRCRAW      "S1\0 ""S2\0 ""LS\0 ""RS\0 "
  #define TR_SW_VSRCRAW        "SA\0 ""SB\0 ""SC\0 ""SD\0 ""SE\0 ""SF\0 ""SG\0 ""SH\0 "
#elif defined(EXTRA_3POS)
  #define TR_POTS_VSRCRAW      "P1\0 ""P2\0 "
  #define TR_SW_VSRCRAW        "3P1\0""3P2\0"
  #define TR_9X_3POS_SWITCHES  "ID0""ID1""ID2""ID3""ID4""ID5"
#else
  #define TR_POTS_VSRCRAW      "P1\0 ""P2\0 ""P3\0 "
  #define TR_SW_VSRCRAW        "3POS"
  #define TR_9X_3POS_SWITCHES  "ID0""ID1""ID2"
#endif

#if defined(CPUARM)
  #define TR_CUSTOMSW          "CS1""CS2""CS3""CS4""CS5""CS6""CS7""CS8""CS9""CSA""CSB""CSC""CSD""CSE""CSF""CSG""CSH""CSI""CSJ""CSK""CSL""CSM""CSN""CSO""CSP""CSQ""CSR""CSS""CST""CSU""CSV""CSW"
#elif defined(PCBGRUVIN9X) || defined(CPUM2561) || defined(CPUM128)
  #define TR_CUSTOMSW          "CS1""CS2""CS3""CS4""CS5""CS6""CS7""CS8""CS9""CSA""CSB""CSC""CSD""CSE""CSF"
#else
  #define TR_CUSTOMSW          "CS1""CS2""CS3""CS4""CS5""CS6""CS7""CS8""CS9""CSA""CSB""CSC"
#endif

#if defined(PCBTARANIS)
  #define TR_VSWITCHES         "SA\300""SA-""SA\301""SB\300""SB-""SB\301""SC\300""SC-""SC\301""SD\300""SD-""SD\301""SE\300""SE-""SE\301""SF\300""SF\301""SG\300""SG-""SG\301""SH\300""SH\301" TR_CUSTOMSW "Uno"
#else
  #define TR_VSWITCHES         TR_9X_3POS_SWITCHES "ACE""DIR""ELE""ALE""GEA""TRN" TR_CUSTOMSW "Uno"
#endif

#if defined(PCBSKY9X)
  #define TR_ROTARY_ENCODERS_VSRCRAW "REnc"
#elif defined(PCBGRUVIN9X) && ROTARY_ENCODERS > 2
  #define TR_ROTARY_ENCODERS_VSRCRAW "REa ""REb ""REc ""REd "
#elif defined(PCBGRUVIN9X) && ROTARY_ENCODERS <= 2
  #define TR_ROTARY_ENCODERS_VSRCRAW "REa ""REb "
#else
  #define TR_ROTARY_ENCODERS_VSRCRAW
#endif

#if defined(HELI)
  #define TR_CYC_VSRCRAW       "CYC1""CYC2""CYC3"
#else
  #define TR_CYC_VSRCRAW       "[C1]""[C2]""[C3]"
#endif

#define TR_VSRCRAW             "---\0""Dir\0""Ele\0""Thr\0""Ale\0" TR_POTS_VSRCRAW TR_ROTARY_ENCODERS_VSRCRAW "MAX\0" TR_CYC_VSRCRAW "TrmR" "TrmE" "TrmT" "TrmA" TR_SW_VSRCRAW

#define LEN_VTMRMODES          "\003"
#define TR_VTMRMODES           "OFF""ABS""THs""TH%""THt"

#define LEN_VTRAINERMODES      "\006"
#define TR_VTRAINERMODES       "Master""Esclav"

#define LEN_VFAILSAFE          "\011"
#define TR_VFAILSAFE           "Guardar\0 ""Adaptar\0 ""Sin pulsos"

#if defined(MAVLINK)
  #define LEN_MAVLINK_BAUDS		"\006"
  #define TR_MAVLINK_BAUDS		"4800  ""9600  ""14400 ""19200 ""38400 ""57600 ""76800 ""115200"
  #define LEN_MAVLINK_AC_MODES	"\011"
  #define TR_MAVLINK_AC_MODES	"Estabilizar""Acrobat. ""Alt Hold ""Auto     ""Guiado   ""Loiter   ""RTL      ""Circulo  ""Pos Hold ""Tierra   ""OF Loiter""Toy A    ""Toy M    ""INVALIDO "
  #define LEN_MAVLINK_AP_MODES	"\015"
  #define TR_MAVLINK_AP_MODES	"Manual       ""Circulo       ""Estabilizar   ""Entrenamiento""Fly by Wire A""Fly by Wire A""Auto         ""RTL          ""Loiter       ""Guiado       ""Inicialisando""INVALID      "
#endif

// ZERO TERMINATED STRINGS
#define INDENT                 "\001"
#define LEN_INDENT             1
#define INDENT_WIDTH           (FW/2)

#if defined(PCBTARANIS)
  #define TR_ENTER             "[ENTER]"
#else
  #define TR_ENTER             "[MENU]"
#endif

#define TR_POPUPS              TR_ENTER "\010[SALIR]"
#define OFS_EXIT               sizeof(TR_ENTER)

#define TR_MENUWHENDONE        CENTER "\006" TR_ENTER "AL ACABAR "
#define TR_FREE                "libre"
#define TR_DELETEMODEL         "BORRAR MODELO"
#define TR_COPYINGMODEL        "Copiando modelo.."
#define TR_MOVINGMODEL         "Mover modelo..."
#define TR_LOADINGMODEL        "Cargar modelo..."
#define TR_NAME                "Nombre"
#define TR_MODELNAME           "Nom.Modelo"
#define TR_PHASENAME           "Nom.Fase "
#define TR_MIXNAME             "Nom.Mezcla"
#define TR_EXPONAME            "Nom. Expo"
#define TR_BITMAP              "Imagen Modelo"
#define TR_TIMER               TR("Reloj","Reloj ")
#define TR_ELIMITS             TR("E.Limite","Ampliar Limites")
#define TR_ETRIMS              TR("E.Trims","Ampliar Trims")
#define TR_TRIMINC             "Paso Trim"
#define TR_TTRACE              TR("Fuente-A","Fuente Acelerad")
#define TR_TTRIM               TR("Trim-A","Trim Acelerad")
#define TR_BEEPCTR             TR("Ctr Beep","Center Beep")
#define TR_PROTO               TR(INDENT"Proto",INDENT"Protocol")
#define TR_PPMFRAME            "Trama PPM"
#define TR_MS                  "ms"
#define TR_SWITCH              "Interr"
#define TR_TRIMS               "Trims"
#define TR_FADEIN              "Inicio"
#define TR_FADEOUT             "Final"
#define TR_DEFAULT             "(defecto)"
#define TR_CHECKTRIMS          CENTER "\006Check\012Trims"
#define OFS_CHECKTRIMS         CENTER_OFS+(9*FW)
#define TR_SWASHTYPE           "Tipo ciclico"
#define TR_COLLECTIVE          TR("Colectivo","Fuente Colectivo")
#define TR_SWASHRING           "Ciclico"
#define TR_ELEDIRECTION        TR("ELE Direccion","Largo cyc. direccion")
#define TR_AILDIRECTION        TR("AIL Direccion","Lateral cyc. direccion")
#define TR_COLDIRECTION        TR("PIT Direccion","Coll. pitch direccion")
#define TR_MODE                INDENT"Modo"
#define TR_NOFREEEXPO          "No expo libre!"
#define TR_NOFREEMIXER         "No mezcla lib!"
#define TR_INSERTMIX           "INSERTAR MIX"
#define TR_EDITMIX             "EDITAR MIX "
#define TR_SOURCE              INDENT"Fuente"
#define TR_WEIGHT              "Cantidad"
#define TR_EXPO                TR("Expo","Exponencial")
#define TR_SIDE                "Lado"
#define TR_DIFFERENTIAL        "Diferenc"
#define TR_OFFSET              INDENT"Offset"
#define TR_TRIM                "Trim"
#define TR_DREX                "DRex"
#define TR_CURVE               "Curva"
#define TR_FLMODE              TR("Modo","Modos")
#define TR_MIXWARNING          "Aviso"
#define TR_OFF                 "OFF"
#define TR_MULTPX              "Multpx"
#define TR_DELAYDOWN           "Delay Dn"
#define TR_DELAYUP             "Delay Up"
#define TR_SLOWDOWN            "Slow  Dn"
#define TR_SLOWUP              "Slow  Up"
#define TR_MIXER               "Mezclas"
#define TR_CV                  "CV"
#define TR_GV                  "GV"
#define TR_ACHANNEL            "A\004canal"
#define TR_RANGE               INDENT"Alcance"
#define TR_BAR                 "Bar"
#define TR_ALARM               INDENT"Alarma"
#define TR_USRDATA             "UsrData"
#define TR_BLADES              INDENT"Palas"
#define TR_SCREEN              "Pantalla"
#define TR_SOUND_LABEL         "Sonido"
#define TR_LENGTH              INDENT"Longitud"
#define TR_SPKRPITCH           INDENT"Tono"
#define TR_HAPTIC_LABEL        "Tactil"
#define TR_HAPTICSTRENGTH      INDENT"Intensidad"
#define TR_CONTRAST            "Contraste"
#define TR_ALARMS_LABEL        "Alarmas"
#define TR_BATTERY_RANGE       TR("Rango bateria","Rango medidor Bater")
#define TR_BATTERYWARNING      INDENT"Bateria Baja"
#define TR_INACTIVITYALARM     INDENT"Inactividad"
#define TR_MEMORYWARNING       INDENT"Memoria Baja"
#define TR_ALARMWARNING        INDENT"Sin Sonido"
#define TR_RENAVIG             "RotEnc Navig"
#define TR_THROTTLEREVERSE     TR("Invert_Acel", "Invertir Acel.")
#define TR_MINUTEBEEP          TR(INDENT"Minuto",INDENT"Cada Minuto")
#define TR_BEEPCOUNTDOWN       INDENT"Cuentaatras"
#define TR_PERSISTENT          TR(INDENT"Persist.",INDENT"Persistente")
#define TR_BACKLIGHT_LABEL     "Luz Fondo"
#define TR_BLDELAY             INDENT"Duracion"
#define TR_BLONBRIGHTNESS      INDENT"MAS Brillo"
#define TR_BLOFFBRIGHTNESS     INDENT"MENOS Brillo"
#define TR_SPLASHSCREEN        "Ptalla.inicio"
#define TR_THROTTLEWARNING     TR("Aviso-A", "Aviso Acelerador")
#define TR_SWITCHWARNING       TR("Aviso-I", "Aviso Intrptor")
#define TR_TIMEZONE            TR("Zona Hora", "GPS Zona Hora")
#define TR_RXCHANNELORD        TR("Rx Orden canal", "Orden habitual canales")
#define TR_SLAVE               "Esclavo"
#define TR_MODESRC             "Modo\006% Fuente"
#define TR_MULTIPLIER          "Multiplicar"
#define TR_CAL                 "Cal"
#define TR_VTRIM               "Trim- +"
#define TR_BG                  "BG:"
#define TR_MENUTOSTART         CENTER "\006" TR_ENTER "EMPEZAR"
#define TR_SETMIDPOINT         CENTER "\003STICKS AL CENTRO"
#define TR_MOVESTICKSPOTS      CENTER "\006MOVER STICKS/POTS"
#define TR_RXBATT              "Rx Batt:"
#define TR_TXnRX               "Tx:\0Rx:"
#define OFS_RX                 4
#define TR_ACCEL               "Acc:"
#define TR_NODATA              CENTER "SIN DATOS"
#define TR_TM1TM2              "TM1\032TM2"
#define TR_THRTHP              "THR\032TH%"
#define TR_TOT                 "TOT"
#define TR_TMR1LATMAXUS        "Tmr1Lat max\006us"
#define STR_US (STR_TMR1LATMAXUS+12)
#define TR_TMR1LATMINUS        "Tmr1Lat min\006us"
#define TR_TMR1JITTERUS        "Tmr1 Jitter\006us"

#if defined(CPUARM)
  #define TR_TMIXMAXMS         "Tmix max\012ms"
#else
  #define TR_TMIXMAXMS         "Tmix max\014ms"
#endif

#define TR_T10MSUS             "T10ms\016us"
#define TR_FREESTACKMINB       "Pila LIbre\010b"
#define TR_MENUTORESET         CENTER TR_ENTER "Resetear"
#define TR_PPM                 "PPM"
#define TR_CH                  "CH"
#define TR_MODEL               "MODELO"
#define TR_FP                  "FM"
#define TR_MIX                 "MIX"
#define TR_EEPROMLOWMEM        "EEPROM mem.baja"
#define TR_ALERT               "\016ALERTA"
#define TR_PRESSANYKEYTOSKIP   "Pulsar tecla omitir"
#define TR_THROTTLENOTIDLE     "Aceler.Activado"
#define TR_ALARMSDISABLED      "Alarmas Desact."
#define TR_PRESSANYKEY         TR("\010Pulsa una Tecla", "Pulsa una Tecla")
#define TR_BADEEPROMDATA       "Datos EEprom mal"
#define TR_EEPROMFORMATTING    "Formateo EEPROM"
#define TR_EEPROMOVERFLOW      "Desborde EEPROM"
#define TR_MENURADIOSETUP      "CONFIGURACION"
#define TR_MENUDATEANDTIME     "FECHA Y HORA"
#define TR_MENUTRAINER         "APRENDIZ"
#define TR_MENUVERSION         "VERSION"
#define TR_MENUDIAG            TR("INTERUPTS", "TEST INTERUP.")
#define TR_MENUANA             TR("ANAS", "ENTRADAS ANALOG")
#define TR_MENUCALIBRATION     "CALIBRACION"
#define TR_TRIMS2OFFSETS       "\006Trims => Offsets"
#define TR_MENUMODELSEL        TR("MODELSEL", "SELECCION MODELO")
#define TR_MENUSETUP           TR("CONF.", "CONF.MODELO")
#define TR_MENUFLIGHTPHASE     "MODO VUELO"
#define TR_MENUFLIGHTPHASES    "MODOS VUELO"
#define TR_MENUHELISETUP       "CONF. HELI"

#if defined(PPM_CENTER_ADJUSTABLE) || defined(PPM_LIMITS_SYMETRICAL) // The right menu titles for the gurus ...
  #define TR_MENUDREXPO        "STICKS"
  #define TR_MENULIMITS        "SERVOS"
#else
  #define TR_MENUDREXPO        "DR/EXPO"
  #define TR_MENULIMITS        "LIMITES"
#endif

#define TR_MENUCURVES          "CURVAS"
#define TR_MENUCURVE           "CURVA"
#define TR_MENUCUSTOMSWITCH    "AJTE.INTERUP."
#define TR_MENUCUSTOMSWITCHES  "AJTE.INTERUPTS."
#define TR_MENUCUSTOMFUNC      "AJTE. FUNCIONES"
#define TR_MENUTELEMETRY       "TELEMETRIA"
#define TR_MENUTEMPLATES       "PLANTILLAS"
#define TR_MENUSTAT            "STATS"
#define TR_MENUDEBUG           "DEBUG"
#define TR_RXNUM               TR("RxNum", INDENT"Receptor No.")
#define TR_SYNCMENU            "Sync "TR_ENTER
#define TR_LIMIT               INDENT"Limite"
#define TR_MINRSSI             "Min Rssi"
#define TR_LATITUDE            "Latitud"
#define TR_LONGITUDE           "Longitud"
#define TR_GPSCOORD            TR("GPS Coords", "GPS formato coordenadas")
#define TR_VARIO               TR("Vario", "Variometro")
#define TR_SHUTDOWN            "APAGANDO"
#define TR_BATT_CALIB          "Calib.bateria"
#define TR_CURRENT_CALIB       "Calib. actual"
#define TR_VOLTAGE             INDENT"Voltaje"
#define TR_CURRENT             INDENT"Actual"
#define TR_SELECT_MODEL        "Selec Modelo"
#define TR_CREATE_MODEL        "Crear Modelo"
#define TR_COPY_MODEL          "Copiar Modelo"
#define TR_MOVE_MODEL          "Mover Modelo"
#define TR_BACKUP_MODEL        "Copia Sgdad Mod."
#define TR_DELETE_MODEL        "Borrar Modelo"
#define TR_RESTORE_MODEL       "Restaurar Modelo"
#define TR_SDCARD_ERROR        "SDCARD Error"
#define TR_NO_SDCARD           "No SDCARD"
#define TR_INCOMPATIBLE        "Incompatible"
#define TR_WARNING             "AVISO"
#define TR_EEPROMWARN          "EEPROM"
#define TR_THROTTLEWARN        "ACELERADOR"
#define TR_ALARMSWARN          "ALARMAS"
#define TR_SWITCHWARN          "INTERPTOR"
#define TR_INVERT_THR          TR("Invertir Acel?", "Invertir Acel.?")
#define TR_SPEAKER_VOLUME      INDENT "Volumen"
#define TR_LCD                 "LCD"
#define TR_BRIGHTNESS          INDENT "Brillo"
#define TR_CPU_TEMP            "CPU Temp.\016>"
#define TR_CPU_CURRENT         "Actual\022>"
#define TR_CPU_MAH             "Consumo"
#define TR_COPROC              "CoProc."
#define TR_COPROC_TEMP         "MB Temp. \016>"
#define TR_CAPAWARNING         INDENT "Capacidad Baja"
#define TR_TEMPWARNING         INDENT "Sobrecalent"
#define TR_FUNC                "Func"
#define TR_V1                  "V1"
#define TR_V2                  "V2"
#define TR_DURATION            "Duracion"
#define TR_DELAY               "Atraso"
#define TR_SD_CARD             "SD CARD"
#define TR_SDHC_CARD           "SD-HC CARD"
#define TR_NO_SOUNDS_ON_SD     "Sin sonidos en SD"
#define TR_NO_MODELS_ON_SD     "Sin Modelos en SD"
#define TR_NO_BITMAPS_ON_SD    "Sin imagenes en SD"
#define TR_PLAY_FILE           "Play"
#define TR_DELETE_FILE         "Borrar"
#define TR_COPY_FILE           "Copiar"
#define TR_RENAME_FILE         "Renombrar"
#define TR_ASSIGN_BITMAP       "Asignar Imagen"
#define TR_REMOVED             "Borrado"
#define TR_SD_INFO             "Informacion"
#define TR_SD_FORMAT           "Formatear"
#define TR_NA                  "N/A"
#define TR_HARDWARE            "COMPONENTES"
#define TR_FORMATTING          "Formateando.."
#define TR_TEMP_CALIB          "Temp. Calib"
#define TR_TIME                "Hora"
#define TR_BAUDRATE            "BT Baudrate"
#define TR_SD_INFO_TITLE       "SD INFO"
#define TR_SD_TYPE             "Tipo:"
#define TR_SD_SPEED            "Velocidad:"
#define TR_SD_SECTORS          "Sectores:"
#define TR_SD_SIZE             "Tama�o:"
#define TR_TYPE                "Tipo"
#define TR_GLOBAL_VARS         "Global Variables"
#define TR_GLOBAL_VAR          "Global Variable"
#define TR_MENUGLOBALVARS      "GLOBAL VARIABLES"
#define TR_OWN                 "Propio"
#define TR_DATE                "Fecha"
#define TR_ROTARY_ENCODER      "R.Encs"
#define TR_CHANNELS_MONITOR    "MONITOR CANALES"
#define TR_INTERNALRF          "Interna RF"
#define TR_EXTERNALRF          "Externa RF"
#define TR_FAILSAFE            INDENT"Modo sgdad."
#define TR_FAILSAFESET         "AJUSTES SGDAD."
#define TR_COUNTRYCODE         "Codigo Pais"
#define TR_VOICELANG           "Idioma voces"
#define TR_UNITSSYSTEM         "Unidades"
#define TR_EDIT                "Editar"
#define TR_INSERT_BEFORE       "Insertar antes"
#define TR_INSERT_AFTER        "Insertar despues"
#define TR_COPY                "Copiar"
#define TR_MOVE                "Mover"
#define TR_PASTE               "Pegar"
#define TR_DELETE              "Borrar"
#define TR_RESET_FLIGHT        "Reset Vuelo"
#define TR_RESET_TIMER1        "Reset Reloj1"
#define TR_RESET_TIMER2        "Reset Reloj2"
#define TR_RESET_TELEMETRY     "Reset Telemetria"
#define TR_STATISTICS          "Estadisticas"
#define TR_ABOUT_US            "Nosotros"
#define TR_AND_SWITCH          "AND Inter."
#define TR_CF                  "CF"
#define TR_SPEAKER             INDENT"Altavoz"
#define TR_BUZZER              INDENT"Zumbador"
#define TR_BYTES               "bytes"
#define TR_MODULE_BIND         "[Enlace]"
#define TR_MODULE_RANGE        "[Limites]"
#define TR_RESET               "[Reset]"
#define TR_SET                 "[Ajuste]"
#define TR_TRAINER             "Aprendiz"
#define TR_ANTENNAPROBLEM      CENTER "�Problema antena TX!"
#define TR_MODELIDUSED         TR("ID en uso", "ID modelo en uso")
#define TR_MODULE              INDENT "Modulo"
#define TR_CHANNELRANGE        INDENT "Gama de canales"
#define TR_LOWALARM            INDENT "Alarma baja"
#define TR_CRITICALALARM       INDENT "Alarma Critica"

#if defined(MAVLINK)
  #define TR_MAVLINK_RC_RSSI_SCALE_LABEL	"Max RSSI"
  #define TR_MAVLINK_PC_RSSI_EN_LABEL		"PC RSSI EN"
  #define TR_MAVMENUSETUP_TITLE				"Mavlink Setup"
  #define TR_MAVLINK_BAUD_LABEL				"Baudrate"
  #define TR_MAVLINK_INFOS					"INFOS"
  #define TR_MAVLINK_MODE					"MODO"
  #define TR_MAVLINK_CUR_MODE				"Modo actual"
  #define TR_MAVLINK_ARMED					"Armad0"
  #define TR_MAVLINK_BAT_MENU_TITLE			"BAT RSSI"
  #define TR_MAVLINK_BATTERY_LABEL			"Estado Bateria de vuelo"
  #define TR_MAVLINK_RC_RSSI_LABEL			"RC RSSI"
  #define TR_MAVLINK_PC_RSSI_LABEL			"PC RSSI"
  #define TR_MAVLINK_NAV_MENU_TITLE			"NAV"
  #define TR_MAVLINK_COURSE					"Carrera"
  #define TR_MAVLINK_HEADING				"Titulo"
  #define TR_MAVLINK_BEARING				"Soporte"
  #define TR_MAVLINK_ALTITUDE				"Altitud"
  #define TR_MAVLINK_GPS					"GPS"
  #define TR_MAVLINK_NO_FIX					"NO Fix"
  #define TR_MAVLINK_SAT					"SAT"
  #define TR_MAVLINK_HDOP					"HDOP"
  #define TR_MAVLINK_LAT					"LAT"
  #define TR_MAVLINK_LON					"LON"
#endif

// Taranis column headers
#define TR_PHASES_HEADERS      { " Nombre ", " Interrup.", " Trims ", " Aparecer ", " Desparecer " }
#define TR_LIMITS_HEADERS      { " Nombre ", " Compensacion", " Min ", " Max ", " Direccion ", " Centrado PPM ", " Simetrica " }
#define TR_CSW_HEADERS         { " Funcion ", " V1 ", " V2 ", " AND Interrup. ", " Duracion ", " Retardo " }

//Taranis About screen
#define TR_ABOUTUS             "Nosotros"

#define TR_ABOUT_OPENTX_1      "OpenTX es open source, no-"
#define TR_ABOUT_OPENTX_2      "comercial y viene sin "
#define TR_ABOUT_OPENTX_3      "garantias. Fue desarrollado"
#define TR_ABOUT_OPENTX_4      "libremente. Ayudas a traves"
#define TR_ABOUT_OPENTX_5      "de donaciones son bienvenidas!"

#define TR_ABOUT_BERTRAND_1    "Bertrand Songis"
#define TR_ABOUT_BERTRAND_2    "Autor principal OpenTX"
#define TR_ABOUT_BERTRAND_3    "Companion9x codesarrollador"

#define TR_ABOUT_MIKE_1        "Mike Blandford"
#define TR_ABOUT_MIKE_2        "Guru de codigo y drivers"
#define TR_ABOUT_MIKE_3        "Seguramente uno de los"
#define TR_ABOUT_MIKE_4        "mejores inspiradores"
       
#define TR_ABOUT_ROMOLO_1      "Romolo Manfredini"
#define TR_ABOUT_ROMOLO_2      "Desarrollador principal" 
#define TR_ABOUT_ROMOLO_3      "Companion9x"

#define TR_ABOUT_ANDRE_1       "Andre Bernet"
#define TR_ABOUT_ANDRE_2       "Funcionalidad, usabilidad,"
#define TR_ABOUT_ANDRE_3       "depurado, documentacion"

#define TR_ABOUT_ROB_1         "Rob Thomson"
#define TR_ABOUT_ROB_2         "openrcforums webmaster"

#define TR_ABOUT_MARTIN_1      "Martin Hotar"
#define TR_ABOUT_MARTIN_2      "Dise\201no grafico"

#if defined(PCBTARANIS)
  #define TR_ABOUT_HARDWARE_1  "FrSky"
  #define TR_ABOUT_HARDWARE_2  "Productor dise\201o de hardware"
  #define TR_ABOUT_HARDWARE_3  "Firmware contributor"
#else
  #define TR_ABOUT_HARDWARE_1  "Brent Nelson"
  #define TR_ABOUT_HARDWARE_2  "Sky9x dise\201ador/productor"
  #define TR_ABOUT_HARDWARE_3  ""
#endif

#define TR_ABOUT_PARENTS_1     "Padres del proyecto"
#define TR_ABOUT_PARENTS_2     "ersky9x (Mike Blandford)"
#define TR_ABOUT_PARENTS_3     "ER9X (Erez Raviv)"
#define TR_ABOUT_PARENTS_4     "TH9X (Thomas Husterer)"

#define TR_CHR_SHORT  's'
#define TR_CHR_LONG   'l'
#define TR_CHR_TOGGLE 't'
#define TR_CHR_HOUR   'h'

#define TR_BEEP_VOLUME         "Volumen Beep"
#define TR_WAV_VOLUME          "Volumen Wav"
#define TR_VARIO_VOLUME        "Volumen Vario"
#define TR_BG_VOLUME           "Volumen Bg"