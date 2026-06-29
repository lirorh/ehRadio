/*************************************************************************************
    TFT220x176 displays configuration file.
*************************************************************************************/

#ifndef displayTFT220x176conf_h
#define displayTFT220x176conf_h

#define TFT_FRAMEWDT    4
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#if BITRATE_FULL
  #define TITLE_FIX     28
#else
  #define TITLE_FIX     0
#endif
#define BOOTLOGOTOP     28

/* SCROLLS  */                           /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 2, WA_LEFT }, 140, true, DSP_WIDTH+10, SCROLLDELAY, 2, SCROLLTIME*7/4 };
const ScrollConfig title1Conf     PROGMEM = {{ TFT_FRAMEWDT, 28, 1, WA_LEFT }, 140, true, MAX_WIDTH-TITLE_FIX, SCROLLDELAY, 1, SCROLLTIME };
const ScrollConfig title2Conf     PROGMEM = {{ TFT_FRAMEWDT, 40, 1, WA_LEFT }, 140, true, MAX_WIDTH-TITLE_FIX, SCROLLDELAY, 1, SCROLLTIME };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 80, 2, WA_LEFT }, 140, true, DSP_WIDTH+10, SCROLLDELAY/5, 2, SCROLLTIME };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 2, WA_CENTER }, 140, false, MAX_WIDTH, 0, 2, SCROLLTIME };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, DSP_HEIGHT-TFT_FRAMEWDT-16, 2, WA_LEFT }, 140, false, DSP_WIDTH+10, 0, 2, SCROLLTIME };
const ScrollConfig weatherConf    PROGMEM = {{ TFT_FRAMEWDT, 56, 2, WA_LEFT }, 140, true, DSP_WIDTH+10, 0, 2, SCROLLTIME };

/* BACKGROUNDS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig metaBGConf       PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 22, false };
const FillConfig metaBGConfInv    PROGMEM = {{ 0, 22, 0, WA_LEFT }, DSP_WIDTH, 1, false };
const FillConfig volbarConf       PROGMEM = {{ TFT_FRAMEWDT, DSP_HEIGHT-TFT_FRAMEWDT-4, 0, WA_LEFT }, MAX_WIDTH, 4, true };
const FillConfig playlBGConf      PROGMEM = {{ 0, 76, 0, WA_LEFT }, DSP_WIDTH, 22, false };
const FillConfig bufferbarConf    PROGMEM = {{ 0, DSP_HEIGHT-1, 0, WA_LEFT }, DSP_WIDTH, 1, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 150, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT+6, DSP_HEIGHT-TFT_FRAMEWDT-14-14, 1, WA_RIGHT };
const WidgetConfig voltxtConf     PROGMEM = { TFT_FRAMEWDT, DSP_HEIGHT-TFT_FRAMEWDT-14, 1, WA_LEFT };
const WidgetConfig batteryConf    PROGMEM = { (DSP_WIDTH*2)/3+2, DSP_HEIGHT-TFT_FRAMEWDT-14, 1, WA_LEFT };
const WidgetConfig iptxtConf      PROGMEM = { TFT_FRAMEWDT, DSP_HEIGHT-TFT_FRAMEWDT-14, 1, WA_CENTER };
const WidgetConfig rssiConf       PROGMEM = { TFT_FRAMEWDT, DSP_HEIGHT-TFT_FRAMEWDT-14, 1, WA_RIGHT };
const WidgetConfig numConf        PROGMEM = { 0, 110, 0, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { TFT_FRAMEWDT, 38, 2, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { TFT_FRAMEWDT, 62, 2, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { TFT_FRAMEWDT, 102, 2, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { TFT_FRAMEWDT, 126, 2, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { TFT_FRAMEWDT*3, 130, 0, WA_RIGHT };
const WidgetConfig vuConf         PROGMEM = { TFT_FRAMEWDT, 58, 1, WA_LEFT };

const WidgetConfig bootWdtConf    PROGMEM = { 0, 130, 1, WA_CENTER };
const ProgressConfig bootPrgConf  PROGMEM = { 90, 14, 4 };
const BitrateConfig fullbitrateConf PROGMEM = {{DSP_WIDTH-TFT_FRAMEWDT-21, 25, 1, WA_LEFT}, 22 };

/* BANDS  */                             /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
const VUBandsConfig bandsConf     PROGMEM = { 19, 90, 2, 2, 10, 2 };

/* STRINGS  */
const char numtxtFmt[]            PROGMEM = "%d";
const char rssiFmt[]              PROGMEM = "WiFi %d";
const char iptxtFmt[]             PROGMEM = "\010 %s";
const char voltxtFmt[]            PROGMEM = "\023\025%d";
const char batteryRangeFmt[][8]   PROGMEM = { "\013 %d%%", "\014 %d%%", "\017 %d%%" };
const char bitrateFmt[]           PROGMEM = "%d kBs";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig clockMove        PROGMEM = { TFT_FRAMEWDT*2, 130, 0 };
const MoveConfig weatherMove      PROGMEM = { TFT_FRAMEWDT, 64, DSP_WIDTH+10 };
const MoveConfig weatherMoveVU    PROGMEM = { TFT_FRAMEWDT+46, 58, DSP_WIDTH+10-46 };

#endif

