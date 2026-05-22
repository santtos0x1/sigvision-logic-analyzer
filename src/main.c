#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#include <stdio.h>
#include "stdint.h"

GPIO_InitTypeDef emb_led = {
    .Pin = GPIO_PIN_13,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Speed = GPIO_SPEED_FREQ_MEDIUM,
    .Pull = GPIO_NOPULL,
};

#define PLLN_336MHZ_MUL 0b101010000

#define PLLM_16MHZ_DIV 0B10000

volatile uint32_t millis_count = 0;

__attribute__((always_inline)) static inline void clktree_init(void)
{
    // ------ MCU PLL CONFIG ------
    // Enables PLL 
    RCC->CR &= ~(RCC_CR_PLLON_Msk);
    RCC->CR &= (0b1 << RCC_CR_PLLON_Pos);

    // Sets PLL config to use internal clock output
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC_Msk);
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;

    // Configurese frequency divider to 4, i.e: 336Mhz / 4 = 84Mhz System clock (VCO output)
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP_Msk);
    RCC->PLLCFGR |= (0b01 << RCC_PLLCFGR_PLLP_Pos);

    // Configures frequency multiplier to 336Mhz (VCO input)
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN_Msk);
    RCC->PLLCFGR |= (PLLN_336MHZ_MUL << RCC_PLLCFGR_PLLN_Pos);

    // Configures HSI frequency divider to 16mhz
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk);
    RCC->PLLCFGR |= (PLLM_16MHZ_DIV << RCC_PLLCFGR_PLLM_Pos);

    // Waits until PLL lock
    while(((RCC->CR >> 25) & 0x01) != 0x01);

    // ------ ------ ------

    // ------ Flash config ------
    // Enables Data cache
    FLASH->ACR &= ~(FLASH_ACR_DCEN_Msk);
    FLASH->ACR |= (0B01 << FLASH_ACR_DCEN_Pos);
    
    // Enables Instruction cache
    FLASH->ACR &= ~(FLASH_ACR_ICEN_Msk);
    FLASH->ACR |= (0B01 << FLASH_ACR_ICEN_Pos);

    // Enables Prefetch CPU instructions 
    FLASH->ACR &= ~(FLASH_ACR_PRFTEN_Msk);
    FLASH->ACR |= (0B01 << FLASH_ACR_PRFTEN_Pos);
    
    // Sets latency to wait 2 states for high frequency
    FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk);
    FLASH->ACR |= (0B10 << FLASH_ACR_LATENCY_Pos);
    // ------ ------ ------

    // ------ RCC_CFGR Global configs ------
    // Sets AHB CFGR divider to 1, using total clock frequency
    RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
    RCC->CFGR |= (0B00 << RCC_CFGR_HPRE_Pos);

    // Sets APB1 CFGR divider to 1, using total clock frequency
    RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
    RCC->CFGR |= (0B00 << RCC_CFGR_PPRE1_Pos);

    // Configures clock source to use HSI
    RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
    RCC->CFGR |= RCC_CFGR_SW_HSI;

    // Waits util PLL is set to clock source
    while((((RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos)) != 0b10);
    // ------ ------ ------
}

__attribute__((always_inline)) static inline void systick_init(void)
{
    // Set systick to use internal clock
    SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk);
    SysTick->CTRL |= (0b01 << SysTick_CTRL_CLKSOURCE_Pos);

    // Enables counter
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
    SysTick->CTRL |= (0b01 << SysTick_CTRL_ENABLE_Pos);
}

__attribute__((always_inline)) static inline uint32_t get_millis(void)
{
    return millis_count;
}

// Hadware called function
void SysTick_Handler(void)
{
    millis_count++;
}

int main(void)
{
    clktree_init();

    systick_init();

    // Enables GPIOC clock
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Init GPIO pin configuration
    HAL_GPIO_Init(GPIOC, &emb_led);

    uint32_t last_time = 0;

    for(;;)
    {
        if(get_millis() - last_time >= 1000)
        {
            last_time = get_millis();
        
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }
    }

    return 0;
}