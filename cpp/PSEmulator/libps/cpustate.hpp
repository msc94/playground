#pragma once

#include <cstdint>

class CpuState
{
    uint32_t _pc;
    uint32_t _registers[32];

public:
    void initialize();

    void incrementProgramCounter();
    void setProgramCounter(uint32_t value);
    uint32_t getProgramCounter();

    void setRegister(uint8_t index, uint32_t value);
    uint32_t getRegister(uint8_t index);
};