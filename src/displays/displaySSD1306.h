#ifndef displaySSD1306_h
#define displaySSD1306_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if DSP_MODEL==DSP_SSD1306
  #include "bootlogo/110x32mono.h"
#endif

#if DSP_MODEL==DSP_SSD1306
  #include "ehfonts/font15.h"
#endif

typedef GFXcanvas1 Canvas;
typedef Adafruit_SSD1306 yoDisplay;

#include "tools/commongfx.h"

#if __has_include("conf/displaySSD1306conf_custom.h")
  #include "conf/displaySSD1306conf_custom.h"
#else
  #if DSP_MODEL==DSP_SSD1306
    #include "conf/displaySSD1306conf.h"
  #else
    #include "conf/displaySSD1306x32conf.h"
  #endif
#endif

#endif
