#ifndef displayN5110_h
#define displayN5110_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "ehfonts/TinyFont5.h"
#include "ehfonts/TinyFont6.h"
#include "bootlogo/36x32mono.h"

typedef GFXcanvas1 Canvas;
typedef Adafruit_PCD8544 yoDisplay;

#include "tools/commongfx.h"

#if __has_include("conf/displayN5110conf_custom.h")
  #include "conf/displayN5110conf_custom.h"
#else
  #include "conf/displayN5110conf.h"
#endif

#endif
