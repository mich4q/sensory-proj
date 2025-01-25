#ifndef BMEData_H
#define BMEData_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include "constants.h" 
#include <time.h>


class BMEData{
    public:
    float temperature = 0.0;
    float humidity = 0.0;

    const char* ntpServer = "pool.ntp.org";
    const long  gmtOffset_sec = 3600;
    const int   daylightOffset_sec = 3600;

    void getBMEdata();
    String getReadingTimestamp();
    void checkConditions();
};
extern BMEData bmeData;
#endif