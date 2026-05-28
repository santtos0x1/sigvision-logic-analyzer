#pragma once

#include <stdint.h>

/**
    * @brief Introduces a delay in microseconds using GCC's Extended Assembly
    *   
    * @param us The number of microseconds to wait
*/
__attribute__((always_inline)) inline void delay_us(uint32_t us);