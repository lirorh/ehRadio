#pragma once
#include <Arduino.h>
#include <pgmspace.h>

// ==========================================================================
// icons.h — Icon glyphs extracted from the classic glcdfont
// ==========================================================================
// Each icon is 5 bytes (5 columns wide × 8 rows tall).
// Binary format: MSB = top row, LSB = bottom row.
//  @ = pixel ON    . = pixel OFF
// ==========================================================================

// \001 (dec 1) — RSSI bar 00__  (used in display.cpp RSSI rendering)
static const uint8_t ICON_RSSI_00[] PROGMEM = {
    0b01000000,  // .@......
    0b01000000,  // .@......
    0b00000000,  // ........
    0b01000000,  // .@......
    0b01000000,  // .@......
};

// \002 (dec 2) — RSSI bar __00  (used in display.cpp RSSI rendering)
static const uint8_t ICON_RSSI__00[] PROGMEM = {
    0b01000000,  // .@......
    0b01000000,  // .@......
    0b00000000,  // ........
    0b01000000,  // .@......
    0b01000000,  // .@......
};

// \003 (dec 3) — RSSI bar 10__  (used in display.cpp RSSI rendering)
static const uint8_t ICON_RSSI_10[] PROGMEM = {
    0b01100000,  // .@@.....
    0b01100000,  // .@@.....
    0b00000000,  // ........
    0b01000000,  // .@......
    0b01000000,  // .@......
};

// \004 (dec 4) — RSSI bar 11__  (used in display.cpp RSSI rendering)
static const uint8_t ICON_RSSI_11[] PROGMEM = {
    0b01100000,  // .@@.....
    0b01100000,  // .@@.....
    0b00000000,  // ........
    0b01110000,  // .@@@....
    0b01110000,  // .@@@....
};

// \005 (dec 5) — RSSI bar __10  (used in display.cpp RSSI rendering)
static const uint8_t ICON_RSSI__10[] PROGMEM = {
    0b01111000,  // .@@@@...
    0b01111000,  // .@@@@...
    0b00000000,  // ........
    0b01000000,  // .@......
    0b01000000,  // .@......
};

// \006 (dec 6) — RSSI bar __11  (used in display.cpp RSSI rendering)
static const uint8_t ICON_RSSI__11[] PROGMEM = {
    0b01111000,  // .@@@@...
    0b01111000,  // .@@@@...
    0b00000000,  // ........
    0b01111100,  // .@@@@@..
    0b01111100,  // .@@@@@..
};

// \007 (dec 7) — Weather divider / bullet  (used in network.cpp weather strings)
static const uint8_t ICON_WEATHER_DIV[] PROGMEM = {
    0b00000000,  // ........
    0b00011100,  // ...@@@..
    0b00011100,  // ...@@@..
    0b00011100,  // ...@@@..
    0b00000000,  // ........
};

// \010 (dec 8) — IP address icon  (used in conf files: iptxtFmt)
static const uint8_t ICON_IP[] PROGMEM = {
    0b00100111,  // ..@..@@@
    0b00100010,  // ..@...@.
    0b00100010,  // ..@...@.
    0b00100010,  // ..@...@.
    0b01110010,  // .@@@..@.
};

// \013 (dec 11) — Battery LOW (0-25%)  (used in conf files: batteryRangeFmt[0])
static const uint8_t ICON_BATTERY_LOW[] PROGMEM = {
    0b01111110,  // .@@@@@@.
    0b01000011,  // .@....@@
    0b01000001,  // .@.....@
    0b01000011,  // .@....@@
    0b01111110,  // .@@@@@@.
};

// \014 (dec 12) — Battery MID (25-75%)  (used in conf files: batteryRangeFmt[1])
static const uint8_t ICON_BATTERY_MID[] PROGMEM = {
    0b01111110,  // .@@@@@@.
    0b01100011,  // .@@...@@
    0b01110001,  // .@@@...@
    0b01111011,  // .@@@@.@@
    0b01111110,  // .@@@@@@.
};

// \016 (dec 14) — Note icon  (unused in current code)
static const uint8_t ICON_NOTE[] PROGMEM = {
    0b01100000,  // .@@.....
    0b01111111,  // .@@@@@@@
    0b00000101,  // .....@.@
    0b00110101,  // ..@@.@.@
    0b00111111,  // ..@@@@@@
};

// \017 (dec 15) — Battery HIGH (75-100%)  (used in conf files: batteryRangeFmt[2])
static const uint8_t ICON_BATTERY_HIGH[] PROGMEM = {
    0b01111110,  // .@@@@@@.
    0b01111111,  // .@@@@@@@
    0b01111111,  // .@@@@@@@
    0b01111111,  // .@@@@@@@
    0b01111110,  // .@@@@@@.
};

