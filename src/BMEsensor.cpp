#include "BMEsensor.hpp"
#include "DataJson.hpp"

BMEData bmeData;

String BMEData::getReadingTimestamp() {
    
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    
    struct tm timeinfo;
    // Pobranie lokalnego czasu
    if (!getLocalTime(&timeinfo)) {
        return "Brak synchronizacji czasu"; // Obsługa błędu
    }

    // Konwersja czasu do formatu "YYYY-MM-DD HH:MM:SS"
    char timeStampBuffer[20];
    strftime(timeStampBuffer, sizeof(timeStampBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    
    return String(timeStampBuffer); // Zwrócenie jako String
}

void BMEData::getBMEdata(){
    // SensorData data;
    dataHandler.data["temperature"] = 0;//bme.readTemperature();
    dataHandler.data["humidity"] = 0;//bme.readHumidity();
    dataHandler.data["timestamp"] = getReadingTimestamp();
    dataHandler.data["co2"] = 0;//co2Sensor.readCO2();
    dataHandler.data["soil_humidity"] = 0;//soilSensor.readSoilHumidity();
    
    // data.temperature = 0;//bme.readTemperature();
    // data.humidity = 0 ;//bme.readHumidity();
    // data.timestamp = getReadingTimestamp();
    // data.co2 = 0;//co2Sensor.readCO2();
    // data.soil_humidity = 0;//soilSensor.readSoilHumidity();

    // return data;
}

void BMEData::checkConditions(){
    getBMEdata();
    if(dataHandler.data["soil_humidity"] < dataHandler.thresholds["soil_humidity"]){
        Serial.println("pump on");
    }
    if(dataHandler.data["co2"] > dataHandler.thresholds["co2"]){
        Serial.println("fans on");
    }
}