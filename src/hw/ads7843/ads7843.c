/**
 * @file ads7843.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief ads7843 touch screen controller hw configuration
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ads7843.h"
#include "errno.h"
#include "gpio.h"
#include "platform_specific.h"
#include "stm32f1xx.h"

#define TOUCH_SCHREEN_PIN 6

/**
 * @brief Initialize GPIOs for ads7843 outputs/inputs
 */
static void gpio_init(void);

void ads7843_init(void)
{
    gpio_init();
}

uint32_t ads7843_touch_screen_get(void)
{
    return (GPIOB->IDR & (1 << TOUCH_SCHREEN_PIN)) == 0;
}

void gpio_init(void)
{
    /* Enable clock for GPIO */
    gpio_clock_init();

    /* PB.06(TP_IRQ) */
    gpio_pin_cfg(GPIOB, TOUCH_SCHREEN_PIN, GPIO_CRx_MODE_CNF_IN_PULL_U_D_value);
}