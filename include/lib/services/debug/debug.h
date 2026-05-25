#pragma once

#include "stm32f4xx_hal_uart.h"

typedef enum
{
    DEBUG_INFO,
    DEBUG_WARN,
    DEBUG_DATA,
    DEBUG_ERROR
} debug_type_t;

/**
 * @brief Sends text data through UART.
 * 
 * @param pdata Text data to send
 * 
 * @return HAL_StatusTypeDef: status
 */
__attribute__((always_inline)) inline HAL_StatusTypeDef debug_print(const char *pdata);

/**
 * @brief Converts debug type to text.
 * 
 * @param d_type Debug type
 * 
 * @return Char *
 */
char *debug_type_to_name(debug_type_t d_type);