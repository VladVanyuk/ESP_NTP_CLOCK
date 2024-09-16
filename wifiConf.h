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


void setupWifi(LiquidCrystal_I2C *lcd_p) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");


  for (int i = 0; i < 16; i++) {
    lcd_p->setCursor(i, 1);
    lcd_p->write((char)LCD_DOT);
    Serial.print(".");
  }

  uint8_t pos = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
    lcd_p->setCursor(pos, 1);
    if(pos%2 == 0){
      lcd_p->write((char)LCD_PACMAN);
    }else{
      lcd_p->write((char)LCD_PACMAN_CL);
    }

    lcd_p->setCursor(pos-1, 1);
    lcd_p->print(" ");
    
    Serial.print("+");
    pos++;
    delay(500);


    /*
        for (int i = 1; i < 16; i++) 
        {
            if(WiFi.status() == WL_CONNECTED) break;

            lcd_p->setCursor(i, 1);
            lcd_p->print("\1");
        
                for (int j = i + 1; j < 16; j++) 
                {
                    lcd_p->setCursor(j, 1);
                    lcd_p->print("\2");
                   
                }
                
                lcd_p->createChar(1, pacmanClosed);
                delay(300);
                lcd_p->createChar(1, pacmanOpen);
                delay(300);
                lcd_p->setCursor(i, 1);
                lcd_p->print(" ");
        }

        */

    // if (++retry_count > 1000) ESP.restart();
  }

  Serial.println();
  Serial.println("\n\nWiFi connected\n\n");
}

#endif
/*
// europe.pool.ntp.org

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

timeClient.begin();
timeClient.update();

Serial.print(daysOfTheWeek[timeClient.getDay()]);
Serial.print(", ");
Serial.print(timeClient.getHours());
Serial.print(":");
Serial.print(timeClient.getMinutes());
Serial.print(":");
Serial.println(timeClient.getSeconds());
*/