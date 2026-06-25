# ehRadio — Languages, Fonts & Localization

This document explains the localization pipeline: how language selection flows from a `myoptions.h` define through locale strings and the GFXfont renderer to the display.

---

## Table of Contents

1. [Overview](#overview)
2. [Configuration Cascade](#configuration-cascade)
3. [Picking a Language — `DSP_LANGUAGE`](#picking-a-language--dsp_language)
4. [Locale Files (`displayL10n_*.h`)](#locale-files-displayl10n_h)
5. [The Include Chain (`l10n.h`)](#the-include-chain-l10nh)
6. [Custom Locale Override](#custom-locale-override)
7. [Display Font (`dspfont.h`)](#display-font-dspfonth)
8. [Text Rendering Pipeline](#text-rendering-pipeline)
9. [Weather Language (`weatherLang`)](#weather-language-weatherlang)
10. [How to Add a New Language](#how-to-add-a-new-language)
11. [WebUI i18n](#webui-i18n)
12. [Developer Tools](#developer-tools)

---

## Overview

The display uses a **Unicode GFXfont** (Adafruit GFXfont format, converted from BDF), selected via the `DISPLAYFONT` macro in `dspfont.h`. The font contains 400+ glyphs covering Latin, Cyrillic, Greek, and other scripts — it can render these characters directly without transliteration or codepage switching.

The active language controls:
- UI strings (day names, month names, wind directions, weather labels) from `displayL10n_*.h`
- The language code sent to the OpenWeather API
- Optional all-caps conversion for languages with no lowercase distinction in the font

Separately, the **WebUI** (served from the device over Wi-Fi) has its own runtime i18n layer: translated strings are loaded from JSON files on the device filesystem.

---

## Configuration Cascade

Settings are applied in this order — later entries override earlier ones:

```
src/core/options.h          ← built-in system defaults (DO NOT EDIT)
         ↓
myoptions.h                 ← your hardware & locale overrides
         ↓
mytheme.h                   ← colour / UI overrides (optional)
```

All language configuration belongs in **`myoptions.h`**. Language selection is **compile‑time only**.

---

## Picking a Language — `DSP_LANGUAGE`

In `myoptions.h`, set:

```cpp
#define DSP_LANGUAGE_de_DE
```

If a `DSP_LANGUAGE_*` is not defined, it defaults to `DSP_LANGUAGE_en_US`.

Each language entry in `src/core/locale.h` selects:
- The locale header file to include
- The `weatherLang` API code for OpenWeather
- Whether `allCaps()` is applied (for scripts that are uppercase-only in the font)

The full list of supported languages is in `src/core/locale.h`.

---

## Locale Files (`displayL10n_*.h`)

Each locale file lives in `src/locale/` and is named using IETF BCP 47 format:

```
src/locale/displayL10n_en_US.h
src/locale/displayL10n_ru_RU.h
src/locale/displayL10n_uk_UA.h
...
```

Every locale file defines the same set of `PROGMEM` string constants in the `LANG` namespace:

| Constant group | Example values |
|---|---|
| Short day names | `mon`, `tue`, `wed`, `thu`, `fri`, `sat`, `sun` |
| Full day names | `monday`, `tuesday`, `wednesday`, … |
| Month names | `jan`, `feb`, `mar`, … `dec` |
| Wind direction strings | `wn_N`, `wn_NE`, `wn_E`, … `wn_NNW` |
| Weather condition labels | `wc_thunder`, `wc_rain`, `wc_snow`, `wc_clear`, etc. |
| OpenWeather language code | `weatherLang[]` — the API `lang` parameter |

All strings are stored in flash (`PROGMEM`) to conserve RAM.

---

## The Include Chain (`l10n.h`)

`src/displays/tools/l10n.h` is the single include point for locale strings:

1. Checks `DSP_LANGUAGE_*` with an `#if / #elif` ladder and sets `L10N_INCLUDE` to the matching locale file path.
2. Checks whether `src/locale/displayL10n_custom.h` exists — if so, it is included **instead** of the auto-selected locale (see below).
3. Wraps `L10N_INCLUDE` inside `namespace LANG { ... }` so locale strings don't pollute the global namespace.

All display code that needs localized strings includes `l10n.h` and accesses strings as `LANG::mon`, `LANG::weatherLang`, etc.

---

## Custom Locale Override

To modify UI strings without touching built-in locale files, create:

```
src/locale/displayL10n_custom.h
```

This file completely replaces the auto-selected locale — the compiler will not include the standard `displayL10n_*.h`. Copy the locale you want to base yours on and edit from there.

Add it to your `.gitignore` so it persists across project updates.

---

## Display Font (`dspfont.h`)

The display font is selected at compile time via the `DISPLAYFONT` macro, resolved in `src/displays/dspfont.h`:

| `DISPLAYFONT` value | Font file | Description |
|---|---|---|
| `MATRIXLIGHT` (default) | `MatrixLight8x6.h` | 6×8 pixel, ~400 glyphs |
| `MATRIXCHUNKY` | `MatrixChunky8x6.h` | 6×8 bold variant |
| `X11` | `UnixX11_6x9.h` | 6×9, 1421 glyphs (largest coverage) |

Override in `myoptions.h`:
```cpp
#define DISPLAYFONT MATRIXCHUNKY
```

The selected font is assigned to the `DisplayFont` symbol and used by `_writeGlyph()` in `src/displays/tools/commongfx.h` for all text rendering. It supports Latin, Cyrillic, Greek, and extended punctuation — no codepage switching or glcdfont replacement is needed.

Clock fonts are separate — they live in `src/displays/clockfonts/` and are selected via the `CLOCKFONT` macro.

---

## Text Rendering Pipeline

All text rendering goes through `DspCore::write(uint8_t)` → `_writeGlyph(uint16_t cp)` in `src/displays/tools/commongfx.h`.

### Per-character processing

1. **UTF-8 decode** — `write()` accumulates bytes into a full codepoint.
2. **Icon check** — codepoints 0x01–0x1F render from `ICON_TABLE[]`.
3. **Space** — advances cursor by the font's `xAdvance`.
4. **Clock font dispatch** — if a special clock font is active (`gfxFont != NULL && gfxFont != &DisplayFont`), delegates to `Adafruit_GFX::write()`.
5. **Preprocessing** — `preText(cp, f)` applies:
   - `allCaps()` if the locale requires uppercase-only display
   - `foldAccent()` for accent-stripping fallback
6. **Glyph lookup** — searches `DisplayFont` for the codepoint. If found, renders the glyph bitmap (foreground + background fill). If not found, tries `foldAccent()` recursion; if still unmapped, advances cursor by `xAdvance` (blank space).

### Key rendering invariants

- All glyph rendering uses `&DisplayFont` (the Unicode GFXfont), NOT the built-in 256-slot glcdfont.
- `startWrite()`/`endWrite()` wrap icon and glyph rendering blocks (required by Adafruit SPI TFT drivers; no-ops on I2C OLEDs).
- Glyph columns beyond `xAdvance` are bit-consumed but not rendered — prevents bleed into adjacent characters.
- `resetUTF8()` must be called before every `print()` in scroll widgets to prevent orphan UTF-8 bytes from corrupting the first glyph of the next frame.

---

## Weather Language (`weatherLang`)

Each locale file defines `weatherLang[]` — a PROGMEM string sent as the `lang` parameter to the OpenWeather API. This controls the language of weather condition text returned by the API (e.g., "Clouds" vs "Облачно").

---

## How to Add a New Language

1. **Copy an existing locale file:**
   ```
   src/locale/displayL10n_en_US.h  →  src/locale/displayL10n_xx_XX.h
   ```

2. **Translate all string constants** (day names, month names, weather labels, wind directions).

3. **Add an `#elif` branch** in `src/core/locale.h` with the locale include, weather language code, and `allCaps` setting. Keep alphabetically ordered.

4. **Update `src/locale/l10n.md`** with the new entry.

5. **Add a WebUI locale JSON file** in `src/locale/webui/`. Copy `src/locale/webui/en_US.json`, rename to `{code}.json`, and translate all values. The build script deploys it to SPIFFS.

6. **Set `DSP_LANGUAGE_xx_XX`** in `myoptions.h` and build.
   Optionally define `WEBUI_LANGUAGE` if the WebUI should use a different locale than the display.

---

## WebUI i18n

The WebUI has its own runtime translation layer, independent of the firmware display locale.

### How it works

1. **Language detection** — the server serves `locale.json` from SPIFFS matching the preferred locale code. If `en_US` is selected (and the HTML contains English), no JSON is fetched — built-in text is used.

2. **`t(key, ...args)` helper** — looks up `key` in the loaded `i18n` object. Positional placeholders `{0}`, `{1}` are substituted with extra arguments.

3. **`applyI18n()` DOM walker** — queries every `[data-i18n]` element and replaces its text content (or `value`/`placeholder` for inputs) with `t(key)`.

4. **`data-i18n` attributes** — every translatable label in the HTML files carries a `data-i18n="key"` attribute with English fallback text as the element's default content.

5. **Dynamic strings** — JS-generated text (OTA progress, update buttons, battery status) calls `t()` directly.

6. **Battery status** — the firmware sends battery info as an English string; `script.js` parses and rebuilds it using `t()` keys.

7. **CSS knob labels** — toggle switch text is set via CSS custom properties from `t('lbl_off')` / `t('lbl_on')`.

### JSON locale files

WebUI locale JSONs live in `src/locale/webui/`. The build script (`platformio_pre_gzip_www.py`) copies the selected JSON to `data/www/locale/` before building the SPIFFS image.

| File | Purpose |
|---|---|
| `src/locale/webui/en_US.json` | Master key reference (not deployed — English is hardcoded) |
| `src/locale/webui/ru_RU.json` | Russian translation example |

To add a language: copy `en_US.json`, rename to `<code>.json`, translate all values, run `make_data_www_locales_json.py` to regenerate the locale list.

### Key categories

| Prefix | Examples | Covers |
|---|---|---|
| `ttl_` | `ttl_settings`, `ttl_playlist_editor` | Page & section titles |
| `lbl_` | `lbl_flip_screen`, `lbl_volume` | Input / toggle labels |
| `btn_` | `btn_save`, `btn_reset` | Button labels |
| `msg_` | `msg_ota_complete`, `msg_no_update` | Status messages / placeholders |
| `unit_` | `unit_dbm`, `unit_kbits` | Units of measurement |

---

## Developer Tools

### Python tools in `src/locale/`

| Tool | Purpose |
|---|---|
| `scan_www_check_json.py` | Checks `.html`/`.js` files against a locale `.json` — can auto-translate, add, sort, and delete missing keys |
| `hardcode_locale_to_webui.py` | Replaces all text in `data/www` files using a locale `.json`; updates `#define HARDCODED_WEBUI_LOCALE` in `locale.h` |
| `make_data_www_locales_json.py` | Generates `locales.json` for the WebUI locale dropdown |

### Translation assistance

| `scan_trans_deepl.py` | Auto-translation via DeepL API |
| `scan_trans_deepl.md` | Setup instructions for DeepL |

Usage: `py scan_trans_deepl.py en_US de_DE Hello` → `Hallo`

To add another translation API, create a `scan_trans_<api>.py` script matching the same command-line and output structure. `scan_www_check_json.py` automatically discovers any `scan_trans_*.py` that has a matching `scan_trans_<api>.key` file.

### Font conversion

The BDF→GFXfont converter is `src/displays/fonts/bdf2adafruit3.py`. It converts `.bdf` bitmap font files into Adafruit GFXfont format (`.h` header with PROGMEM bitmaps, glyph table, and font struct).

---

## Legacy: GLCD Font System (Removed)

Prior versions used a 256-slot `glcdfont` system with codepage-based font swapping:

- `glcdfont_Latin.c` — Latin extended glyphs in slots 0x80–0xFF
- `glcdfont_Cyrillic.c` — Cyrillic glyphs in the same slots
- `platformio_pre_replace_font.py` — swapped the `.c` file at build time based on `L10N_CP_LATIN` / `L10N_CP_CYRILLIC`
- `utf8To()`, `shouldPreserveChar()`, `canRenderNative()` — filtered characters to what the active codepage could display

This system has been replaced by the Unicode GFXfont pipeline described above. The old `glcdfont/` directory, `utf8To.*`, `utf8_common.*`, `utf8Latin.*`, and `utf8Cyrillic.*` files are retained for reference but are no longer compiled into builds.
