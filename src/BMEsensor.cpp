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

SensorData BMEData::getBMEdata(){
    SensorData data;

    data.temperature = 0;
    data.humidity = 0 ;
    data.timestamp = getReadingTimestamp();
    data.co2 = 0;
    data.soil_humidity = 0;
    
    return data;
}

