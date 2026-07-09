/*************************************************************************************
    OLED128x128 displays configuration file.
*************************************************************************************/

#ifndef displayOLED128x128conf_h
#define displayOLED128x128conf_h

#define TFT_FRAMEWDT    4
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#define HIDE_BUFFERBAR
#define HIDE_VU

#define BOOTLOGOTOP     34

/* SCROLLS  */                           /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 2, WA_LEFT }, 140, true, MAX_WIDTH, SCROLLDELAY, 2, SCROLLTIME*7/4 };
const ScrollConfig title1Conf     PROGMEM = {{ TFT_FRAMEWDT, 26, 1, WA_LEFT }, 140, true, MAX_WIDTH, SCROLLDELAY, 1, SCROLLTIME };
const ScrollConfig title2Conf     PROGMEM = {{ TFT_FRAMEWDT, 36, 1, WA_LEFT }, 140, true, MAX_WIDTH-6*3-4, SCROLLDELAY, 1, SCROLLTIME };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 56, 1, WA_LEFT }, 140, true, MAX_WIDTH, SCROLLDELAY/5, 1, SCROLLTIME };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 2, WA_CENTER }, 140, false, MAX_WIDTH, 0, 2, SCROLLTIME };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, 128-TFT_FRAMEWDT-8, 1, WA_LEFT }, 140, false, MAX_WIDTH, 0, 1, SCROLLTIME };
const ScrollConfig weatherConf    PROGMEM = {{ TFT_FRAMEWDT, 42, 1, WA_LEFT }, 140, true, MAX_WIDTH, 0, 1, SCROLLTIME };

/* BACKGROUNDS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig metaBGConf       PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 22, false };
const FillConfig metaBGConfInv    PROGMEM = {{ 0, 22, 0, WA_LEFT }, DSP_WIDTH, 1, false };
const FillConfig volbarConf       PROGMEM = {{ TFT_FRAMEWDT, 118, 0, WA_LEFT }, MAX_WIDTH-6*3-4, 5, true };
const FillConfig playlBGConf      PROGMEM = {{ 0, 52, 0, WA_LEFT }, DSP_WIDTH, 22, false };
const FillConfig bufferbarConf    PROGMEM = {{ 0, 127, 0, WA_LEFT }, DSP_WIDTH, 1, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 110, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT, 36, 1, WA_RIGHT };
//const WidgetConfig voltxtConf     PROGMEM = { 32, 108, 1, WA_RIGHT };
const WidgetConfig voltxtConf     PROGMEM = { TFT_FRAMEWDT, 128-10, 1, WA_RIGHT };
const WidgetConfig iptxtConf      PROGMEM = { TFT_FRAMEWDT, 108, 1, WA_LEFT };
const WidgetConfig rssiConf       PROGMEM = { TFT_FRAMEWDT, 108, 1, WA_RIGHT };
const WidgetConfig batteryConf    PROGMEM = { (DSP_WIDTH*2)/3+2, 108, 1, WA_LEFT };
const WidgetConfig numConf        PROGMEM = { 0, 86, 0, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { 0, 40, 1, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { 0, 54, 1, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { 0, 74, 1, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { 0, 88, 1, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { 0, 94, 0, WA_RIGHT };
const WidgetConfig vuConf         PROGMEM = { TFT_FRAMEWDT, 99, 1, WA_CENTER };

const WidgetConfig bootWdtConf    PROGMEM = { 0, 90, 1, WA_CENTER };
const ProgressConfig bootPrgConf  PROGMEM = { 90, 14, 4 };

/* BANDS  */                             /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
const VUBandsConfig bandsConf     PROGMEM = { 56, 7, 2, 1, 8, 2 };

/* STRINGS  */
const char numtxtFmt[]            PROGMEM = "%d";
const char rssiFmt[]              PROGMEM = "%d";
const char iptxtFmt[]             PROGMEM = "\010 %s";
const char voltxtFmt[]            PROGMEM = "%d";
const char batteryRangeFmt[][8]   PROGMEM = { "\013 %d%%", "\014 %d%%", "\015 %d%%" };
const char bitrateFmt[]           PROGMEM = "%d";

/* MOVES  */                             /* { left, top, width (0 - auto, -1 - lock } */
const MoveConfig clockMove        PROGMEM = { 0, 94, -1 };
const MoveConfig weatherMove      PROGMEM = { TFT_FRAMEWDT, 48, 122 };
const MoveConfig weatherMoveVU    PROGMEM = { TFT_FRAMEWDT, 48, 122 };

#endif

