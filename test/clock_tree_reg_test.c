#include "lib/drivers/clock/sys_clock.h"
#include "mocks/regs.h"

#include "stm32f4xx_hal.h"

#include <stdio.h>

void rcc_cr_reg(void)
{
    RCC_test.CR &= ~(RCC_CR_PLLON_Msk);
    RCC_test.CR |= RCC_PLL_EN;
}