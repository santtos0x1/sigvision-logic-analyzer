#include "lib/drivers/clock/sys_clock.h"

#include "stm32f4xx_hal.h"

#define PLLN_336MHZ_MUL     0b101010000
#define PLLM_16MHZ_DIV      0B10000
#define RCC_PLL_ON          0b01
#define RCC_FREQ_DIV4       0b01
#define FLASH_DATA_CACHE_EN 0b01
#define FLASH_INST_CACHE_EN 0b01
#define FLASH_PREFETCH_EN   0b01
#define FLASH_ACR_2STATES   0b10
#define RCC_CFGR_AHB1_DIV1  0b00
#define RCC_CFGR_APB1_DIV1  0b00

#define RCC_PLL_EN                  (RCC_PLL_ON << RCC_CR_PLLON_Pos)
#define RCC_FREQ_DIV_4              (RCC_FREQ_DIV4 << RCC_PLLCFGR_PLLP_Pos)
#define RCC_FREQ_MUL_336MHZ         (PLLN_336MHZ_MUL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_HSI_FREQ_DIV_16MHZ      (PLLM_16MHZ_DIV << RCC_PLLCFGR_PLLM_Pos)
#define FLASH_ACR_DATA_CACHE        (FLASH_DATA_CACHE_EN << FLASH_ACR_DCEN_Pos)
#define FLASH_ACR_INSTRUCTION_CACHE (FLASH_INST_CACHE_EN << FLASH_ACR_ICEN_Pos)
#define FLASH_ACR_PREFETCH_EN       (FLASH_PREFETCH_EN << FLASH_ACR_PRFTEN_Pos)
#define FLASH_ACR_LATENCY_2STATES   (FLASH_ACR_2STATES << FLASH_ACR_LATENCY_Pos)
#define RCC_CFGR_AHB1_DIVIDER_1     (RCC_CFGR_AHB1_DIV1 << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_APB1_DIVIDER_1     (RCC_CFGR_APB1_DIV1 << RCC_CFGR_PPRE1_Pos)
#define RCC_PLL_LOCK                ((RCC->CR >> 25) & 0x01)
#define PLL_CLK_SRC                 (((RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos))

__attribute__((always_inline)) inline void config_reg_rcc_cr(void)
{
    // Enables PLL 
    RCC->CR &= ~(RCC_CR_PLLON_Msk);
    RCC->CR |= RCC_PLL_EN;
}

__attribute__((always_inline)) inline void config_reg_rcc_pllcfgr(void)
{
    // Sets PLL config to use internal clock output
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC_Msk);
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;

    // Configures frequency divider to 4, i.e: 336Mhz / 4 = 84Mhz System clock (VCO output)
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP_Msk);
    RCC->PLLCFGR |= RCC_FREQ_DIV_4;

    // Configures frequency multiplier to 336Mhz (VCO input)
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN_Msk);
    RCC->PLLCFGR |= RCC_FREQ_MUL_336MHZ;

    // Configures HSI frequency divider to 16mhz
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk);
    RCC->PLLCFGR |= RCC_HSI_FREQ_DIV_16MHZ;

    // Waits until PLL lock
    while(RCC_PLL_LOCK != 0x01);
}

__attribute__((always_inline)) inline void config_reg_flash_acr(void)
{
    // Enables Data cache
    FLASH->ACR &= ~(FLASH_ACR_DCEN_Msk);
    FLASH->ACR |= FLASH_ACR_DATA_CACHE;
    
    // Enables Instruction cache
    FLASH->ACR &= ~(FLASH_ACR_ICEN_Msk);
    FLASH->ACR |= FLASH_ACR_INSTRUCTION_CACHE;

    // Enables Prefetch CPU instructions 
    FLASH->ACR &= ~(FLASH_ACR_PRFTEN_Msk);
    FLASH->ACR |= FLASH_ACR_PREFETCH_EN;
    
    // Sets latency to wait 2 states for high frequency
    FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk);
    FLASH->ACR |= FLASH_ACR_LATENCY;
}

__attribute__((always_inline)) inline void config_reg_rcc_cfgr(void)
{
    // Sets AHB CFGR divider to 1, using total clock frequency
    RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
    RCC->CFGR |= RCC_CFGR_AHB1_DIVIDER_1;

    // Sets APB1 CFGR divider to 1, using total clock frequency
    RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
    RCC->CFGR |= RCC_CFGR_APB1_DIVIDER_1;

    // Configures clock source to use HSI
    RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
    RCC->CFGR |= RCC_CFGR_SW_HSI;

    // Waits util PLL is set to clock source
    while(PLL_CLK_SRC != 0b10);
}

__attribute__((always_inline)) inline void system_clock_init(void)
{
    config_reg_rcc_cr();
    config_reg_rcc_pllcfgr();
    config_reg_flash_acr();
    config_reg_rcc_cfgr();
}