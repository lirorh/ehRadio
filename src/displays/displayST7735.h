#ifndef displayST7735_h
#define displayST7735_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

typedef GFXcanvas16 Canvas;
typedef Adafruit_ST7735 yoDisplay;

// DTYPE fully determines panel dimensions — no override possible.
#undef DSP_WIDTH
#undef DSP_HEIGHT
#if DTYPE==INITR_MINI160x80
  #define DSP_WIDTH  160
  #define DSP_HEIGHT 80
#elif DTYPE==INITR_144GREENTAB
  #define DSP_WIDTH  128
  #define DSP_HEIGHT 128
#else
  #define DSP_WIDTH  160
  #define DSP_HEIGHT 128
#endif

#include "dspfont.h"

#include "tools/commongfx.h"

#include "dspconf.h"
#endif
