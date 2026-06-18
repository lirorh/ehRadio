#ifndef startup_h
#define startup_h
#pragma once

#include <Arduino.h>

class Startup {
public:
  void deassertCsPins();
  void checkVerAndSpiffs();
  void initNetwork();
  void startupServices();
  void checkSafeMode();
  void loop();

private:
  void bootInSafeMode();
  void markBootStable();
  void cleanStaleSearchResults();
  void getRequiredFiles();
  void checkNewVersionFile();
  bool checkLocaleFile();
  static void startupServicesAsync(void* param);

  uint32_t _bootStartMs = 0;
  bool _bootStablePending = false;
};

extern Startup startup;

#endif // startup_h
