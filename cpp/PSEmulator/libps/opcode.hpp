#pragma once

#include "cpustate.hpp"
#include "memory.hpp"

#include <cstdint>

class Opcode {
private:
    uint32_t _opcode;

    // For debugging purposes
    uint32_t _address;

public:
    Opcode(uint32_t opcode);

    void setAddress(uint32_t address) { _address = address; }
    uint32_t address() { return _address; }

    uint32_t raw();

    // Get bits 31..26
    uint8_t instruction();

    // Get bits 20..16
    uint8_t rt();

    // Get bits 25..21
    uint8_t rs();

    // Get bits 15..11
    uint8_t rd();

    // Get bits 15..0
    uint16_t imm16();

    // Get bits 10..6
    uint8_t imm5();

    // Get bits 25..0
    uint32_t imm26();

    // Gets bits 5..0
    uint8_t subfunction();

    static Opcode NOP() { return Opcode(0); }
};

namespace OpcodeImplementation {
void lui(Opcode opcode, CpuState *cpuState);
void ori(Opcode opcode, CpuState *cpuState);
void sw(Opcode opcode, CpuState *cpuState, Memory *memory);
void sll(Opcode opcode, CpuState *cpuState);
void addiu(Opcode opcode, CpuState *cpuState);
void j(Opcode opcode, CpuState *cpuState);
}; // namespace OpcodeImplementation
