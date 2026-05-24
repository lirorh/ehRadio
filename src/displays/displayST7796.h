#ifndef displayST7796_h
#define displayST7796_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "../libraries/Adafruit_ST7796S/Adafruit_ST7796S_kbv.h"

#if defined(BIG_BOOT_LOGO) || BIG_BOOT_LOGO //true
  #include "bootlogo/198x128.h"
#else
  #include "bootlogo/99x64.h"
#endif

#include "ehfonts/font70.h"

typedef GFXcanvas16 Canvas;
typedef Adafruit_ST7796S_kbv yoDisplay;

#include "tools/commongfx.h"

#include "conf/displayTFT480x320conf.h"

#endif
