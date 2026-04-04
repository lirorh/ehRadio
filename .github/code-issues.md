# code-issues.md — ehRadio Issue Tracker

Working document for audit findings. Does **not** replace `code-summary.md` (the permanent operational bible).
Delete this file once all items are resolved or explicitly accepted.
Add `(ALL FIXED)` to title/section after issues are resolved.

**Severity**: `[HIGH]` = silent data corruption or crash risk | `[MEDIUM]` = incorrect behavior or user-facing bug | `[LOW]` = code quality / inconsistency | `[TRIVIAL]` = naming / doc only

---

## [X] 1. Dead or Misnamed Macros (Silent Failure Risk) (ALL FIXED)

These macros are mentioned in comments in `myoptions.h` as something a user can define, but they are **never consumed anywhere in `src/`**. Defining them produces no effect and no error — pure silent failure.

| Macro | Where it appears | Silent-failure scenario |
|---|---|---|
| `WEATHER_IMPERIAL` | `myoptions.h` comment | User defines it expecting imperial units. Nothing changes. Correct macros are `WEATHER_TEMPERATURE_F`, `WEATHER_PRESSURE_MMHG`, `WEATHER_WIND_SPEED_UNITS` (set by `#define WEATHER_METRIC false` in `options.h`). |
| `WEBUI_LANGUAGE_STRING` | `myoptions.h` comment | User defines it expecting to set the WebUI language. Nothing changes. Correct macro is `WEBUI_LOCALE` (used in `src/core/locale.h`). |

**Action**: Remove misleading comments, add correct names with examples in `myoptions.h`. `[MEDIUM]` — user-facing documentation bug.

---

## [X] 2. Dead Defines (Defined But Never Consumed) (ALL FIXED)

These macros are actually **defined** (not just commented) in `myoptions.h` board profiles but are **never read by any code in `src/`**.

| Fixed | Macro | Defined in | Notes |
|---|---|---|---|
| [x] | `PA_ENABLE` | `myoptions.h` ES3C28P profile | Defined as `1`. Zero matches in all of `src/` and in `ES8311_Audio/`. **The actual amp-enable is fully implemented via `MUTE_PIN 1` / `MUTE_VAL HIGH` in `player.cpp` (lines ~54 and ~214).** `PA_ENABLE` is a dead legacy name for the same GPIO — `MUTE_PIN` replaced it. Safe to remove from the profile. |
| [X] | `GFX_BL` | `myoptions.h` (commented out) | Zero matches in `src/`. Possibly a leftover from an alternate display backlight approach. |
| [x] | `TFT_MOSI`, `TFT_SCLK`, `TFT_MISO` | `myoptions.h` ES3C28P profile (values 11, 12, 13) | Zero matches in `src/`. Adafruit_ILI9341 does not read these macros — it takes a `SPIClass*` and calls `spi->begin()` with the bus defaults. Confirmed from `variants/esp32s3/pins_arduino.h`: ESP32-S3 devkitc-1 default SPI pins are exactly `MOSI=11, MISO=13, SCK=12`. These macros are 100% redundant — they match hardware defaults and are never consumed. |
| [x] | `TFT_BL` | `myoptions.h` ES3C28P profile (value 45) | Only exists to be aliased as `#define BRIGHTNESS_PIN TFT_BL`. `BRIGHTNESS_PIN` is the macro actually consumed by `main.cpp` (multiple sites) and has an `options.h` fallback (=255). No library reads `TFT_BL` directly. Could be collapsed to `#define BRIGHTNESS_PIN 45` removing the intermediate name. |
| [x] | `FF_FS_EXFAT` | `myoptions.h` comment — "Does this get carried to SD Lib?" | The comment itself expresses uncertainty. Zero matches in `src/`. Whether it propagates to the SD library at the linker/compile level is unclear. |

**Action**: Remove `PA_ENABLE` — amp control is covered by `MUTE_PIN`. Remove `TFT_MOSI`/`TFT_SCLK`/`TFT_MISO` — confirmed redundant to board defaults. Optionally collapse `TFT_BL` + `BRIGHTNESS_PIN` to a single define. Clarify `FF_FS_EXFAT`. `[LOW]` to `[MEDIUM]`.

---

## [ ] 3. Macros Without `options.h` Fallback

These macros are consumed in `src/` via `#ifdef`/`#if defined` guards (so they are safe when undefined), but they have **no fallback default in `options.h`**. This is inconsistent with how most settings are managed and makes them invisible to someone reading `options.h` for the full feature list.

| Fixed | Macro | Consumed in | Fallback location | Notes |
|---|---|---|---|---|
| [X] | `BIG_BOOT_LOGO` | `displayILI9488.h`, `displayST7796.h`, conf files | None — `#ifdef` only | Safe: undefined = no big logo. But undocumented in `options.h`. |
| [ ] | `DOWN_LEVEL` | `main.cpp` (heavily, with `#ifdef`) | None — optional feature | Safe: undefined = feature disabled. Only present in ILI9488 board profile. |
| [ ] | `DOWN_INTERVAL` | `main.cpp` (heavily, with `#ifdef`) | None — optional feature | Same as `DOWN_LEVEL`. |
| [X] | `FIRMWARE_NAME` | `network.cpp` lines ~337–346 via `#ifdef` | None | Safe: undefined = no firmware name in eHDP discovery. But boards built without a profile won't get a name, and there's no documented way to add one without knowing this macro exists. |
| [x] | `SDSPISPEED` | `sdmanager.cpp` | Fallback defined **inside `sdmanager.cpp`** itself (`#ifndef SDSPISPEED #define SDSPISPEED 20000000`), NOT in `options.h` | Inconsistent pattern. Works fine, but breaks the convention that `options.h` is the canonical fallback location. |
| [X] | `ESPFILEUPDATER_DEBUG` | `config.h` line ~13 via `#ifdef` | None — intentional debug flag | Safe but worth noting in `options.h` as a commented-out debug option. |
| [X] | `MQTT_ENABLE` | `mqtt.h`, `mqtt.cpp`, `netserver.cpp`, `player.cpp`, `commandhandler.cpp`, `main.cpp` — guards the entire MQTT subsystem | None — opt-in feature | Undefined = MQTT disabled. No `#ifndef MQTT_ENABLE` entry in `options.h`. Should appear as a commented-out stub so it's discoverable without consulting board profiles or README. |
| [X] | `RGB_LED_PIN` | `rgbled.cpp` — `#if defined(RGB_LED_PIN) && (RGB_LED_PIN!=255)` guards the entire NeoPixel module | None for `RGB_LED_PIN` itself; `RGB_LED_ORDER` falls back inside `rgbled.cpp`; `NUM_RGB_LEDS` is hardcoded as `1` in `rgbled.cpp` | Undefined = NeoPixel disabled. The `=255 means disabled` convention used for all other pin macros (MUTE_PIN, BRIGHTNESS_PIN, etc.) is not applied here — no options.h entry at all. |
| [X] | `MAX_PL_READ_BYTES` | `netserver.cpp` line ~312 — caps playlist body size during HTTP upload | None anywhere | Undefined = no upper limit on playlist read size. Tuning parameter that should have an options.h default (e.g., something like `65536`). |
| [X] | `PLAYLIST_DEFAULT_URL` | `config.cpp` line ~1307 — seeds default playlist on first boot | None | Undefined = no default playlist URL seeded. Silent, no fallback. Should have a commented stub in `options.h`. |
| [ ] | `SD_SPIPINS` | `config.cpp` line ~75, `sdmanager.h/cpp` — custom SPI pin tuple for SD card | None | Paired feature with `SD_HSPI` which HAS an `options.h` fallback, but `SD_SPIPINS` itself does not. Inconsistent. |
| [ ] | `TS_SPIPINS` | `touchscreen.cpp` lines ~27, ~46 — custom SPI pin tuple for touchscreen | None | Same asymmetry as `SD_SPIPINS` vs `SD_HSPI`. `TS_HSPI` has an `options.h` fallback; `TS_SPIPINS` does not. |
| [X] | `DEBUG_V`, `CORS_DEBUG`, `BATTERY_DEBUG` | Various `src/core/` files | None — intentional debug flags | Same category as `ESPFILEUPDATER_DEBUG`. Three separate debug flags with no options.h entry. Should be grouped as commented-out debug stubs. |

**Action**: Consider documenting these in `options.h` as commented-out stubs so they are discoverable. Move the `SDSPISPEED` fallback from `sdmanager.cpp` to `options.h`. Add `RGB_LED_PIN 255` default following the existing `=255 means disabled` pin convention. Add a default for `MAX_PL_READ_BYTES`. `[LOW]`.

---

## [ ] 4. Write-Only Variables (Set But Never Read)

### [ ] 4.1 `network.trueWeather` `[MEDIUM]`

- **Declaration**: `bool trueWeather;` in `src/core/network.h` line ~24
- **Written**: `config.cpp` (3 assignments), `network.cpp` `getWeather()` return value stored here (2 assignments including the return)
- **Read**: **Zero occurrences anywhere in `src/`**
- **Analysis**: `getWeather()` returns a `bool` indicating whether real weather data was received. The caller stores this in `trueWeather`, but no code path ever checks `trueWeather`. The variable appears intended to track "we have real data vs. placeholder" but the consuming logic was never written (or was removed). The indicator is silently discarded every time.
- **Action**: Either add consuming logic that uses `trueWeather` (e.g., suppress stale display when false), or remove the variable and ignore the return value explicitly at the call sites.

