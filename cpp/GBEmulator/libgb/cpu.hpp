#pragma once

#include <vector>
#include <functional>

#include "cpustate.hpp"
#include "memory.hpp"

class CPU
{
private:
    CpuState _cpuState = {};
    Memory *_memory = nullptr;
    std::vector<std::function<void(CpuState*)>> _opcodeTable;

public:
    CPU() = default;

    void setMemory(Memory *memory);

    void initializeState();
    void step();
};