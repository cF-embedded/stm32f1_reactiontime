/**
 * @file core_init.c
 * @author cF-embedded (cf@embedded.pl)
 * @brief core initialization
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "core_init.h"
#include "platform_specific.h"
#include "stm32f1xx.h"

#define PLL_MUL             9   // PLL multiplier, e.g., 8 MHz HSE x 9 = 72 MHz
#define HSE_STARTUP_TIMEOUT ((uint16_t)0x0500)

void core_init(void)
{
    /* Enable HSE and wait for it to be ready */
    RCC->CR |= RCC_CR_HSEON;
    uint32_t startupCounter = 0, HSEStatus = 0;
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        startupCounter++;
    } while((HSEStatus == 0) && (startupCounter != HSE_STARTUP_TIMEOUT));

    if((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if(HSEStatus == 0x01)
    {
        /* Flash latency */
        FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;

        /* HCLK = SYSCLK */
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK/2 */
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

        /* PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
        RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
            ;

        /* Select PLL as system clock source */
        RCC->CFGR &= ~(RCC_CFGR_SW);
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
            ;
    }

    /* Configure other system settings as needed */
}
