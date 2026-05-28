#pragma once

#include <stdint.h>

/**
 * Bare-metal initialization and configuration of all required GPIO pins.
*/
__attribute((always_inline)) inline void gpio_init(void);

/**
 * Reads the digital state of all probes, including the CLK probe.
 *
 * @return uint16_t  2-byte bitmask representing the digital state of each probe
 */
uint8_t probes_read(void);