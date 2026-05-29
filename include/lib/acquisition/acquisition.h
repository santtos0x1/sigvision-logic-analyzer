#pragma once

#include <stdint.h>
#include "lib/services/error/error.h"

/**
 * @brief Fills a 16-bit integer buffer with data samples from all 8 channel probes and the CLK probe.
 *
 * Each entry of the buffer represents the simultaneous state of all 8 probes and the CLK probe:
 * each bit corresponds to one channel, where bit 8 represents the CLK probe, bit 7 represents
 * probe7, and bit 0 represents probe0.
 *
 * Bit mapping within each entry:
 * @code
 *   Bit:   8     7       6       5       4       3       2       1       0
 *          clk   probe7  probe6  probe5  probe4  probe3  probe2  probe1  probe0
 *
 *   Example: 0x112 = 0b100010010
 *            -> probe1 = 1, probe4 = 1, clk = 1, all others = 0
 * @endcode
 *
 * @param[out] buff     Buffer to be filled with probe samples.
 * @param[in]  buff_len Number of entries to write into the buffer.
 *
 * @return log_err_t    Error code indicating success or failure.
 */
log_err_t sample_acq(uint16_t *buff, uint16_t buff_len);