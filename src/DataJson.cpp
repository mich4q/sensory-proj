#include "DataJson.hpp"
DataHandler dataHandler;

void DataHandler::saveToFile(){
    File file = LittleFS.open(dataFilePath, "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }
    serializeJson(data, file);
    file.close();
}
