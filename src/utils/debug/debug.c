#include "utils/debug/debug.h"
#include "drivers/uart/uart_conf.h"

#include "stm32f4xx_hal_uart.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

__attribute__((always_inline)) inline HAL_StatusTypeDef debug_print(const char *pdata)
{
    HAL_StatusTypeDef status = 0;
    size_t pd_size = strlen(pdata);

    status = UART_TX_data(pdata, (uint16_t)pd_size);

    return status;
}