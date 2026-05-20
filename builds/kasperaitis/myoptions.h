#ifndef myoptions_h
#define myoptions_h

/*        ************************************************************************      */
/*        *        This file must be in the root folder of the sketch !!!        *      */
/*        ************************************************************************      */
/*        . . .  CHECK options.h for full options, examples, and overrides   . . .      */

// ESP32-S3 ES3C28P (ESP32-S3-N16R8)
// Display: ILI9341 (SPI 320x240 TFT)
// Audio Decoder: ES8311 (PCM I2S Mono Decoder)
// SPI Bus A: ILI9341 (SPI 320x240 TFT)
// SPI Bus B: SD Card Reader
//
//  Pin  Function
//  ---  --------
//  -1   TFT_RST
//  0    BTN_NEXT
//  1    MUTE_PIN
//  4    I2S_MCLK
//  5    I2S_BCLK
//  6    I2S_DIN
//  7    I2S_LRC
//  8    I2S_DOUT
//  10   TFT_CS
//  11   SPIA_MOSI
//  12   SPIA_SCK
//  15   ES8311_I2C_SCL + TS_SCL
//  16   ES8311_I2C_SDA + TS_SDA
//  17   TS_INT
//  18   TS_RST
//  38   SPIB_SCK
//  39   SPIB_MISO
//  40   SPIB_MOSI
//  42   RGB_LED_PIN
//  45   BRIGHTNESS_PIN
//  46   TFT_DC
//  47   SD_CS


