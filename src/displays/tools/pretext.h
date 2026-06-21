#ifndef pretext_h
#define pretext_h

#include <stdint.h>

// Strip diacritical marks from Latin-1 and Latin Extended-A characters.
// Returns the base ASCII codepoint, or 0 if no mapping exists.
uint16_t foldAccent(uint16_t cp);

#endif
