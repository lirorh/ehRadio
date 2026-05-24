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

#if __has_include("conf/displayST7789conf_custom.h")
  #include "conf/displayST7789conf_custom.h"
#else
  #if DSP_MODEL==DSP_ST7789
    #include "conf/displayST7789conf.h"
  #elif DSP_MODEL==DSP_ST7789_76
    #include "conf/displayST7789_76conf.h"
  #else
    #include "conf/displayST7789_240conf.h"
  #endif
#endif

#endif