- Trip5 note: This is supposed to track if weather info held in cache is valid.  Is it seriously not being checked anywhere?  It's supposed to be refreshed according to config.store... weather interval?

---

## [ ] 5. Dead / Unreachable Code

### [ ] 5.1 `|| true` dead branch in `player.cpp` `[LOW]`

- **Line 132**: `if (strlen(file)==0 || true) return; //TODO Read TAGs`
- **Analysis**: `|| true` permanently short-circuits to `true`. Any code below this `return` is unreachable. This appears to be an acknowledged TODO — someone commented out the tag-reading functionality with `|| true` as a temporary measure that became permanent.
- **Action**: Either implement the tag-reading block and remove `|| true`, or remove the `|| true` and let `strlen(file)==0` be the real condition. The current state is confusing because it looks like a real condition check when it is not.

---

## [X] 6. Commandhandler Issues

### [X] 6.1 Command handlers in `config.cpp` that can be moved to `commandhandler.cpp` `[MEDIUM]`

The refactor pattern (as completed for `setSmartStart()`) is: inline the wrapper body into `commandhandler.cpp` and remove the wrapper from `config.cpp`/`config.h`. Functions that are also called from other places (`mqtt.cpp`, etc.) cannot be fully removed from `config.cpp` — those are noted separately at the bottom.

- [X] **`setSmartStart()`** — inlined; commandhandler now calls `config.saveValue` directly.
- [X] **`setShuffle(bool)`** — 2 lines: `saveValue` + `player.next()`. Easy.
- [X] **`setBalance(int8_t)`** — 3 lines: `saveValue` + `player.setBalance` + `requestOnChange`. Fix the dup + cast bugs from §6.4 and §6.5 at the same time.
- [X] **`enableScreensaver(bool)`** — `saveValue` + `#ifndef DSP_LCD display.putRequest(NEWMODE, PLAYER)`. Carry the `#ifndef DSP_LCD` guard into commandhandler.
- [X] **`setScreensaverTimeout(uint16_t)`** — `constrain(val,5,65520)` + `saveValue` + same `#ifndef DSP_LCD` guard. Note: brings its own input clamp.
- [X] **`setScreensaverBlank(bool)`** — same pattern as `enableScreensaver`.
- [X] **`setScreensaverPlayingEnabled(bool)`** — same pattern.
- [X] **`setScreensaverPlayingTimeout(uint16_t)`** — `constrain(val,1,1080)` + `saveValue` + `#ifndef DSP_LCD` guard.
- [X] **`setScreensaverPlayingBlank(bool)`** — same pattern as `enableScreensaver`.
- [X] **`setShowweather(bool)`** — 4 lines: `saveValue` + `network.trueWeather=false` + `network.forceWeather=true` + `display.putRequest(SHOWWEATHER)`.
- [X] **`setWeatherKey(const char*)`** — 4 lines: `saveValue` + `network.trueWeather=false` + two `display.putRequest` calls.
- [X] **`setIrBtn(int)`** — body is entirely inside `#if IR_PIN!=255`; the commandhandler caller is already inside that same guard, so the inline is clean.
- [X] **`setSDpos(uint32_t)`** — multi-branch (checks `PM_SDCARD`, calls `player.setResumeFilePos` / `player.setFilePos`). Candidate but less trivial than the above.

**Others Cannot be fully removed from `config.cpp`** (also called from non-commandhandler callers — deferred to §8.3):

### [X] 6.2 Sort all commands in `commandhandler.cpp` according to their order in WebUI (mostly-ish) `[LOW]`

Just sort them a bit into categories for future maintenance.

### [X] 6.3 config.SaveValue - booleans ignored for compatibility `[LOW]`

Originally kept for compatibility with existing yoRadio functions, booleans are ignored and thus can be removed everywhere in the codebase.

### [X] 6.4 Duplicate `balance` handler in `commandhandler.cpp` `[MEDIUM]`

- **Line ~30**: `if (strEquals(command, "balance")) { config.setBalance(atoi(value)); return true; }`
- **Line ~118**: `if (strEquals(command, "balance")) { config.setBalance(static_cast<uint8_t>(atoi(value))); return true; }`
- **Analysis**: The handler at line ~30 runs first and always returns `true`. The handler at line ~118 (inside the `//<-----TODO` block) is **unreachable dead code**. It will never execute.
- **Side effect of the dead code**: The cast at line ~118 is also wrong — it casts to `uint8_t` before passing to `int8_t`, which corrupts negative balance values (e.g., -10 → `uint8_t` 246 → `int8_t` -10 by accident in twos-complement, but values like -100 → `uint8_t` 156 → `int8_t` -100, so actually they happen to be equivalent for most values due to twos-complement... BUT the intent is wrong and a future reader would see a bogus cast).
- **The live handler (line ~30)** has its own problem: it passes raw `int` from `atoi()` directly with no cast and no range clamp (see Section 6.1 below).
- **TODO block context**: The `//<-----TODO` marker separates two groups of handlers. Commands BELOW the marker (`volume`, `sdpos`, `shuffle`, `reboot`, `format`, `submitplaylist`, `irbtn`, `chkid`, `irclr`, etc.) are **not duplicates** — they are the only handlers for those commands. Only `balance` is accidentally duplicated. This indicates an **incomplete refactoring**: some commands were being migrated or reworked, but the work stopped partway. The entire EQ missing-handler situation (`treble`, `bass`, `middle`) is a direct result of this same incomplete state — see Section 7.1.
- **Action**: Remove the dead handler at line ~118. Fix the live handler at line ~30 (see Section 6.1).

### [X] 6.5 Incorrect Casts / Type Safety Issues

#### [X] 6.5.1 `balance` command — no range clamp, implicit narrowing `[MEDIUM]`

- **File**: `src/core/commandhandler.cpp` line ~30
- **Code**: `config.setBalance(atoi(value))`
- **Signature**: `Config::setBalance(int8_t balance)` in `config.cpp`
- **Problem**: `atoi()` returns `int`. Passing it to `int8_t` is an implicit narrowing conversion. Values outside −128..127 silently truncate. No input validation. Compare how `dim` command clamps before cast (e.g., `val < 0 ? 0 : val > 100 ? 100 : val`).
- **Action**: Add `int b = atoi(value); b = (b < -16) ? -16 : (b > 16 ? 16 : b); config.setBalance(static_cast<int8_t>(b));` at the live handler. The correct range is **-16..16**, matching: (1) the HTML slider (`min="-16" max="16"`), (2) the `options.h` compile-time `SOUND_BALANCE` validation guard (`#elif (SOUND_BALANCE < -16) || (SOUND_BALANCE > 16)`). The prior suggestion of -100..100 in this document was incorrect.

#### [X] 6.5.1 `brightness` command — no range clamp before `uint8_t` cast `[MEDIUM]`

- **File**: `src/core/commandhandler.cpp` line ~69
- **Code**: `config.store.brightness = static_cast<uint8_t>(atoi(value));`
- **Problem**: `atoi()` on a negative or very large string silently wraps into a garbage `uint8_t`. The nearby `dim` command at line ~46 properly clamps with a ternary to 0..100.
- **Action**: Clamp `atoi(value)` to **0..100** before the cast (matching the HTML slider `min="0" max="100"` and the `dim` handler which also clamps to 0..100). Not 0..255.

#### [X] 6.5.2 `contrast` command — same pattern as `brightness` `[LOW]`

- **File**: `src/core/commandhandler.cpp` — the `contrast` command
- **Code**: `config.saveValue(&config.store.contrast, static_cast<uint8_t>(atoi(value)))`
- **Problem**: Same unclamped `uint8_t` cast. Input from the WebUI is expected to be 0..100 (HTML slider `min="0" max="100"`) but no firmware guard enforces this.
- **Action**: Clamp to **0..100** before cast, consistent with the HTML slider range.

## [X] 7. Unhandled or Mis-handled Web UI Commands

### [X] 7.1 `treble`, `middle`, `bass` bypass `commandhandler` — split routing `[MEDIUM]`

- **Context**: All four EQ sliders in `player.html` have `data-command` values matching their names (`balance`, `treble`, `middle`, `bass`), all with `min="-16" max="16"`. Moving a slider sends `command=value` via WebSocket.
- **`balance`**: Handled in `commandhandler.cpp` at line ~30 (above the `//-----TODO` marker).
- **`treble`, `middle`, `bass`**: **Not present in `commandhandler.cpp` at all.** They are intercepted in `netserver.cpp` directly (lines ~614–627), *before* `cmd.exec()` is called, in the raw WebSocket message handler.
- **Split routing impact**: Commands handled in `netserver.cpp` before `cmd.exec()` are invisible to any command source that doesn't go through `netserver.cpp`. **Neither MQTT nor telnet routes through `cmd.exec()` today** — both have their own separate hardcoded dispatch loops (`mqtt.cpp` `onMqttMessage()` and `telnet.cpp` `on_input()`). Concretely: none of `balance`, `treble`, `middle`, or `bass` are reachable via MQTT or telnet in any form — `balance` happens to be in `commandhandler.cpp` but that file isn't called from either subsystem.
- **Root cause**: `treble`/`middle`/`bass` were added directly to `netserver.cpp` as a shortcut while `balance` was added to `commandhandler` as part of the incomplete TODO-block refactoring (see Section 5.1). The intent was clearly for all four to be in `commandhandler`, but the work was never finished.
- **Action**: Move the `treble`, `middle`, `bass` handlers from `netserver.cpp` into `commandhandler.cpp` alongside `balance`. Use `config.setTone()` the same way those handlers already do. Add appropriate clamping (see Section 7.2).

