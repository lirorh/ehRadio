#ifndef dspconf_h
#define dspconf_h
#pragma once

// ==========================================================================
// dspconf.h — Centralized display configuration file selection
// ==========================================================================
// Selects the appropriate conf/display*conf.h based on:
//   DSP_WIDTH, DSP_HEIGHT  — resolution (set in options.h, overridable in myoptions.h)
//   DSP_LCD / DSP_OLED     — display category (set in dspcore.h)
//   DSP_MODEL              — for special cases (GC9A01A round, Nokia, ST7920)
//
// TFT (PSFBUFFER) is the default fallback when neither DSP_LCD nor DSP_OLED
// is defined.
// ==========================================================================

#if defined(DSP_LCD)
  // ── Character LCDs ──────────────────────────────────────
  #if DSP_WIDTH==20 && DSP_HEIGHT==4
    #include "conf/displayLCD20x4conf.h"
  #elif DSP_WIDTH==16 && DSP_HEIGHT==2
    #include "conf/displayLCD16x2conf.h"
  #else
    #error "Unsupported LCD resolution! Must be 20x4 or 16x2 (should have been set by displayLC1602.h)"
  #endif

#elif defined(DSP_OLED)
  // ── OLED / monochrome displays ──────────────────────────
  #if DSP_MODEL==DSP_NOKIA5110
    #include "conf/displayLCD84x48conf.h"
  #elif DSP_MODEL==DSP_ST7920
    #include "conf/displayLCD128x64conf.h"
  #elif DSP_WIDTH==256 && DSP_HEIGHT==64
    #include "conf/displayOLED256x64conf.h"
  #elif DSP_WIDTH==128 && DSP_HEIGHT==128
    #include "conf/displayOLED128x128conf.h"
  #elif DSP_WIDTH==128 && DSP_HEIGHT==64
    #include "conf/displayOLED128x64conf.h"
  #elif DSP_WIDTH==128 && DSP_HEIGHT==32
    #include "conf/displayOLED128x32conf.h"
  #else
    #error "Unsupported OLED resolution! Must be 256x64, 128x128, 128x64, or 128x32."
  #endif

#else
  // ── TFT / color displays (default) ──────────────────────
  #if DSP_WIDTH==480 && DSP_HEIGHT==320
    #include "conf/displayTFT480x320conf.h"
  #elif DSP_WIDTH==320 && DSP_HEIGHT==240
    #include "conf/displayTFT320x240conf.h"
  #elif DSP_WIDTH==284 && DSP_HEIGHT==76
    #include "conf/displayTFT284x76conf.h"
  #elif DSP_WIDTH==240 && DSP_HEIGHT==240
    #if DSP_MODEL==DSP_GC9A01A
      #include "conf/displayTFT240x240roundconf.h"
    #else
      #include "conf/displayTFT240x240conf.h"
    #endif
  #elif DSP_WIDTH==220 && DSP_HEIGHT==176
    #include "conf/displayTFT220x176conf.h"
  #elif DSP_WIDTH==160 && DSP_HEIGHT==128
    #include "conf/displayTFT160x128conf.h"
  #elif DSP_WIDTH==160 && DSP_HEIGHT==80
    #include "conf/displayTFT160x80conf.h"
  #elif DSP_WIDTH==128 && DSP_HEIGHT==128
    #include "conf/displayTFT128x128conf.h"
  #else
    #error "Unsupported TFT resolution! Must be 480x320, 320x240, 284x76, 240x240, 220x176, 160x128, 160x80, or 128x128."
  #endif
#endif

#endif // dspconf_h
