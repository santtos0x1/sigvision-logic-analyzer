#pragma once

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

/**
 * @brief  Configures the system clock tree.
 * 
 * This function enables the PLL oscillator using the internal clock source,
 * configures the flash cache and prefetch optimizations, and sets the Flash 
 * latency to 2 wait states to support the high clock frequency of 84 MHz.
 * 
 * @note   Clock distribution setup:
 *          - Core / CPU Clock : 84 MHz (via PLL)
 *          - AHB / Bus Clock  : 84 MHz
 *          - APB Peripherals  : 84 MHz
 * 
 */
__attribute__((always_inline)) inline void system_clock_init(void);