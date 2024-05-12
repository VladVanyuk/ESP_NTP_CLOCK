#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BigNumbers_I2C.h>
#include "clock.h"
#include "weather.h"

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

void printTimeLCD(tm newTime, bool forcePrint = false)
{
  if (((newTime.tm_sec != lastPrintedTime.tm_sec) && (millis() - lastPrintedClockTime > 1000)) || forcePrint == true)
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
    LCD.print(newTime.tm_min);
    LCD.print(':');
    LCD.print(newTime.tm_sec);
    lastPrintedTime = newTime;
  }
}

void printWeatherLCD(bool forcePrint = false)
{
  if ((millis() - lastPrintedWeatherTime > timerSyncDelay_w) || forcePrint == true)
  {
    LCD.setCursor(10, 0);
    LCD.print(Weather.temp);
    LCD.print((char)223);
    LCD.print('C');
      // lcd.write((char)0b11011111); //todo: test
    LCD.setCursor(12, 1);
    LCD.print(Weather.humidity);
    LCD.print('%');
  }
}

void lcdSetupOne()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  LCD.init();
  LCD.backlight();
  bigNum.begin();
  LCD.setCursor(0, 0);
  LCD.print("Connecting to ");
  LCD.setCursor(0, 1);
  LCD.print("WiFi ");
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
  LCD.setCursor(0, 0);
  lastPrintedClockTime = millis();
  printTimeLCD(timeinfo, true);
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