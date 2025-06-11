#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include "wifi_conf.h"

class Weather {
private:
    static constexpr float K_TO_C = 273.15f; // Kelvin to Celsius conversion factor
    
    // configuration
    String location;
    String api_key;
    
    // timing
    uint32_t last_sync_time         = 0;
    const uint32_t timer_sync_delay = 60000;
    
    // weather data
    float temp          = 0.0;
    int8 humidity       = 0;
    float pressure      = 0.0;
    float wind_speed    = 0.0;
    int16_t wind_degree = 0;
    
    void setWeatherData(const JsonDocument& doc);
    void httpGETRequest(const char *server_name);

public:
    Weather(const String& loc = "Lviv,UA", 
            const String& key = "8cd7834a6b2b8a74a77b47b7feb76237");
    
    void setup();
    void loop();
    void printCurrent() const;

    inline float get_temp() const { return temp; }
    inline int8 get_humidity() const { return humidity; }
    inline const float get_timer_sync_delay() const { return timer_sync_delay; }
};

Weather::Weather(const String& loc, const String& key) 
    : location(loc), api_key(key) {}

void Weather::setWeatherData(const JsonDocument& doc)
{
    temp        = static_cast<float>(doc["main"]["temp"]) - K_TO_C;
    humidity    = static_cast<int8>(doc["main"]["humidity"]);
    pressure    = static_cast<float>(doc["main"]["pressure"]) / 1000;
    wind_speed  = doc["wind"]["speed"];
    wind_degree = doc["wind"]["deg"];
}

void Weather::printCurrent() const
{
    Serial.printf("Temperature = %.2f°C\r\n", temp);
    Serial.printf("Humidity = %d %%\r\n", humidity);
    Serial.printf("Pressure = %.3f bar\r\n", pressure);
    Serial.printf("Wind speed = %.1f m/s\r\n", wind_speed);
    Serial.printf("Wind degree = %d°\r\n\r\n", wind_degree);
}

void Weather::httpGETRequest(const char *server_name)
{
    WiFiClient client;
    HTTPClient http;

    http.useHTTP10(true);
    http.begin(client, server_name);

    int http_response_code = http.GET();
    if (http_response_code > 0) {
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, http.getStream());
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }

        setWeatherData(doc);
        printCurrent();
    } else {
        Serial.print("Error code: ");
        Serial.println(http_response_code);
    }
    http.end();
}

void Weather::setup()
{
    last_sync_time = millis();
    String server_path = "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&APPID=" + api_key;
    httpGETRequest(server_path.c_str());
}

void Weather::loop()
{
    if (millis() - last_sync_time > timer_sync_delay) {
        if (WiFi.status() == WL_CONNECTED) {
            String server_path = "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&APPID=" + api_key;
            Serial.println(server_path.c_str());
            httpGETRequest(server_path.c_str());
        }
        last_sync_time = millis();
    }
}