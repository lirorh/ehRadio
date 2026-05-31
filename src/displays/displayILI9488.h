#ifndef displayILI9488_h
#define displayILI9488_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "../libraries/ILI9488/ILI9486_SPI.h"

typedef GFXcanvas16 Canvas;
typedef ILI9486_SPI yoDisplay;

#include "dspfont.h"

#include "tools/commongfx.h"

#include "dspconf.h"

#define ILI9488_SLPIN     0x10
#define ILI9488_SLPOUT    0x11
#define ILI9488_DISPOFF   0x28
#define ILI9488_DISPON    0x29

#endif
