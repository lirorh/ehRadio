/*************************************************************************************
    OLED256x64 displays configuration file.
*************************************************************************************/

#ifndef displayOLED256x64conf_h
#define displayOLED256x64conf_h

#define TFT_FRAMEWDT    1
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#define HIDE_BUFFERBAR
#define HIDE_VOL
#define HIDE_VU
//#define HIDE_TITLE2

#define BOOTLOGOTOP     8

/* SCROLLS  */                           /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT+1, TFT_FRAMEWDT+1, 2, WA_LEFT }, 140, true, MAX_WIDTH-2, SCROLLDELAY, 2, SCROLLTIME*7/4 };
const ScrollConfig title1Conf     PROGMEM = {{ 0, 20, 1, WA_LEFT }, 140, true, DSP_WIDTH/2+2, SCROLLDELAY, 1, SCROLLTIME };
const ScrollConfig title2Conf     PROGMEM = {{ 0, 29, 1, WA_LEFT }, 140, true, DSP_WIDTH/2+2, SCROLLDELAY, 1, SCROLLTIME };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 30, 1, WA_LEFT }, 140, true, MAX_WIDTH, SCROLLDELAY/5, 1, SCROLLTIME };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT+1, TFT_FRAMEWDT+1, 1, WA_CENTER }, 140, false, MAX_WIDTH-2, 0, 1, SCROLLTIME };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, 64-7, 1, WA_LEFT }, 140, false, MAX_WIDTH, 0, 1, SCROLLTIME };
const ScrollConfig weatherConf    PROGMEM = {{ 0, 64-12, 1, WA_LEFT }, 140, true, DSP_WIDTH/2+2, 0, 1, SCROLLTIME };

/* BACKGROUNGC9106DS  */                 /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig metaBGConf       PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 18, false };
const FillConfig volbarConf       PROGMEM = {{ 0, 64-1-1-1, 0, WA_LEFT }, DSP_WIDTH, 3, true };
const FillConfig playlBGConf      PROGMEM = {{ 0, 26, 0, WA_LEFT }, DSP_WIDTH, 12, false };
const FillConfig bufferbarConf    PROGMEM = {{ 0, 63, 0, WA_LEFT }, DSP_WIDTH, 1, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 64-8, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT+20, 64-11-10, 1, WA_LEFT };
//const WidgetConfig voltxtConf     PROGMEM = { 32, 108, 1, WA_RIGHT };
const WidgetConfig iptxtConf      PROGMEM = { 0, 64-12, 1, WA_LEFT };
const WidgetConfig rssiConf       PROGMEM = { 0, 64-11-10, 1, WA_LEFT };
const WidgetConfig batteryConf    PROGMEM = { (DSP_WIDTH*2)/3+2, 64-11-10, 1, WA_LEFT };
const WidgetConfig numConf        PROGMEM = { TFT_FRAMEWDT, 57, 0, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { 0, 18, 1, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { 0, 26, 1, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { 0, 37, 1, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { 0, 45, 1, WA_CENTER };
//const WidgetConfig clockConf      PROGMEM = { 6, 34, 2, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { 0, 57, 0, WA_RIGHT };
const WidgetConfig vuConf         PROGMEM = { 1, 28, 1, WA_LEFT };

const WidgetConfig bootWdtConf    PROGMEM = { 0, 64-8*2-5, 1, WA_CENTER };
const ProgressConfig bootPrgConf  PROGMEM = { 90, 10, 4 };

/* BANDS  */                             /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
const VUBandsConfig bandsConf     PROGMEM = { 12, 48, 2, 1, 8, 3 };

/* STRINGS  */
const char numtxtFmt[]            PROGMEM = "%d";
const char rssiFmt[]              PROGMEM = "%d";
const char iptxtFmt[]             PROGMEM = "\010 %s";
//const char voltxtFmt[]            PROGMEM = "%d";
const char batteryRangeFmt[][8]   PROGMEM = { "\013 %d%%", "\014 %d%%", "\015 %d%%" };
const char bitrateFmt[]           PROGMEM = "%d kBs";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig clockMove        PROGMEM = { 0, 0, -1 };
const MoveConfig weatherMove      PROGMEM = { 0, 0, -1 };
const MoveConfig weatherMoveVU    PROGMEM = { 0, 0, -1 };

#endif

