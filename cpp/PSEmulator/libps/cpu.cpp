#include "cpu.hpp"

#include <cstring>

#include "opcodes.hpp"

void CPU::setMemory(Memory *memory)
{
    _memory = memory;
}

void CPU::initializeState()
{
    memset(&_cpuState, 0, sizeof(CpuState));
    // _opcodeTable = initializeOpcodeTable();
}

void CPU::step()
{
    // Get Opcode at current PC address
    auto instructionPointer = _cpuState.PC.full;
    auto opcode = _memory->uint8(instructionPointer);
    auto opcodeFunction = _opcodeTable[opcode];
    opcodeFunction(&_cpuState);
}
