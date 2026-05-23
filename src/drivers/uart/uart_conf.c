#include "drivers/uart/uart_conf.h"

#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_rcc.h"

#include <stdint.h>

#define UART_MAX_DELAY 1000 // UART Delay timout

UART_HandleTypeDef huart = {0}; // UART config struct

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_ENABLE(); // Enables USART1 clock
        __HAL_RCC_GPIOA_CLK_ENABLE(); // Enables GPIOA clock

        GPIO_InitTypeDef tx = {0};

        // Configures GPIOA pin 9 as USART1 TX
        tx.Pin = GPIO_PIN_9;
        tx.Mode = GPIO_MODE_AF_PP;
        tx.Pull = GPIO_NOPULL;
        tx.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        tx.Alternate = GPIO_AF7_USART1;

        HAL_GPIO_Init(GPIOA, &tx);
    }
}

__attribute__((always_inline)) inline HAL_StatusTypeDef UART_init(void)
{
    HAL_StatusTypeDef status = 0;

    huart.Instance = USART1;

    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    status = HAL_UART_Init(&huart); // Initializes UART asynchronous mode

    return status;
}

HAL_StatusTypeDef UART_TX_data(const char *pdata, uint16_t size)
{
    HAL_StatusTypeDef status = 0;
    
    // Sends data through UART
    status = HAL_UART_Transmit(&huart, (uint8_t *)pdata, size, UART_MAX_DELAY);

    return status;
}
