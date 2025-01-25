#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "network.hpp"


Network network; 

void Network::init() {
    setWifiMode();
}

void Network::setWifiMode() {
    const char* ssid = handlePreferences.ssid.c_str();
    const char* password = handlePreferences.pw.c_str();
    const char* wifiMode = handlePreferences.wifiMode.c_str();

    if (strcmp(wifiMode, "AP") == 0) {
        startAccessPoint(ssid, password);
    } else {
        Serial.println("Setting WiFi in Client mode");
        Serial.printf("*%s*\n", wifiMode);

        WiFi.mode(WIFI_OFF);
        WiFi.mode(WIFI_STA);
        WiFi.setHostname(hostname);
        WiFi.begin(ssid, password);

        int retries = 0;
        const int maxRetries = 10; // Max attempts to connect

        while (WiFi.status() != WL_CONNECTED && retries < maxRetries) {
            delay(1000);
            Serial.printf("Connecting to WiFi (%d/%d): %s\n", retries + 1, maxRetries, ssid);
            retries++;
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected to the WiFi network");
            Serial.print("IP address: ");
            IPAddress ip = WiFi.localIP();
            Serial.println(ip);

            if (!MDNS.begin(hostname)) {
                Serial.println("Error setting up MDNS responder");
            } else {
                Serial.println("mDNS responder started");
            }
        } else {
            Serial.println("Failed to connect to WiFi. Starting as Access Point...");
            startAccessPoint(ssid, password);
        }
    }
}

void Network::startAccessPoint(const char* ssid, const char* password) {
    Serial.println("Setting WiFi in AP mode");
    handlePreferences.readNetworkValues();
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ESSID, PW);

    IPAddress apIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(apIP);

    if (!MDNS.begin(hostname)) {
        Serial.println("Error setting up MDNS responder");
    } else {
        Serial.println("mDNS responder started");
    }
}
