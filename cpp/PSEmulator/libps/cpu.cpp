#include "cpu.hpp"
#include "libutils/memory_utils.hpp"
#include "libutils/platform.hpp"
#include "opcode.hpp"

#include <algorithm>
#include <cstring>
#include <fmt/format.h>

void CPU::setMemory(Memory *memory) {
    _memory = memory;
}

void CPU::initializeState() {
    _cpuState.initialize();
    _nextOpcode = Opcode::NOP();
}

void CPU::decodeAndExecute(Opcode opcode) {
    auto instruction = opcode.instruction();
    spdlog::trace("[decode] instruction {0:#04x} ({0:#08b})", instruction);

    switch (instruction) {
    case 0b001111:
        OpcodeImplementation::lui(opcode, &_cpuState);
        return;

    case 0b001101:
        OpcodeImplementation::ori(opcode, &_cpuState);
        return;

    case 0b101011:
        OpcodeImplementation::sw(opcode, &_cpuState, _memory);
        return;

    case 0b001001:
        OpcodeImplementation::addiu(opcode, &_cpuState);
        return;

    case 0b000010:
        OpcodeImplementation::j(opcode, &_cpuState);
        return;

    case 0b000000: {
        auto subfunction = opcode.subfunction();
        switch (subfunction) {
        case 0b000000:
            OpcodeImplementation::sll(opcode, &_cpuState);
            return;
        }
    }

    default: {
        auto rawOpcode = opcode.raw();
        THROW(std::runtime_error,
              fmt::format("Unhandled opcode {0:#x} ({0:#b})", rawOpcode));
    }

    } // switch (instruction)
}

std::vector<uint32_t> BREAKPOINTS = {
    0xbfc00158,
};

void CPU::step() {
    // Always execute the last opcode we have seen to handle Branch Delay Slots
    auto opcode = _nextOpcode;

    auto pc = _cpuState.getProgramCounter();
    auto rawOpcode = _memory->u32(pc);
    _nextOpcode = Opcode(rawOpcode);
    _nextOpcode.setAddress(pc);
    _cpuState.incrementProgramCounter();

    auto breakpointHit = std::any_of(BREAKPOINTS.begin(), BREAKPOINTS.end(), [&](auto x) {
        return x == opcode.address();
    });

    if (breakpointHit) {
        platform::debuggerBreak();
    }

    spdlog::trace("[decode] raw {0:#010x} ({0:#034b})", opcode.raw());
    decodeAndExecute(opcode);
}
