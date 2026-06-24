/*************************************************************************************
    LCD128x64 displays configuration file.
*************************************************************************************/

#ifndef displayLCD128x64conf_h
#define displayLCD128x64conf_h

#define TFT_FRAMEWDT    1
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#define HIDE_BUFFERBAR
#define HIDE_VOL
#define HIDE_VU

#define BOOTLOGOTOP     8

/* SCROLLS  */                           /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT+1, TFT_FRAMEWDT+1, 1, WA_LEFT }, 140, true, MAX_WIDTH-2, SCROLLDELAY, 5, SCROLLTIME };
const ScrollConfig title1Conf     PROGMEM = {{ 0, 13, 1, WA_LEFT }, 140, true, DSP_WIDTH-6*4, SCROLLDELAY, 5, SCROLLTIME };
const ScrollConfig title2Conf     PROGMEM = {{ 0, 22, 1, WA_LEFT }, 140, true, DSP_WIDTH, SCROLLDELAY, 5, SCROLLTIME };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 30, 1, WA_LEFT }, 140, true, MAX_WIDTH, SCROLLDELAY/5, 5, SCROLLTIME };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT+1, TFT_FRAMEWDT+1, 1, WA_CENTER }, 140, false, MAX_WIDTH-2, 0, 5, SCROLLTIME };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, 64-7, 1, WA_LEFT }, 140, false, MAX_WIDTH, 0, 5, SCROLLTIME };
const ScrollConfig weatherConf    PROGMEM = {{ 0, 64-11, 1, WA_LEFT }, 140, true, DSP_WIDTH-6*4, 0, 5, SCROLLTIME };

/* BACKGROUNGC9106DS  */                 /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig metaBGConf       PROGMEM = {{ 0, 0,  0, WA_LEFT }, DSP_WIDTH, 11, false };
const FillConfig metaBGConfInv    PROGMEM = {{ 0, 11, 0, WA_LEFT }, DSP_WIDTH, 1,  false };
const FillConfig volbarConf       PROGMEM = {{ 0, 64-1-1-1, 0, WA_LEFT }, DSP_WIDTH, 3, true };
const FillConfig playlBGConf      PROGMEM = {{ 0, 26, 0, WA_LEFT }, DSP_WIDTH, 12, false };
const FillConfig bufferbarConf    PROGMEM = {{ 0, 63, 0, WA_LEFT }, DSP_WIDTH, 1, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 64-8, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { 0, 13, 1, WA_RIGHT };
//const WidgetConfig voltxtConf     PROGMEM = { 32, 108, 1, WA_RIGHT };
const WidgetConfig iptxtConf      PROGMEM = { 0, 64-11, 1, WA_LEFT };
const WidgetConfig rssiConf       PROGMEM = { 0, 64-11, 1, WA_RIGHT };
const WidgetConfig batteryConf    PROGMEM = { (DSP_WIDTH*2)/3+2, 64-11, 1, WA_LEFT };
const WidgetConfig numConf        PROGMEM = { 0, 26, 0, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { 0, 18, 1, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { 0, 26, 1, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { 0, 37, 1, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { 0, 45, 1, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { 0, 34, 0, WA_CENTER };
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
const char batteryRangeFmt[][8]   PROGMEM = { "\013 %d%%", "\014 %d%%", "\017 %d%%" };
const char bitrateFmt[]           PROGMEM = "%d";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig clockMove        PROGMEM = { 0, 0, -1 };
const MoveConfig weatherMove      PROGMEM = { 0, 0, -1 };
const MoveConfig weatherMoveVU    PROGMEM = { 0, 0, -1 };

#endif

