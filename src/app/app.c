#include "app/app.h"
#include "lib/drivers/clock/sys_clock.h"
#include "lib/drivers/gpio/gpio.h"
#include "lib/services/debug/debug.h"
#include "lib/protocol/uart/uart_conf.h"
#include "lib/services/error/error.h"

fsm_state_t fsm_state = STATE_IDLE;

void start_app(void)
{
    log_err_t g_err;

    switch(fsm_state)
    {
        case STATE_IDLE:
        {
            // Initializes GPIO module
            gpio_init();

            // Initializes system clock tree module
            system_clock_init();

            // Initializes UART config
            g_err = UART_init();
            if(g_err != HAL_OK)
            {
                set_state(STATE_ERROR);
            }
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