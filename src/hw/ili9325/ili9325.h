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
    enum
    {
        WHITE = 0xFFFF,
        BLACK = 0x0000,
        GREY = 0xF7DE,
        BLUE = 0x001F,
        BLUE2 = 0x051F,
        RED = 0xF800,
        MAGENTA = 0xF81F,
        GREEN = 0x07E0,
        CYAN = 0x7FFF,
        YELLOW = 0xFFE0
    };

    /**
     * @defgroup hw_core
     * @{
     */

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
