#include "app/app.h"
#include "lib/drivers/clock/sys_clock.h"
#include "lib/drivers/gpio/gpio.h"
#include "lib/services/debug/debug.h"
#include "lib/protocol/uart/uart_conf.h"
#include "lib/services/error/error.h"
#include "lib/acquisition/sampling_time.h"
#include "lib/acquisition/dma_capture.h"

fsm_state_t fsm_state = STATE_IDLE;

void start_app(void)
{
    log_err_t g_err;

    switch(fsm_state)
    {
        case STATE_IDLE:
        {
            // Initializes system clock tree module
            system_clock_init();

            // Initializes GPIO module
            gpio_init();
            
            // Initializes UART config
            g_err = UART_init();
            if(g_err != HAL_OK)
            {
                set_state(STATE_ERROR);
            }

            // Initializes TIM1 registers
            config_timer();

            // Initializes DMA2 module
            dma_init();
        }

        case STATE_ACQUISITION:
        {

        }
        
        case STATE_ERROR:
        {
            
        }
    }
}

static void set_state(fsm_state_t next_state)
{
    fsm_state = next_state;
}