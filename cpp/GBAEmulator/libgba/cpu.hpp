#pragma once

#include "cpustate.hpp"
#include "memory.hpp"

class CPU
{
private:
    CpuState _cpuState = {};
    Memory *_memory;
    
public:
    CPU() = default;

    void setMemory(Memory *memory);

    void initializeState();
    void step();
};