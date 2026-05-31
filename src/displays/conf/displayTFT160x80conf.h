/*************************************************************************************
    TFT160x80 displays configuration file.
*************************************************************************************/

#ifndef displayTFT160x80conf_h
#define displayTFT160x80conf_h


#define TFT_FRAMEWDT    1
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#define HIDE_IP
#define HIDE_TITLE2
#define HIDE_VOL

#define BOOTLOGOTOP     5

/* SCROLLS  */                           /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 2, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 3, 30 };
const ScrollConfig title1Conf     PROGMEM = {{ TFT_FRAMEWDT, 19, 1, WA_LEFT }, 140, true, MAX_WIDTH-6*3-4, 5000, 3, 30 };
//const ScrollConfig title2Conf     PROGMEM = {{ TFT_FRAMEWDT, 36, 1, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 2, 30 };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 33, 1, WA_LEFT }, 140, true, MAX_WIDTH, 0, 3, 30 };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 2, WA_CENTER }, 140, false, MAX_WIDTH, 0, 3, 30 };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, 80-TFT_FRAMEWDT-8, 1, WA_LEFT }, 140, false, MAX_WIDTH, 0, 3, 30 };
const ScrollConfig weatherConf    PROGMEM = {{ TFT_FRAMEWDT, 80-13, 1, WA_LEFT }, 140, true, MAX_WIDTH-6*3, 0, 3, 30 }; // ??????!!

/* BACKGROUNGC9106DS  */                 /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig metaBGConf       PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 16, false };
const FillConfig metaBGConfInv    PROGMEM = {{ 0, 16, 0, WA_LEFT }, DSP_WIDTH, 1, false };
const FillConfig volbarConf       PROGMEM = {{ TFT_FRAMEWDT, 80-1-1-2, 0, WA_LEFT }, MAX_WIDTH, 2, false };
const FillConfig playlBGConf      PROGMEM = {{ 0, 30, 0, WA_LEFT }, DSP_WIDTH, 20, false };
const FillConfig bufferbarConf    PROGMEM = {{ 0, 79, 0, WA_LEFT }, DSP_WIDTH, 1, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 65, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT, 19, 1, WA_RIGHT };
//const WidgetConfig voltxtConf     PROGMEM = { 32, 108, 1, WA_RIGHT };
//const WidgetConfig iptxtConf      PROGMEM = { TFT_FRAMEWDT, 108, 1, WA_LEFT };
const WidgetConfig rssiConf       PROGMEM = { TFT_FRAMEWDT, 80-13, 1, WA_RIGHT };
const WidgetConfig batteryConf    PROGMEM = { (DSP_WIDTH*2)/3+2, 80-13, 1, WA_LEFT };
const WidgetConfig numConf        PROGMEM = { 0, 29+32, 0, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { 0, 20, 1, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { 0, 32, 1, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { 0, 46, 1, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { 0, 58, 1, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { 20, 29+34, 0, WA_RIGHT };
const WidgetConfig vuConf         PROGMEM = { 1, 28, 1, WA_LEFT };

const WidgetConfig bootWdtConf    PROGMEM = { 0, 50, 1, WA_CENTER };
const ProgressConfig bootPrgConf  PROGMEM = { 90, 14, 4 };

/* BANDS  */                             /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
const VUBandsConfig bandsConf     PROGMEM = { 12, 48, 2, 1, 8, 2 };

/* STRINGS  */
const char numtxtFmt[]            PROGMEM = "%d";
const char rssiFmt[]              PROGMEM = "%d";
//const char iptxtFmt[]             PROGMEM = "%s";
//const char voltxtFmt[]            PROGMEM = "%d";
const char batteryRangeFmt[][8]   PROGMEM = { "\013 %d%%", "\014 %d%%", "\017 %d%%" };
const char bitrateFmt[]           PROGMEM = "%d";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig clockMove        PROGMEM = { 6, 29+34, 0};
const MoveConfig weatherMove      PROGMEM = { TFT_FRAMEWDT, 80-13, MAX_WIDTH-6*3-30 };
const MoveConfig weatherMoveVU    PROGMEM = { 30, 80-13, MAX_WIDTH-6*3-30 };

#endif