### [X] 7.2 All four EQ commands lack server-side range clamping `[MEDIUM]`

- **`treble`, `middle`, `bass`** handlers in `netserver.cpp`: `int8_t valb = atoi(val)` is an implicit narrowing cast with no range validation.
- **`balance`** handler in `commandhandler.cpp`: passes raw `atoi(value)` directly to `int8_t` param (see Section 6.1 for the live handler; section 6.1 recommended clamp has been corrected to -16..16 in this update).
- The valid range **-16..16** is enforced consistently in three places: (1) HTML sliders with `min="-16" max="16"`, (2) `options.h` `SOUND_BALANCE` guard `#elif (SOUND_BALANCE < -16) || (SOUND_BALANCE > 16)`, and (3) `options.h` `EQ_TREBLE`/`EQ_MIDDLE`/`EQ_BASS` guards with the same -16..16 bounds. The firmware runtime handlers are the only place that does not enforce this.
- **Action**: Each EQ command handler should clamp: `int v = atoi(val); v = (v < -16) ? -16 : (v > 16 ? 16 : v); config.setXxx((int8_t)v);`

### [X] 7.3 `volume` command (WebUI slider) vs `vol` command — inconsistent behavior `[MEDIUM]`

- **HTML sends `volume=N`**: The volume slider uses `data-command="volume"`, so `sliderInput()` sends `volume=N` to the backend.
- **Handler for `volume=N`** (commandhandler.cpp TODO block, line ~119): `player.setVol(static_cast<uint8_t>(atoi(value)))` — queues `PR_VOL` asynchronously; `config.store.volume` is only updated when the queue processes (via `config.setVolume()` inside `PR_VOL` handler in `player.cpp`).
- **Handler for `vol=N`** (commandhandler.cpp line ~40, above TODO): Clamps value to 0..254, **synchronously** updates `config.store.volume = clamped_v`, then queues `player.setVol(v)`. This is the robust path used by MQTT, telnet, and IR.
- **Behavioral differences**:
  1. `volume` handler: no clamp before `uint8_t` cast (negative values or values > 255 silently wrap).
  2. `volume` handler: `config.store.volume` lags until `PR_VOL` processes. If `VOLUME` is broadcast between receiving the command and the queue processing, the old value is reported.
  3. `vol` handler: proper clamp, immediate synchronous config update.
- **Action**: Either consolidate both commands into one handler using the `vol` pattern (clamp + synchronous update), or fix the `volume` handler to match: clamp to 0..254 and synchronously set `config.store.volume` before calling `player.setVol()`.

### [X] 7.4 `submitplaylistdone` intercepted in `netserver.cpp` before `cmd.exec()` `[LOW]`

- **Location**: `netserver.cpp` `onWsMessage()`, lines ~630–645 — handled **before** `cmd.exec()` is called.
- **Sent by**: `script.js` sends `websocket.send('submitplaylistdone=1')` after the server has confirmed the playlist file was saved. This triggers MQTT republish and playlist-length validation in the firmware.
- **Routing impact**: Same as 8.1 — any MQTT or telnet path that sends `submitplaylistdone` falls through `cmd.exec()` unhandled (returns `false`). Currently this only matters for testing or automation, since it's an internal JS signal.
- **Action**: Low priority. Consider moving to `commandhandler.cpp` for consistency.

---

## [ ] 8. Unified Command Dispatch — Route MQTT, Telnet, and URL Parameters Through `commandhandler.cpp` `[MEDIUM]`

Today there are **four separate, independent command dispatch tables** that must all be updated when a command changes:

- **WebSocket** (from WebUI): `netserver.cpp` `onWsMessage()` → `cmd.exec()` in `commandhandler.cpp`
- **MQTT**: `mqtt.cpp` `onMqttMessage()` — own hardcoded handler, ~10 commands only
- **Telnet / Serial**: `telnet.cpp` `on_input()` — own hardcoded handler, a different ~15-command set
- **HTTP GET** (URL params): `netserver.cpp` `handleIndex()` — single-param calls already route through `cmd.exec()`, but multi-param combinations have hardcoded special cases that bypass it

Adding or fixing a command currently means updating up to four files. The refactor goal is to make `commandhandler.cpp` the **single source of truth** for all command logic, with MQTT, Telnet, and HTTP GET routing through it via thin parser shims. This is also the prerequisite for §6.1 (moving `config.cpp` wrappers into `commandhandler`) to have full system-wide effect.

### [ ] 8.1 Route MQTT Through `commandhandler` `[MEDIUM]`

**Current state**: `onMqttMessage()` in `mqtt.cpp` manually handles: `prev`, `next`, `toggle`, `stop`, `start`/`play`, `boot`/`reboot`, `voldown`/`volm`, `volup`/`volp`, `turnoff`, `turnon`, `vol N`, `play N`, and raw URL strings (`burl`). All other `commandhandler.cpp` commands are unreachable via MQTT.

**Strategy**:
1. Add a `burl` command to `commandhandler.cpp` that loads a URL directly into `player.burl` and sends `PR_BURL` — currently only reachable via raw MQTT long-payload path.
2. Keep `turnoff` / `turnon` as thin wrappers in `onMqttMessage()` (they combine `setDspOn` + `smartstart` logic that has no single commandhandler equivalent), or add them to commandhandler.
3. For short payloads (`len < 20`), parse `"key value"` or `"key=value"` format, split into `cmd`/`val`, and call `cmd.exec(cmd, val, 0)`.
4. Replace the remaining manual handlers with the `cmd.exec()` call once all equivalents are confirmed present in `commandhandler`.

**Commands to block from MQTT dispatch** (do not forward to `cmd.exec()`):

| Command | Reason to block |
|---|---|
| `get*` family (`getsystem`, `getscreen`, `getlocale`, `getcontrols`, `getweather`, `getmqtt`, `getactive`, `getbattery`, `getindex`) | These trigger `netserver.requestOnChange()` which broadcasts JSON over WebSocket to a web client. Via MQTT the response is silently lost — wasted work always. |
| `rebootmdns` | Restarts after a short delay and no longer calls `websocket.text(cid, ...)` (the old cid misrouting issue is fixed). |
| `newmode` | Sets `config.newConfigMode` and triggers `requestOnChange(CHANGEMODE)` — an interactive WebUI display-flow command with no meaning over MQTT. |

**Commands that need care but are otherwise safe**:

| Command | Note |
|---|---|
| `reboot`, `format`, `clearspiffs` | Destructive. Consider gating behind `#ifdef MQTT_ALLOW_DANGEROUS_COMMANDS` (opt-in at build time). Currently `reboot` is already handled inline in `onMqttMessage()`. |
| `battref` | Calibration; calls `netserver.requestOnChange(GETBATTERY, cid)` with `cid=0` — sends WebSocket feedback to client 0. The calibration save still works; only the WebSocket confirmation is misdirected. |
| `curated_import`, `loadindex`, `loadplaylist` | Send `websocket.text(cid, ...)` inline responses. Via MQTT `cid=0` — file operations succeed but feedback is misdirected to a WebSocket client. |

### [ ] 8.2 Route Telnet Through `commandhandler` `[MEDIUM]`

**Current state**: `telnet.on_input()` has its own ~15-command hardcoded handler covering `prev`, `next`, `toggle`, `stop`, `start`, `vol`, `vol±`, battery commands, `date`, `audioinfo`, `smartstart`, `list`, `info`, and a few others. Commands added to `commandhandler.cpp` are not automatically accessible from telnet. This is the "duplicated command form list vs. `commandhandler.cpp`" problem noted in §13 (Stability Risks).

**Strategy**: Telnet-native commands stay in `on_input()` because they produce telnet-specific formatted output (e.g., `cli.list` prints a numbered station list, `cli.info` prints status lines, `calbatt` has interactive multi-line calibration output). For everything else, fall through to `cmd.exec()` at the bottom of `on_input()` before the `show_prompt` label:

```cpp
// At end of on_input(), before show_prompt:
char tcmd[64] = {0}, tval[BUFLEN] = {0};
if (config.parseWsCommand(str, tcmd, tval, sizeof(tcmd))) {
    if (cmd.exec(tcmd, tval, clientId)) goto show_prompt;
}
```

`parseWsCommand()` already splits `"key=value"` format used by WebSocket messages. Telnet also uses `"key value"` and `"key(value)"` forms — either extend the parser or add a simple space-split before the fallthrough.

**Commands to block from telnet dispatch** (handle in `on_input()` with a CLI response instead):

| Command | Reason |
|---|---|
| `get*` family | Triggers `requestOnChange()` → JSON broadcast over WebSocket. These could eventually be rerouted to print on the telnet stream, but that requires a netserver refactor. For now: block and print `##CLI.UNSUPPORTED#`. |
| `rebootmdns` | Restarts after a short delay and no longer calls `websocket.text(cid, ...)`, so telnet/WebSocket client-id namespace confusion is removed for this command. |
| `curated_import`, `loadindex`, `loadplaylist` | Same `websocket.text(cid, ...)` namespace mismatch. Block or add telnet-specific response. |

