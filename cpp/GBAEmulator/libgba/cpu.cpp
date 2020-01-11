#include "cpu.hpp"

void CPU::setMemory(Memory *memory)
{
    _memory = memory;
}

void CPU::initializeState()
{
    _cpuState.InstructionPointer = 0;
}

void CPU::step()
{
    
}
