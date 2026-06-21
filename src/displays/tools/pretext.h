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

// Count Unicode characters (not bytes) in a UTF-8 string.
uint16_t utf8_strlen(const char *s);

// Return a pointer to the byte position of the Nth character in a UTF-8 string.
// If charIndex exceeds the string length, returns a pointer to the null terminator.
const char* utf8_offset(const char *s, uint16_t charIndex);

#endif
