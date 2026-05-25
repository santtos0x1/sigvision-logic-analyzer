#include "lib/drivers/time/systick.h"

#include "stm32f4xx_hal.h"

__attribute__((always_inline)) inline void systick_init(void)
{
    // Set systick to use internal clock
    SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk);
    SysTick->CTRL |= (0b01 << SysTick_CTRL_CLKSOURCE_Pos);

    // Enables counter
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
    SysTick->CTRL |= (0b01 << SysTick_CTRL_ENABLE_Pos);
}