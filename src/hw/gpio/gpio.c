/** \file gpio.c
 * \brief GPIO driver.
 * \details GPIO default configuration and function for configuring a pin
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-07
 */

#include "gpio.h"
#include "stm32f1xx.h"

void gpio_clock_init(void)
{
    RCC->APB2ENR = RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPEEN | RCC_APB2ENR_AFIOEN;   // enable all GPIOs and AFIO

    // set all ports to input with pull-down
    GPIOA->CRL = 0x88888888;
    GPIOA->CRH = 0x88888888;
    GPIOA->ODR = 0;
    GPIOB->CRL = 0x88888888;
    GPIOB->CRH = 0x88888888;
    GPIOB->ODR = 0;
    GPIOC->CRL = 0x88888888;
    GPIOC->CRH = 0x88888888;
    GPIOC->ODR = 0;
    GPIOD->CRL = 0x88888888;
    GPIOD->CRH = 0x88888888;
    GPIOD->ODR = 0;
    GPIOE->CRL = 0x88888888;
    GPIOE->CRH = 0x88888888;
    GPIOE->ODR = 0;
}

/*------------------------------------------------------------------------*//**
* \brief Configures pin.
* \details Configures one pin in one port.
*
* \param [in] port_ptr points to the configuration structure of desired port
* \param [in] pin selects one pin, [0,15]
* \param [in] mode_cnf_value is a value of MODE and CNF which will be set for
* selected pin, {GPIO_CRx_MODE_CNF_IN_ANALOG_value,
* GPIO_CRx_MODE_CNF_IN_FLOATING_value, GPIO_CRx_MODE_CNF_IN_PULL_U_D_value,
* GPIO_CRx_MODE_CNF_OUT_PP_2M_value, GPIO_CRx_MODE_CNF_OUT_PP_10M_value,
* GPIO_CRx_MODE_CNF_OUT_PP_50M_value, GPIO_CRx_MODE_CNF_OUT_OD_2M_value,
* GPIO_CRx_MODE_CNF_OUT_OD_10M_value, GPIO_CRx_MODE_CNF_OUT_OD_50M_value,
* GPIO_CRx_MODE_CNF_ALT_PP_2M_value, GPIO_CRx_MODE_CNF_ALT_PP_10M_value,
* GPIO_CRx_MODE_CNF_ALT_PP_50M_value, GPIO_CRx_MODE_CNF_ALT_OD_2M_value,
* GPIO_CRx_MODE_CNF_ALT_OD_10M_value, GPIO_CRx_MODE_CNF_ALT_OD_50M_value} or
* use m_GPIO_MODE_CNF_value(mode, cnf) macro
*//*-------------------------------------------------------------------------*/

void gpio_pin_cfg(GPIO_TypeDef* port_ptr, uint32_t pin, uint32_t mode_cnf_value)
{
    volatile uint32_t* cr_ptr;
    uint32_t cr_value;

    cr_ptr = &port_ptr->CRL;   // configuration of pins [0,7] is in CRL

    if(pin >= 8)    // is pin in [8; 15]?
    {               // configuration of pins [8,15] is in CRH
        cr_ptr++;   // advance to next struct element CRL -> CRH
        pin -= 8;   // crop the pin number
    }

    cr_value = *cr_ptr;   // localize the CRL / CRH value

    cr_value &= ~(GPIO_CRx_MODE_CNF_mask << (pin * 4));   // clear the MODE and CNF fields (now that pin is an analog input)
    cr_value |= (mode_cnf_value << (pin * 4));            // save new MODE and CNF value for desired pin

    *cr_ptr = cr_value;   // save localized value to CRL / CRL
}
