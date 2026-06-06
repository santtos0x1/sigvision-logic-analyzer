#include "app/app.h"

#include "stm32f4xx.h"

#include <stdint.h>

#define SxCR_MSIZE_HALFW   0b01
#define SxCR_PSIZE_HALFW   0b01
#define SxCR_CIRC_MODE_DIS 0b00
#define SxCR_DIR_P2M       0b00
#define SxCR_PFCTRL_DMA    0b00
#define SxCR_STREAM_EN     0b01

#define DMA_MSIZE_HALFWORD (SxCR_MSIZE_HALFW << DMA_SxCR_MSIZE_Pos)
#define DMA_PSIZE_HALFWORD (SxCR_PSIZE_HALFW << DMA_SxCR_PSIZE_Pos)
#define DMA_CIRC_MODE_DIS  (SxCR_CIRC_MODE_DIS << DMA_SxCR_CIRC_Pos)
#define DMA_DIR_P2M        (SxCR_DIR_P2M << DMA_SxCR_DIR_Pos)
#define DMA_PFCTRL_DMA     (SxCR_PFCTRL_DMA << DMA_SxCR_PFCTRL_Pos)
#define DMA_EN_EN          (SxCR_STREAM_EN << DMA_SxCR_EN_Msk);

#define DMA_NDT_8192       0x2000

__attribute((always_inline)) static inline void config_reg_cr(void)
{
    // Selects DMA2 controller Stream 5 channel 6
    DMA2_Stream5->CR &= ~(DMA_SxCR_CHSEL_Msk);
    DMA2_Stream5->CR |= DMA_CHANNEL_6;

    // Sets MBURST to a single transfer
    DMA2_Stream5->CR &= ~(DMA_SxCR_MBURST_Msk);
    DMA2_Stream5->CR |= DMA_MBURST_SINGLE;

    // Sets PBURST to a single transfer
    DMA2_Stream5->CR &= ~(DMA_SxCR_PBURST_Msk);
    DMA2_Stream5->CR |= DMA_PBURST_SINGLE;

    // Configures to use no double buffer mode
    DMA2_Stream5->CR &= ~(DMA_SxCR_DBM_Msk);
    
    // Sets Stream 5 very high PL
    DMA2_Stream5->CR &= ~(DMA_SxCR_PL_Msk);
    DMA2_Stream5->CR |= DMA_PRIORITY_VERY_HIGH;

    // Configures PINCO to increment address by 1 byte
    DMA2_Stream5->CR &= ~(DMA_SxCR_PINCOS_Msk);
    
    // Sets Memory size to Half Word (16 bits)
    DMA2_Stream5->CR &= ~(DMA_SxCR_MSIZE_Msk);
    DMA2_Stream5->CR |= DMA_MSIZE_HALFWORD;

    // Sets Peripheral size to Half Word (16 bits)
    DMA2_Stream5->CR &= ~(DMA_SxCR_PSIZE_Msk);
    DMA2_Stream5->CR |= DMA_PSIZE_HALFWORD;

    // Sets Memory pointer incrementer to enable
    DMA2_Stream5->CR &= ~(DMA_SxCR_MINC_Msk);
    DMA2_Stream5->CR |= DMA_MINC_ENABLE;
    
    // Sets Peripheral pointer incrementer to enable
    DMA2_Stream5->CR &= ~(DMA_SxCR_PINC_Msk);
    DMA2_Stream5->CR |= DMA_PINC_ENABLE;

    // Sets circular mode to disabled
    DMA2_Stream5->CR &= ~(DMA_SxCR_CIRC_Pos);
    DMA2_Stream5->CR |= DMA_CIRC_MODE_DIS;

    // Sets data direction to Peripheral to Memory
    DMA2_Stream5->CR &= ~(DMA_SxCR_DIR_Msk);
    DMA2_Stream5->CR |= DMA_DIR_P2M;

    // Sets the DMA controller to control the peripheral flow
    DMA2_Stream5->CR &= ~(DMA_SxCR_PFCTRL_Msk);
    DMA2_Stream5->CR |= DMA_PFCTRL_DMA;

    // Disables all CPU interrupts from DMA
    DMA2_Stream5->CR &= ~(
        DMA_SxCR_TCIE_Msk | DMA_SxCR_HTIE_Msk | 
        DMA_SxCR_TEIE_Msk | DMA_SxCR_DMEIE_Msk
    );
}

__attribute((always_inline)) static inline void config_reg_ndtr(void)
{
    // Sets Stream data number to 8192
    DMA2_Stream5->NDTR &= ~(DMA_SxNDT_Msk);
    DMA2_Stream5->NDTR |= (DMA_NDT_8192 << DMA_SxNDT_Pos);
}

__attribute((always_inline)) static inline void config_reg_par(void)
{
    // Sets GPIOA first 8 bits address
    DMA2_Stream5->PAR = (uint32_t) &GPIOA->IDR;
}

__attribute((always_inline)) static inline void config_reg_m0ar(void)
{
    // Sets SRAM memory address from sample_buffer
    DMA2_Stream5->M0AR = (uint32_t) &sample_buffer;
}

__attribute((always_inline)) static inline void dma_stream_enable(void)
{
    // Sets DMA stream to enable
    DMA2_Stream5->CR &= ~(DMA_SxCR_EN_Msk);
    DMA2_Stream5->CR |= DMA_EN_EN;
}

void dma_init(void)
{    
    config_reg_cr();
    config_reg_ndtr();
    config_reg_par();
    config_reg_m0ar();
    
    dma_stream_enable();
}