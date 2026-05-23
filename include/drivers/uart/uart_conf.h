#pragma once

__attribute__((always_inline)) inline void UART_init(void);

HAL_StatusTypeDef UART_TX_data(const char *pdata, uint16_t size);