- [X] `rebootmdns` websocket redirect/cid-misdirection bug fixed by removing backend redirect payloads and handling redirect timing entirely in browser-side ready polling.

**⚠️ Client ID namespace collision — important hazard**:

Telnet client IDs are `0`–`(MAX_TLN_CLIENTS-1)` (typically 0–4), assigned by telnet slot number. WebSocket client IDs are assigned by `AsyncWebSocket`, also starting from 0. Any place in `commandhandler.cpp` that calls `websocket.text(cid, ...)` with the `cid` argument will accidentally target a real WebSocket client when the caller is telnet. **Audit every `websocket.text(cid, ...)` call in `commandhandler.cpp` before routing telnet through it.** Proposed mitigation: define `#define CID_NO_WEBSOCKET 255` and pass that from the telnet shim — handlers can then check `if (cid != CID_NO_WEBSOCKET) websocket.text(cid, ...)`.

**Commands immediately available once routed through `cmd.exec()`** (none of these call `websocket.text(cid,...)`):
`balance`, `volume`, `shuffle`, `screensaver*`, `wenable`, `wapi`, `wlat`/`wlon`, `locale_webui`, `tz_name`, `tzposix`, and all other settings commands. Also `treble`/`middle`/`bass` once moved from `netserver.cpp` per §7.1.

**Payoff**: Every future command added to `commandhandler.cpp` automatically becomes available from the telnet CLI with zero additional code.



### [ ] 8.3 Route URL Parameters Through `commandhandler` `[LOW]`

**Current state**: `handleIndex()` in `netserver.cpp` already routes single-param GET requests through `cmd.exec()` (e.g., `/?vol=50`, `/?play=3`, `/?toggle=1`). However, multi-param combinations fall through to hardcoded special cases instead of iterating through all params. Two legacy cases remain (see §8.5.1 and §8.5.2).

**Strategy**:
1. Add `sleep` to `commandhandler.cpp` — value is sleep minutes, `after` offset defaults to 0. Single-param `/?sleep=30` sleeps immediately; two-param `/?sleep=30&after=5` is handled by the loop executing both params.
2. Replace the `paramsNr==1` guard in `handleIndex()` with a loop over all params, calling `cmd.exec()` for each. This makes `/?treble=3&middle=0&bass=-2` route through the existing clamped handlers and `/?sleep=30` route through the new `sleep` handler.
3. Keep a targeted two-param carve-out only for `sleep`+`after` (since `after` is not a standalone command and needs to be passed together with `sleep` to `config.sleepForAfter()`), or extend the `sleep` handler to read `after` from a pre-scanned request context.
4. Special-case carve-out: `reset` and `clearspiffs` still need `request->redirect("/")` after `cmd.exec()` — the loop must check for these by name after executing.
5. Once the loop is in place, remove the hardcoded `treble`+`middle`+`bass` block (§8.5.2) and the `sleep`+`after` block (§8.5.1) — both are superseded.

### [ ] 8.4 Move `setDspOn` and `setBrightness` to `commandhandler.cpp` `[MEDIUM]`

Once MQTT and Telnet are routed through `commandhandler` (per §8.1 and §8.2), `setDspOn` and `setBrightness` can be moved from `config.cpp` into `commandhandler.cpp`. Both are currently too multi-path to inline cleanly, and both have non-commandhandler callers that only survive as long as MQTT/telnet have separate dispatch loops. After §8.1+§8.2 unification, their only callers will be in `commandhandler` and they can be inlined.

### [ ] 8.5 Commands with No HTML Entry Point

These commands exist in `commandhandler.cpp` (or elsewhere in firmware) but **cannot be triggered from any `.html` file** in the WebUI. They are reachable only via MQTT, telnet, HTTP GET URL params, or are effectively inaccessible to most users.

| Fixed | Command | Handler location | How accessible | Notes |
|---|---|---|---|---|
| [ ] | `start` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?start=1` | Plays last station. No HTML button. The WebUI uses `toggle` for play/pause instead. |
| [ ] | `stop` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?stop=1` | Stops playback. No HTML button. |
| [ ] | `dspon` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?dspon=N` | Identical to `screenon`. Both remain in commandhandler but their HTML element is **commented out** in `options.html` line 120 with note: *"Left from yoRadio but seems to have no purpose"*. |
| [ ] | `screenon` | `commandhandler.cpp` | MQTT, telnet | Same as `dspon`. HTML element commented out. |
| [ ] | `clearspiffs` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?clearspiffs=1` | Clears SPIFFS and resets play mode. No HTML button. Useful for factory cleanup but not exposed to users. |
| [ ] | `sleep` | `netserver.cpp` `handleIndex()` | HTTP `/?sleep=N&after=N` **only** | Schedules sleep timer. No WebSocket handler. No HTML. |
| [ ] | `playstation` | `commandhandler.cpp` (alias for `play`) | MQTT, telnet | The HTML uses `play=N` (via `websocket.send(\`play=${item}\`)`). `playstation` is a legacy alias; both spellings work. |

**Notes**:
- `start`, `stop`, and `dspon`/`screenon` are yoRadio leftovers that were never assigned HTML buttons in the ehRadio fork. Their presence in `commandhandler.cpp` is not harmful — they remain useful for MQTT/telnet automation — but they add dead weight to the handler if never used interactively.
- `clearspiffs` and `sleep` are subtle traps: a user configuring MQTT automations would have no way to discover these commands from the WebUI documentation or source code without reading `commandhandler.cpp` directly.

**Action items**:
- `dspon` / `screenon`: Remove the duplicate or point both to the same implementation. Decide whether to restore the HTML element or remove the command.
- `sleep`: Expose via a WebUI sleep-timer control (options page) or remove from firmware if the feature is not intended for production use.
- Document all MQTT/telnet-accessible commands in one place (currently they must be inferred by reading `commandhandler.cpp` and `telnet.cpp` separately).

#### [ ] 8.5.1 `sleep` / `after` — HTTP GET only, no WebSocket path `[MEDIUM]`

- **Location**: `netserver.cpp` `handleIndex()`.
- **Code**: `if (request->hasArg("sleep")) { ... config.sleepForAfter(sford, safterd); ... }`
- **What it does**: Schedules the device to sleep for `sleep` minutes, starting `after` minutes from now.
- **Access**: HTTP GET URL parameters only — e.g., `http://device/?sleep=30&after=5`. No WebSocket equivalent, no MQTT/telnet path, no HTML entry point.
- **Action**: Add `sleep` to `commandhandler.cpp` (per §8.3 strategy). Once the §8.3 loop is in place this hardcoded block is fully superseded and can be safely removed. Consider also exposing `sleep` via the WebUI settings page once it is in commandhandler.

#### [ ] 8.5.2 HTTP GET `treble`+`middle`+`bass` multi-param route `[LOW]`

- **Location**: `netserver.cpp` `handleIndex()`.
- **Code**: `if (request->hasArg("treble") && request->hasArg("middle") && request->hasArg("bass")) { config.setTone(...) }`
- **Analysis**: Legacy URL-parameter API that sets all three EQ bands at once (`http://device/?treble=3&middle=0&bass=-2`). Not used by any current JS code. No clamping applied.
- **Action**: Once §8.3 loop is in place, each param is dispatched individually through the existing clamped commandhandler handlers. This hardcoded block is then fully superseded and can be safely removed.

---


## [X] 9. Logic / Correctness Bugs

### [X] 9.1 `display.cpp` — `while(!_bootStep==0)` precedence bug `[MEDIUM]`

- **Line 113**: `while(!_bootStep==0) { delay(10); }`
- Due to C++ operator precedence, this evaluates as `(!_bootStep) == 0`. When `_bootStep = 0` (initial state), `!0 = 1`, `1 == 0 = false` → loop exits immediately without waiting. When `_bootStep = 1` or `2`, `!x = 0`, `0 == 0 = true` → loop runs indefinitely.
- Likely intent was `while(_bootStep == 0)` (wait for boot to start) or `while(_bootStep < 2)` (wait for boot to complete).
- `_bootStep` is `uint8_t` in `display.h` line ~83.

### [X] 9.2 `netserver.cpp` — upload cleanup deletes wrong file `[HIGH]`

- Upload cleanup block: `if (SPIFFS.exists(INDEX_PATH)) SPIFFS.remove(PLAYLIST_PATH)` — should call `SPIFFS.remove(INDEX_PATH)`. The index file is never cleaned up; the playlist may be deleted instead.

### [X] 9.3 `optionschecker.h` — weather interval guard mismatch `[LOW]` (FIXED)

- Guard message says "10 to 60" but the enforced condition is "1 to 24". Message and bounds are mismatched.

### [X] 9.4 `netserver.cpp` — `selectRadioBrowserServer()` `size_t` underflow `[HIGH]`

- `for (size_t i = count - 1; i > 0; --i)` runs even when `count == 0`. `size_t` is unsigned, so `0 - 1` wraps to a very large value and the loop indexes out of bounds.
- `rb_servers[count] = RADIO_BROWSER_SERVER` also writes past the array end when `count == arr_size`.

---


## [ ] 10. `BUFLEN` — Multi-Purpose Magic Number

`BUFLEN = 170` is defined in `options.h` (`#define BUFLEN 170 // 170 seems safe... a lot of multipliers exist in the code...`). The comment itself is a warning sign: "a lot of multipliers exist" means 170 was already insufficient for some callers when it was written.

### 10.1 Call-site inventory

