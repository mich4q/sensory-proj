#include "networkPreferences.hpp"

PreferencesHandler handlePreferences;

void PreferencesHandler::saveNetworkValues() {
  if (preferences.begin("network", false)) {
    preferences.putString("ssid", ssid);
    preferences.putString("pw", pw);
    preferences.putString("wifiMode", wifiMode);
    Serial.println("Network preferences updated");
    preferences.end();
  } else {
    Serial.println(F("writing network preferences failed"));
  }
}

void PreferencesHandler::readNetworkValues() {
  if (preferences.begin("network", false)) {
    ssid = preferences.getString("ssid", ESSID);
    pw = preferences.getString("pw", PW);
    wifiMode = preferences.getString("wifiMode", "AP");
    Serial.printf(
        "Values from network preferences: \n ssid:%s, pw:%s, mode:%s\n ",
        ssid.c_str(), pw.c_str(), wifiMode.c_str());
  } else {
    Serial.println(F("reading preferences failed"));
  }
  preferences.end();
}

void PreferencesHandler::preferencesClear() { 
  preferences.clear(); 
}

void PreferencesHandler::saveThresholds(){
  if (preferences.begin("thresholds", false)) {
    preferences.putInt("soil_humidity", dataHandler.thresholds["soil_humidity"]);
    preferences.putInt("co2", dataHandler.thresholds["co2"]);
    Serial.println("Thresholds preferences updated");
    preferences.end();
  } else {
    Serial.println(F("writing thresholds preferences failed"));
  }
}

String PreferencesHandler::readThresholds(){
  if (preferences.begin("thresholds", false)) {
    soilHumidityThreshold = preferences.getInt("soil_humidity", 0);
    co2Threshold = preferences.getInt("co2", 0);
    Serial.println("Thresholds preferences read");
    Serial.println("soil_humidity: " + String(soilHumidityThreshold)+ ", co2: " + String(co2Threshold));
    preferences.end();
  } else {
    Serial.println(F("reading thresholds preferences failed"));
  }
  return "{\"soil_humidity\":" + String(soilHumidityThreshold) + ",\"co2\":" + String(co2Threshold) + "}";
}
