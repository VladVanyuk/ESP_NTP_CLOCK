#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>
#include <StreamUtils.h>
#include <ArduinoJson.h>
#include "wifiConf.h"

// set location and API key
String Location = "Lviv,UA";
String API_Key = "8cd7834a6b2b8a74a77b47b7feb76237";

uint32_t lastSyncTime_w = 0;
const uint32_t timerSyncDelay_w = 60000;

struct Weather
{
    float temp = 0.0;
    int16_t humidity = 0;
    float pressure = 0.0;
    float wind_speed = 0.0;
    int16_t wind_degree = 0;
} Weather;

void printWeatherCurrent()
{
    // print data
    Serial.printf("Temperature = %.2f°C\r\n", Weather.temp);
    Serial.printf("Humidity = %d %%\r\n", Weather.humidity);
    Serial.printf("Pressure = %.3f bar\r\n", Weather.pressure);
    Serial.printf("Wind speed = %.1f m/s\r\n", Weather.wind_speed);
    Serial.printf("Wind degree = %d°\r\n\r\n", Weather.wind_degree);
}

void setWeatherData(JsonDocument doc)
{
    // Serial.println(doc["time"].as<long>());

    Weather.temp = (float)(doc["main"]["temp"]) - 273.15;       // get temperature in °C
    Weather.humidity = doc["main"]["humidity"];                 // get humidity in %
    Weather.pressure = (float)(doc["main"]["pressure"]) / 1000; // get pressure in bar
    Weather.wind_speed = doc["wind"]["speed"];                  // get wind speed in m/s
    Weather.wind_degree = doc["wind"]["deg"];                   // get wind degree in °
}

void httpGETRequest(const char *serverName)
{
    WiFiClient client;
    HTTPClient http;

    http.useHTTP10(true);
    http.begin(client, serverName);

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
        JsonDocument doc;
        ReadLoggingStream loggingStream(http.getStream(), Serial);
        deserializeJson(doc, loggingStream);
        setWeatherData(doc);
        printWeatherCurrent();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    // return payload;
}

void weatherSetup()
{
    lastSyncTime_w = millis();
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + Location + "&APPID=" + API_Key;
    httpGETRequest(serverPath.c_str());
}

void getWeatherLoop(uint32_t timeDelay)
{
    if (millis() - lastSyncTime_w > timeDelay)
    {
        if (WiFi.status() == WL_CONNECTED) // Check WiFi connection status
        {
            String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + Location + "&APPID=" + API_Key;
            Serial.println(serverPath.c_str());
            httpGETRequest(serverPath.c_str());
        }
        lastSyncTime_w = millis();
    }
}

#endif