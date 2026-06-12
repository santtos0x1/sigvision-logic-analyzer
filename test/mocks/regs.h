#pragma once

#include <stdint.h>

typedef struct
{
    uint32_t CR;
    uint32_t PLLCFGR;
    uint32_t CFGR;
} RCC_reg;

typedef struct
{
    uint32_t ACR;
} FLASH_reg;

extern RCC_reg RCC_test;
extern FLASH_reg FLASH_test;