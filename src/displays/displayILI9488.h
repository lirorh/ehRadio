#ifndef displayILI9488_h
#define displayILI9488_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "../libraries/ILI9488/ILI9486_SPI.h"
#if defined(BIG_BOOT_LOGO) || BIG_BOOT_LOGO //true
  #include "bootlogo/198x128.h"
#else
  #include "bootlogo/99x64.h"
#endif
#include "ehfonts/font70.h"

typedef GFXcanvas16 Canvas;
typedef ILI9486_SPI yoDisplay;

#include "tools/commongfx.h"

#include "conf/displayTFT480x320conf.h"

#define ILI9488_SLPIN     0x10
#define ILI9488_SLPOUT    0x11
#define ILI9488_DISPOFF   0x28
#define ILI9488_DISPON    0x29

#endif
