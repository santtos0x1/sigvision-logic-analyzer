#pragma once

#include <stdint.h>

__attribute((always_inline)) inline void gpio_init(void);

uint8_t probes_read(void);