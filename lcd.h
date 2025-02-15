#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BigNumbers_I2C.h>
#include "clock.h"
#include "weather.h"
#include "special_chars.h"

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x26, 16, 2);
BigNumbers_I2C bigNum(&LCD);
tm lastPrintedTime;

uint32_t lastPrintedWeatherTime = 0;
uint32_t lastPrintedClockTime = 0;


void printTimeLCD(tm newTime, bool forcePrint = false)
{ 
  if (((newTime.tm_sec != lastPrintedTime.tm_sec) && (millis() - lastPrintedClockTime > 1000)) || forcePrint == true)
  {

     if ((newTime.tm_min != lastPrintedTime.tm_min) || (newTime.tm_hour != lastPrintedTime.tm_hour ) )
     {
        LCD.clear();
     }
    
    LCD.setCursor(0, 0);
    LCD.print(newTime.tm_mday);
    LCD.print('/');
    if ((newTime.tm_mon + 1) < 10 )
    {
       LCD.print('0');
    }
    LCD.print((newTime.tm_mon + 1));
    LCD.print('/');
    LCD.print(newTime.tm_year - 100);

    LCD.setCursor(0, 1);
    if(newTime.tm_hour < 10)
    {
      LCD.print('0');
    }
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

void setupChars()
{
  LCD.createChar(LCD_PACMAN_CL, pacmanClosed);
  LCD.createChar(LCD_PACMAN, pacmanOpen);
  LCD.createChar(LCD_DOT, dot);
  LCD.createChar(LCD_TERMOMETER, termometer);
  LCD.createChar(LCD_DROPLET, droplet);
}

uint8_t dropletPercent(float humidity)
{
  if (humidity < 15) //0-15
  {
     LCD.createChar(LCD_DROPLET, droplet);
    return 0;
  }
  if (humidity < 30) //10-30
  {
     LCD.createChar(LCD_DROPLET, droplet_1);
    return 1;
  }
  else if (humidity < 50) //25-50
  {
     LCD.createChar(LCD_DROPLET, droplet_2);
    return 2;
  }
  else if (humidity < 65) //50 -65
  {
     LCD.createChar(LCD_DROPLET, droplet_3);
    return 3;
  }
  else if (humidity < 80) //65-80
  {
     LCD.createChar(LCD_DROPLET, droplet_4);
    return 4;
  }
  else //80-100
  {
     LCD.createChar(LCD_DROPLET, droplet_full);
    return 5;
  }
}

void printWeatherLCD(bool forcePrint = false, bool setChars = false)
{
  if ((millis() - lastPrintedWeatherTime > timerSyncDelay_w) || forcePrint == true)
  {
    if (setChars)
    {
      setupChars();
      dropletPercent(Weather.humidity);
    }

    LCD.setCursor(9, 0);
    LCD.write((char)LCD_TERMOMETER);
    LCD.print((float)Weather.temp, 1);
    LCD.print((char)223);   // lcd.write((char)0b11011111);
    LCD.print('C');
    //
    LCD.setCursor(12, 1);//todo add % for droplets
    LCD.write((char)LCD_DROPLET);
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
  setupChars();

  LCD.setCursor(0, 0);
  LCD.print("WIFI Connecting");
}

void lcdSetupTwo()
{
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Setup done");
  LCD.setCursor(0, 1);
  LCD.print("Starting");
  delay(3000);
  LCD.clear();
  LCD.setCursor(0, 0);
  lastPrintedClockTime = millis();
  printTimeLCD(timeinfo, true);
  lastPrintedWeatherTime = millis();
  printWeatherLCD(true, true);
  digitalWrite(LED_BUILTIN, HIGH);
}

void lcdLoop()
{
  printTimeLCD(timeinfo);
  printWeatherLCD();
}

#endif
/*
#if 0
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





void printTimeLCD(tm newTime, bool forcePrint = false)
{
  if (((newTime.tm_sec != lastPrintedTime.tm_sec) && (millis() - lastPrintedClockTime > 3000)) || forcePrint == true)
  {
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
  
  LCD.createChar(LCD_PACMAN, pacmanClosed);
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
*/
