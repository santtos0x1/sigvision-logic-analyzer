#include "lib/drivers/time/delay.h"

#include <stdint.h>

__attribute__((always_inline)) inline void delay_us(uint32_t us)
{
    uint32_t cycles = us * 33; // Configuration for 84Mhz

    __asm__ volatile (
        "1: \n\t"
        "subs %0, %0, #1 \n\t" // Sub 1 from a reg placeholder
        "bne 1b \n\t" // Verifies if reg placeholder equals zero, if its not, returns to backwards placeholder 1"backwards"
        : "+r" (cycles) // Sets the cycles variable to %0 reg placeholder
        : // Input value 
        : "cc" // Tells the GCC that flags will be modified
    );
}