/**
 * @file lcd.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief lcd driver for drawing inherited from Adafruit_GFX
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Adafruit_GFX.h"
#include <string>

#ifndef _LCD_H
#define _LCD_H

/* LCD X Axis size*/
constexpr auto LCD_X_SIZE = 320;
/* LCD Y Axis size*/
constexpr auto LCD_Y_SIZE = 240;

class LCD : public Adafruit_GFX
{
  public:
    LCD(int16_t width, int16_t height);

    bool isTouchScreenPressed();
    void begin();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void fillScreen(uint16_t color);
    int16_t setBacklight(uint8_t percent);
};

#endif   // _LCD_H
