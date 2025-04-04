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

/**
 * @brief Initialize GPIOs for ads7843 outputs/inputs
 */
static void gpio_init(void);

/**
 * @brief Initialize SPI for ads7843
 *
 */
static void spi_init(void);

void ads7843_init(void)
{
    gpio_init();
    spi_init();
}

void gpio_init(void)
{
    /* Enable clock for GPIO */
    gpio_clock_init();

    /* PA.05(SCK), PA.06(MISO), PA.07(MOSI) */
    gpio_pin_cfg(GPIOA, 5, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOA, 6, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOA, 7, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    /* PA.04(TP_CS) */
    gpio_pin_cfg(GPIOA, 4, GPIO_CRx_MODE_CNF_OUT_PP_50M_value);
    /* PB.06(TP_IRQ) */
    gpio_pin_cfg(GPIOB, 6, GPIO_CRx_MODE_CNF_IN_PULL_U_D_value);
}

void spi_init(void)
{
    /* Enable clock for SPI */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 = (1 << SPI_CR1_SSM_Pos |    // Software slave managment enabled
                 7 << SPI_CR1_BR_Pos |     // Baud rate = fpclk / 256
                 1 << SPI_CR1_MSTR_Pos);   // Master mode

    SPI1->CRCPR = 7;   // CRC polynomial

    /* Enable SPI */
    SPI1->CR1 |= SPI_CR1_SPE;
}
