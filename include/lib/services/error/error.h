#pragma once

typedef enum {
    LOG_OK,
    LOG_MEM_ERR,
    LOG_TIMEOUT_ERR,
    LOG_GENERIC_ERR,
} log_err_t;

__attribute((always_inline)) inline char *log_err_to_name(log_err_t error);