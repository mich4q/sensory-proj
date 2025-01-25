#ifndef WEB_HPP
#define WEB_HPP

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Update.h>
#include "network.hpp"
#include "BMEsensor.hpp"

class Web {
public:
    // Konstruktor z portem (domyślnie 80)
    Web(): server(80), updateContentLen(0) {}

    void setup();
    void saveNetwork(AsyncWebServerRequest *request);
    void getData(AsyncWebServerRequest *request);
    bool loadStaticFiles();
    
    void getThresholds(AsyncWebServerRequest *request);
    void sendThresholds(AsyncWebServerRequest *request);

    void pumpControl(AsyncWebServerRequest *request);
    void fanControl(AsyncWebServerRequest *request);
    void fanOn();
    void fanOff();
    void pumpOn();
    void pumpOff();
private:
    AsyncWebServer server;
    size_t updateContentLen;

};

extern Web web;
#endif
