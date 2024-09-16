#pragma once

const char LCD_ALPHA    = 0xE0;
const char LCD_BETA     = 0xE2;
const char LCD_EPSILON  = 0xE3;
const char LCD_MU       = 0xE4;
const char LCD_RHO      = 0xE5;
const char LCD_SQROOT   = 0xE7;

const char LCD_THETA    = 0xF2;
const char LCD_INFINITY = 0xF3;
const char LCD_OHM      = 0xF4;
const char LCD_SIGMA    = 0xF6;
const char LCD_PI       = 0xF7;
const char LCD_XAVG     = 0xF8;

const char LCD_DEGREE   = 0xDF;
const char LCD_DIVIDE   = 0xFD;

enum CUSTOM_CHARS
{
  LCD_PACMAN_CL = 1,
  LCD_PACMAN,
  LCD_DOT,
  LCD_TERMOMETER,
  LCD_DROPLET
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

uint8_t dot[] = {
  0b00000,
  0b00000,
  0b00000,
  0b00110,
  0b00110,
  0b00000,
  0b00000,
  0b00000
};

byte termometer[8] = //icon for termometer
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

byte droplet[8] = //icon for water droplet
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



byte droplet_1[8] = //icon for water droplet
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

byte droplet_2[8] = //icon for water droplet
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


byte droplet_3[8] = //icon for water droplet
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

byte droplet_4[8] = //icon for water droplet
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

byte droplet_full[8] = //icon for water droplet
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

// #define MODO_CMD  0
// #define MODO_DATA 1
// #define LCD_DISPLAY_ON 0X08
// #define LCD_DISPLAY_OFF 0X0C
// #define LCD_DESP_IZQ 0X18
// #define LCD_DESP_DER 0X1C
// #define LCD_CLEAR 0X01
// #define LCD_INCREMENTAR_CURSOR 0X06
// #define LCD_CONFIG_8BITS_5X7 0x38
// #define LCD_CONFIG_4BITS_5X8 0x28
// #define LCD_MODO_8BITS 0x33
// #define LCD_MODO_4BITS 0x32
// #define LCD_4BIT_MODE  0x02
// #define LCD_8BIT_MODE  0x03
// #define LCD_DISPLAY_ON_NO_CURSOR_NO_BLINK 0x0C
