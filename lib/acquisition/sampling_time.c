#include "lib/acquisition/sampling_time.h"

#include "stm32f4xx.h"

__attribute((always_inline)) inline void config_timer(void)
{
    // Sets Auto-Reload Register(ARR) preload
    TIM1->CR1 &= ~(TIM_CR1_ARPE_Msk);
    TIM1->CR1 |= (0b01 << TIM_CR1_ARPE_Pos);

    // Configures CMS to Edge-aligned mode
    TIM1->CR1 &= ~(TIM_CR1_CMS_Msk);
    TIM1->CR1 |= (0b00 << TIM_CR1_CMS_Pos);

    // Configures DIR to Up counter
    TIM1->CR1 &= ~(TIM_CR1_DIR_Msk);
    TIM1->CR1 |= (0b00 << TIM_CR1_DIR_Pos);

    // Configures One Pulse Mode to disabled, continuous counting
    TIM1->CR1 &= ~(TIM_CR1_OPM_Msk);
    TIM1->CR1 |= (0b00 << TIM_CR1_OPM_Pos);

    // Sets UDIS to UEV enabled
    TIM1->CR1 &= ~(TIM_CR1_UDIS_Msk);
    TIM1->CR1 |= (0b00 << TIM_CR1_UDIS_Pos);

    // Filters Update interrupt for DMA requests and overflow/underflow
    TIM1->CR1 &= ~(TIM_CR1_URS_Msk);
    TIM1->CR1 |= (0b01 << TIM_CR1_URS_Pos);

    // Sets Update DMA request enable
    TIM1->DIER &= ~(TIM_DIER_UDE_Msk);
    TIM1->DIER |= (0b01 << TIM_DIER_UDE_Pos);

    // Configures PSC(pre-scaler) to 83, resulting 1Mhz in counter
    TIM1->PSC &= ~(TIM_PSC_PSC_Msk);
    TIM1->PSC = 0b01010011;

    // Sets ARR to 0
    TIM1->ARR = 0;

    // Enables counter
    TIM1->CR1 &= ~(TIM_CR1_CEN_Msk);
    TIM1->CR1 |= (0b01 << TIM_CR1_CEN_Pos);
}