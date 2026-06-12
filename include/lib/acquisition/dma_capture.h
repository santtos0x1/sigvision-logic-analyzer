#pragma once

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

__attribute((always_inline)) inline void dma_init(void);