#pragma once

#define CLKSOURCE_INTERNAL_CLK 0b01
#define SYSTICK_ENABLE_COUNTER 0b01

#define ARM_SYSTICK_CTRL_CLKSOURCE      (CLKSOURCE_INTERNAL_CLK << SysTick_CTRL_CLKSOURCE_Pos)
#define ARM_SYSTICK_CTRL_ENABLE_COUNTER (SYSTICK_ENABLE_COUNTER << SysTick_CTRL_ENABLE_Pos)

/**
 * @brief Configures and initializes the ARM Cortex SysTick register.
 */
__attribute__((always_inline)) inline void systick_init(void);