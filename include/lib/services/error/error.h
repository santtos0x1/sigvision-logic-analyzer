#pragma once

typedef enum {
    LOG_OK,
    LOG_MEM_ERR,
    LOG_TIMEOUT_ERR,
    LOG_GENERIC_ERR,
} log_err_t;

/**
 * Converts a log_err_t error code to its corresponding string representation.
 *
 * @param error The log_err_t error code to be converted
 *
 * @return char*  Pointer to a string containing the error name
 */
__attribute((always_inline)) inline char *log_err_to_name(log_err_t error);