#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#else
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#include <WiFiClient.h>
#include "lcd.h"
#include "special_chars.h"

const char *ssid = "AsusLyra";
const char *password = "123456qwerty";


void setupWifi(LiquidCrystal_I2C *lcd_p)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting");

    // int retry_count = 0
    while (WiFi.status() != WL_CONNECTED)
    {
        
        Serial.print(".");
        for (int i = 1; i < 16; i++) {
            lcd_p->setCursor(i, 1);
            lcd_p->print("\1");
        
                for (int j = i + 1; j < 16; j++) {
                    lcd_p->setCursor(j, 1);
                    lcd_p->print("\2");
                   
                }
                 lcd_p->createChar(1, pacman);
                delay(300);
                lcd_p->createChar(1, pacmanOpen);
                delay(300);
                lcd_p->setCursor(i, 1);
                lcd_p->print(" ");
        }
        // if (++retry_count > 1000) ESP.restart();
        // spinner();
    }
    Serial.println();
    Serial.println("\n\nWiFi connected\n\n");
    Serial.print("ESP IP Address: http://");
    Serial.println(WiFi.localIP());
}

#endif