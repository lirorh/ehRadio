#ifndef dsfont_h
#define dsfont_h

#if CLOCKFONT == YO_MONO
  #include "DS_DIGI/DS_DIGI28pt7b_mono.h"
#elif CLOCKFONT == YO_CLASSIC
  #include "DS_DIGI/DS_DIGI28pt7b.h"
#elif CLOCKFONT == CHUNKY6_PX
  #include "Chunky6/Chunky6_35_px.h"
#elif CLOCKFONT == CHUNKY6
  #include "Chunky6/Chunky6_35.h"
#endif

#endif