/* --- Firmware File & Board --- */
#define FIRMWARE "kasperaitis_es3c28p.bin" // "esp32_s3_n16r8", "ESP32-S3", "Kasperaitis"
#define FIRMWARE_NAME "ES3C28P" // "https://trip5.github.io/ehRadio/myoptions/generator.html#eyJibiI6IkVTUDMyLVMzIEVTM0MyOFAgKEVTUDMyLVMzLU4xNlI4KSIsImRkIjoiRFNQX01PREVMIERTUF9JTEk5MzQxIiwiZG4iOiJJTEk5MzQxIChTUEkgMzIweDI0MCBURlQpIiwiYWQiOiJVU0VfRVM4MzExIiwiYW4iOiJFUzgzMTEgKFBDTSBJMlMgTW9ubyBEZWNvZGVyKSIsImNpIjpbIlRTX01PREVMIFRTX01PREVMX0ZUNjMzNiIsIk5leHQgc3RhdGlvbi90cmFjayBidXR0b24iXSwiY3AiOlsiUkdCIExFRCIsIk1RVFRfRU5BQkxFIiwiU0QgQ2FyZCBSZWFkZXIiXSwiY3MiOlsiQSIsIkIiXSwiY28iOlsiVEZUX1JTVCIsIkJSSUdIVE5FU1NfUElOIiwiRFNQX0RJTU1JTkdfRU5BQkxFRCIsIkRTUF9JTlZFUlRfUVVJUksiLCJNVVRFX1BJTiIsIkVTODMxMV9JMkNfU0RBIiwiRVM4MzExX0kyQ19TQ0wiLCJMRURfSU5WRVJUIl0sImNkIjpbIk9ORV9DTElDS19TV0lUQ0giLCJTU19QTEFZSU5HIiwiU0NSRUVOX0ZMSVAiLCJTSE9XX0FVRElPX0lORk8iLCJTSE9XX1ZVX01FVEVSIiwiU01BUlRfU1RBUlQiLCJTTlRQXzEiLCJTTlRQXzIiLCJWT0xVTUVfU1RFUFMiLCJXRUFUSEVSX0xBVCIsIldFQVRIRVJfTE9OIiwiV0lGSV9TQ0FOX0JFU1RfUlNTSSJdLCJwIjp7IlNQSUFfU0NLIjoiMTIiLCJTUElBX01JU08iOiIyNTUiLCJTUElBX01PU0kiOiIxMSIsIlNQSUJfU0NLIjoiMzgiLCJTUElCX01JU08iOiIzOSIsIlNQSUJfTU9TSSI6IjQwIiwiVEZUX0NTIjoiMTAiLCJURlRfREMiOiI0NiIsIlRGVF9SU1QiOiItMSIsIkJSSUdIVE5FU1NfUElOIjoiNDUiLCJJMlNfTUNMSyI6IjQiLCJJMlNfQkNMSyI6IjUiLCJJMlNfTFJDIjoiNyIsIkkyU19ET1VUIjoiOCIsIkkyU19ESU4iOiI2IiwiTVVURV9QSU4iOiIxIiwiRVM4MzExX0kyQ19TREEiOiIxNiIsIkVTODMxMV9JMkNfU0NMIjoiMTUiLCJUU19TREEiOiIxNiIsIlRTX1NDTCI6IjE1IiwiVFNfSU5UIjoiMTciLCJUU19SU1QiOiIxOCIsIkJUTl9ORVhUIjoiMCIsIlJHQl9MRURfUElOIjoiNDIiLCJTRF9DUyI6IjQ3In0sInYiOnsiTVVURV9WQUwiOiJISUdIIiwiU0RfU1BJIjoiQiIsIkRTUF9ESU1NSU5HX0VOQUJMRUQiOiJ0cnVlIiwiRFNQX0lOVkVSVF9RVUlSSyI6InRydWUiLCJQTEFZRVJfRk9SQ0VfTU9OTyI6InRydWUiLCJPTkVfQ0xJQ0tfU1dJVENIIjoidHJ1ZSIsIlNTX1BMQVlJTkciOiJ0cnVlIiwiU0NSRUVOX0ZMSVAiOiJ0cnVlIiwiU0hPV19BVURJT19JTkZPIjoidHJ1ZSIsIlNIT1dfVlVfTUVURVIiOiJ0cnVlIiwiU01BUlRfU1RBUlQiOiJ0cnVlIiwiV0lGSV9TQ0FOX0JFU1RfUlNTSSI6InRydWUiLCJGSVJNV0FSRV9OQU1FIjoiZXMzYzI4cCIsIkVTODMxMV9NQVhfSTJTIjoiMTgwIiwiU05UUF8xIjoibHQucG9vbC5udHAub3JnIiwiU05UUF8yIjoicG9vbC5udHAub3JnIiwiVk9MVU1FX1NURVBTIjoiNSIsIldFQVRIRVJfTEFUIjoiNTUuNzIxOTI0IiwiV0VBVEhFUl9MT04iOiIyMS4xMTc4NjgifSwibGMiOiJsdF9MVCIsInR6IjoiRXVyb3BlL1ZpbG5pdXMiLCJ4ZSI6dHJ1ZSwieGQiOiIvKiAtLS0gQmF0dGVyeSAtLS0gKi9cbiNkZWZpbmUgQkFUVEVSWV9QSU4gOSAgICAgICAgICAgICAgICAgIC8qIEdQSU85OiBBREMgcGluIGZvciBiYXR0ZXJ5IHZvbHRhZ2UgKi9cbi8vI2RlZmluZSBCQVRURVJZX0NIQVJHRV9QSU4gMjU1ICAgICAgIC8qIE5vIGNoYXJnaW5nIHN0YXR1cyBHUElPIGV4cG9zZWQgKFRQNDA1NCBDSFJHIHBpbiBub3QgY29ubmVjdGVkIG9uIEVTM0MyOFApICovXG5cbiNkZWZpbmUgQkFUVEVSWV9ESVZJREVSX1JBVElPIDIuMCAgICAgIC8qIDEwMGsgKyAxMDBrIHZvbHRhZ2UgZGl2aWRlciA9IDE6MiByYXRpbyAqL1xuI2RlZmluZSBCQVRURVJZX0FEQ19SRUZfTVYgICAgMzQzOCAgICAgLyogRVNQMzItUzMgQURDIHJlZmVyZW5jZSB2b2x0YWdlIChjYWxpYnJhdGVkIEVMMTAzNTY1IDMwMDBtQWggMTEuMVdoKSAqL1xuI2RlZmluZSBCQVRURVJZX1VQREFURV9JTlRFUlZBTCA2MDAwMCAgLyogVXBkYXRlIGV2ZXJ5IDYwIHNlY29uZHMgKi9cblxuLy8jZGVmaW5lIEJBVFRFUllfREVCVUcgICAgICAgICAgICAgICAgLyogVW5jb21tZW50IHRvIGVuYWJsZSBkZWJ1ZyBvdXRwdXQgKi9cbiNkZWZpbmUgQkFUVEVSWV9DSEFSR0VfSU5GRVJfSE9MRF9TQU1QTEVTIDMgLyogbnVtYmVyIG9mIG1lYXN1cmVtZW50cyAoc2FtcGxlcykgdG8gaG9sZCAoZS5nLiwgMyByZWFkaW5ncyBhdCBCQVRURVJZX1VQREFURV9JTlRFUlZBTCkgKi9cbiNkZWZpbmUgQkFUVEVSWV9JTU1FRElBVEVfUEVSQ0VOVF9USFJFU0hPTEQgMjAgLyogcGVyY2VudCAqL1xuI2RlZmluZSBCQVRURVJZX0NBTkRJREFURV9QRVJDRU5UX0RFTFRBIDEgLyogcGVyY2VudCAqL1xuI2RlZmluZSBCQVRURVJZX1NVU1RBSU5FRF9QRVJDRU5UX1dJTkRPV19USFJFU0hPTEQgMCAvKiBwZXJjZW50IG92ZXIgaG9sZCB3aW5kb3cgKi8ifQ%3D%3D"
#define ENABLE_UPDATER // enables OTA updates

