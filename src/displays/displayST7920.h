#ifndef displayST7920_h
#define displayST7920_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "../libraries/ST7920/ST7920.h"
#include "bootlogo/110x32mono.h"

typedef GFXcanvas1 Canvas;
typedef ST7920 yoDisplay;

#include "tools/commongfx.h"

#if __has_include("conf/displayST7920conf_custom.h")
  #include "conf/displayST7920conf_custom.h"
#else
  #include "conf/displayST7920conf.h"
#endif

#endif
