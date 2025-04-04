/**
 * @file ili9325.c
 * @author cF-embedded (cf@embedded.pl)
 * @brief ili9325 hw configuration
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ili9325.h"
#include "errno.h"
#include "gpio.h"
#include "platform_specific.h"
#include "stm32f1xx.h"

#define ILI9325_REG_ADDR (*((volatile unsigned short*)0x60000000))
#define ILI9325_RAM_ADDR (*((volatile unsigned short*)0x60020000))

/* ili9325 instruction registers */
#define RW_GRAM 0x22 /* READ OR WRITE DATA TO GRAM */

/**
 * @brief Initialize GPIOs for ili9325 outputs/inputs
 */
static void gpio_init(void);

/**
 * @brief Initialize FSMC for ili9325
 *
 */
static void fsmc_init(void);

/**
 * @brief Initialize timer for blacklight control ili9325
 *
 */
static void timer_init(void);

void ili9325_init(void)
{
    gpio_init();
    fsmc_init();
    timer_init();
}

void ili9325_write_reg(uint8_t reg, uint16_t data)
{
    ILI9325_REG_ADDR = reg;

    ILI9325_RAM_ADDR = data;
}

uint16_t ili9325_read_reg(uint8_t reg)
{
    ILI9325_REG_ADDR = reg;

    return (uint16_t)ILI9325_RAM_ADDR;
}

void ili9325_write_ram(uint16_t data)
{
    ili9325_write_reg(RW_GRAM, data);
}

uint16_t ili9325_read_ram(void)
{
    return ili9325_read_reg(RW_GRAM);
}

void ili9325_set_cursor(uint16_t x, uint16_t y)
{
    ili9325_write_reg(0x20, x);
    ili9325_write_reg(0x21, y);
}

int16_t ili9325_set_backlight(uint8_t percent)
{
    if(percent > 100)
    {
        return -EINVAL;
    }

    TIM3->CR1 &= ~(TIM_CR1_CEN);
    TIM3->CCR2 = (percent * (TIM3->ARR + 1)) / 100;
    TIM3->CR1 |= TIM_CR1_CEN;

    return 0;
}

void gpio_init(void)
{
    /* Enable clock for GPIOE */
    gpio_clock_init();

    /* PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9),
    PE.13(D10), PE.14(D11), PE.15(D12) */
    gpio_pin_cfg(GPIOE, 7, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 8, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 9, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 10, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 11, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 12, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 13, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 14, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOE, 15, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);

    /* PD.00(D2), PD.01(D3), PD.04(RD), PD.5(WR), PD.7(CS), PD.8(D13), PD.9(D14),
     PD.10(D15), PD.11(RS) PD.14(D0) PD.15(D1) */
    gpio_pin_cfg(GPIOD, 0, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 1, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 4, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 5, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 7, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 8, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 9, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 10, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 11, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 14, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    gpio_pin_cfg(GPIOD, 15, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);

    /* PB.05 BLACKLIGHT */
    gpio_pin_cfg(GPIOB, 5, GPIO_CRx_MODE_CNF_ALT_PP_50M_value);
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}

void fsmc_init(void)
{
    /* Enable FSMC clock */
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;

    FSMC_Bank1->BTCR[1] = (30 << FSMC_BTRx_ADDSET_Pos)   // Address Setup Time
        | (0 << FSMC_BTRx_ADDHLD_Pos)                    // Address Hold Time
        | (30 << FSMC_BTRx_DATAST_Pos)                   // Data Setup Time
        | (0 << FSMC_BTRx_BUSTURN_Pos)                   // Bus Turn Around Duration
        | (0 << FSMC_BTRx_CLKDIV_Pos)                    // CLK Division
        | (0 << FSMC_BTRx_DATLAT_Pos)                    // Data Latency
        | (0 << FSMC_BTRx_ACCMOD_Pos);                   // Access Mode A

    FSMC_Bank1E->BWTR[1] = (2 << FSMC_BWTRx_ADDSET_Pos)   // Address Setup Time
        | (0 << FSMC_BWTRx_ADDHLD_Pos)                    // Address Hold Time
        | (2 << FSMC_BWTRx_DATAST_Pos)                    // Data Setup Time
        | (0 << FSMC_BWTRx_BUSTURN_Pos)                   // Bus Turn Around Duration
        | (0 << FSMC_BWTRx_ACCMOD_Pos);                   // Access Mode A

    FSMC_Bank1->BTCR[0] = FSMC_BCRx_MWID_0   // Memory Data Width = 16 bits
        | FSMC_BCRx_MTYP_0                   // Memory Type = SRAM
        | FSMC_BCRx_WREN                     // Write operation enabled
        | FSMC_BCRx_EXTMOD;                  // Extended Mode Disabled

    /* Enable Bank1 */
    FSMC_Bank1->BTCR[0] |= FSMC_BCRx_MBKEN;
}

void timer_init(void)
{
    /* Enable timer clock */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    uint16_t timer_period = (MCU_CLOCK_FREQ / 1000000) - 1;
    TIM3->PSC = timer_period;   // Setting prescaler

    TIM3->ARR = 999;            // Setting auto-reload register
    TIM3->CR1 = TIM_CR1_ARPE;   // Auto-reload preload enable

    TIM3->CCMR1 = TIM_CCMR1_OC2M_1 |          // Enable PWM mode for channel 2
        TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE;   // Enable preload for channel 2

    TIM3->CCER = TIM_CCER_CC2E;   // Enable channel 2 output

    TIM3->CCR2 = 300;

    /* Enable timer */
    TIM3->CR1 |= TIM_CR1_CEN;
}
