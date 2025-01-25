#include "DataJson.hpp"
DataHandler dataHandler;

void DataHandler::saveToFile(){
    File file = LittleFS.open(dataFilePath, "a"); 
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }
    serializeJson(data, file);
    file.close();
}

void DataHandler::createFile(){
 File file = LittleFS.open("/data.json", "r");
    if (!file) {
        Serial.println("File doesn't exist, creating new file...");
        // Tworzymy plik w trybie zapisu (jeśli nie istnieje)
        file = LittleFS.open("/data.json", "w"); 
        if (!file) {
            Serial.println("Failed to create file.");
            return;
        }
        Serial.println("File created successfully.");
        file.close();
    } else {
        Serial.println("File already exists.");
        file.close();
    }
}