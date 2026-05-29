#include "lib/drivers/gpio/gpio.h"

#include "stm32f4xx.h"

#include <stdint.h>

__attribute((always_inline)) inline void gpio_init(void)
{
    // Enables GPIOA clock
    RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOAEN_Msk);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOBEN_Msk);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Sets GPIOA pin 0-7 to input mode (Channel probes)
    GPIOA->MODER &= ~(
        GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk | GPIO_MODER_MODE2_Msk |
        GPIO_MODER_MODE3_Msk | GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk |
        GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk
    );
    
    // Sets GPIOB pin 0 to input mode (CLK)
    GPIOB->MODER &= ~(GPIO_MODER_MODE0_Msk);

    // Sets GPIOA pin 0-7 to no pull
    GPIOA->PUPDR &= ~(
        GPIO_PUPDR_PUPD0_Msk | GPIO_PUPDR_PUPD1_Msk | GPIO_PUPDR_PUPD2_Msk |
        GPIO_PUPDR_PUPD3_Msk | GPIO_PUPDR_PUPD4_Msk | GPIO_PUPDR_PUPD5_Msk |
        GPIO_PUPDR_PUPD6_Msk | GPIO_PUPDR_PUPD7_Msk
    );

    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk);
}

uint16_t probes_read(void)
{
    uint16_t sample_data = 0;
    
    // 00000...11111111 -> 0xFF
    // 01010...10010100 -> GPIOA->IDR 32-bit register
    // 00000...10010100 -> Filtered data
    sample_data = GPIOA->IDR & 0xFF;

    // Gets 1 bit of the CLK pin and merges to sample_data
    sample_data |= (GPIOB->IDR & 0x01) << 8;
    
    return sample_data;
}