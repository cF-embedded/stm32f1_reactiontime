extern "C"
{
#include "core_init.h"
#include "platform_specific.h"
}

void system_init(void)
{
    /* PLL configuration for 84 MHz */
    core_init();

    /* FreeRTOS scheduler start */
    vTaskStartScheduler();
}