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
#define FIRMWARE_NAME "es3c28p" // "https://trip5.github.io/ehRadio/myoptions/generator.html#eyJibiI6IkVTUDMyLVMzIEVTM0MyOFAgKEVTUDMyLVMzLU4xNlI4KSIsImRkIjoiRFNQX01PREVMIERTUF9JTEk5MzQxIiwiZG4iOiJJTEk5MzQxIChTUEkgMzIweDI0MCBURlQpIiwiYWQiOiJVU0VfRVM4MzExIiwiYW4iOiJFUzgzMTEgKFBDTSBJMlMgTW9ubyBEZWNvZGVyKSIsImNpIjpbIlRTX01PREVMIFRTX01PREVMX0ZUNjMzNiIsIkJ1dHRvbjogTmV4dCBTdGF0aW9uL1RyYWNrIl0sImNwIjpbIlJHQiBMRUQiLCJNUVRUX0VOQUJMRSIsIlNEIENhcmQgUmVhZGVyIl0sImNzIjpbIkEiLCJCIl0sImNvIjpbIlRGVF9SU1QiLCJCUklHSFRORVNTX1BJTiIsIkRTUF9ESU1NSU5HX0VOQUJMRUQiLCJEU1BfSU5WRVJUX1FVSVJLIiwiTVVURV9QSU4iLCJFUzgzMTFfSTJDX1NEQSIsIkVTODMxMV9JMkNfU0NMIiwiTEVEX0lOVkVSVCJdLCJjZCI6WyJEU1BfTEFOR1VBR0UiLCJUSU1FWk9ORSIsIk9ORV9DTElDS19TV0lUQ0giLCJTQ1JFRU5fRkxJUCIsIlNTX1BMQVlJTkciLCJTSE9XX1ZVX01FVEVSIiwiU01BUlRfU1RBUlQiLCJTTlRQXzEiLCJTTlRQXzIiLCJXRUFUSEVSX0xBVCIsIldFQVRIRVJfTE9OIiwiV0lGSV9TQ0FOX0JFU1RfUlNTSSJdLCJwIjp7IlNQSUFfU0NLIjoiMTIiLCJTUElBX01JU08iOiIyNTUiLCJTUElBX01PU0kiOiIxMSIsIlNQSUJfU0NLIjoiMzgiLCJTUElCX01JU08iOiIzOSIsIlNQSUJfTU9TSSI6IjQwIiwiVEZUX0RDIjoiNDYiLCJURlRfQ1MiOiIxMCIsIlRGVF9SU1QiOiItMSIsIkJSSUdIVE5FU1NfUElOIjoiNDUiLCJJMlNfTUNMSyI6IjQiLCJJMlNfQkNMSyI6IjUiLCJJMlNfTFJDIjoiNyIsIkkyU19ET1VUIjoiOCIsIkkyU19ESU4iOiI2IiwiTVVURV9QSU4iOiIxIiwiRVM4MzExX0kyQ19TREEiOiIxNiIsIkVTODMxMV9JMkNfU0NMIjoiMTUiLCJUU19TREEiOiIxNiIsIlRTX1NDTCI6IjE1IiwiVFNfSU5UIjoiMTciLCJUU19SU1QiOiIxOCIsIkJUTl9ORVhUIjoiMCIsIlJHQl9MRURfUElOIjoiNDIiLCJTRF9DUyI6IjQ3In0sInYiOnsiTVVURV9WQUwiOiJISUdIIiwiU0RfU1BJIjoiQiIsIkRTUF9MQU5HVUFHRSI6Imx0X0xUIiwiVElNRVpPTkUiOiJFdXJvcGUvVmlsbml1cyIsIkRTUF9ESU1NSU5HX0VOQUJMRUQiOiJ0cnVlIiwiRFNQX0lOVkVSVF9RVUlSSyI6InRydWUiLCJQTEFZRVJfRk9SQ0VfTU9OTyI6InRydWUiLCJPTkVfQ0xJQ0tfU1dJVENIIjoidHJ1ZSIsIlNDUkVFTl9GTElQIjoidHJ1ZSIsIlNTX1BMQVlJTkciOiJ0cnVlIiwiU0hPV19WVV9NRVRFUiI6InRydWUiLCJTTUFSVF9TVEFSVCI6InRydWUiLCJXSUZJX1NDQU5fQkVTVF9SU1NJIjoidHJ1ZSIsIkZJUk1XQVJFX05BTUUiOiJlczNjMjhwIiwiRVM4MzExX01BWF9JMlMiOiIxODAiLCJTTlRQXzEiOiJsdC5wb29sLm50cC5vcmciLCJTTlRQXzIiOiJwb29sLm50cC5vcmciLCJXRUFUSEVSX0xBVCI6IjU1LjcyMTkyNCIsIldFQVRIRVJfTE9OIjoiMjEuMTE3ODY4In0sInhlIjp0cnVlLCJ4ZCI6Ii8qIC0tLSBCYXR0ZXJ5IC0tLSAqL1xuI2RlZmluZSBCQVRURVJZX1BJTiA5ICAgICAgICAgICAgICAgICAgLyogR1BJTzk6IEFEQyBwaW4gZm9yIGJhdHRlcnkgdm9sdGFnZSAqL1xuLy8jZGVmaW5lIEJBVFRFUllfQ0hBUkdFX1BJTiAyNTUgICAgICAgLyogTm8gY2hhcmdpbmcgc3RhdHVzIEdQSU8gZXhwb3NlZCAoVFA0MDU0IENIUkcgcGluIG5vdCBjb25uZWN0ZWQgb24gRVMzQzI4UCkgKi9cblxuI2RlZmluZSBCQVRURVJZX0RJVklERVJfUkFUSU8gMi4wICAgICAgLyogMTAwayArIDEwMGsgdm9sdGFnZSBkaXZpZGVyID0gMToyIHJhdGlvICovXG4jZGVmaW5lIEJBVFRFUllfQURDX1JFRl9NViAgICAzNDM4ICAgICAvKiBFU1AzMi1TMyBBREMgcmVmZXJlbmNlIHZvbHRhZ2UgKGNhbGlicmF0ZWQgRUwxMDM1NjUgMzAwMG1BaCAxMS4xV2gpICovXG4jZGVmaW5lIEJBVFRFUllfVVBEQVRFX0lOVEVSVkFMIDYwMDAwICAvKiBVcGRhdGUgZXZlcnkgNjAgc2Vjb25kcyAqL1xuXG4vLyNkZWZpbmUgQkFUVEVSWV9ERUJVRyAgICAgICAgICAgICAgICAvKiBVbmNvbW1lbnQgdG8gZW5hYmxlIGRlYnVnIG91dHB1dCAqL1xuI2RlZmluZSBCQVRURVJZX0NIQVJHRV9JTkZFUl9IT0xEX1NBTVBMRVMgMyAvKiBudW1iZXIgb2YgbWVhc3VyZW1lbnRzIChzYW1wbGVzKSB0byBob2xkIChlLmcuLCAzIHJlYWRpbmdzIGF0IEJBVFRFUllfVVBEQVRFX0lOVEVSVkFMKSAqL1xuI2RlZmluZSBCQVRURVJZX0lNTUVESUFURV9QRVJDRU5UX1RIUkVTSE9MRCAyMCAvKiBwZXJjZW50ICovXG4jZGVmaW5lIEJBVFRFUllfQ0FORElEQVRFX1BFUkNFTlRfREVMVEEgMSAvKiBwZXJjZW50ICovXG4jZGVmaW5lIEJBVFRFUllfU1VTVEFJTkVEX1BFUkNFTlRfV0lORE9XX1RIUkVTSE9MRCAwIC8qIHBlcmNlbnQgb3ZlciBob2xkIHdpbmRvdyAqLyJ9
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
#define TFT_DC               46
#define TFT_RST              -1        /* pin RST is attached to (-1 = EN pin) */
#define BRIGHTNESS_PIN       45        /* pin that controls brightness / backlight (255 = unused) */
#define DSP_DIMMING_ENABLED  true      /* enable screen dimming (depends on brightness pin) */
#define DSP_INVERT_QUIRK     true      /* fixes display inversion quirk (very common) */
#define TFT_CS               10        /* pin CS is attached to (255 = tied to GND) */

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

/* --- Inputs --- */
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

/* --- User Defaults --- */
#define DSP_LANGUAGE         "lt_LT"
#define TIMEZONE_NAME        "Europe/Vilnius"
#define TIMEZONE_POSIX       "EET-2EEST,M3.5.0/3,M10.5.0/4"
#define ONE_CLICK_SWITCH     true
#define SCREEN_FLIP          true
#define SS_PLAYING           true
#define SHOW_VU_METER        true
#define SMART_START          true
#define SNTP_1               "lt.pool.ntp.org"
#define SNTP_2               "pool.ntp.org"
#define WEATHER_LAT          "55.721924" /* latitude */
#define WEATHER_LON          "21.117868" /* longitude */
#define WIFI_SCAN_BEST_RSSI  true

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