| Call site | File | Purpose | Notes |
|---|---|---|---|
| `StationInfo::name[BUFLEN]`, `::url[BUFLEN]`, `::title[BUFLEN]` | `config.h` struct | Runtime RAM fields — populated from SPIFFS playlist file | **Not NVS-stored.** Only `store.lastStation` (a `uint16_t` index) is persisted. `station.title` is from stream metadata, never saved. Changing BUFLEN just changes truncation threshold for long names/URLs. |
| `Config::_stationBuf[BUFLEN/2]` | `config.h` | Temporary CSV row parsing buffer | Consistent with playlist tab-fragment size |
| `sName[BUFLEN]`, `sUrl[BUFLEN]` | `config.cpp`, `telnet.cpp` | Stack temps matching struct field size | Consistent |
| `utf8_common.h`, `utf8Latin.cpp`, `utf8Cyrillic.cpp`, `nextion.cpp` | Display tools | Transliteration output buffer | Correct to match `title` field size |
| `audiohandlers.h` `b[BUFLEN/2]` | Audio handlers | Bitrate info string (85 bytes) | Adequate for bitrate strings |
| `audiohandlers.h` `tmp[BUFLEN]` | Audio handlers | Station title + audio info combined | Appropriate |
| `nomedia[BUFLEN]` | `sdmanager.cpp` | SD path building (`path + "/.nomedia"`) | Wrong semantic — SD paths can exceed 170 chars |
| `wsbuf[BUFLEN*2]`, `payload[BUFLEN*2]`, `buf[BUFLEN*2]`, `msgBuf[BUFLEN*2]`, `varjsbuf[BUFLEN*2]` | `netserver.cpp` | WebSocket JSON payloads, URL buffers | `*2` multiplier is a code smell — see 10.2 |
| `buf[BUFLEN]`, scratch uses | `telnet.cpp`, `netserver.cpp` | Short `snprintf` scratch buffers | Acceptable for short messages |
| `BOOTLOG` macro | `telnet.h` | Boot log buffer with bare `sprintf` | Overflow risk — cross-ref Section 11 |

### 10.2 The `*2` and `/2` multiplier smell `[MEDIUM]`

Five places in `netserver.cpp` use `BUFLEN*2` (340 bytes) because 170 was insufficient for JSON payloads. The code doubled an already-arbitrary number rather than defining an appropriately-sized constant. This conflates two unrelated constraints in one macro:

- **`wsbuf[BUFLEN*2]` with bare `sprintf`**: embeds `config.station.name` (up to 170 bytes) and `config.station.title` (up to 170 bytes) simultaneously into a 340-byte buffer with JSON framing overhead. At worst-case inputs, this is structurally too small. Already flagged in Section 11 as unsafe `sprintf`.
- The multiply/divide pattern (`*2`, `/2`) makes the actual buffer sizes invisible and means any future change to `BUFLEN` for the struct silently changes all these buffers too.

### 10.3 No NVS tie-in — RAM only `[correction]`

`station_t` (`name`, `url`, `title`) is **not stored in NVS**. `loadStation()` reads the SPIFFS playlist file at runtime and fills `station` in RAM. `station.title` is set from audio stream metadata and is never persisted. The only NVS save is `store.lastStation` — a `uint16_t` index.

Changing `BUFLEN` carries **no NVS migration risk**. The only behavioral change would be the truncation threshold for very long station names or URLs read from the playlist. Raising it does increase stack frame sizes wherever `char buf[BUFLEN]` locals are declared. The `*2` multipliers in `netserver.cpp` still exist as a sizing smell, but the cause is simpler: the JSON payload combining name + title was larger than a single BUFLEN.

### 10.4 Relationship to `RXBUFLEN` / `TXBUFLEN`

`RXBUFLEN = 50` and `TXBUFLEN = 255` are defined in `src/displays/nextion.h`. They are **completely unrelated** to `BUFLEN` — they are Nextion serial protocol frame sizes. The naming similarity is coincidental.

### 10.5 Other buffer-size constants not derived from `BUFLEN`

| Constant | Where | Value | Notes |
|---|---|---|---|
| `SET_PLAY_ERROR` buff size | `player.h` macro | `512 + 64` = 576 | Fixed literal; independent. Bare `sprintf` — see Section 11. |
| `DBGVB` buf size | `netserver.cpp` macro | `200` | Fixed literal; bare `sprintf` — see Section 11. |
| `MAX_PRINTF_LEN` | `telnet.h` | `BUFLEN + 50` = 220 | Derived from `BUFLEN`. If `BUFLEN` changes, this changes silently too. |
| `EHDPNAME_LENGTH` | `config.h` | `24` | Named purpose-specific constant — **this is the right pattern**. |

### 10.6 Recommended resolution `[LOW]`

The core problem: `BUFLEN` conflates two distinct things that happen to share one numeric value:
1. **Station field size** (`StationInfo` fields and matching transliteration buffers) — the meaningful semantic is "max station name/URL/title length".
2. **General scratch sentinel** — arbitrary "safe size" for stack temporaries.

Recommended approach: introduce `STATION_FIELD_LEN` (or similar) for category 1, making the intent explicit. Leave `BUFLEN` as-is or remove it for category 2. Replace `BUFLEN*2` and `BUFLEN/2` with purpose-named sizes or comment-justified literals. This is a **refactor, not an urgent fix** — nothing is currently broken solely because of `BUFLEN` — and unlike the previous analysis, there is **no NVS migration risk** involved.

### [ ] 10.7 Replacing `BUFLEN` Usage as a Magic Number

Each call site below should be investigated and given either a purpose-specific named constant or an inline literal with a justifying comment.

- [ ] `StationInfo::name[BUFLEN]`, `::url[BUFLEN]`, `::title[BUFLEN]` (`config.h`) — primary semantic: "max station name/URL/title length". Candidate: introduce `STATION_FIELD_LEN 170`.
- [ ] `Config::_stationBuf[BUFLEN/2]` (`config.h`) — name explicitly (e.g., `STATION_FIELD_LEN/2`) or justified inline literal.
- [ ] `sName[BUFLEN]`, `sUrl[BUFLEN]` in `config.cpp`, `telnet.cpp` — stack temps matching struct field size; update to follow `STATION_FIELD_LEN` once defined.
- [ ] Transliteration output buffers in `utf8_common.h`, `utf8Latin.cpp`, `utf8Cyrillic.cpp`, `nextion.cpp` — should match `title` field size; update to `STATION_FIELD_LEN`.
- [ ] `b[BUFLEN/2]` in `audiohandlers.h` (bitrate string, 85 bytes) — adequate size; name it or leave as explicit literal with comment.
- [ ] `tmp[BUFLEN]` in `audiohandlers.h` (title + audio info combined) — appropriate; update to `STATION_FIELD_LEN`.
- [ ] `nomedia[BUFLEN]` in `sdmanager.cpp` (SD path building) — wrong semantic; SD paths can exceed 170 chars. Replace with a purpose-specific `SD_PATH_LEN` or explicit larger literal.
- [ ] `wsbuf[BUFLEN*2]`, `payload[BUFLEN*2]`, `buf[BUFLEN*2]`, `msgBuf[BUFLEN*2]`, `varjsbuf[BUFLEN*2]` in `netserver.cpp` — the `*2` is the smell. Each should become a justified literal or purpose-named size.
- [ ] `buf[BUFLEN]` scratch uses in `telnet.cpp`, `netserver.cpp` — evaluate each; either leave with an explicit literal + comment, or retain `BUFLEN` if it remains as a general scratch sentinel.
- [ ] `BOOTLOG` macro buffer `buf[BUFLEN]` in `telnet.h` — also has bare `sprintf` overflow risk (cross-ref Section 11); address rename alongside `snprintf` fix.
- [ ] `MAX_PRINTF_LEN = BUFLEN + 50` in `telnet.h` — must not silently change if `BUFLEN` changes for other reasons. Replace with explicit `220` or `STATION_FIELD_LEN + 50` with comment.

---

## [X] 11. Unsafe String Handling / Buffer Overflow Risks

| Fixed | Location | Issue |
|---|---|---|
| [X] | `config.cpp` `u8fix()` | `src[strlen(src)-1]` with no empty-string guard — UB if `strlen(src) == 0`. |
| [X] | `sdmanager.cpp` | `strrchr(filePath, '/') + 1` — if `strrchr` returns NULL, `NULL+1` is UB. |
| [X] | `nextion.cpp` rx buffer | `rx_pos` incremented without bounds check against `RXBUFLEN` (50). Overflow on long frames. |
| [X] | `nextion.cpp` `sscanf` | `sscanf(rxbuf, "page=%s", scanBuf)` uses `%s` without width; `scanBuf[50]` can overflow by prefix length. |
| [X] | `commandhandler.cpp` `irclr` | `config.irindex` initialized to -1; `irVals[config.irindex][...]` is out-of-bounds if `irclr` sent before `chkid`. Also second subscript from `atoi` can be 0–255 but array dim is only 3. |
| [X] | `netserver.cpp` `STATIONNAME`/`TITLE` | `sprintf(wsbuf, ...)` embeds ~170-byte fields into a 340-byte buffer with JSON framing. Near-limit inputs can overflow. |
| [X] | `netserver.cpp` `DBGVB` macro | `char buf[200]; sprintf(buf, __VA_ARGS__)` — VA_ARGS controlled by callers, no overflow guard. |
| [X] | `network.cpp` `strcpy(weatherBuf, LANG::weather_loading)` | `weatherBuf` is 254 bytes; locale string has no enforced max. Long translations overflow. |
| [X] | `network.cpp` weather builder | Chained `sprintf` advancing pointer `p` across `weatherBuf` (254 bytes) with no remaining-length checks. |
| [X] | `telnet.h` `BOOTLOG` macro | `sprintf(buf, __VA_ARGS__)` into `buf[BUFLEN]` (170 bytes); no VA_ARGS overflow guard. |
| [X] | `player.h` `SET_PLAY_ERROR` macro | `sprintf(buff, __VA_ARGS__)` into `buff[576]`; caller-controlled VA_ARGS. |
| [X] | `widgets.cpp` date string | `sprintf(_tmp, "%2d %s %d", ..., LANG::mnths[...], ...)` into `_tmp[30]`; UTF-8 month names have more bytes than display characters; 30-byte buffer can overflow with multi-byte locale encodings. |

