#include "lib/acquisition/sampling_time.h"

#include "stm32f4xx.h"

#define TIMx_ARR_ISBUFF           0b01
#define TIMx_EDGE_ALIGNED_MODE    0b00
#define TIMx_UPCOUNTER            0b00
#define TIMx_OPM_DISABLE          0b00
#define TIMx_UDIS_UEV_EN          0b00
#define TIMx_URS_DMAREQ_OVERUNDER 0b01
#define TIMx_CEN                  0b01
#define TIMx_UPDMA_REQ_EN         0b01

#define TIM_ARPE_PRELOAD       (TIMx_ARR_ISBUFF << TIM_CR1_ARPE_Pos)
#define TIM_CMS_EDGE_ALI_M     (TIMx_EDGE_ALIGNED_MODE << TIM_CR1_CMS_Pos)
#define TIM_DIR_UP             (TIMx_UPCOUNTER << TIM_CR1_DIR_Pos) 
#define TIM_OPM_DIS            (TIMx_OPM_DISABLE << TIM_CR1_OPM_Pos)
#define TIM_UDIS_UPEVENT_EN    (TIMx_UDIS_UEV_EN << TIM_CR1_UDIS_Pos)
#define TIM_URS_DMA_OVER_UNDER (TIMx_URS_DMAREQ_OVERUNDER << TIM_CR1_URS_Pos)
#define TIM_COUNT_EN           (TIMx_CEN << TIM_CR1_CEN_Pos)

#define TIM_UP_DMA_REQ_EN      (TIMx_UPDMA_REQ_EN << TIM_DIER_UDE_Pos)

#define TIM_PSC_83             0b01010011

__attribute((always_inline)) static inline void config_reg_cr1(void)
{
    // Sets clock division to tdts=tck_int
    TIM1->CR1 &= ~(TIM_CR1_CKD_Msk);

    // Sets Auto-Reload Register(ARR) preload
    TIM1->CR1 &= ~(TIM_CR1_ARPE_Msk);
    TIM1->CR1 |= TIM_ARPE_PRELOAD;

    // Configures CMS to Edge-aligned mode
    TIM1->CR1 &= ~(TIM_CR1_CMS_Msk);
    TIM1->CR1 |= TIM_CMS_EDGE_ALI_M;

    // Configures DIR to Up counter
    TIM1->CR1 &= ~(TIM_CR1_DIR_Msk);
    TIM1->CR1 |= TIM_DIR_UP;

    // Configures One Pulse Mode to disabled, continuous counting
    TIM1->CR1 &= ~(TIM_CR1_OPM_Msk);
    TIM1->CR1 |= TIM_OPM_DIS;

    // Sets UDIS to UEV enabled
    TIM1->CR1 &= ~(TIM_CR1_UDIS_Msk);
    TIM1->CR1 |= TIM_UDIS_UPEVENT_EN;

    // Filters Update interrupt for DMA requests and overflow/underflow
    TIM1->CR1 &= ~(TIM_CR1_URS_Msk);
    TIM1->CR1 |= TIM_URS_DMA_OVER_UNDER;
}

__attribute((always_inline)) static inline void config_reg_dier(void)
{
    // Sets Update DMA request enable
    TIM1->DIER &= ~(TIM_DIER_UDE_Msk);
    TIM1->DIER |= TIM_UP_DMA_REQ_EN;
}

__attribute((always_inline)) static inline void config_reg_psc(void)
{
    // Configures PSC(pre-scaler) to 83, resulting 1Mhz in counter
    TIM1->PSC &= ~(TIM_PSC_PSC_Msk);
    TIM1->PSC = TIM_PSC_83;
}

__attribute((always_inline)) static inline void config_reg_arr(void)
{
    // Sets ARR to 0
    TIM1->ARR = 0;
}

__attribute((always_inline)) static inline void counter_enable(void)
{
    // Enables counter
    TIM1->CR1 &= ~(TIM_CR1_CEN_Msk);
    TIM1->CR1 |= TIM_COUNT_EN;
}

__attribute((always_inline)) inline void config_timer(void)
{
    config_reg_cr1();
    config_reg_dier();
    config_reg_psc();
    config_reg_arr();

    counter_enable();
}