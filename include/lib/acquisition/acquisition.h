#pragma once

#include <stdint.h>
#include "lib/services/error/error.h"

/**
 * @brief Fills a buffer with data samples from all 8 probe channels.
 *
 * Each entry of the buffer represents the simultaneous state of the 8 probes,
 * where each bit corresponds to a probe channel.
 *
 * Bit mapping within each entry:
 * @code
 *   Bit:   7       6       5       4       3       2       1       0
 *          probe7  probe6  probe5  probe4  probe3  probe2  probe1  probe0
 *
 *   Example: 0x12 = 0b00010010
 *            -> probe4 = 1, probe1 = 1, all others = 0
 * @endcode
 *
 * @param[out] buff     Buffer to be filled with probe samples.
 * @param[in]  buff_len Number of entries to write into the buffer.
 *
 * @return log_err_t    Error code indicating success or failure.
 */
log_err_t sample_acq(uint8_t *buff, uint16_t buff_len);