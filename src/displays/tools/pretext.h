#ifndef pretext_h
#define pretext_h

#include <stdint.h>
#include <Adafruit_GFX.h>   // GFXfont, GFXglyph, pgm_read_*

// Pre-render text processing pipeline.
// Currently only does accent folding, but can chain other preprocessors.
// Returns the processed codepoint (may be unchanged if no mapping needed),
// or 0 if the character should be silently dropped.
uint16_t preText(uint16_t cp, const GFXfont *font);
uint16_t foldAccent(uint16_t cp, const GFXfont *font);

#endif
