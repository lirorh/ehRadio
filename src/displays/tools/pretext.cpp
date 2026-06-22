#include "pretext.h"

// Pre-render text processing pipeline.  Add new preprocessors here.
// No-op unless PRETEXT_FOLDACCENT or PRETEXT_ALLCAPS is defined.
uint16_t preText(uint16_t cp, const GFXfont *font) {
  #if defined(PRETEXT_FOLDACCENT) || defined(PRETEXT_ALLCAPS)
    #ifdef PRETEXT_ALLCAPS
      cp = allCaps(cp);
    #endif
    #ifdef PRETEXT_FOLDACCENT
      cp = foldAccent(cp, font);
    #endif
    return cp;
  #else
    return cp;  // no-op when no preprocessors enabled
  #endif
}

// Convert lowercase letters to uppercase (Latin + Cyrillic).
// Used only when PRETEXT_ALLCAPS is defined (font testing).
uint16_t allCaps(uint16_t cp) {
  // ASCII a-z → A-Z
  if (cp >= 'a' && cp <= 'z') return cp - 32;
  // Latin-1 Supplement lowercase accented → uppercase
  if (cp >= 0x00E0 && cp <= 0x00F6 && cp != 0x00F7) return cp - 32;
  if (cp == 0x00F8) return 0x00D8;  // ø → Ø
  if (cp >= 0x00F9 && cp <= 0x00FE) return cp - 32;
  if (cp == 0x00FF) return 0x0178;  // ÿ → Ÿ
  // Latin Extended-A lowercase → uppercase
  if (cp >= 0x0101 && cp <= 0x017E && (cp & 1)) return cp - 1;  // odd = lowercase
  // Cyrillic lowercase а-я → А-Я (U+0430–U+044F → U+0410–U+042F)
  if (cp >= 0x0430 && cp <= 0x044F) return cp - 32;
  // Cyrillic lowercase ё → Ё
  if (cp == 0x0451) return 0x0401;
  // Cyrillic Extended lowercase → uppercase
  if (cp >= 0x0460 && cp <= 0x0481 && (cp & 1)) return cp - 1;
  if (cp >= 0x048C && cp <= 0x04BF && (cp & 1)) return cp - 1;
  if (cp >= 0x04D0 && cp <= 0x04FF && (cp & 1)) return cp - 1;
  return cp;  // not lowercase, return unchanged
}

// Strip diacritical marks from Latin-1 and Latin Extended-A characters.
// Only applies if the codepoint has NO glyph in the font (w==0 or h==0).
// Returns the folded codepoint, or cp unchanged if the glyph exists,
// or 0 if no fallback is available.
uint16_t foldAccent(uint16_t cp, const GFXfont *font) {
  // Check if glyph exists in font — if yes, no folding needed
  if (cp >= pgm_read_word(&font->first) && cp <= pgm_read_word(&font->last)) {
    uint16_t idx = cp - pgm_read_word(&font->first);
    if (pgm_read_byte(&font->glyph[idx].width) > 0 &&
        pgm_read_byte(&font->glyph[idx].height) > 0)
      return cp;  // glyph exists, keep as-is
  }
  // Glyph not in font or empty slot — try accent folding
  // Latin-1 Supplement (U+00C0–U+00FF) → ASCII
  if (cp >= 0x00C0 && cp <= 0x00C5) return 'A';
  if (cp == 0x00C7) return 'C';
  if (cp >= 0x00C8 && cp <= 0x00CB) return 'E';
  if (cp >= 0x00CC && cp <= 0x00CF) return 'I';
  if (cp == 0x00D1) return 'N';
  if (cp >= 0x00D2 && cp <= 0x00D6) return 'O';
  if (cp == 0x00D8) return 'O';
  if (cp >= 0x00D9 && cp <= 0x00DC) return 'U';
  if (cp == 0x00DD) return 'Y';
  if (cp >= 0x00E0 && cp <= 0x00E5) return 'a';
  if (cp == 0x00E7) return 'c';
  if (cp >= 0x00E8 && cp <= 0x00EB) return 'e';
  if (cp >= 0x00EC && cp <= 0x00EF) return 'i';
  if (cp == 0x00F1) return 'n';
  if (cp >= 0x00F2 && cp <= 0x00F6) return 'o';
  if (cp == 0x00F8) return 'o';
  if (cp >= 0x00F9 && cp <= 0x00FC) return 'u';
  if (cp == 0x00FD) return 'y';
  if (cp == 0x00FF) return 'y';
  // Latin Extended-A (U+0100–U+017F) → ASCII
  if (cp >= 0x0100 && cp <= 0x0105) return 'A';
  if (cp >= 0x0106 && cp <= 0x010D) return 'C';
  if (cp >= 0x010E && cp <= 0x0111) return 'D';
  if (cp >= 0x0112 && cp <= 0x011B) return 'E';
  if (cp >= 0x011C && cp <= 0x0123) return 'G';
  if (cp >= 0x0124 && cp <= 0x0127) return 'H';
  if (cp >= 0x0128 && cp <= 0x0131) return 'I';
  if (cp >= 0x0134 && cp <= 0x0135) return 'J';
  if (cp >= 0x0136 && cp <= 0x0138) return 'K';
  if (cp >= 0x0139 && cp <= 0x0142) return 'L';
  if (cp >= 0x0143 && cp <= 0x014B) return 'N';
  if (cp >= 0x014C && cp <= 0x0151) return 'O';
  if (cp >= 0x0154 && cp <= 0x0159) return 'R';
  if (cp >= 0x015A && cp <= 0x0161) return 'S';
  if (cp >= 0x0162 && cp <= 0x0167) return 'T';
  if (cp >= 0x0168 && cp <= 0x0173) return 'U';
  if (cp >= 0x0174 && cp <= 0x0175) return 'W';
  if (cp >= 0x0176 && cp <= 0x0178) return 'Y';
  if (cp >= 0x0179 && cp <= 0x017E) return 'Z';
  return 0;
}

// Count Unicode characters (not bytes) in a UTF-8 string.
uint16_t utf8_strlen(const char *s) {
  uint16_t count = 0;
  while (*s) {
    if ((*s & 0xC0) != 0x80) count++; // not a continuation byte
    s++;
  }
  return count;
}

// Return byte pointer to the Nth Unicode character in a UTF-8 string.
const char* utf8_offset(const char *s, uint16_t charIndex) {
  uint16_t idx = 0;
  while (*s && idx < charIndex) {
    if ((*s & 0xC0) != 0x80) idx++; // not a continuation byte
    s++;
  }
  return s;
}
