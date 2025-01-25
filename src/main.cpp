#include <Arduino.h>
#include "main.hpp"
#include "web.hpp"
#include "networkPreferences.hpp"
#include "network.hpp"



void setup() {
    hardwareInit();
    initFilesystem();
    initWiFi();
    web.setup();
}
unsigned long lastmillis = 0;

void loop() {
    unsigned long currentmillis = millis();
    if(currentmillis - lastmillis >= 5000){
        size_t freeMemory = ESP.getFreeHeap();

        Serial.print("Dostępna pamięć: ");
        Serial.print(freeMemory);
        Serial.println(" bajtów");
        lastmillis = currentmillis;
    }    
}

void initWiFi(){
    handlePreferences.readNetworkValues();
    network.init();
}
void initFilesystem(){
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount filesystem.");
        return;
    }
    Serial.println("Filesystem mounted successfully.");
}

void hardwareInit(){
    Serial.begin(115200);
}