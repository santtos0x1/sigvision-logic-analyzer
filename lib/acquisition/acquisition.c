#include "lib/acquisition/acquisition.h"
#include "lib/drivers/gpio/gpio.h"

#include "stm32f4xx.h"

#include <stdint.h>

void sample_acq(uint8_t *buff, uint16_t buff_len)
{
    for(int i = 0; i < buff_len; i++)
    {
        buff[i] = probes_read();
    }-
}