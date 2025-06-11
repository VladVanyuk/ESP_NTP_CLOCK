#pragma once

enum CUSTOM_CHARS
{
    LCD_PACMAN_CL,
    LCD_PACMAN,
    LCD_SMALL_DROPLET = 6,
    LCD_SMALL_THERMOMETER
};

uint8_t pacmanClosed[8] = {
    0b00000,
    0b00000,
    0b01110,
    0b11011,
    0b11111,
    0b01110,
    0b00000,
    0b00000};

uint8_t pacmanOpen[] = {
    0b00000,
    0b00000,
    0b01110,
    0b11011,
    0b11100,
    0b01110,
    0b00000,
    0b00000};

byte thermometer[8] =
    {
        B00100,
        B01010,
        B01010,
        B01110,
        B01110,
        B11111,
        B11111,
        B01110};

byte droplet_empty[8] =
    {
        B00100,
        B00100,
        B01010,
        B01010,
        B10001,
        B10001,
        B10001,
        B01110,
};

byte droplet_low[8] =
    {
        B00100,
        B00100,
        B01010,
        B01010,
        B10001,
        B10001,
        B11111,
        B01110,
};

byte droplet_mid1[8] =
    {
        B00100,
        B00100,
        B01010,
        B01010,
        B10001,
        B11111,
        B11111,
        B01110,
};

byte droplet_mid2[8] =
    {
        B00100,
        B00100,
        B01010,
        B01010,
        B11111,
        B11111,
        B11111,
        B01110,
};

byte droplet_mid3[8] =
    {
        B00100,
        B00100,
        B01010,
        B01110,
        B11111,
        B11111,
        B11111,
        B01110,
};

byte droplet_full[8] =
    {
        B00100,
        B00100,
        B01110,
        B01110,
        B11111,
        B11111,
        B11111,
        B01110,
};

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x26, 16, 2);

byte LT[8] =
    {

        B00111,
        B01111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
byte UB[8] =
    {
        B11111,
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000};
byte RT[8] =
    {

        B11100,
        B11110,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
byte LL[8] =
    {

        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B01111,
        B00111};
byte LB[8] =
    {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111,
        B11111};
byte LR[8] =
    {

        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11110,
        B11100};
byte MB[8] =
    {
        B11111,
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111};
byte block[8] =
    {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};


void custom0(int x)
{

    LCD.setCursor(x, 0);
    LCD.write(0);
    LCD.write(1);
    LCD.write(2);
    LCD.setCursor(x, 1);
    LCD.write(3);
    LCD.write(4);
    LCD.write(5);
}

void custom1(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(1);
    LCD.write(2);
    LCD.print(" ");
    LCD.setCursor(x, 1);
    LCD.write(4);
    LCD.write(7);
    LCD.write(4);
}

void custom2(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(6);
    LCD.write(6);
    LCD.write(2);
    LCD.setCursor(x, 1);
    LCD.write(3);
    LCD.write(4);
    LCD.write(4);
}

void custom3(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(6);
    LCD.write(6);
    LCD.write(2);
    LCD.setCursor(x, 1);
    LCD.write(4);
    LCD.write(4);
    LCD.write(5);
}

void custom4(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(3);
    LCD.write(4);
    LCD.write(7);
    LCD.setCursor(x, 1);
    LCD.print(" ");
    LCD.print(" ");
    LCD.write(7);
}

void custom5(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(3);
    LCD.write(6);
    LCD.write(6);
    LCD.setCursor(x, 1);
    LCD.write(4);
    LCD.write(4);
    LCD.write(5);
}

void custom6(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(0);
    LCD.write(6);
    LCD.write(6);
    LCD.setCursor(x, 1);
    LCD.write(3);
    LCD.write(4);
    LCD.write(5);
}

void custom7(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(1);
    LCD.write(1);
    LCD.write(2);
    LCD.setCursor(x, 1);
    LCD.print(" ");
    LCD.print(" ");
    LCD.write(7);
}

void custom8(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(0);
    LCD.write(6);
    LCD.write(2);
    LCD.setCursor(x, 1);
    LCD.write(3);
    LCD.write(4);
    LCD.write(5);
}

void custom9(int x)
{
    LCD.setCursor(x, 0);
    LCD.write(0);
    LCD.write(6);
    LCD.write(2);
    LCD.setCursor(x, 1);
    LCD.print(" ");
    LCD.print(" ");
    LCD.write(7);
}

void printDigit(int digit, int x)
{
    switch (digit)
    {
    case 0:
        custom0(x);
        break;
    case 1:
        custom1(x);
        break;
    case 2:
        custom2(x);
        break;
    case 3:
        custom3(x);
        break;
    case 4:
        custom4(x);
        break;
    case 5:
        custom5(x);
        break;
    case 6:
        custom6(x);
        break;
    case 7:
        custom7(x);
        break;
    case 8:
        custom8(x);
        break;
    case 9:
        custom9(x);
        break;
    }
}