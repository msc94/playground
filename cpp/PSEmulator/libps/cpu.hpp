#pragma once

#include <functional>
#include <vector>

#include "cpustate.hpp"
#include "memory.hpp"
#include "opcode.hpp"

class CPU {
private:
    CpuState _cpuState = {};
    Memory *_memory = nullptr;
    Opcode _nextOpcode = Opcode::NOP();

public:
    CPU() = default;

    void setMemory(Memory *memory);

    void initializeState();
    void decodeAndExecute(Opcode opcode);
    void step();
};