/**
 * @file lcd.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief lcd driver for drawing inherited from Adafruit_GFX
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Adafruit_GFX.h"
#include <ili9325.h>
#include <string.h>

#ifndef _LCD_H
#define _LCD_H

/* LCD X Axis size*/
constexpr auto LCD_X_SIZE = 320;
/* LCD Y Axis size*/
constexpr auto LCD_Y_SIZE = 240;

enum class Color : uint16_t
{
    WHITE = COLOR_WHITE,
    BLACK = COLOR_BLACK,
    GREY = COLOR_GREY,
    BLUE = COLOR_BLUE,
    BLUE2 = COLOR_BLUE2,
    RED = COLOR_RED,
    MAGENTA = COLOR_MAGENTA,
    GREEN = COLOR_GREEN,
    CYAN = COLOR_CYAN,
    YELLOW = COLOR_YELLOW
};

constexpr uint16_t to_uint16(Color color)
{
    return static_cast<uint16_t>(color);
}

class LCD : public Adafruit_GFX
{
  public:
    LCD(int16_t width, int16_t height);

    bool isTouchScreenPressed();
    void begin();
    void drawString(int16_t x, int16_t y, std::string, Color color, Color bg, uint8_t size);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void fillScreen(Color color);
    int16_t setBacklight(uint8_t percent);
};

#endif   // _LCD_H
