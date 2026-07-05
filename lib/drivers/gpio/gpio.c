#include "lib/drivers/gpio/gpio.h"

#include "stm32f4xx.h"

#include <stdint.h>

__attribute((always_inline)) static inline void config_reg_ahb1enr(void)
{
    // Enables GPIOA clock
    RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOAEN_Msk);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

__attribute((always_inline)) static inline void config_reg_moder(void)
{
    // Sets GPIOA pin 0-7 to input mode (Channel probes)
    GPIOA->MODER &= ~(
        GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk | 
        GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk
    );
}

__attribute((always_inline)) static inline void config_reg_pupdr(void)
{
    // Sets GPIOA pin 0-7 to no pull
    GPIOA->PUPDR &= ~(
        GPIO_PUPDR_PUPD0_Msk | GPIO_PUPDR_PUPD1_Msk | 
        GPIO_PUPDR_PUPD2_Msk | GPIO_PUPDR_PUPD3_Msk 
    );
}

__attribute((always_inline)) inline void gpio_init(void)
{
    config_reg_ahb1enr();
    config_reg_moder();
    config_reg_pupdr();
}

uint8_t probes_read(void)
{
    uint8_t sample_data = 0;

    // 00000...00001111 -> 0x0F
    // 01010...10010100 -> GPIOA->IDR 32-bit register
    // 00000...00000100 -> Filtered data
    sample_data = GPIOA->IDR & 0x0F;

    return sample_data;
}

// 0 & 1 = 0
