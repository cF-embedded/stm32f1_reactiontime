/**
 * @file ili9325.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief ili9325 hw configuration
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _ILI9325_H
#define _ILI9325_H

#include "platform_specific.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @brief Availe colors on ili9325
 *
 */
#define COLOR_WHITE   0xFFFF
#define COLOR_BLACK   0x0000
#define COLOR_GREY    0xF7DE
#define COLOR_BLUE    0x001F
#define COLOR_BLUE2   0x051F
#define COLOR_RED     0xF800
#define COLOR_MAGENTA 0xF81F
#define COLOR_GREEN   0x07E0
#define COLOR_CYAN    0x7FFF
#define COLOR_YELLOW  0xFFE0

    /**
     * @brief function to hw initialize
     *
     */
    void ili9325_init(void);

    /**
     * @brief Write 16 bit value to register
     *
     * @param reg
     * @param data
     */
    void ili9325_write_reg(uint8_t reg, uint16_t data);

    /**
     * @brief Read 16 bit value from register
     *
     * @param reg
     * @return uint16_t
     */
    uint16_t ili9325_read_reg(uint8_t reg);

    /**
     * @brief Write 16 bit value to RAM Memory
     *
     * @param data
     */
    void ili9325_write_ram(uint16_t data);

    /**
     * @brief Write 16 bit values to RAM Memory by DMA
     *
     * @param data
     * @param length
     */
    void ili9325_write_ram_fast(uint16_t* data, uint32_t length);

    /**
     * @brief Read 16 bit value from RAM Memory
     *
     * @return uint16_t
     */
    uint16_t ili9325_read_ram(void);

    /**
     * @brief Set cursor position
     *
     * @param x
     * @param y
     */
    void ili9325_set_cursor(uint16_t x, uint16_t y);

    /**
     * @brief Set backlight brightness
     *
     * @param percent
     * @return int16_t
     */
    int16_t ili9325_set_backlight(uint8_t percent);

/**
 * @}
 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ILI9325_H */
