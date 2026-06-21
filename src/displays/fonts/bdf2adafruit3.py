#!/usr/bin/env python3
"""
bdf2adafruit3.py — Convert BDF bitmap font to Adafruit GFXfont header (Python 3)
An adaptation of the bdf2adafruit py2 script included in Adafruit GFX Library

Usage:
    py bdf2adafruit3.py MatrixChunky8.bdf 0x0020 0x04FF -o MatrixChunky8.h
    py bdf2adafruit3.py MatrixLight8.bdf 0x20 0x04FF -o MatrixLight8.h

The optional first/last args limit the codepoint range (default: auto-detect).
GFXfont uses a contiguous glyph array indexed by (codepoint - first), so the
range should be kept as tight as possible to avoid flash waste.

Output: A .h file with bitmap data, glyph descriptors, and GFXfont struct.

Copyright (c) 2026 Trip5
SPDX-License-Identifier: GPL-3.0-only
"""

import sys
import re


# ---------------------------------------------------------------------------
# BDF parser
# ---------------------------------------------------------------------------

class Glyph:
    __slots__ = ('encoding', 'name', 'advance', 'width', 'height',
                 'xoffs', 'yoffs', 'rows')
    def __init__(self):
        self.encoding = -1
        self.name = ''
        self.advance = 0
        self.width = 0
        self.height = 0
        self.xoffs = 0
        self.yoffs = 0
        self.rows = []


def parse_bdf(filepath: str):
    """Parse a BDF file and return (glyphs, ascent, descent)."""
    glyphs = {}
    ascent = 8
    descent = 0
    current = None
    bitmap_mode = False

    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        for line in f:
            line = line.rstrip('\n\r')
            if not line:
                continue

            if line.startswith('FONT_ASCENT'):
                ascent = int(line.split()[1])
            elif line.startswith('FONT_DESCENT'):
                descent = int(line.split()[1])

            if line.startswith('STARTCHAR'):
                current = Glyph()
                current.name = line.split(None, 1)[1]
                bitmap_mode = False
                continue

            if current is None:
                continue

            if line.startswith('ENDCHAR'):
                if current.encoding >= 0:
                    glyphs[current.encoding] = current
                current = None
                bitmap_mode = False
                continue

            if line.startswith('ENCODING'):
                current.encoding = int(line.split()[1])
            elif line.startswith('DWIDTH'):
                current.advance = int(line.split()[1])
            elif line.startswith('BBX'):
                parts = line.split()
                current.width = int(parts[1])
                current.height = int(parts[2])
                current.xoffs = int(parts[3])
                current.yoffs = int(parts[4])
            elif line.startswith('BITMAP'):
                bitmap_mode = True
            elif bitmap_mode:
                current.rows.append(int(line.strip(), 16))

    return glyphs, ascent, descent


def is_empty_glyph(g: Glyph) -> bool:
    """Check if glyph has no visible pixels."""
    return all(r == 0 for r in g.rows) or len(g.rows) == 0


# ---------------------------------------------------------------------------
# Bitmap packing
# ---------------------------------------------------------------------------

MAX_ROWS = 8  # Force all glyphs to 8 rows to match glcdfont line height

def pack_bitmap(glyph: Glyph, skip_top: int = 0, max_rows: int = MAX_ROWS):
    """Pack glyph bitmap into byte array (1bpp, MSB first, L-to-R, T-to-B).
    If the glyph is taller than max_rows, keep only the bottom max_rows rows
    (discard empty top rows).  skip_top rows are excluded from the top."""
    packed = []
    bit_acc = 0
    bit_count = 0

    rows = glyph.rows
    if len(rows) > max_rows:
        # Drop top rows, keep bottom max_rows
        skip_top = len(rows) - max_rows
        rows = rows[skip_top:]

    for row_val in rows:
        for col in range(glyph.width):
            # BDF stores pixel data LEFT-ALIGNED in each row byte.
            # Column 0 = MSB (bit 7), column 1 = bit 6, etc.
            mask = 0x80 >> col
            bit = 1 if (row_val & mask) else 0
            bit_acc = (bit_acc << 1) | bit
            bit_count += 1
            if bit_count == 8:
                packed.append(bit_acc)
                bit_acc = 0
                bit_count = 0

    if bit_count > 0:
        bit_acc <<= (8 - bit_count)
        packed.append(bit_acc)

    return packed


