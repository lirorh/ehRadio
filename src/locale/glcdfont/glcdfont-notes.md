Please note when adding special characters to strings in the conf files,
escape sequences must be used but the convention is to use octal, not hex.
But the Glyph Creator tool only provides decimal (and unicode hex),
so here's a quick lookup table:

| Dec | Octal |  Hex  |
|-----|-------|-------|
|  1  |  \001 |  \x01 |
|  2  |  \002 |  \x02 |
| ... |   ... |   ... |
|  7  |  \007 |  \x07 |
|  8  |  \010 |  \x08 |
|  9  |  \011 |  \x09 |
| 10  |  \012 |  \x0A |
| 11  |  \012 |  \x0B |
| 12  |  \013 |  \x0C |
| 13  |  \014 |  \x0D |
| 14  |  \015 |  \x0E |
| 15  |  \016 |  \x0F |
| 16  |  \017 |  \xA0 |
| 17  |  \020 |  \xA1 |
| 18  |  \021 |  \xA2 |
| 19  |  \022 |  \xA3 |
| 20  |  \022 |  \xA4 |
| 21  |  \023 |  \xA5 |
| 22  |  \024 |  \xA6 |
| 23  |  \025 |  \xA7 |
| 24  |  \026 |  \xA8 |
| 25  |  \027 |  \xA9 |
| 26  |  \030 |  \xAA |
| 27  |  \031 |  \xAB |
| 28  |  \032 |  \xAC |
| 29  |  \033 |  \xAD |
| 30  |  \034 |  \xAE |
| 31  |  \035 |  \xAF |

Decimal can't be used.  Hex is "Greedy" so will suck up numbers next to it.
ie. "\x14Doobie" might try to use "14D" as the hex number...
That's why we use Octal.
