/*************************************************************************************
    LCD16x2 displays configuration file.
*************************************************************************************/

#ifndef displayLCD16x2conf_h
#define displayLCD16x2conf_h

#define TFT_FRAMEWDT    0
#define MAX_WIDTH       16
#define PLMITEMS        2

#define HIDE_IP
#define HIDE_TITLE2
#define HIDE_VOL
#define HIDE_VOLBAR
#define HIDE_BUFFERBAR
#define HIDE_RSSI
#define HIDE_VU
#define HIDE_WEATHER
#define HIDE_BATTERY
#define META_MOVE

#define BOOTLOGOTOP     0

/* SCROLLS  */                           /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
// SDELTA removed - using SCROLLDELTA from dspconf.h
// STIME removed - using SCROLLTIME from dspconf.h
const ScrollConfig metaConf       PROGMEM = {{ 0, 0, 1, WA_LEFT }, 140, true, MAX_WIDTH-6, SCROLLDELAY, 2, SCROLLTIME };
const ScrollConfig title1Conf     PROGMEM = {{ 0, 1, 1, WA_LEFT }, 140, true, MAX_WIDTH-4, SCROLLDELAY, 2, SCROLLTIME };
const ScrollConfig playlistConf   PROGMEM = {{ 1, 1, 1, WA_LEFT }, 140, true, MAX_WIDTH-1, SCROLLDELAY, 2, SCROLLTIME };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 0, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { 0, 1, 1, WA_RIGHT };
const WidgetConfig numConf        PROGMEM = { 0, 1, 1, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { 0, 0, 1, WA_RIGHT };
const WidgetConfig bootWdtConf    PROGMEM = { 0, 1, 1, WA_CENTER };
const ProgressConfig bootPrgConf  PROGMEM = { 250, 10, 4 };

/* STRINGS  */
const char numtxtFmt[]            PROGMEM = "%d";
const char bitrateFmt[]           PROGMEM = "%d";
const char rssiFmt[]              PROGMEM = "";
const char const_lcdApMode[]      PROGMEM = "AP-IMPROV MODE";
const char const_lcdApName[]      PROGMEM = "AP NAME: ";
const char const_lcdApPass[]      PROGMEM = "PASSWORD: ";
//const char bootstrFmt[]           PROGMEM = "Wifi- %s";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig metaMove         PROGMEM = { 0, 0, MAX_WIDTH };
const MoveConfig clockMove        PROGMEM = { 0, 0, -1 };
const MoveConfig weatherMove      PROGMEM = { 0, 0, -1 };
const MoveConfig weatherMoveVU    PROGMEM = { 0, 0, -1 };

#endif

