#include <ArduinoJson.h>
#include "constants.h"
#include <LittleFS.h>


class DataHandler{
    public:
    JsonDocument data;
    JsonDocument thresholds;
    DataHandler(){
        data["temperature"] = 0;
        data["humidity"] = 0;
        data["soil_humidity"] = 0;
        data["co2"] = 0;
        data["timestamp"] = "";

        thresholds["soil_humidity"] = 0;
        thresholds["co2"] = 0;
    }    
    const char* dataFilePath = "/data.json";
    void saveToFile();
    void createFile();
};
extern DataHandler dataHandler;