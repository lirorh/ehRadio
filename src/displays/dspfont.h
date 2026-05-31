#ifndef dspfont_h
#define dspfont_h
#pragma once

// ==========================================================================
// dspfont.h — Centralized font, bootlogo, and TIME_SIZE selection
// ==========================================================================
// Selects bootlogo, clock font, and TIME_SIZE based on:
//   DSP_WIDTH, DSP_HEIGHT  — resolution (set in options.h, overridable in myoptions.h)
//   DSP_MODEL              — for outlier overrides (ST7920, SSD1322)
//   BIG_BOOT_LOGO          — optional, for 480px-wide displays
//   CLOCKFONT              — for chunky-font TIME_SIZE override
//   DSP_LCD                — character LCDs get TIME_SIZE=1, no bootlogo/font
// ==========================================================================

// ── TIME_SIZE ───────────────────────────────────────────────────────────
// Outlier overrides (checked before generic resolution rules)
#if DSP_MODEL==DSP_ST7920
  #define TIME_SIZE 2
#elif DSP_MODEL==DSP_SSD1322
  #define TIME_SIZE 35

// Generic resolution-based defaults
#elif DSP_WIDTH >= 480
  #define TIME_SIZE 70
#elif (DSP_WIDTH==320 && DSP_HEIGHT==240) || (DSP_WIDTH==240 && DSP_HEIGHT==240)
  #define TIME_SIZE 52
#elif DSP_WIDTH==284 && DSP_HEIGHT==76
  #define TIME_SIZE 35
#elif DSP_WIDTH==256
  #define TIME_SIZE 35
#elif DSP_WIDTH==220
  #define TIME_SIZE 35
#elif DSP_WIDTH==160
  #define TIME_SIZE 35
#elif DSP_WIDTH==128 && DSP_HEIGHT==128
  #define TIME_SIZE 35
#elif DSP_WIDTH==128 && DSP_HEIGHT==64
  #define TIME_SIZE 15
#elif DSP_WIDTH==128 && DSP_HEIGHT==32
  #define TIME_SIZE 1
#elif DSP_WIDTH==84
  #define TIME_SIZE 15
#elif defined(DSP_LCD)
  #define TIME_SIZE 1
#else
  #define TIME_SIZE 1
#endif

// Chunky-font override — when using YO_MONO or YO_CLASSIC on small OLEDs,
// revert to GLCD font size (moved from dspcore.h)
#if TIME_SIZE == 15 && (CLOCKFONT == YO_MONO || CLOCKFONT == YO_CLASSIC)
  #undef TIME_SIZE
  #define TIME_SIZE 2
#endif

// ── BOOTLOGO ────────────────────────────────────────────────────────────
#if DSP_WIDTH >= 480
  #if defined(BIG_BOOT_LOGO) && BIG_BOOT_LOGO
    #include "bootlogo/198x128.h"
  #else
    #include "bootlogo/99x64.h"
  #endif
#elif (DSP_WIDTH==320 && DSP_HEIGHT==240) || (DSP_WIDTH==240 && DSP_HEIGHT==240)
  #include "bootlogo/99x64.h"
#elif DSP_WIDTH==220
  #include "bootlogo/99x64.h"
#elif DSP_WIDTH==160 && DSP_HEIGHT==128
  #include "bootlogo/99x64.h"
#elif DSP_WIDTH==160 && DSP_HEIGHT==80
  #include "bootlogo/62x40.h"
#elif DSP_WIDTH==284 && DSP_HEIGHT==76
  #include "bootlogo/62x40.h"
#elif DSP_WIDTH==128 && DSP_HEIGHT==128
  #include "bootlogo/62x40.h"
#elif DSP_WIDTH==128 && DSP_HEIGHT==64
  #include "bootlogo/110x32mono.h"
#elif DSP_WIDTH==256
  #include "bootlogo/110x32mono.h"
#elif DSP_WIDTH==84
  #include "bootlogo/36x32mono.h"
// 128x32, character LCDs: no bootlogo
#endif

// ── CLOCK FONT ──────────────────────────────────────────────────────────
#if DSP_WIDTH >= 480
  #include "ehfonts/font70.h"
#elif (DSP_WIDTH==320 && DSP_HEIGHT==240) || (DSP_WIDTH==240 && DSP_HEIGHT==240)
  #include "ehfonts/font52.h"
#elif DSP_WIDTH==220
  #include "ehfonts/font35.h"
#elif DSP_WIDTH==160
  #include "ehfonts/font35.h"
#elif DSP_WIDTH==284
  #include "ehfonts/font35.h"
#elif DSP_WIDTH==128 && DSP_HEIGHT==128
  #include "ehfonts/font35.h"
#elif DSP_WIDTH==256
  #include "ehfonts/font35.h"
#elif DSP_WIDTH==128 && DSP_HEIGHT==64
  // ST7920 uses GLCD font (no include); OLEDs use font15
  #if DSP_MODEL!=DSP_ST7920
    #include "ehfonts/font15.h"
  #endif
#elif DSP_WIDTH==84
  #include "ehfonts/TinyFont5.h"
  #include "ehfonts/TinyFont6.h"
// 128x32, character LCDs: use GLCD font (no include)
#endif

#endif // dspfont_h
