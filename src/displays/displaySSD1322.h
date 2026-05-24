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

#include "conf/displayOLED256x64conf.h"

#endif