/* --- SPI Bus Pins --- */
#define SPIA_SCK             12
#define SPIA_MISO            255
#define SPIA_MOSI            11
#define SPIB_SCK             38
#define SPIB_MISO            39
#define SPIB_MOSI            40

/* --- Display --- */
#define DSP_MODEL            DSP_ILI9341
#define TFT_CS               10
#define TFT_DC               46
#define TFT_RST              -1        /* pin RST is attached to (-1 = EN pin) */
#define BRIGHTNESS_PIN       45        /* pin that controls brightness / backlight (255 = unused) */
#define DSP_DIMMING_ENABLED  true      /* enable screen dimming (depends on brightness pin) */
#define DSP_INVERT_QUIRK     true      /* fixes display inversion quirk (very common) */

/* --- Audio Decoder --- */
#define I2S_MCLK             4
#define I2S_BCLK             5
#define I2S_LRC              7
#define I2S_DOUT             8
#define I2S_DIN              6
#define MUTE_PIN             1         /* pin MUTE is attached to (255 for unused) */
#define ES8311_I2C_SDA       16        /* may fix volume control on boot */
#define ES8311_I2C_SCL       15        /* may fix volume control on boot */
#define USE_ES8311
#define MUTE_VAL             HIGH      /* enables turning off audio amplifier */
#define ES8311_MAX_I2S       180       /* maximum I2S value to allow when mapping to ES8311 codec (0..254) */
#define PLAYER_FORCE_MONO    true      /* forces VU meter to mono mode */

/* --- Input --- */
#define TS_MODEL             TS_MODEL_FT6336
#define TS_SDA               16
#define TS_SCL               15
#define TS_INT               17
#define TS_RST               18
#define BTN_NEXT             0

/* --- Peripherals and Build Options --- */
#define RGB_LED_PIN          42
#define MQTT_ENABLE
#define SD_CS                47
#define SD_SPI               'B'       /* assign SD to SPI bus */

/* --- Locale --- */
#define DSP_LANGUAGE_lt_LT

/* --- User Defaults --- */
#define ONE_CLICK_SWITCH     true
#define SS_PLAYING           true
#define SCREEN_FLIP          true
#define SHOW_AUDIO_INFO      true
#define SHOW_VU_METER        true
#define SMART_START          true
#define SNTP_1               "lt.pool.ntp.org"
#define SNTP_2               "pool.ntp.org"
#define VOLUME_STEPS         5
#define WEATHER_LAT          "55.721924" /* latitude */
#define WEATHER_LON          "21.117868" /* longitude */
#define WIFI_SCAN_BEST_RSSI  true

/* --- Time Zone --- */
#define TIMEZONE_NAME        "Europe/Vilnius"
#define TIMEZONE_POSIX       "EET-2EEST,M3.5.0/3,M10.5.0/4"

/* --- Extra defines --- */
/* --- Battery --- */
#define BATTERY_PIN 9                  /* GPIO9: ADC pin for battery voltage */
//#define BATTERY_CHARGE_PIN 255       /* No charging status GPIO exposed (TP4054 CHRG pin not connected on ES3C28P) */

#define BATTERY_DIVIDER_RATIO 2.0      /* 100k + 100k voltage divider = 1:2 ratio */
#define BATTERY_ADC_REF_MV    3438     /* ESP32-S3 ADC reference voltage (calibrated EL103565 3000mAh 11.1Wh) */
#define BATTERY_UPDATE_INTERVAL 60000  /* Update every 60 seconds */

//#define BATTERY_DEBUG                /* Uncomment to enable debug output */
#define BATTERY_CHARGE_INFER_HOLD_SAMPLES 3 /* number of measurements (samples) to hold (e.g., 3 readings at BATTERY_UPDATE_INTERVAL) */
#define BATTERY_IMMEDIATE_PERCENT_THRESHOLD 20 /* percent */
#define BATTERY_CANDIDATE_PERCENT_DELTA 1 /* percent */
#define BATTERY_SUSTAINED_PERCENT_WINDOW_THRESHOLD 0 /* percent over hold window */

#endif // myoptions_h
