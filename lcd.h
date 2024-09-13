#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BigNumbers_I2C.h>
#include "clock.h"
#include "weather.h"
#include "special_chars.h"

enum CUSTOM_CHARS
{
  LCD_PACMAN = 1,
  LCD_DOT = 2,
  LCD_TERMOMETER = 3,
  LCD_DROPLET = 4
};

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x26, 16, 2);
BigNumbers_I2C bigNum(&LCD);
tm lastPrintedTime;

uint32_t lastPrintedWeatherTime = 0;
uint32_t lastPrintedClockTime = 0;


void spinner()
{
  static int8_t counter = 0;
  const char *glyphs = "\xa1\xa5\xdb";
  LCD.setCursor(15, 1);
  LCD.print(glyphs[counter++]);
  if (counter == (int8_t)strlen(glyphs))
  {
    counter = 0;
  }
}

// void printLocalTime() {
//   struct tm timeinfo_print;
//   if (!getLocalTime(&timeinfo_print)) {
//     LCD.setCursor(0, 1);
//     LCD.println("Connection Err");
//     return;
//   }

//   LCD.setCursor(8, 0);
//   LCD.println(&timeinfo_print, "%H:%M:%S");

//   LCD.setCursor(0, 1);
//   LCD.println(&timeinfo_print, "%d/%m/%Y   %Z");
// }

void printTimeLCD(tm newTime, bool forcePrint = false)
{
  if (((newTime.tm_sec != lastPrintedTime.tm_sec) && (millis() - lastPrintedClockTime > 3000)) || forcePrint == true)
  {

    // if (newTime.tm_mday != lastPrintedTime.tm_mday)
    // {
      // LCD.setCursor(0, 0);
      // LCD.print(newTime.tm_mday);
  // lcd.write("\xF2");
    // }
     if (newTime.tm_min != lastPrintedTime.tm_min)
     {
        LCD.clear();
     }
    
    LCD.setCursor(0, 0);
    LCD.print(newTime.tm_mday);
    LCD.print('/');
    LCD.print(newTime.tm_mon + 1);
    LCD.print('/');
    LCD.print(newTime.tm_year - 100);

    LCD.setCursor(0, 1);
    LCD.print(newTime.tm_hour);
    LCD.print(':');
    if(newTime.tm_min < 10)
    {
      LCD.print('0');
    }
    LCD.print(newTime.tm_min);
    LCD.print(':');
    if(newTime.tm_sec < 10)
    {
      LCD.print('0');
    }
    LCD.print(newTime.tm_sec);
    lastPrintedTime = newTime;
  }
}

void printTempLCD(float temp)
{
  LCD.setCursor(10, 0);
  LCD.write((char)LCD_TERMOMETER);
  LCD.print((float)temp,1);
  LCD.write((char)LCD_DEGREE);
  LCD.write('C');
}

void printHumLCD(float hum)
{
  LCD.setCursor(12, 1);
  LCD.write((char)LCD_DROPLET);
  LCD.print((float)hum,0);
  LCD.write('%');
}

void printWeatherLCD(bool forcePrint = false)
{
  if ((millis() - lastPrintedWeatherTime > timerSyncDelay_w) || forcePrint == true)
  {
    printTempLCD(Weather.temp);
    printHumLCD(Weather.humidity);
  }
}

void lcdSetupOne()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  LCD.init();
  LCD.backlight();
  bigNum.begin();
  
  LCD.createChar(LCD_PACMAN, pacman);
  LCD.createChar(LCD_DOT, dot);
  LCD.createChar(LCD_TERMOMETER, termometer);
  LCD.createChar(LCD_DROPLET, droplet);
  
  LCD.home();
  LCD.print("WiFi Connecting");
  
}

void lcdSetupTwo()
{
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Setup done");
  LCD.setCursor(1, 0);
  LCD.print("Starting");
  delay(3000);
  LCD.clear();
  LCD.home();
  lastPrintedClockTime = millis();
  printTimeLCD(timeinfo, true);
  // printLocalTime();
  lastPrintedWeatherTime = millis();
  printWeatherLCD(true);
  digitalWrite(LED_BUILTIN, HIGH);
}

void lcdLoop()
{
  printTimeLCD(timeinfo);
  printWeatherLCD();
}

#endif