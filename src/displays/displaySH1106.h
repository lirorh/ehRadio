#ifndef displaySH1106_h
#define displaySH1106_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "bootlogo/110x32mono.h"
#include "ehfonts/font15.h"

typedef GFXcanvas1 Canvas;

#if DSP_MODEL==DSP_SH1106
  typedef Adafruit_SH1106G yoDisplay;
#else
  typedef Adafruit_SH1107 yoDisplay;
#endif

#include "tools/commongfx.h"

#if __has_include("conf/displaySH1106conf_custom.h")
  #include "conf/displaySH1106conf_custom.h"
#else
  #include "conf/displaySH1106conf.h"
#endif

#endif