---

## [X] 12. WebUI / JavaScript Security Issues

| Fixed | Location | Issue |
|---|---|---|
| [X] | `data/www/search.js` | `${station.name}` injected into `innerHTML` without escaping. Station names from Radio Browser API (external, untrusted). Script injection risk. `escapeHtml()` exists in `curated.js` but not applied here. |
| [X] | `data/www/curated.js` | `curatedName` injected into `innerHTML` without escaping. `escapeHtml()` now applied. Note: `curatedLink` href scheme validation was reviewed and decided unnecessary (build-time SPIFFS data, not external API input). |

---

## [ ] 13. Stability / Architecture Risks

- `nextion.cpp`: file starts with explicit warning comment that implementation may be broken; treat as unstable until revalidated.
- `telnet.cpp`: duplicated command form list vs. `commandhandler.cpp`; new settings added to one path are easily missed in the other.
- `touchscreen.h`: enum member naming inconsistency `TDS_REQUEST` vs. `TSD_*` pattern.
- Heavy async queue and task usage — ordering/race conditions are possible (display queue, netserver queue, search/curated/update tasks).
- SPIFFS space constraints can silently break search, curated, and update workflows.

---

## [ ] 14. Dead / Redundant Includes (`netserver.cpp`) `[LOW]`

`src/core/netserver.cpp` contains duplicate `#include` directives (include guards make them a no-op at compile time, but they add noise):

| Fixed | Duplicate | Lines |
|---|---|---|
| [ ] | `#include "config.h"` | Lines 7 AND 11 — two identical includes |
| [ ] | `#include "options.h"` | Lines 1 AND 15 — two identical includes |
| [ ] | `//= #include <ESPmDNS.h>` | Line 25 — commented-out redundant copy of the active include on line 5 |

**Action**: Remove the second `#include "config.h"` (line 11), the second `#include "options.h"` (line 15), and the commented-out dead include on line 25. `[LOW]` — no runtime impact.

---

## [X] 15. Include Path Convention Inconsistency `[TRIVIAL]`

Most `src/core/*.cpp` files include peer headers using relative names (`#include "battery.h"`), but `battery.cpp` and `rgbled.cpp` use fully-prefixed paths (`#include "core/battery.h"`, `#include "core/rgbled.h"`) even for their **own** headers. This works because PlatformIO exposes both `src/` and `src/core/` as include roots, but the mixed convention is confusing.

Notable cases:
- `battery.cpp` includes `"core/battery.h"` (self-include with prefix) and all peers with `"core/xxx.h"`
- `rgbled.cpp` includes `"core/rgbled.h"` (self-include with prefix)
- `commandhandler.cpp` includes `"core/battery.h"` but `"commandhandler.h"` without prefix

**Action**: Normalise to either all-relative (preferred for files in `src/core/`) or all-prefixed, not mixed. Low priority but makes `#include` scanning clearer. `[TRIVIAL]`

---

## [ ] 16. `battery.cpp` / `battery.h` — C-style module should be refactored to class + global instance `[LOW]`

`battery.cpp` was written as a C-style module (free functions + file-static state) rather than following the codebase convention of a C++ class with a single global instance declared `extern` in the header.

Every other core module follows the same pattern:
- **Class** defined in `.h` (e.g. `class Config`, `class NetServer`, `class Player`)
- **Single global instance** defined in `.cpp` (e.g. `Config config;`)
- **`extern` declaration** in `.h` so any includer gets the named global (e.g. `extern Config config;`)
- Callers use `config.saveValue(...)`, `netserver.requestOnChange(...)`, `player.setVol(...)`, etc.

`battery.cpp` instead exposes bare functions: `battery_init()`, `battery_loop()`, `battery_recalc_now()`, `battery_calibrate()`, `battery_get_status()`, etc., with all state in file-static variables. This works but is inconsistent with every other core module. The §8 MQTT/telnet consolidation does **not** depend on this refactor — `battery_calibrate()` and friends are already clean free functions that commandhandler calls fine today and will continue to call fine after §8. This is purely a long-term consistency item.

**Suggested refactor** (future, not urgent):
1. Define `class Battery` in `battery.h` with public methods mirroring current free functions (`init()`, `loop()`, `recalcNow()`, `calibrate(int meas_mv)`, `getStatus()`, `isInitialized()`, `formatStatusLine(...)`, `bootStatus()`).
2. Move all file-static state to private members of the class.
3. Define `Battery battery;` in `battery.cpp` and `extern Battery battery;` in `battery.h`.
4. Update all callers: `commandhandler.cpp`, `telnet.cpp`, `netserver.cpp`, `main.cpp` (and any display drivers that call `battery_get_status()`).
5. The `#if` hardware guard should wrap the class body or use a no-op base class / `#else` stub class.

**Blockers / notes:**
- The `#if (defined(BATTERY_PIN)...) || (defined(BATTERY_CHARGE_PIN)...)` guard that wraps nearly the entire `.cpp` needs careful handling so the no-op stubs still compile as class methods.
- Not urgent — the C-style module is functionally correct; this is purely a consistency/maintainability issue.

---

## [ ] 17. Memory Leaks and Heap Fragmentation

ESP32 devices run indefinitely without rebooting (under normal conditions). Any heap allocation that is not freed, or any pattern that fragments the heap over time, will eventually exhaust memory, causing allocation failures that manifest as silent playback failures, failed updates, or hard resets. This section audits all dynamic allocation patterns in the application code.

### [ ] 17.1 `Config::startupServices()` — `ESPFileUpdater* updater` never freed `[MEDIUM]`

- **File**: `src/core/config.cpp`, around line 1255.
- **Code**:
  ```cpp
  ESPFileUpdater* updater = new ESPFileUpdater(SPIFFS);
  ...
  xTaskCreate(startupServicesAsync, "startupServicesAsync", 8192, updater, 2, NULL);
  ```
- **Task (`startupServicesAsync`)**: receives `updater` as `param`, calls `config.updateFile(param, ...)` for each file update, then calls `vTaskDelete(NULL)` — **without ever calling `delete (ESPFileUpdater*)param`**.
- **Second path** (`!wwwFilesExist`): `updater` is allocated, then `getRequiredFiles()` is called. `getRequiredFiles()` calls `ESP.restart()` on success — but if it returns on failure the `updater` is never freed.
- **Impact**: A one-time leak of one `ESPFileUpdater` object per boot-services invocation. Not recurring, but confirms the design does not account for ownership transfer through `void*` task parameters.
- **Action**: At the end of `startupServicesAsync`, before `vTaskDelete(NULL)`, add `delete (ESPFileUpdater*)param;`. In the `!wwwFilesExist` path, add `delete updater;` after `getRequiredFiles()` returns.

### [ ] 17.2 `MyNetwork::setWifiParams()` — `weatherBuf` reassigned without `free()` `[MEDIUM]`

- **File**: `src/core/network.cpp`, around line 491.
- **Code**:
  ```cpp
  weatherBuf = NULL;   // ← overwrites existing pointer without free()
  ...
  weatherBuf = (char *) malloc(sizeof(char) * WEATHER_STRING_L);
  ```
- **Problem**: If `setWifiParams()` is called more than once (e.g., during the `searchWiFi` task retry path in SD-card mode, or any future reconnect code path), the previously `malloc`'d block of `WEATHER_STRING_L` bytes is leaked.
- **Current risk**: In typical boot flows `setWifiParams()` is called once. The `WiFiReconnected` callback does not call it again. However the design has no protection against accidental double-call leaking `WEATHER_STRING_L` bytes.
- **Action**: Add a guard before the assignment: `if (weatherBuf) { free(weatherBuf); weatherBuf = nullptr; }`.

### [ ] 17.3 `xTaskCreate` failure leaves heap allocations unclaimed `[LOW]`

Four call sites allocate heap memory and pass the pointer as `pvParameters` to `xTaskCreate`, but do not free the memory if `xTaskCreate` fails (returns `errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY`). Task creation failure is unlikely in normal operation but is most likely to occur precisely when the heap is already critically fragmented.

