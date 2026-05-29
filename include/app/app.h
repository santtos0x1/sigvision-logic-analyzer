#pragma once

typedef enum
{
    STATE_IDLE,
    STATE_ACQUISITION,
    STATE_ERROR
} fsm_state_t;

void start_app(void);