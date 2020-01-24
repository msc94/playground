#pragma once

#include <cstdint>

struct HiLo
{
    uint8_t hi;
    uint8_t lo;
};

union Register
{
    uint16_t full;
    HiLo hilo;
};

struct CpuState
{
    Register AF;
    Register BC;
    Register DE;
    Register HL;
    Register SP;
    Register PC;
};