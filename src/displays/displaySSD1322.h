#ifndef displaySSD1322_h
#define displaySSD1322_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "../libraries/SSD1322/SSD1322.h"
#include "bootlogo/110x32mono.h"
#include "ehfonts/font35.h"

typedef GFXcanvas1 Canvas;
typedef Jamis_SSD1322 yoDisplay;

#include "tools/commongfx.h"

#if __has_include("conf/displaySSD1322conf_custom.h")
  #include "conf/displaySSD1322conf_custom.h"
#else
  #include "conf/displaySSD1322conf.h"
#endif

#endif
