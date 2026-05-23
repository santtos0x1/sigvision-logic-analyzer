#pragma once

#include "stm32f4xx_hal_uart.h"

typedef enum
{
    DEBUG_INFO,
    DEBUG_WARN,
    DEBUG_DATA,
    DEBUG_ERROR
} debug_type_t;

__attribute__((always_inline)) inline HAL_StatusTypeDef debug_print(const char *pdata);

char *debug_type_to_name(debug_type_t d_type);