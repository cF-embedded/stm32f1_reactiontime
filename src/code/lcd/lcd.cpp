/**
 * @file lcd.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief lcd driver for drawing
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "lcd.h"
#include "Adafruit_GFX.h"
#include "ads7843.h"
#include "ili9325.h"
#include "ili9325_registers.h"
#include "platform_specific.h"
#include <math.h>

LCD::LCD(int16_t width, int16_t height) : Adafruit_GFX(width, height)
{
    ads7843_init();
    ili9325_init();

    ili9325_write_reg(ILI9325_INTERNAL_TIMING_1, 0x3008);                 // Set internal timing
    ili9325_write_reg(ILI9325_INTERNAL_TIMING_2, 0x0012);                 // Set internal timing
    ili9325_write_reg(ILI9325_INTERNAL_TIMING_3, 0x1231);                 // Set internal timing
    ili9325_write_reg(ILI9325_DRIVER_OUTPUT_CONTROL_1, 0x0000);           // Set SS=1 and SM=0 bit
    ili9325_write_reg(ILI9325_LCD_DRIVING_WAVE_CONTROL, 0x0700);          // Set 1 line inversion
    ili9325_write_reg(ILI9325_ENTRY_MODE, 0x1030);                        // Set GRAM write direction and BGR=1
    ili9325_write_reg(ILI9325_RESIZING_CONTROL_REGISTER, 0x0000);         // Set Resize register
    ili9325_write_reg(ILI9325_DISPLAY_CONTROL_2, 0x0207);                 // Set the back porch and front porch from AN(orginal in driver 0x0202)
    ili9325_write_reg(ILI9325_DISPLAY_CONTROL_3, 0x0000);                 // Set non-display area refresh cycle ISC[3:0]
    ili9325_write_reg(ILI9325_DISPLAY_CONTROL_4, 0x0000);                 // FMARK function
    ili9325_write_reg(ILI9325_RGB_DISPLAY_INTERFACE_CONTROL_1, 0x0000);   // RGB interface setting
    ili9325_write_reg(ILI9325_FRAME_MAKER_POSITION, 0x0000);              // Frame marker Position
    ili9325_write_reg(ILI9325_RGB_DISPLAY_INTERFACE_CONTROL_2, 0x0000);   // RGB interface polarity
    ili9325_write_reg(ILI9325_POWER_CONTROL_1, 0x0000);                   // SAP, BT[3:0], AP, DSTB, SLP, STB
    ili9325_write_reg(ILI9325_POWER_CONTROL_2, 0x0007);                   // DC1[2:0], DC0[2:0], VC[2:0]
    ili9325_write_reg(ILI9325_POWER_CONTROL_3, 0x0000);                   // VREG1OUT voltage
    ili9325_write_reg(ILI9325_POWER_CONTROL_4, 0x0000);                   // VDV[4:0] for VCOM amplitude
    // rtos_delay(200);                                                      // Dis-charge capacitor power voltage 200ms
    ili9325_write_reg(ILI9325_POWER_CONTROL_1, 0x1190);   // SAP, BT[3:0], AP, DSTB, SLP, STB (other value: 0x1190 0x1290 0x1490 0x1690)
    ili9325_write_reg(ILI9325_POWER_CONTROL_2, 0x0221);   // DC1[2:0], DC0[2:0], VC[2:0] (other value: 0x0221 0x0227)
    // rtos_delay(50);                                                       // Dis-charge capacitor power voltage 50ms
    ili9325_write_reg(ILI9325_POWER_CONTROL_3, 0x001A);   // VREG1OUT voltage (other value: 0x0018 0x001A 0x001B 0x001C)
    // rtos_delay(50);                                                       // Dis-charge capacitor power voltage 50ms
    ili9325_write_reg(ILI9325_POWER_CONTROL_4, 0x1800);                // VDV[4:0] for VCOM amplitude (other: 0x1A00)
    ili9325_write_reg(ILI9325_POWER_CONTROL_7, 0x002A);                // Set VCM[5:0] for VCOMH (other: 0x0025)
    ili9325_write_reg(ILI9325_FRAME_RATE_AND_COLOR_CONTROL, 0x000C);   // Set Frame Rate
    // rtos_delay(50);                                                       // Dis-charge capacitor power voltage 50ms
    ili9325_write_reg(ILI9325_HORIZONTAL_GRAM_ADDRESS_SET, 0x0000);   // Set GRAM horizontal Address
    ili9325_write_reg(ILI9325_VERTICAL_GRAM_ADDRESS_SET, 0x0000);     // Set GRAM Vertical Address
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_1, 0x0000);
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_2, 0x0000);
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_3, 0x0000);
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_4, 0x0206);   // Gradient adjustment registers
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_5, 0x0808);   // Amplitude adjustment registers
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_6, 0x0007);
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_7, 0x0201);
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_8, 0x0000);
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_9, 0x0000);                     // Gradient adjustment registers
    ili9325_write_reg(ILI9325_GAMMA_CONTROL_10, 0x0000);                    // Amplitude adjustment registers
    ili9325_write_reg(ILI9325_HORIZONTAL_ADDRESS_START_POSITION, 0x0000);   // Horizontal GRAM Start Address = 0
    ili9325_write_reg(ILI9325_HORIZONTAL_ADDRESS_END_POSITION, 0x00EF);     // Horizontal GRAM End Address = 239
    ili9325_write_reg(ILI9325_VERTICAL_ADDRESS_START_POSITION, 0x0000);     // Vertical GRAM Start Address = 0
    ili9325_write_reg(ILI9325_VERTICAL_ADDRESS_END_POSITION, 0x013F);       // Vertical GRAM End Address = 319
    ili9325_write_reg(ILI9325_DRIVER_OUTPUT_CONTROL_2, 0x2700);
    ili9325_write_reg(ILI9325_BASE_IMAGE_DISPLAY_CONTROL, 0x0003);   // NDL,VLE, REV (other: 0x0001)
    ili9325_write_reg(ILI9325_VERTICAL_SCROLL_CONTROL, 0x0000);      // Set scrolling line
    ili9325_write_reg(ILI9325_PARTIAL_IMAGE_1_DISPLAY_POSITION, 0x0000);
    ili9325_write_reg(ILI9325_PARTIAL_IMAGE_1_AREA_START_LINE, 0x0000);
    ili9325_write_reg(ILI9325_PARTIAL_IMAGE_1_AREA_END_LINE, 0x0000);
    ili9325_write_reg(ILI9325_PARTIAL_IMAGE_2_DISPLAY_POSITION, 0x0000);
    ili9325_write_reg(ILI9325_PARTIAL_IMAGE_2_AREA_START_LINE, 0x0000);
    ili9325_write_reg(ILI9325_PARTIAL_IMAGE_2_AREA_END_LINE, 0x0000);
    ili9325_write_reg(ILI9325_PANEL_INTERFACE_CONTROL_1, 0x0010);
    ili9325_write_reg(ILI9325_PANEL_INTERFACE_CONTROL_2, 0x0000);   // (other: 0x0600)
    ili9325_write_reg(ILI9325_PANEL_INTERFACE_CONTROL_3, 0x0003);
    ili9325_write_reg(ILI9325_PANEL_INTERFACE_CONTROL_4, 0x1100);
    ili9325_write_reg(ILI9325_PANEL_INTERFACE_CONTROL_5, 0x0000);
    ili9325_write_reg(ILI9325_PANEL_INTERFACE_CONTROL_6, 0x0000);
    ili9325_write_reg(ILI9325_DISPLAY_CONTROL_1, 0x0133);   // 262K color and display ON
}

bool LCD::isTouchScreenPressed()
{
    return (ads7843_touch_screen_get() == 0);
}

void LCD::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if((x < 0) || (x >= width()) || (y < 0) || (y >= height()))
        return;

    ili9325_set_cursor(x, y);   // Set the address for pixel data
    ili9325_write_ram(color);   // Write the color to the GRAM
}

void LCD::fillScreen(Color color)
{
    ili9325_set_cursor(0, 0);

    /* Fill the entire screen */
    for(uint i = 0; i < (width() * height()); i++)
    {
        ili9325_write_ram(to_uint16(color));   // Write the color to the GRAM
    }
}

int16_t LCD::setBacklight(uint8_t percent)
{
    return ili9325_set_backlight(percent);
}