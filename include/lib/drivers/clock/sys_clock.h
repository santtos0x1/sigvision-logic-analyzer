#pragma once

/**
 * @brief  Configures the system clock tree.
 * 
 * This function enables the PLL oscillator using the internal clock source,
 * configures the flash cache and prefetch optimizations, and sets the Flash 
 * latency to 2 wait states to support the high clock frequency of 84 MHz.
 * 
 * @note   Clock distribution setup:
 *          - Core / CPU Clock : 84 MHz (via PLL)
 *          - AHB / Bus Clock  : 84 MHz
 *          - APB Peripherals  : 84 MHz
 * 
 * @return void
 */
__attribute__((always_inline)) inline void system_clock_init(void);