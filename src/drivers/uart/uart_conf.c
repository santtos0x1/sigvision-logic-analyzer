#include "drivers/uart/uart_conf.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_rcc.h"

// UART config struct
UART_HandleTypeDef huart = {0};

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        // Enables USART1 clock
        __HAL_RCC_USART1_CLK_ENABLE();
        // Enables GPIOA clock
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
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

__attribute__((always_inline)) inline void UART_init(void)
{
    huart.Instance = USART1;

    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    // Initializes UART asynchronous mode
    HAL_UART_Init(&huart);
}