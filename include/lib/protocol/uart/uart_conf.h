#pragma once

/**
 * @brief Configures and initializes UART communication for debugging.
 * Uses USART1 instace and only configures TX pin. Using pin 9 in GPIOA by default TX pin
 *  
 * @return HAL_StatusTypeDef: status
 * 
 * @note Baud Rate default value is 115200
 */
__attribute__((always_inline)) inline HAL_StatusTypeDef UART_init(void);


/**
 * @brief Sends data through UART transmitter pin (TX).
 * 
 * @param pdata Data to trasmit
 * @param size Size of the transmitted data
 * 
 * @return HAL_StatusTypeDef: status
 */
HAL_StatusTypeDef UART_TX_data(const char *pdata, uint16_t size);