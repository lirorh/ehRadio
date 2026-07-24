#ifndef myoptions_h
#define myoptions_h

/*        ************************************************************************      */
/*        *        This file must be in the root folder of the sketch !!!        *      */
/*        ************************************************************************      */
/*        . . .  CHECK options.h for full options, examples, and overrides   . . .      */

// ESP32-S3-DevKitC-1 N16R8 (16MB Flash 8MB PSRAM)
// Display: Dummy (no physical display)
// Audio Decoder: I2S (PCM I2S Decoder)
//
//             |----------|
//         3V3 |          | G
//         3V3 |          | 43
//          -1 |          | 44
//           4 |          | 1
//           5 |          | 2
//           6 |          | 42
//           7 |          | 41
//          15 |          | 40
//          16 |          | 39
//          17 |          | 38
//          18 |          | 37
//           8 |          | 36
//           3 |          | 35
//          46 |          | 0
//           9 |          | 45
//  I2S_LRC 10 |          | 48
// I2S_BCLK 11 |          | 47
// I2S_DOUT 12 |          | 21
//          13 |          | 20
//          14 |          | 19
//          5V |          | G
//           G |          | G
//             |----------|


/* --- Firmware File --- */
#define FIRMWARE_NAME        "ehradio_nodisplay" /* your ehRadio's name */

/* --- Display --- */
#define DSP_MODEL            DSP_DUMMY

/* --- Audio Decoder --- */
#define I2S_DOUT             12
#define I2S_BCLK             11
#define I2S_LRC              10
#define MUTE_PIN             255       /* pin MUTE is attached to (255 for unused) */

/* --- User Defaults --- */
#define SMART_START          true
#define WIFI_SCAN_BEST_RSSI  true

#endif // myoptions_h
