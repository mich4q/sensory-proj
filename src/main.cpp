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

    dataHandler.createFile();
}
unsigned long lastmillis = 0;

void loop() {
    unsigned long currentmillis = millis();
    if(currentmillis - lastmillis >= 5000){
        bmeData.checkConditions();
        
        dataHandler.saveToFile();
        size_t freeMemory = ESP.getFreeHeap();
        // Serial.print("Dostępna pamięć: ");

        Serial.println(freeMemory);
        // Serial.println(" bajtow");
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
    // Sprawdzamy, czy plik już istnieje
}

void hardwareInit(){
    Serial.begin(115200);
}