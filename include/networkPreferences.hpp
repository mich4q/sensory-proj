#ifndef NETWORKPREFERENCES_HPP
#define NETWORKPREFERENCES_HPP

#include <Preferences.h>
#include <Arduino.h>
#include "DataJson.hpp"
#define ESSID "GREENHOUSE"
#define PW "GREENHOUSE"

class PreferencesHandler {
public:
  Preferences preferences;
  
  String ssid;
  String pw;
  String wifiMode;

  // Metody do zapisywania i odczytywania ustawień
  void saveNetworkValues();
  void saveThresholds();
  String readThresholds();

  void readNetworkValues();
  void preferencesClear();
  private:
  int soilHumidityThreshold;
  int co2Threshold;
};

extern PreferencesHandler handlePreferences;

#endif // NETWORKPREFERENCES_HPP
