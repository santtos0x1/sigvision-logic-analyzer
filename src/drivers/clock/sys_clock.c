#include "drivers/clock/sys_clock.h"

#include "stm32f4xx_hal.h"

#define PLLN_336MHZ_MUL 0b101010000
#define PLLM_16MHZ_DIV 0B10000

__attribute__((always_inline)) inline void system_clock_init(void)
{
    // ------ MCU PLL CONFIG ------
    // Enables PLL 
    RCC->CR &= ~(RCC_CR_PLLON_Msk);
    RCC->CR &= (0b1 << RCC_CR_PLLON_Pos);

    // Sets PLL config to use internal clock output
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC_Msk);
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;

    // Configures frequency divider to 4, i.e: 336Mhz / 4 = 84Mhz System clock (VCO output)
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