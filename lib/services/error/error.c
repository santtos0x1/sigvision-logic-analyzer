#include "lib/services/error/error.h"

__attribute((always_inline)) inline char *log_err_to_name(log_err_t error)
{
    switch (error)
    {
        case LOG_OK: return "LOG_OK";
        case LOG_MEM_ERR: return "LOG_MEM_ERR";
        case LOG_GENERIC_ERR: return "LOG_GENERIC_ERR";
        case LOG_TIMEOUT_ERR: return "LOG_TIMEOUT_ERR";

        default: return "Not found";
    }
}