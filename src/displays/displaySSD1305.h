#ifndef displaySSD1305_h
#define displaySSD1305_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include "bootlogo/110x32mono.h"
#include "ehfonts/font15.h"

typedef GFXcanvas1 Canvas;
typedef Adafruit_SSD1305 yoDisplay;

#include "tools/commongfx.h"

#if __has_include("conf/displaySSD1305conf_custom.h")
  #include "conf/displaySSD1305conf_custom.h"
#else
  #include "conf/displaySSD1305conf.h"
#endif

#endif
