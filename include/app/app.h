#pragma once

typedef enum
{
    STATE_IDLE,
    STATE_ACQUISITION,
    STATE_ERROR
} fsm_state_t;

uint8_t sample_buffer[8192];

void start_app(void);