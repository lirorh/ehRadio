#ifndef displayST7789_h
#define displayST7789_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#if DSP_MODEL==DSP_ST7789_76
  #include "bootlogo/62x40.h"
  #include "ehfonts/font35.h"
#else
  #include "bootlogo/99x64.h"
  #include "ehfonts/font52.h"
#endif

typedef GFXcanvas16 Canvas;
typedef Adafruit_ST7789 yoDisplay;

#include "tools/commongfx.h"

#if DSP_MODEL==DSP_ST7789
  #include "conf/displayTFT320x240conf.h"
#elif DSP_MODEL==DSP_ST7789_76
  #include "conf/displayTFT284x76conf.h"
#else
  #include "conf/displayTFT240x240conf.h"
#endif

#endif
