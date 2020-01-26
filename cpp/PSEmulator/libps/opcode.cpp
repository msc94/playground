#include "opcode.hpp"

Opcode::Opcode(uint32_t opcode)
    : _opcode(opcode)
{
}

uint32_t Opcode::raw()
{
    return _opcode;
}

uint8_t Opcode::instruction()
{
    return _opcode >> 26;
}

uint8_t Opcode::rt()
{
    return (_opcode >> 16) & 0x1F;
}

uint8_t Opcode::rs()
{
    return (_opcode >> 21) & 0x1F;
}

uint16_t Opcode::immediate()
{
    return _opcode & 0xFFFF;
}

// Set high 16 bits of rt to imm
void OpcodeImplementation::lui(Opcode opcode, CpuState *cpuState)
{
    auto rt = opcode.rt();
    auto imm = opcode.immediate();

    uint32_t value = imm << 16;
    cpuState->setRegister(rt, value);

    spdlog::trace("[opcode] lui ${}, {:#x}", rt, imm);
}

void OpcodeImplementation::ori(Opcode opcode, CpuState *cpuState)
{
    auto rt = opcode.rt();
    auto rs = opcode.rs();
    auto imm = opcode.immediate();

    uint32_t value = rs | imm;
    cpuState->setRegister(rt, value);

    spdlog::trace("[opcode] ori ${}, ${}, {:#x}", rt, rs, imm);
}

void OpcodeImplementation::sw(Opcode opcode, CpuState *cpuState, Memory *memory)
{
    auto rt = opcode.rt();
    auto rs = opcode.rs();
    auto imm = opcode.immediate();

    uint32_t address = cpuState->getRegister(rs) + imm;
    uint32_t value = cpuState->getRegister(rt);
    memory->u32Write(address, value);

    spdlog::trace("[opcode] sw ${}, {:#x}(${})", rt, imm, rs);
}
