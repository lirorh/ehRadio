<img src="images/logo-color.svg" width="50%">

# ehRadio

***This documentation is the same on the [Github Page](https://trip5.github.io/ehRadio/), which may be easier to read.***

## Introduction

<img src="images/Trip5_ILI9488.jpg" width="50%">

ehRadio runs on an ESP32 to play Internet radio streams. 

A radio may be built using an ESP32, an audio decoder, a display, and some inputs.
I prefer to build with ESP32-S3 boards but ESP32 or ESP32-C3 boards are possible, too.
In some cases, like for the ES3C28P, no peripherals are even needed.

To develop, I prefer [VS Code](https://code.visualstudio.com/) but you may try other IDEs.
I compile using [Platformio](https://platformio.org/) but it may compile in Arduino IDE as well.
Some libraries may only be available from [Platformio Registry](https://registry.platformio.org/).

If you have zero desire to use VS Code but still want to build a radio, that's OK, too.
I would suggest you read the documentation a bit to make sure you get the right firmware for your radio.

ehRadio is a fork of [ёRadio](https://github.com/e2002/yoradio/) / yoRadio v0.9.533 and would not exist without
the years of work e2002 put into it.  Read [A History of ESP Radios](#a-history-of-esp-radios) for more.

---

## Features

ehRadio is focused on increasing usability for a non-builder / non-coder while at the same time
stressing future-compatibility for builders (starting with the ESP32-S3 and future ESP boards).

ehRadio inherits a lot from ёRadio, so here's some similarities and differences,
especially in terms of how they are used and how they are built.

### Features For Users

| ёRadio | ehRadio |
| ------ | --------|
| Physical controls (builder's choice)          | Uses ёRadio control architecture |
| - up to 2 rotaries and 6 buttons              | - same |
| - touchscreen control (basic swipes and taps) | - same | 
| - IR remote control                           | - same |
| - Nextion uses advanced control               | - Nextion support removed |
| Must be flashed using VS Code / Arduino IDE   | Web flasher & Internet OTA updates make getting a new version easy-peasy |
| English or Russian display                    | 36 Display languages (using a single Unicode font) (easily changeable)
| MQTT, Telnet, HTTP                            | MQTT, Telnet, HTTP |
| - mostly used for playback                    | - all WebUI commands are available |
| Home Assistant integration (through MQTT)     | Home Assistant integration (through MQTT) - improved |
| WebUI interface, includes control playback    | WebUI mobile-first re-design |
| - change certain settings                     | - change many settings |
| - edit/import/export playlists                | - edit/import/export/merge playlists |
| - English UI                                  | - 50 Languages (easily changeable)
|                                               | - easy to locate with [ehDP](https://github.com/trip5/eh-Device-Scanner) |
|                                               | - Radio Station search using Radio-browser API |
|                                               | - Playlists can be shared via [webstations](https://github.com/trip5/webstations) |
|                                               | - Curated lists can download/merge/preview other playlists |

### Features For Builders

| ёRadio | ehRadio |
| ------ | --------|
| Primarily focused on ESP32                           | Primarily focused on ESP32-S3 |
| - 4MB of flash is fine                               | - 8MB flash recommended, 4MB possible but will break features |
| - ESP-WROVER has PSRAM, works better                 | - ESP-WROVER with PSRAM probably supported but untested |
| - ESP32-WROOM has no PSRAM but still functions       | - ESP32-WROOM likely doesn't work at all |  
| - Some support for ESP32-S3 and ESP32-C3             | - ESP32-S3 well-tested, ESP32-C3 untested |
| Multiple audio decoders supported                    | Multiple audio decoders supported (based on ёRadio) | 
| - I2S PCM decoder                                    | - I2S and VS1053 updated (for higher bitrate streams) |
| - VS1053 (or VS1003)                                 | - ES8311 works (a common codec on ESP32-S3 display boards) |
| - ESP32's builtin DAC                                |   |
| Multiple displays                                    | Based on 'ёRadio' display architecture |
| - see `options.h` for a full list                    | - ёRadio and ehRadio display configs should be compatible with each other |
| SPI buses use default pins                           | SPI buses can use custom pins |
| - SPI display and VS1053 can only use VSPI or HSPI   | - non-standard bus pins may be assigned to Bus A or B |
| - VSPI and HSPI are in board definition files        | - bus pins defined in `myoptions.h` |
| - ESP32 defines VSPI/SPI3 bus or HSPI/SPI2 bus       | - it is still recommended to use default pins wherever possible |
| - ESP32-S3 defines FSPI/SPI2 but no second bus       | - ESP32-S3's FSPI pins should be assigned as Bus A but any pins can be assigned to Bus B  |
| - no way to use VS1053 and SPI display together      | - SPI display must be on A, recommended to put VS1053 alone (on B with SPI display) |
| Most default settings hardcoded                      | Almost all system and user default settings can be set in `myoptions.h` |

---

## WebUI

The WebUI is optimized for mobile browsers but looks great on PCs, too.

![image](images/Screenshot_Player.jpg)

More screenshots from the WebUI are [here](WebUI.md).

---

## Hardware Choices

There are many considerations to make when building a radio.

### ESP Board

I personally build with ESP32-S3 boards.  I recommend using an S3 board with at least 2MB of PSRAM and 8MB of flash.

This code may still run on an ESP32 but without at least 1MB of PSRAM will have serious issues.

I recommend choosing a board which has the option of an external antenna.

### Display

ILI9488 is big but uses a 24-bit bus so can be slow to update (so choose the ST7796 if you want a display that updates faster).

SPI color TFT displays all look pretty good.

OLEDs are cheap, beautiful and just as functional (SPI or I2C doesn't matter).

### Audio Decoder

VS1053b can be a tricky decoder to buy - some are sold as VS1003/1053 which are almost certainly a VS1003.
Genuine VS1053 is usually $10 minimum. Shop carefully and don't buy the cheapest one.

The VS1053's advantage is that it takes pressure off the CPU and decodes streams on-board.
It also has an amplifer. For the VU Meter to function, the patch MUST be enabled.
Even with the patch, though, it cannot decode FLAC streams and some other "unusal" stream types.

A VS1003 will still be functional for MP3 stations but not much else. It cannot use the patch.

I2S Decoders use the CPU to decode data so it can be used with many types of streams.
It does put pressure on the CPU so it does have trouble running with large SPI displays.
I have done my best to mitigate that but it is what is.

I2S decoders are cheap and plentiful and I don't think anyone has ever worrried about buying a fake..

A good I2S Decoder is the PCM5102. The UDA1334 should work and there are likely others.

You will need an amplifer when building with a DAC like these. I have used the PAM8406.
PAM IC amps are generally easy to work with but... your mileage will vary.

The ES8311 is a mono I2S decoder included on some dev board / display combos.  It's not terrible.

### Controls

ehRadio can be built with various control methods, including rotary encoders, buttons, an IR receiver, touchscreen, WebUI, Home Assistant, MQTT, Telnet, and HTTP.

The most basic physical control is a rotary encoder.  All functions can be accomplished with just one encoder.

Information on how the controls function detailed are [here](Controls.md).

---

## Documentation

The best starting point (after reading this page) is the [myoptions Generator](https://trip5.github.io/ehRadio/myoptions/generator.html).
This can assist in making a very good `myoptions.h` file, which should be placed in the root of the build folder next to `platformio.ini` (which the generator also makes). 
It contains almost all supported hardware and peripherals which can be used when building an ehRadio.
It can generate a shareable link (json is encoded in the URL) and can even contain advanced options and notes.

If you need to get more advanced options, a lot of build options and comments and notes are actually in `options.h`.
Contained within are numerous notes on how to further customize your `myoptions.h`.
Some hardware questions may also be answered within this file.

Want to get even more advanced? There are bunches of notes and tools in the codebase including font editors & builders, localization scripts, and more.

### Audio Libraries and Other Issues

ehRadio currently uses the `ESP32-audioI2S` library from [Maleksm's ёRadio mod v0.9.434m](https://4pda.to/forum/index.php?showtopic=1010378&st=11240#entry125839228),
likely mostly from schreibfaul1's library [3.1.0 January 7, 2025](https://github.com/schreibfaul1/ESP32-audioI2S/releases/tag/3.1.0).

ehRadio also currently uses the `ESP32-vs1053_ext` library from `nsteplanets` [PR226](https://github.com/e2002/yoradio/pull/226) to yoRadio.

Both libraries have been further optimized to get the best playback possible... and further optimization is possible.

There are notes in the `libraries` folder regarding some of the "Frankenstein" operations I have performed (since I know very little about decoding libraries).

For that and other major needed changes to the codebase, there is a `code-issues.md` file which may be a messy file to look at, depending on how these efforts are going.

### Languages

If using a display other than English (either on the display or in the WebUI), there be errors in the translation.

They are really there as proof-of-concept.  They were translated by machines.  Fixes or additions are absolutely welcome.

There are tools in the codebase to assist with translation work.

---

## Radio Creations

I can't 100% confirm this, but I am pretty sure all devices built for other ESP-based radio projects will run ehRadio, as long as the hardware is supported.
And although (as of `2026.06.15`), ehRadio has been reworked so an ESP32-S3 can be wired with an SPI display and a VS1053 (which ёRadio & ESP32-RadioV2 can't),

Below here are some sketches and helpful hints to building one of the "prebuilt" firmwares as available in the Releases and the
[online flasher](https://trip5.github.io/ehRadio/firmware.html).

If you already have a good idea on how the hardware works and would just like to use a prebuilt binary,
check out the [Releases](https://github.com/trip5/ehRadio/releases/) and click on a link to open the generator with that binary's profile,
which includes hardware needed, pins to connect, and more.

Note that if following this path, you don't necessarily to attach all peripherals (rotary, buttons, IR Receiver, SD card, display).
The radio needs only the ESP board and the audio decoder to function... although your WebUI may show links to peripherals that don't exist.

If don't want to mess around with VS Code but would still like your own build added to the Releases, you can make a
[firmware request](https://github.com/trip5/ehRadio/discussions/categories/firmware-requests).
Please also do some research before requesting a firmware.

### Trip5's Radios

These are a few I have made, using cheap Bluetooth speakers from Aliexpress, gutted, and fitted with plastic cases stuck where the Bluetooth control once was.

![image](images/Trip5_ehRadio_family.jpg)

I exclusively use XH2.54 connectors to connect between components with headers and to the ESP32-S3.
With a bit of practice, it becomes quite easy to make reliable conections that can also be (fairly) easily changed later.
They are way more reliable than using breadboards and duPont connectors.

![image](images/Trip5_SH1106_VS1053_3buttons1.jpg)

And painter's tape keeps the components from making contact with each other when I stuff them into the speaker.

![image](images/Trip5_SH1106_VS1053_3buttons2.jpg)

Of course, switches will still require some soldering.

For more notes about this build, check out [my Notebook](images/notebook/notebook.md), which contains notes about various components.

At some point, I will make a more beautiful radio, perhaps taking inspiration from:

- [ThomasH358](https://www.instructables.com/How-to-Build-a-Portable-Bluetooth-Tube-Amplifier/)
- [WelshWoodWorking](https://www.instructables.com/Vintage-Style-MP3-Radio/)
- [Peppy Radio Woodware](https://github.com/project-owner/Peppy.doc/wiki/Woodware)
- [Peppy Player on DIY Audio](https://www.diyaudio.com/community/threads/peppy-player.288412/)
- [Google Image Search](https://www.google.com/search?q=diy+arduino+radio+project&tbm=isch)

### ёRadio Builds

e2002 collected a lot of pictures of ёRadio builds [here](Images.md).

---

## A History of ESP Radios

### In the beginning...

Edzelf was probably the first to work on the idea of an ESP-based radio with [Esp-radio](https://github.com/Edzelf/Esp-radio/), making his first Github upload
[April 4, 2016](https://github.com/Edzelf/Esp-radio/tree/0a53a03c2301e9e5f0bfaee418942be67739dee0) which included audio decoding with a VS1053 decoder, built on a ESP8266.

Edzelf then made [ESP32-Radio](https://github.com/Edzelf/ESP32-Radio/), with his first release on [May 23, 2017](https://github.com/Edzelf/ESP32-Radio/tree/c268677dd8e46db2b7a8bfbd12a131c169e32019).
Later, [ESP32Radio-V2](https://github.com/Edzelf/ESP32Radio-V2/) was created on [October 4, 2021](https://github.com/Edzelf/ESP32Radio-V2/tree/81ea92481eb36e49c8983e9dd1e5a34fecca73a9) and includes I2C audio decoding (see below).
Edzelf still maintains ESP32Radio-V2.

karawin began work on [Ka-Radio](https://github.com/karawin/Ka-Radio) with his first Github submission [June 15, 2016](https://github.com/karawin/Ka-Radio/tree/13df16e5bd4dcf646ebfa6ffbb1eeb43173d2093) for VS1053 and ESP8266.
Unlike the other projects and libraries here, it is not done using Arduino code. It uses the ESP8266 RTOS SDK directly using C and assmbly.
karawin continued with [Ka-Radio32](https://github.com/karawin/Ka-Radio32/), with the first commits on Github [September 20, 2017](https://github.com/karawin/Ka-Radio32/tree/8cfd1f9e41fff42723dcfb8ea1a3244bfe5ef4ae).
Ka-Radio32 credits MrBuddyCasino's [ESP32_MP3_Decoder](https://github.com/MrBuddyCasino/ESP32_MP3_Decoder) for its I2S audio decoder, which was first put on Github
[January 19, 2019](https://github.com/MrBuddyCasino/ESP32_MP3_Decoder/tree/f1a92e1fbdcca3f2ffc6570aa599bc24806d8fd1).

At some point, schreibfaul1 began work on the [ESP32-vs1053_ext](https://github.com/schreibfaul1/ESP32-vs1053_ext) library, making his first version available
on Github [October 13, 2017](https://github.com/schreibfaul1/ESP32-vs1053_ext/tree/651dcce0f7d617a81153bc9a078ee8542db200f1), crediting Edzelf's ESP32-Radio as inspiration.
Further work has been done by [nstepanets](https://github.com/nstepanets/ESP32-vs1053_ext) who took over [October 25, 2025](https://github.com/nstepanets/ESP32-vs1053_ext/tree/bddf3137ec361a6b13d0a1687d3065561d507b8c).

schreibfaul1 also created the [ESP32-audioI2S](https://github.com/schreibfaul1/ESP32-audioI2S) library, making his first version available on Github [October 28, 2018](https://github.com/schreibfaul1/ESP32-audioI2S/tree/dc87801a7b1b369925080276cedd5a019715470a).
Work continues on that library today. Coming full circle, Edzelf likely adapted this library when working on ESP32Radio-V2 radio.

It is hard to say definitively, but more than likely all of these projects have inspired each other in various ways.  The DNA of all these projects are still evident in ёRadio and ehRadio.

If you have more information about the history of these projects or corrections to this story, I'd be interested to know!

### ёRadio

Russian site 4PDA's megathread "WI-FI internet radio DIY" started in [November 21, 2020](https://4pda.to/forum/index.php?showtopic=1010378), at first primarily centered around modifications to Ka-Radio32.
This thread contains a lot of useful information regarding hardware. I can't say how much of this information was used to improve Ka-Radio but easy (e2002) and Wolle (schreibfaul1) both appear to have improved their libraries using this information.

e2002 began sharing his work on the 4PDA "WI-FI internet radio DIY" thread [January 25, 2022](https://4pda.to/forum/index.php?showtopic=1010378&st=1800#entry112992611).

[ёRadio](https://github.com/e2002/yoradio/) v0.4.170 was first added to Github [Feb 4, 2022](https://github.com/e2002/yoradio/tree/6c847cdc308150e786e5340200f8e3ea18c01042), based primarily on schreibfaul1's libraries.

### ehRadio

In July 2023, I built my first radio using Edzelf's [ESP32Radio-V2](https://github.com/Edzelf/ESP32Radio-V2/).
In November 2024, I discovered [ёRadio](https://github.com/e2002/yoradio/) and on December 26, 2024, I made my [first PR](https://github.com/e2002/yoradio/pull/125).

In May 2005 I began adding full support for Radio-browser API with the hope it would improve a user's experience. I also merged many of maleksm's mods.
That PR started [June 13, 2025](https://github.com/e2002/yoradio/pull/184) was abandoned June 19, 2025 with a ridiculous amount of changes.

In retrospect, proposing thousands of lines of changes was rude and unrealistic.  After some thought, ehRadio was forked August 10, 2025.
On May 21, 2026, ehRadio was officially deforked from ёRadio on Github.

I will add a note here that although I do use AI-assisted coding, I am not a "vibe-coder" - except for python and javascript.
I welcome all pull requests but please follow the rules as laid out in `copilot-instructions.md` and `code-summary.md`,
the former of which is a set of hard rules for AI-assisted coding, the latter of which is an AI-generated `Bible` of the codebase to help an LLM maintain codebase consistancy.

---

## Update History

### Updates

| Date       | Release Notes    |
| ---------- | ---------------- |
| 2026.06.28 | Unicode 8x6 fonts with full multilingual support, `Share` added to Playlist Editor, Nextion support removed, VS1053 library updated (patch functional),  |
| 2026.06.18 | WebUI files now served from PSRAM cache (if available) which eliminates audio stuttering for I2S decoders, adjustments to PSRAM-related code, rotary encoders fix |
| 2026.06.15 | SPI fixed so SPI Display and VS1053 are possible, SD fixes, Wi-fi reconnect smarter, generator indicates safe pins |
| 2026.06.08 | Fixed Search/Curated additions corrupting the playlist, changing stations faster, connect errors fail faster, safe mode entered after unsuccessful boot (disables smartstart, autoupdate) |
| 2026.06.03 | Displays overhauled to support more displays more easily, volume now cubic polynomial, `VOLUME_SCALE 42` reduces volume increments from 254, volume steps removed, generator updated |
| 2026.05.29 | IR fixed, HA component updated, playlist page mode added for ILI9486/9488, playing current station does nothing, documentation completely overhauled |
| 2026.05.26 | `Feature Freeze` `De-fork from ёRadio` Theme updated, Chunky6 font, fixes to `options.h`: `BTN_*` fixed & `ENC_*` renamed, screensaver fixes, battery widgets, ILI9225 from ёRadio v0.9.710, generator updated, partitions changed |
| 2026.05.19 | `Feature Freeze` This readme, myoptions generator, cpu cores/stack sizes optimized (monitor added), auto dimming, plugins removed, general & specific code repair, refactor, optimization |
| 2026.05.08 | `Feature Freeze` SPI buses more flexible, unified commandhandler and error logging, Home Assistant component fixed, OTA & naming methods finalized |
| 2026.04.09 | `Feature Freeze` major and minor changes to structure, aggressive reconnect to wi-fi |
| 2026.03.30 | `Feature Freeze` begins, OTA page reload graceful, 3 javascript files combined to 1 (`script2.js`) |
| 2026.03.22 | ehDP added, playlist editor grabbable fixed |
| 2026.03.18 | multiple weather providers, screensaver mode fixed, https connection improved, w/Kasperaitis: multi-locales in display and WebUI, Kasperaitis: battery handling |
| 2026.02.18 | WebUI improved, Curated Lists, default playlist on first boot, Smart start fixed, SPIFFS cleanup, Kasperaitis: battery monitor and telnet formatting |
| 2026.02.06 | online flasher, improv mode |
| 2026.02.04 | scan/connect wi-fi, use PIO libraries and less local libraries, Kasperaitis: ES8311 and FT6336 (for ES3C28) |
| 2025.08.31 | Display fixes and other fixes from ёRadio up to v0.9.693 including framebuffer |
| 2025.08.20 | Online updater fixed, WebUI fixes for mobile displays, MQTT added to WebUI |
| 2025.08.12 | `builds\` folder added to share configurations, hotspot AP mode fixed, preferences in `myoptions.h`, improvements from ёRadio v0.9.574 |
| 2025.08.10 | `ehRadio begins`, folders restructured, `data\` files stay uncompressed (compressed in from Releases, which radio can download), timezones.json updated automatically |
| 2025.07.23 | more options in WebUI |
| 2025.07.19 | PR to ёRadio v0.9.533: EEProm storage changed to Preferences, fixes for screens that can't display certain characters, ESPFileUpdater added (updates timezones and Radio Browser servers), proper timezones, many macros added to `myoptions.h`, Radio station search, Playback queue now RTOS background task, improved JSON and CSV file importing, maleksm's backlightdown and decoder improvements, ESP8266 support removed |

### Old Readme

A full history of ёRadio from v0.4.177 to v0.9.533 can be seen in the [old Readme](README.old.md).

### Credit

Thanks to:
  - [https://github.com/kle7rx] - `ru_RU` translation and debugging
  - [Kasperaitis](https://github.com/kasperaitis) - `lt_LT` translation, initiating locales (WebUI and display language) and a bunch of work for ES3C28P (including ES8311 decoder, ILI9341 battery widget, FT6336 touchscreen)
  - [e2002](https://github.com/e2002) - for [ёRadio](https://github.com/e2002/yoradio/) without which ehRadio would not be possible

