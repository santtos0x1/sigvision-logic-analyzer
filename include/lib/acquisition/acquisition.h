#pragma once

#include <stdint.h>
#include "lib/services/error/error.h"

/**
 * @brief Fills an 8-bit integer buffer with data samples from all 8 channel probes.
 *
 * Each byte of input represents the simultaneous state of all 8 probes: each bit
 * corresponds to one channel, where the most significant bit (bit 7) represents
 * probe7 and the least significant bit (bit 0) represents probe0.
 *
 * Bit mapping within each byte:
 * @code
 *   Bit:   7       6       5       4       3       2       1       0
 *          probe7  probe6  probe5  probe4  probe3  probe2  probe1  probe0
 *
 *   Example: 0x12 = 0b00010010
 *            -> probe1 = 1, probe4 = 1, all others = 0
 * @endcode
 *
 * @param[out] buff     Buffer to be filled with probe samples.
 * @param[in]  buff_len Number of bytes to write into the buffer.
 *
 * @return log_err_t    Error code indicating success or failure.
 */
log_err_t sample_acq(uint8_t *buff, uint16_t buff_len);