# ---------------------------------------------------------------------------
# Output generation
# ---------------------------------------------------------------------------

NULL_GLYPH_DESC = (0, 0, 0, 0, 0, 0)  # offset, width, height, advance, xOff, yOff


def generate_header(glyphs_dict, first_cp, last_cp, ascent, descent,
                    font_name: str):
    """Generate the complete GFXfont .h file.
    All glyphs are forced to MAX_ROWS height with yOffset=-MAX_ROWS,
    i.e. no baseline/descent — all pixels sit above the cursor like glcdfont."""
    prefix = re.sub(r'[^a-zA-Z0-9]', '_', font_name)
    if not prefix[0].isalpha():
        prefix = 'F_' + prefix

    y_advance = MAX_ROWS  # always 8
    range_size = last_cp - first_cp + 1

    lines = []
    lines.append('#pragma once')
    lines.append('#include <Adafruit_GFX.h>')
    lines.append('')

    # ------------------------------------------------------------------
    # Build glyph array: one entry per codepoint in range
    # ------------------------------------------------------------------
    all_bitmaps = []
    glyph_descriptors = []  # list of (offset, width, height, advance, xOff, yOff)

    for cp in range(first_cp, last_cp + 1):
        g = glyphs_dict.get(cp)
        if g is None:
            glyph_descriptors.append(NULL_GLYPH_DESC)
        elif is_empty_glyph(g):
            glyph_descriptors.append(
                (0, 0, 0, g.advance, 0, 0)
            )
        else:
            offset = len(all_bitmaps)
            # Clip to MAX_ROWS, keeping BOTTOM rows (crop empty top)
            rows = g.rows[-MAX_ROWS:] if len(g.rows) > MAX_ROWS else g.rows
            # Pad with empty rows if shorter than MAX_ROWS
            while len(rows) < MAX_ROWS:
                rows.append(0)
            # Pack these rows
            packed = []
            bit_acc = 0
            bit_count = 0
            for row_val in rows:
                for col in range(g.width):
                    mask = 0x80 >> col
                    bit = 1 if (row_val & mask) else 0
                    bit_acc = (bit_acc << 1) | bit
                    bit_count += 1
                    if bit_count == 8:
                        packed.append(bit_acc)
                        bit_acc = 0
                        bit_count = 0
            if bit_count > 0:
                bit_acc <<= (8 - bit_count)
                packed.append(bit_acc)
            all_bitmaps.extend(packed)
            # Always yOffset=-MAX_ROWS: all pixels above cursor
            glyph_descriptors.append(
                (offset, g.width, MAX_ROWS, g.advance, g.xoffs, -MAX_ROWS)
            )

    # ------------------------------------------------------------------
    # Write bitmap data
    # ------------------------------------------------------------------
    lines.append(f'const uint8_t {prefix}Bitmaps[] PROGMEM = {{')
    for i in range(0, len(all_bitmaps), 12):
        chunk = all_bitmaps[i:i + 12]
        hex_vals = ', '.join(f'0x{b:02X}' for b in chunk)
        lines.append(f'    {hex_vals},')
    lines.append('};')
    lines.append('')

    # ------------------------------------------------------------------
    # Write glyph descriptors
    # ------------------------------------------------------------------
    lines.append(f'const GFXglyph {prefix}Glyphs[] PROGMEM = {{')
    for desc, cp in zip(glyph_descriptors, range(first_cp, last_cp + 1)):
        offset, w, h, adv, xo, yo = desc
        g = glyphs_dict.get(cp)
        name = g.name if g and not is_empty_glyph(g) else '(empty)'
        lines.append(
            f'    {{ {offset}, {w}, {h}, {adv}, {xo}, {yo} }},'
            f' /* 0x{cp:04X} {name} */'
        )
    lines.append('};')
    lines.append('')

    # ------------------------------------------------------------------
    # GFXfont struct
    # ------------------------------------------------------------------
    lines.append(f'const GFXfont {prefix} PROGMEM = {{')
    lines.append(f'    (uint8_t *){prefix}Bitmaps,')
    lines.append(f'    (GFXglyph *){prefix}Glyphs,')
    lines.append(f'    0x{first_cp:04X},  /* first */')
    lines.append(f'    0x{last_cp:04X},   /* last */')
    lines.append(f'    {y_advance}         /* yAdvance */')
    lines.append('};')
    lines.append('')

    # Stats
    non_empty = sum(1 for d in glyph_descriptors if d != NULL_GLYPH_DESC)
    lines.append(
        f'// {non_empty} glyphs in range 0x{first_cp:04X}-0x{last_cp:04X}'
        f' ({range_size} slots), {len(all_bitmaps)} bytes bitmap data,'
        f' {range_size * 8} bytes glyph table, yAdvance={y_advance}'
    )

    return '\n'.join(lines)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <font.bdf> [first_cp last_cp] [-o output.h]',
              file=sys.stderr)
        sys.exit(1)

    bdf_path = sys.argv[1]

    # Check for -o output file argument
    output_path = None
    if '-o' in sys.argv:
        idx = sys.argv.index('-o')
        if idx + 1 < len(sys.argv):
            output_path = sys.argv[idx + 1]
            # Remove -o and its argument from argv so they don't confuse range parsing
            sys.argv = sys.argv[:idx] + sys.argv[idx+2:]

    glyphs_dict, ascent, descent = parse_bdf(bdf_path)
    print(f'Parsed {len(glyphs_dict)} glyphs total, ascent={ascent}, descent={descent}',
          file=sys.stderr)

    if not glyphs_dict:
        print('ERROR: No glyphs found in BDF file!', file=sys.stderr)
        sys.exit(1)

    # Determine font name from BDF
    font_name = 'CustomFont'
    with open(bdf_path, 'r', encoding='utf-8', errors='replace') as f:
        for line in f:
            if line.startswith('FAMILY_NAME'):
                font_name = line.split('"')[1] if '"' in line else \
                            line.split(None, 1)[1].strip()
                break

    # Determine codepoint range
    non_empty = sorted(cp for cp, g in glyphs_dict.items() if not is_empty_glyph(g))
    print(f'{len(non_empty)} non-empty glyphs', file=sys.stderr)

    if len(sys.argv) >= 4:
        # User-specified range
        first_cp = int(sys.argv[2], 16) if sys.argv[2].startswith('0x') else int(sys.argv[2])
        last_cp = int(sys.argv[3], 16) if sys.argv[3].startswith('0x') else int(sys.argv[3])
        # Clip to actual data
        first_cp = max(first_cp, min(non_empty))
        last_cp = min(last_cp, max(non_empty))
    else:
        # Auto-detect: use the min/max of non-empty glyphs
        first_cp = min(non_empty)
        last_cp = max(non_empty)

    range_size = last_cp - first_cp + 1
    est_flash = range_size * 8  # 8 bytes per GFXglyph entry

    print(f'Font name: {font_name}', file=sys.stderr)
    print(f'Range: 0x{first_cp:04X} — 0x{last_cp:04X} ({range_size} slots)',
          file=sys.stderr)
    print(f'Estimated glyph table: {est_flash} bytes ({est_flash/1024:.1f} KB)',
          file=sys.stderr)

    if est_flash > 80000:
        print('WARNING: Glyph table is very large! Consider specifying a tighter',
              file=sys.stderr)
        print('  range, e.g.: py bdf2adafruit3.py font.bdf 0x0020 0x04FF',
              file=sys.stderr)

    output = generate_header(glyphs_dict, first_cp, last_cp, ascent, descent,
                             font_name)

    if output_path:
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(output)
        print(f'Wrote to {output_path}', file=sys.stderr)
    else:
        print(output)


if __name__ == '__main__':
    main()
