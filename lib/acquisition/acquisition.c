#include "lib/acquisition/acquisition.h"
#include "lib/drivers/gpio/gpio.h"
#include "lib/services/error/error.h"

#include "stm32f4xx.h"

#include <stdint.h>

#define ACQUISITION_MAX_SAMPLES 8192

log_err_t sample_acq(uint16_t *buff, uint16_t buff_len)
{
    if(buff_len <= ACQUISITION_MAX_SAMPLES)
    {
        for(int i = 0; i < buff_len; i++)
        {
            buff[i] = probes_read();
        }

        return LOG_OK;
    }
    
    return LOG_MEM_ERR;
}