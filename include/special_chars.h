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
    0b00000
};

uint8_t pacmanOpen[] = {
    0b00000,
    0b00000,
    0b01110,
    0b11011,
    0b11100,
    0b01110,
    0b00000,
    0b00000
};

byte thermometer[8] =
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

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