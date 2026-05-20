<!--
![image](./images/logo-color.svg)
-->

<img src="images/logo-color.svg" width="50%">

# ehRadio

***This documentation is the same on the [Github Page](https://trip5.github.io/ehRadio/), which may be easier to read.***

## Introduction

ehRadio runs on an ESP32 to play Internet radio streams. 

A radio may be built using an ESP32, an audio decoder, a display, and some inputs.
I prefer to build with ESP32-S3 boards but ESP32 or ESP32-C3 boards are possible, too.

To develop, I prefer [VS Code](https://code.visualstudio.com/) but you may try other IDEs.
I compiled using [Platformio](https://platformio.org/) but it may compile in Arduino IDE as well
Some libraries may only be available from [Platformio Registry](https://registry.platformio.org/).

If you have zero desire to compile but still want to build a radio?  That's OK, too.
You can check out the [Built ehRadios](#buil)

ehRadio is a fork of [ёRadio](https://github.com/e2002/yoradio/) / yoRadio v0.9.533.
Read the [A History of ESP Radios](#a-history-of-esp-radios).

## Features


ehRadio is focused on increasing usability for a non-builder / non-coder while at the same time
stressing future-compatibility for builders (starting with the ESP32-S3 and future ESP boards).

ehRadio inherits a lot from ёRadio, so here's some similarities and differences,
especially in terms of how they are used and how they are built.

### Features For Users

| ёRadio | ehRadio |
| ------ | --------|
| Physical controls (decided by builder)        | Uses ёRadio control architecture |
| - up to 2 rotaries and 6 buttons              | - same|
| - touchscreen control (basic swipes and taps) | - same | 
| - Nextion uses advanced control               | - Nextion support is incomplete or broken |
| MQTT, Telnet, HTTP                            | MQTT, Telnet, HTTP |
| - mostly used for playback                    | - use the same commands as WebUI (!) |
| Home Assistant integration (through MQTT)     | Home Assistant integration (through MQTT) - improved a bit |
| WebUI interface, includes control playback    | WebUI similar but with added functionality |
| - edit/import/export playlists                | - edit/import/export/merge playlists (works on mobile too) |
| - change certain settings                     | - change many settings |
|                                               | Radio Station search using Radio-browser API | 
|                                               | Curated lists can download/merge/preview other playlists |

### Features For Builders

| ёRadio | ehRadio |
| ------ | --------|
| Primarily focused on ESP32                           | Primarily focused on ESP32-S3 |
| - 4MB of flash is fine                               | - 8MB flash recommended, 4MB certain features will break (until fixed) |
| - ESP-WROVER has PSRAM, works better                 | - ESP-WROVER with PSRAM probably supported but untested |
| - ESP32-WROOM has no PSRAM but still functions       | - ESP32-WROOM likely doesn't work at all |  
| - Some support for ESP32-S3 and ESP32-C3             | - ESP32-S3 well-tested, ESP32-C3 untested |
| Multiple audio decoders supported                    | Multiple audio decoders supported (based on ёRadio) | 
| - I2S PCM decoder                                    | - I2S and VS1053 updated (for higher bitrate streams) |
| - VS1053 (or VS1003)                                 | - ES8311 works (a common codec on ESP32-S3 display boards) |
| - ESP32's builtin DAC                                | - Future updates will support more by using external libraries |
| Multiple displays                                    | Uses 'ёRadio' display architecture |
| - see `options.h` for a full list                    | - ёRadio and ehRadio display configs should be compatible with each other |
| SPI buses use default pins                           | SPI buses can use custom pins |
| - SPI display and VS1053 can only use VSPI or HSPI   | - non-standard bus pins may be assigned to Bus A or B |
| - VSPI and HSPI are in board definition files        | - bus pins defined in `myoptions.h` |
| - ESP32 defines VSPI/SPI3 bus or HSPI/SPI2 bus       | - it is still recommended to use default pins wherever possible |
| - ESP32-S3 defines FSPI/SPI2 but no second bus       | - ESP32-S3's FSPI pins should be assigned as Bus A but any pins can be assigned to Bus B  |
| - no way to use VS1053 and SPI display together      | - Recommended: SPI display on A, VS1053 and other devices on B OR VS1053 on A and others on B |
| Most default settings hardcoded                      | Almost all user default settings can be set in `myoptions.h` |

---

## Tools

[myoptions Generator](https://trip5.github.io/ehRadio/myoptions/generator.html)

[Online Flasher](https://trip5.github.io/ehRadio/firmware.html)

Many more tools for tinkering with the code are available in the codebase as well.

---

## Documentation

I realize documentation is a little sparse right now.  I'm working on it.

A lot of build options and comments and notes are actually in `options.h` and in various files.

As of `2026.05.19` I've done a lot of work to clean up the codebase and organize it.

More work remains to be done and the `Feature Freeze` will remain in place at least until the "de-fork" of the audio libraries is finished.

---

## Radio Creations

I can't 100% confirm this, but I am pretty sure all devices built for other ESP-based radio projects will run ehRadio, as long as the hardware
is supported (and even if it isn't).  Not all radios built for ehRadio will run other firmwares.
The combination of an SPI display with a VS1053 is the type that would be difficult to run yoRadio or ESP32-RadioV2 on an ESP32-S3 (but may be fine on ESP32).
That said, as contributers add their configurations, more than likely, they will continue to use "standard" pins and parts with radios designed
from yoRadio or ESP32-RadioV2 plans.  Devices that have the SPI Display & VS1053 will be marked, so as to keep newbies on track...?

Here will be some sketches and helpful hints to building one of the "prebuilt" firmwares as available in the Releases and the
[online flasher](https://trip5.github.io/ehRadio/firmware.html).

If you don't want to mess around with the code, already have a good idea on how the hardware works, and would just like to use a prebuilt binary,
check out the [Releases](https://github.com/trip5/ehRadio/releases/) and click on a link to open the generator with that binary's profile,
which includes hardware needed, pins to connect, and more.  Note that for inputs and peripherals, you can just nevermind the hardware as the radio
will still function perfectly without it... just your menu system will show things that don't exist.

### Trip5's Radios

...coming soon...

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

In May I began adding full support for Radio-browser API with the hope it would improve a user's experience. I also merged many of maleksm's mods.
That PR started [June 13, 2025](https://github.com/e2002/yoradio/pull/184) was abandoned June 19, 2025 with a ridiculous amount of changes.

In retrospect, proposing thousands of lines of changes was rude and unrealistic.  After some thought, ehRadio was officially forked August 10, 2025.

ehRadio currently uses the `ESP32-audioI2S` library from [Maleksm's ёRadio mod v0.9.512m](https://4pda.to/forum/index.php?showtopic=1010378&st=11240#entry125839228),
likely mostly from schreibfaul1's library [3.1.0 January 7, 2025](https://github.com/schreibfaul1/ESP32-audioI2S/releases/tag/3.1.0).
ehRadio also currently uses the `ESP32-vs1053_ext` library from Maleksm's ёRadio mod v0.9.512m, likely mostly from schreibfaul1's [final version](https://github.com/schreibfaul1/ESP32-vs1053_ext).
These libraries are so intertwined with the codebase that it may be impossible to migrate to newer versions, but... I will try.

For that and other major needed changes to the codebase, I maintain a `code-issues.md` file which may be a messy file to look at, depending on how these efforts are going.

I will add a note here that although I do use AI-assisted coding, I am not a "vibe-coder" - except for python scripts.

---

## Update History

### Updates

| Date       | Release Notes    |
| ---------- | ---------------- |
| 2026.05.20 | `Feature Freeze` Mostly fixes to `options.h`: some `BTN_` macros named wrong, `ENC_` macros renamed, generator updated, other fixes |
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
| 2025.08.10 | ehRadio fork begins, folders restructured, `data\` files stay uncompressed (compressed in from Releases, which radio can download), timezones.json updated automatically |
| 2025.07.23 | more options in WebUI |
| 2025.07.19 | PR to ёRadio v0.9.533: EEProm storage changed to Preferences, fixes for screens that can't display certain characters, ESPFileUpdater added (updates timezones and Radio Browser servers), proper timezones, many macros added to `myoptions.h`, Radio station search, Playback queue now RTOS background task, improved JSON and CSV file importing, maleksm's backlightdown and decoder improvements, ESP8266 support removed |

### Old Readme

A full history of ёRadio from v0.4.177 to v0.9.533 and to ehRadio 2026.05.08 can be seen in the [old Readme](README.old.md).

### Credit

Thanks to:
  - [Kasperaitis](https://github.com/kasperaitis) - for work initiating locales (WebUI and display language, display fonts, etc.) and a bunch of work for ES3C28P (including ES8311 decoder, ILI9341 battery widget, FT6336 touchscreen)
  - [e2002](https://github.com/e2002) - for [ёRadio](https://github.com/e2002/yoradio/)

