#include "cpu.hpp"
#include "libutils/memory_utils.hpp"
#include "opcode.hpp"

#include <cstring>
#include <fmt/format.h>

void CPU::setMemory(Memory *memory) {
    _memory = memory;
}

void CPU::initializeState() {
    _cpuState.initialize();
    // _opcodeTable = initializeOpcodeTable();
}

void CPU::decodeAndExecute(Opcode opcode) {
    auto instruction = opcode.instruction();

    if (instruction == 0b001111) {
        OpcodeImplementation::lui(opcode, &_cpuState);
        return;
    }

    if (instruction == 0b001101) {
        OpcodeImplementation::ori(opcode, &_cpuState);
        return;
    }

    if (instruction == 0b101011) {
        OpcodeImplementation::sw(opcode, &_cpuState, _memory);
        return;
    }

    auto rawOpcode = opcode.raw();
    THROW(std::runtime_error,
          fmt::format("Unhandled opcode {0:#x} ({0:#b})", rawOpcode));
}

void CPU::step() {
    // Get Opcode at current PC address
    auto rawOpcode = _memory->u32(_cpuState.getProgramCounter());
    spdlog::debug("Read raw opcode {0:#x} ({0:#b}). Decoding.", rawOpcode);

    auto opcode = Opcode(rawOpcode);
    decodeAndExecute(opcode);

    _cpuState.incrementProgramCounter();
}
