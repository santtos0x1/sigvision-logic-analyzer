#pragma once

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

__attribute((always_inline)) inline void config_timer(void);
__attribute((always_inline)) inline void tim1_init_counter(void);