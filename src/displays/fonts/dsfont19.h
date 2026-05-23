#ifndef dsfont_h
#define dsfont_h



#if CLOCKFONT == YO_MONO
  #include "DS_DIGI/DS_DIGI15pt7b_mono.h"
#elif CLOCKFONT == YO_CLASSIC
  #include "DS_DIGI/DS_DIGI15pt7b.h"
#else
  #error dsfont19 included... use #define CLOCKFONT YO_MONO or YO_CLASSIC to use a supported font
#endif

#endif