// \020 (dec 16) — Play / Next icon  (used in display.cpp as progress bar fill)
static const uint8_t ICON_PLAY[] PROGMEM = {
    0b00000000,  // ........
    0b01111111,  // .@@@@@@@
    0b00111110,  // ..@@@@@.
    0b00011100,  // ...@@@..
    0b00001000,  // ....@...
};

// \021 (dec 17) — Previous icon  (used in display.cpp)
static const uint8_t ICON_PREV[] PROGMEM = {
    0b00001000,  // ....@...
    0b00011100,  // ...@@@..
    0b00111110,  // ..@@@@@.
    0b01111111,  // .@@@@@@@
    0b00000000,  // ........
};

// \023 (dec 19) — Speaker icon  (used in conf files: voltxtFmt)
static const uint8_t ICON_SPEAKER[] PROGMEM = {
    0b00000000,  // ........
    0b00000000,  // ........
    0b00011000,  // ...@@...
    0b00111100,  // ..@@@@..
    0b01111110,  // .@@@@@@.
};

// \024 (dec 20) — Volume 25%  (unused in current code)
static const uint8_t ICON_VOL_25[] PROGMEM = {
    0b00011000,  // ...@@...
    0b00000000,  // ........
    0b00000000,  // ........
    0b00000000,  // ........
    0b00000000,  // ........
};

// \025 (dec 21) — Volume 50%  (used in conf files: voltxtFmt)
static const uint8_t ICON_VOL_50[] PROGMEM = {
    0b00011000,  // ...@@...
    0b01000010,  // .@....@.
    0b00111100,  // ..@@@@..
    0b00000000,  // ........
    0b00000000,  // ........
};

// \026 (dec 22) — Volume 100%  (unused in current code)
static const uint8_t ICON_VOL_100[] PROGMEM = {
    0b00011000,  // ...@@...
    0b01000010,  // .@....@.
    0b00111100,  // ..@@@@..
    0b01000010,  // .@....@.
    0b00111100,  // ..@@@@..
};

// \030 (dec 24) — Charging icon  (referenced in display.cpp, commented out)
static const uint8_t ICON_CHARGING[] PROGMEM = {
    0b00001000,  // ....@...
    0b00000100,  // .....@..
    0b01111110,  // .@@@@@@.
    0b00000100,  // .....@..
    0b00001000,  // ....@...
};

// \031 (dec 25) — Discharging icon  (referenced in display.cpp, commented out)
static const uint8_t ICON_DISCHARGING[] PROGMEM = {
    0b00010000,  // ...@....
    0b00100000,  // ..@.....
    0b01111110,  // .@@@@@@.
    0b00100000,  // ..@.....
    0b00010000,  // ...@....
};

// \034 (dec 28) — Pause icon  (used in display.cpp)
static const uint8_t ICON_PAUSE[] PROGMEM = {
    0b01111111,  // .@@@@@@@
    0b01111111,  // .@@@@@@@
    0b00000000,  // ........
    0b01111111,  // .@@@@@@@
    0b01111111,  // .@@@@@@@
};

// \035 (dec 29) — List icon  (used in display.cpp)
static const uint8_t ICON_LIST[] PROGMEM = {
    0b01010101,  // .@.@.@.@
    0b00000000,  // ........
    0b01010101,  // .@.@.@.@
    0b01010101,  // .@.@.@.@
    0b01010101,  // .@.@.@.@
};

// ==========================================================================
// Icon lookup table: map byte value (1-31) to icon bitmap pointer.
// Used by TextWidget::_draw() to decode icon markers in format strings.
// ==========================================================================
static const uint8_t* const ICON_TABLE[] PROGMEM = {
    NULL,                //  0: (unused)
    ICON_RSSI_00,        //  1: \001
    ICON_RSSI__00,       //  2: \002
    ICON_RSSI_10,        //  3: \003
    ICON_RSSI_11,        //  4: \004
    ICON_RSSI__10,       //  5: \005
    ICON_RSSI__11,       //  6: \006
    ICON_WEATHER_DIV,    //  7: \007
    ICON_IP,             //  8: \010
    NULL,                //  9: \011 degree (now Unicode)
    NULL,                // 10: (unused)
    ICON_BATTERY_LOW,    // 11: \013
    ICON_BATTERY_MID,    // 12: \014
    NULL,                // 13: (unused)
    ICON_NOTE,           // 14: \016
    ICON_BATTERY_HIGH,   // 15: \017
    ICON_PLAY,           // 16: \020
    ICON_PREV,           // 17: \021
    NULL,                // 18: \022 (unused)
    ICON_SPEAKER,        // 19: \023
    ICON_VOL_25,         // 20: \024
    ICON_VOL_50,         // 21: \025
    ICON_VOL_100,        // 22: \026
    NULL,                // 23: (unused)
    ICON_CHARGING,       // 24: \030
    ICON_DISCHARGING,    // 25: \031
    NULL, NULL, NULL,    // 26-27: (unused)
    ICON_PAUSE,          // 28: \034
    ICON_LIST,           // 29: \035
    NULL, NULL           // 30-31: (unused)
};
