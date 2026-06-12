#include "lib/drivers/time/systick.h"

#include "stm32f4xx_hal.h"

#define CLKSOURCE_INTERNAL_CLK 0b01
#define SYSTICK_ENABLE_COUNTER 0b01

#define ARM_SYSTICK_CTRL_CLKSOURCE      (CLKSOURCE_INTERNAL_CLK << SysTick_CTRL_CLKSOURCE_Pos)
#define ARM_SYSTICK_CTRL_ENABLE_COUNTER (SYSTICK_ENABLE_COUNTER << SysTick_CTRL_ENABLE_Pos)

__attribute__((always_inline)) inline void systick_init(void)
{
    // Set systick to use internal clock
    SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk);
    SysTick->CTRL |= ARM_SYSTICK_CTRL_CLKSOURCE;

    // Enables counter
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
    SysTick->CTRL |= ARM_SYSTICK_CTRL_ENABLE_COUNTER;
}