| File | Site | Allocation | Action on failure |
|---|---|---|---|
| `commandhandler.cpp` ~line 182 | `loadplaylist` handler | `char* filename = new char[strlen(value)+1]` | Not freed if `xTaskCreate` fails |
| `netserver.cpp` ~line 1044 | `launchPlaybackTask()` | `String* url_copy = new String(url)` | Not freed if `xTaskCreate` fails |
| `netserver.cpp` ~line 1219 | `processRadioBrowserClick()` | `char* urlCopy = new char[...]` | Not freed if `xTaskCreate` fails |
| `config.cpp` ~line 1191 | `Config::updateLocaleFileAsync()` | `LocaleUpdateParams*` + inner `ESPFileUpdater*` | Neither freed if `xTaskCreate` fails |

- **Action**: All four sites must check the return value of `xTaskCreate` and free the allocation when it is not `pdPASS`. Pattern:
  ```cpp
  if (xTaskCreate(..., (void*)ptr, ...) != pdPASS) {
      delete[] ptr;  // or delete ptr
      // handle error
  }
  ```

### [ ] 17.4 `rb_servers[20]` global `String` array — recurring heap fragmentation `[LOW]`

- **File**: `src/core/netserver.cpp`, line 61.
- **Declaration**: `String rb_servers[20];`
- **Problem**: 20 Arduino `String` objects at global scope. Each non-empty `String` holds a heap-allocated character buffer. `selectRadioBrowserServer()` rebuilds this array by repeatedly assigning new values, which frees old heap blocks and allocates new ones of varying sizes. On a long-running device, this repeated churn of differently-sized small heap blocks creates fragmentation. Fragmentation is the primary cause of allocation failures on ESP32 that don't appear immediately but develop over hours/days.
- **Action**: Replace with a 2D `char` array: `char rb_servers[20][64]`. Server hostnames are short domain names well under 64 bytes. This eliminates all heap involvement for this array. Replace the `String` assignment and comparison operations with `strlcpy`/`strcmp`.

### [ ] 17.5 Temporary `String` construction in hot/error paths — fragmentation `[LOW]`

- **File**: `src/core/netserver.cpp`, lines ~1275 and ~1331.
- **Code**:
  ```cpp
  websocket.textAll(String("{\"onlineupdateerror\": \"HTTP code ") + httpCode + "\"}");
  websocket.textAll(String("{\"onlineupdateerror\": \"Update failed on end(): ") + String(Update.errorString()) + "\"}");
  ```
- **Problem**: Each statement constructs 2–3 temporary `String` heap objects (allocate → copy → concatenate → allocate again). These are freed immediately after the statement but each allocate+free cycle leaves behind a fragmentation scar. The success path immediately above already uses `snprintf` into a stack `char msgBuf[]` — the error paths should too.
- **Action**: Replace with `snprintf(msgBuf, sizeof(msgBuf), ...)` matching the pattern already used for the success case.

### [ ] 17.6 `MIN_MALLOC` defined but never enforced `[LOW]`

- **File**: `src/core/netserver.cpp`, lines 42–43.
- **Code**: `#define MIN_MALLOC 24112`
- **Problem**: `MIN_MALLOC` is defined (with a `#ifndef` guard suggesting it is user-overridable), but no code anywhere checks `ESP.getFreeHeap() < MIN_MALLOC` before starting new background tasks or network operations. The constant was presumably intended as a low-heap guard threshold but the associated check was never implemented.
- **Action**: Either (a) implement a guard: refuse to create new background tasks (`search`, `curated`, `playback`, `rb_click`) when heap is critically low, logging a warning via `Serial.printf`; or (b) remove `MIN_MALLOC` to avoid misleading future readers into thinking a guard exists.

### [ ] 17.7 No heap health monitoring or low-memory recovery path `[MEDIUM]`

