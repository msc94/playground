#pragma once

#include "cpustate.hpp"
#include "memory.hpp"

#include <cstdint>

class Opcode {
private:
    uint32_t _opcode;

public:
    Opcode(uint32_t opcode);

    uint32_t raw();

    // Get bits 31..26
    uint8_t instruction();

    // Get bits 20..16
    uint8_t rt();

    // Get bits 25..21
    uint8_t rs();

    // Get bits 15..0
    uint16_t immediate();
};

namespace OpcodeImplementation {
void lui(Opcode opcode, CpuState *cpuState);
void ori(Opcode opcode, CpuState *cpuState);
void sw(Opcode opcode, CpuState *cpuState, Memory *memory);
};
