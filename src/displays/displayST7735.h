#ifndef displayST7735_h
#define displayST7735_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "bootlogo/62x40.h"
#include "ehfonts/font35.h"

typedef GFXcanvas16 Canvas;
typedef Adafruit_ST7735 yoDisplay;

#include "tools/commongfx.h"

#if DTYPE==INITR_MINI160x80
  #include "conf/displayTFT160x80conf.h"
#elif DTYPE==INITR_144GREENTAB
  #include "conf/displayTFT128x128conf.h"
#else
  #include "conf/displayTFT160x128conf.h"
#endif
#endif
