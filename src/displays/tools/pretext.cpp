#include "pretext.h"

// Strip diacritical marks from Latin-1 and Latin Extended-A characters.
// Returns the base ASCII codepoint, or 0 if no mapping exists.
uint16_t foldAccent(uint16_t cp) {
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
