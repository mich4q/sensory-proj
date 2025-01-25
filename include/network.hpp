#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include "networkPreferences.hpp"

class Network {
public:
    void init(); // Inicjalizacja i ustawienie trybu Wi-Fi
    void setWifiMode(); // Funkcja do ustawienia trybu Wi-Fi (AP lub STA)
    void startAccessPoint(const char* ssid, const char* password);
private:
    const char* hostname = "GreenHouse"; // Domyślny hostname dla mDNS
    IPAddress apIP = IPAddress(192, 168, 4, 1); // IP dla trybu AP
    IPAddress netmask = IPAddress(255, 255, 255, 0); // Mask sieciowa
};

extern Network network; // Deklaracja zmiennej globalnej dla obiektu klasy Network

#endif
