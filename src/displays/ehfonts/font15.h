#ifndef dsfont_h
#define dsfont_h

#if CLOCKFONT == YO_MONO
  #include "DS_DIGI/DS_DIGI15pt7b_mono.h"
#elif CLOCKFONT == YO_CLASSIC
  #include "DS_DIGI/DS_DIGI15pt7b.h"
#elif CLOCKFONT == CHUNKY6_PX
  #include "Chunky6/Chunky6_15_px.h"
#elif CLOCKFONT == CHUNKY6
  #include "Chunky6/Chunky6_15.h"
#endif

#endif