- The device has no autonomous mechanism to detect gradual heap exhaustion. When the heap fragments below the threshold needed for a new WiFi/TCP connection or audio stream buffer, the symptom is silent failure (station won't play, updates time out) rather than a recoverable logged event.
- `xPortGetFreeHeapSize()` is exposed in telnet `info` output (line 698) but never logged to Serial on a schedule or acted on.
- There is no low-heap watchdog that would trigger a controlled reboot (as opposed to a crash/WDT reset with no log).
- **Suggested actions**:
  1. Add a periodic heap log in the `ticks()` ticker (e.g., every 5 minutes): `Serial.printf("[Heap] Free: %u, Min: %u\n", ESP.getFreeHeap(), ESP.getMinFreeHeap());`. Cheap and invaluable for diagnosing long-uptime degradation.
  2. In the MQTT/WebSocket system-info broadcasts, include `freeHeap` so the WebUI can surface it.
  3. Consider a controlled-reboot policy: if `ESP.getMinFreeHeap()` (the all-time minimum across the session) drops below a configurable threshold (e.g., `LOW_HEAP_REBOOT_THRESHOLD`), reboot at the next station-change boundary rather than waiting for a crash.
  4. Implement the `MIN_MALLOC` guard from §17.6 as the first concrete step.

---

## [ ] 18. Race Conditions and Concurrency Hazards

### [ ] 18.1 ISR reads non-volatile global `_mode` without a barrier `[MEDIUM]`

- **File**: `src/core/controls.cpp`, lines ~70 and ~77.
- **Code**:
  ```cpp
  void IRAM_ATTR readEncoderISR() {
    if ((SDC_CS==255 && display.mode()==LOST) || display.mode()==UPDATING) return;
    encoder.readEncoder_ISR();
  }
  ```
- **Problem**: The ISR reads `display._mode` (an `enum` field on the main-thread `Display` object) without any synchronisation. `_mode` is not `volatile`; the compiler is permitted to cache it in a register. On ESP32 (Xtensa dual-core), the ISR can fire on Core 0 while `_mode` is being written on Core 1. The combined result is a torn read or stale cached value. The ISR may refuse to call `readEncoder_ISR()` when it should, or (worse) allow it when the display is mid-update.
- **Action**: Declare `_mode` as `volatile displayMode_e _mode;` in `display.h`, or add a `portMUX` critical-section wrapper around the read in the ISR. The safest minimal fix is `volatile`.

### [ ] 18.2 `network.lostPlaying` / `network.beginReconnect` written from multiple contexts without synchronisation `[LOW]`

- **File**: `src/core/network.h` line 16 — `bool lostPlaying = false, beginReconnect = false;`
- **Writers**: `WiFiLostConnection()` callback (system WiFi event task), `WiFiReconnected()` callback (system WiFi event task), `retryStreamConnection()` task (Core 0), `player.cpp` line ~270 (player task).
- **Problem**: ESP32 Arduino's `WiFiEvent` callbacks run in the lwIP/WiFi system task, not on Core 0 or Core 1 directly. Non-atomic writes to plain `bool` fields from multiple tasks/cores without a mutex means a reader could see a partially-committed value, or the compiler could reorder accesses relative to surrounding logic. In practice `bool` on Xtensa is single-byte and byte-writes are atomic, but the **visibility** guarantee (cache coherency across cores) is not provided without `volatile` or a memory barrier.
- **Action**: Mark both fields `volatile bool` to prevent compiler caching. For stronger correctness, wrap all writes in `portENTER_CRITICAL` / `portEXIT_CRITICAL` if misfire of the retry logic turns out to be observed in practice.

### [ ] 18.3 `g_searchTaskHandle` / `g_curatedTaskHandle` — NULL-check then use is not atomic `[LOW]`

- **File**: `src/core/commandhandler.cpp` lines ~172 and ~179; `src/core/netserver.cpp` line ~124.
- **Pattern**:
  ```cpp
  if (g_searchTaskHandle == NULL) {
      xTaskCreate(..., &g_searchTaskHandle);
  }
  ```
- **Problem**: The guard reads `NULL`, then `xTaskCreate` sets the handle inside the same task. Because both operations happen on the same core (the WebSocket/HTTP handler callback) this is fine today. However `g_searchTaskHandle` is also set to `NULL` at the end of the task body (running on a different core). If the task completes and NULLs the handle between the guard check and the `xTaskCreate` call — a race that is possible if FreeRTOS task switching is enabled at that point — a second task could be spawned. The handle is not `volatile` either, so the read could be stale.
- **Action**: Mark both handles `volatile TaskHandle_t`. If stronger protection is needed, read the handle into a local variable once and act on that snapshot.

### [ ] 18.4 `mqttplaylistblock` busy-spin without a semaphore `[LOW]`

- **File**: `src/core/netserver.cpp`, line ~1383.
- **Code**: `while (mqttplaylistblock) vTaskDelay(5);`
- **Problem**: `mqttplaylistblock` is a plain `bool` written by `mqttplaylistSend()` (called from a `Ticker` callback). A `Ticker` callback runs in the context of whatever called `ticker.update()`, while the WebSocket file-upload handler runs in the AsyncWebServer task. The spin loop burns CPU time and relies on the `bool` being visible across tasks without `volatile`. A proper binary semaphore (`xSemaphoreCreateBinary`) with `xSemaphoreTake`/`xSemaphoreGive` would be the correct pattern.
- **Action**: Replace the manual `bool` + spin with a `SemaphoreHandle_t` pair, or at minimum mark `mqttplaylistblock` as `volatile bool`.

---

## [ ] 19. Blocking Operations on Real-Time / Non-Background Contexts

### [ ] 19.1 `rebootmdns` executes `delay(1500)` on the calling task `[MEDIUM]`

- **File**: `src/core/commandhandler.cpp`, line ~87.
- **Code**: `if (cmdIs(command, "rebootmdns")) { delay(1500); ESP.restart(); return true; }`
- **Problem**: This command is called directly from `cmd.exec()`, which runs on the AsyncWebServer task (the WebSocket message handler). A `delay(1500)` on that task stalls all WebSocket and HTTP event handling for 1.5 seconds, triggers AsyncWebServer internal timeouts, and may feed the watchdog unevenly. The `clearspiffs` handler in `handleIndex()` has the same pattern with `delay(100)` before restart.
- **Action**: Use a `Ticker.once()` to schedule the restart, mirroring the `improvRebootTicker` pattern already used in `onImprovCustomConnect()`. Return immediately from the command handler. The `clearspiffs` handler should do the same.

### [ ] 19.2 Blocking WiFi scan on the main loop during boot `[LOW]`

- **File**: `src/core/network.cpp`, line ~215.
- **Code**: `int n = WiFi.scanNetworks();` — called synchronously inside `wifiBegin()`, which is called from `network.begin()` on the main Arduino task during boot.
- **Problem**: `WiFi.scanNetworks()` is a blocking call that can take 2–5 seconds. During this time the main task is fully blocked — the watchdog timer is fed by the idle task, but no `loop()` processing, display updates, or serial I/O occurs. On slow RF environments it can take longer.
- **Telnet context**: `telnet.cpp` line ~621 calls `WiFi.scanNetworks()` directly in `on_input()`, blocking the telnet task for the full scan duration.
- **Action**: Use `WiFi.scanNetworks(true)` (async mode, returns immediately with `WIFI_SCAN_RUNNING`) and poll `WiFi.scanComplete()` in combination with `WiFi.scanResults()`. If blocking is required at boot for correctness, at least call `esp_task_wdt_reset()` during the wait. Add a scan timeout.

### [ ] 19.3 Busy-wait spin loops without watchdog care `[LOW]`

Two spin loops use `delay()` to yield but have no timeout guard:
- `src/core/netserver.cpp` line ~247: `while(nsQueue==NULL) {;}` — pure busy-spin, no delay, no WDT reset, no timeout.
- `src/core/display.cpp` line ~111: `while(displayQueue==NULL) {;}` — same.
- `src/core/config.cpp` line ~193: `while(display.mode()!=SDCHANGE) delay(10);` — has a yield but no maximum iteration count; would spin forever if the display task fails to transition.
- `src/core/controls.cpp` line ~185: `while(display.mode() != STATIONS) {delay(10);}` — same problem; no bail-out.

For the queue-creation loops, the `while(x==NULL)` guards are a leftover defensive pattern; if `xQueueCreate` returns NULL, the queue is already broken and a restart is the appropriate response, not an infinite spin. For the mode-transition loops, a timeout (e.g., 2 seconds of total wait) should terminate with a fallback.
- **Action**: Replace the `while(nsQueue==NULL)` and `while(displayQueue==NULL)` spins with an assertion or immediate restart. Replace the mode-transition waits with a timeout + fallback:
  ```cpp
  uint32_t tStart = millis();
  while (display.mode() != STATIONS && millis() - tStart < 2000) { delay(10); }
  ```

---

## [ ] 20. TLS / HTTPS Security

### [ ] 20.1 All HTTPS connections skip certificate validation `[MEDIUM]`

- **File**: `src/core/netserver.cpp`, lines ~1073, ~1234, ~1286.
- **Code**: `client.setInsecure(); // skip server cert validation`
- **Applies to**: the Radio-Browser click-reporting lookup, the version-check download, and the firmware update download.
- **Problem**: `setInsecure()` disables server-certificate verification entirely. Any attacker who can intercept traffic (e.g., a rogue AP, MITM on an unencrypted home network) can serve malicious firmware or version data. The firmware update path is the highest-risk instance: a MITM could serve a re-signed but malicious firmware binary.
- **Context**: Embedding a bundle of CA root certificates on an ESP32 with limited flash is genuinely hard; `WiFiClientSecure::setCACert()` requires the specific root CA PEM for each target host. The `setInsecure()` choice is pragmatic, but should be documented as a known trade-off, not left as a silent comment.
- **Action**:
  - For the **firmware update path** specifically: embed the root CA for `UPDATEURL` (typically a GitHub or self-hosted host) and use `setCACert()`. This is the highest-value fix.
  - For **Radio-Browser API calls**: lower risk (no privileged data), but still document the trade-off.
  - Add `#define HTTPS_SKIP_CERT_VERIFY` as an explicit opt-out define in `options.h` (defaulting to `1` for now) so the current behaviour is acknowledged and can be disabled per-build.

---

## [ ] 21. NVS Write Endurance

### [ ] 21.1 High-frequency NVS writes from volume/brightness sliders `[MEDIUM]`

- **Context**: ESP32 NVS is backed by flash, which has a write endurance of approximately 100,000 erase cycles per sector. The `saveValue()` implementation in `config.h` calls `prefs.begin() / prefs.putBytes() / prefs.end()` which triggers a full NVS commit on every call. The NVS library does do some wear-levelling across allocated pages, but writes are still finite.
- **High-frequency callers**:
  - Volume slider in WebUI sends `volume=N` (resolved through `vol` handler): `config.store.volume` is updated but `saveValue` is called — every drag event generates an NVS write.
  - `dim` command: `config.store.brightness` directly assigned then `setBrightness(true)` — also calls `saveValue` indirectly from `setBrightness`.
  - IR repeat-send scenario: if a held IR button sends volume-up repeatedly, NVS is written every repeat.
  - Encoder volume control: similarly sends a write per encoder step.
- **Note**: The `saveValue` implementation *does* short-circuit on equal values (`needSave = memcmp(...) != 0`), so if the value is unchanged no flash write occurs. This mitigates the worst case of repeated same-value slider sends. The actual per-step change case (each discrete encoder tick changes volume by 1) does still write each time.
- **Action**: Consider a debounce / coalescing policy for transient settings: buffer the last seen value and only commit after a quiet period (e.g., 2 seconds of no change, via a `Ticker`). This is a well-known pattern for embedded UIs. Volume and brightness are the primary candidates. Settings that are changed rarely (locale, timezone, etc.) do not need this treatment.

---

## [ ] 22. Stack Overflow Risks in FreeRTOS Tasks

### [ ] 22.1 `DspTask` stack is a fixed 4KB — no high-watermark monitoring `[LOW]`

- **File**: `src/core/display.cpp`, line ~27 and ~69.
- **Code**: `#define CORE_STACK_SIZE 1024*4` → `xTaskCreatePinnedToCore(loopDspTask, "DspTask", CORE_STACK_SIZE, ...)`
- **Problem**: The display task runs a substantial rendering loop, calls widget draw functions, and on displays backed by Adafruit/TFT_eSPI libraries can invoke moderately deep call stacks. 4KB is tight; a stack overflow on FreeRTOS produces a watchdog reset or heap corruption (the stack grows into adjacent heap). There is no runtime check of the high-water mark.
- **Affected tasks and their declared sizes**:

| Task | Stack | Where |
|---|---|---|
| `DspTask` | 4096 | `display.cpp` |
| `searchRadioBrowser` | 8192 | `netserver.cpp` |
| `curatedIndex` | 8192 | `commandhandler.cpp` |
| `curatedPlaylist` | 8192 | `commandhandler.cpp` |
| `playbackTask` (HTTP) | 4096 | `netserver.cpp` |
| `playbackTask` (HTTPS) | 8192 | `netserver.cpp` |
| `rbClickTask` | 8192 | `netserver.cpp` |
| `startupServicesAsync` | 8192 | `config.cpp` |
| `updateLocaleFileAsync` | 8192 | `config.cpp` |
| `doSync` | 4096 | `network.cpp` |
| `retryStreamConnection` | 4096 | `network.cpp` |
| `checkForOnlineUpdateTask` | 8096 | `netserver.cpp` |
| `startOnlineUpdateTask` | 16384 | `netserver.cpp` |

- **Action**: Add `uxTaskGetStackHighWaterMark(NULL)` logging to each long-lived task at a low-frequency checkpoint (e.g., once per minute or triggered by telnet `info`). The DspTask is the most suspect — consider raising to 8KB. If `uxTaskGetStackHighWaterMark()` returns < 512 bytes in testing, that task's stack needs expanding.

---

## [ ] 23. Telnet `/` WiFi Scan Blocking and Credential Exposure

### [ ] 23.1 `wifi.con` telnet command prints all stored WiFi passwords in cleartext `[MEDIUM]`

- **File**: `src/core/telnet.cpp`, around line ~642.
- **Code**: `printf(clientId, "%d: %s, %s\r\n", c, sSid, sPas);` — prints the SSID and password for every stored network.
- **Problem**: Telnet is unencrypted (plaintext TCP). Anyone who can access the telnet port can send `wifi.con` and receive all configured WiFi passwords in cleartext on a local network. If the device is on an untrusted network or the network is monitored, this is a credential exposure. There is no authentication on the telnet interface.
- **Separate concern**: `wifi.list` calls `WiFi.scanNetworks()` synchronously and blocks the telnet task for the duration of the scan (no timeout, no WDT reset — see §19.2).
- **Action**: At minimum, mask the password field in the output (e.g., show `****` after the first two characters). A stronger fix would require that telnet is only accessible from localhost/loopback or add an optional PIN challenge. Document that the telnet interface should only be used on trusted networks.

---

## 99. [ ] Stuff I found

Just some notes to make while going through code...

  [ ] netserver.loop(); is twice in player.cpp line 241

## 100. [ ] TO-DO: A Workflow that checks pull-requests

