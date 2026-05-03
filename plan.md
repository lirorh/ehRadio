## Plan: Raw Telnet/Serial Output Inventory (Post-Migration)

Discovery-only snapshot of direct Serial/telnet printing that does not pass through the high-level logging macros.

Scope used:
- src/core
- src/displays
- src/libraries
- src/main.cpp
- plugins
- ehRadio.ino

Pattern used:
- Serial.print/println/printf/write
- telnet.print/println/printf/write

## Runtime Raw Output Call Sites (Non-Comment)

### src/core/telnet.cpp
- src/core/telnet.cpp:310 Serial.print(buf)
  - Transport-path output in Telnet::print(const char*), not routed through logging macros.
- src/core/telnet.cpp:410 telnet.printf(clientId, "##CMD_ERROR#\tunknown command <%s>\r\n", str)
  - Client-targeted telnet response path.

## Logging Infrastructure Raw Sinks (Intentional)

### src/core/logging.h
- src/core/logging.h:20 Serial.printf("%s\\r\\n", _log_buf)
- src/core/logging.h:40 Serial.printf("%s", _boot_msg)
- src/core/logging.h:50 Serial.print(".")

### src/core/logging.cpp
- src/core/logging.cpp:5 telnet.printf("%s\r\n", text)
- src/core/logging.cpp:9 telnet.printf("%s", text)

## Comment-Only References (Not Executable)

### src/libraries/ILI9488/ILI9486_SPI.cpp
- src/libraries/ILI9488/ILI9486_SPI.cpp:174 commented Serial.print/println debug line

### src/libraries/SSD1322/SSD1322.cpp
- src/libraries/SSD1322/SSD1322.cpp:467 commented Serial.printf debug line

## Summary
- Executable raw print call sites outside logging macros: 2
- Logging sink internals (expected by design): 5
- Comment-only references: 2
- Conclusion: Logging migration is nearly complete; remaining non-macro runtime output is transport-specific in telnet handling.
