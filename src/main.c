#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#include <stdio.h>
#include <stdint.h>

GPIO_InitTypeDef emb_led = {
    .Pin = GPIO_PIN_13,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Speed = GPIO_SPEED_FREQ_MEDIUM,
    .Pull = GPIO_NOPULL,
};

int main(void)
{
    // Enables GPIOC clock
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Init GPIO pin configuration
    HAL_GPIO_Init(GPIOC, &emb_led);

    for(;;)
    {
        // Main loop
    }

    return 0;
}