#include "opcode.hpp"

Opcode::Opcode(uint32_t opcode)
    : _opcode(opcode) {
}

uint32_t Opcode::raw() {
    return _opcode;
}

uint8_t Opcode::instruction() {
    return _opcode >> 26;
}

uint8_t Opcode::rt() {
    return (_opcode >> 16) & 0x1F;
}

uint8_t Opcode::rs() {
    return (_opcode >> 21) & 0x1F;
}

uint8_t Opcode::rd() {
    return (_opcode >> 11) & 0x1F;
}

uint16_t Opcode::imm16() {
    return _opcode & 0xFFFF;
}

uint8_t Opcode::imm5() {
    return (_opcode >> 6) & 0x1F;
}

uint32_t Opcode::imm26() {
    return _opcode & 0x03FFFFFF;
}

uint8_t Opcode::subfunction() {
    return _opcode & 0x3F;
}

// Set high 16 bits of rt to imm
void OpcodeImplementation::lui(Opcode opcode, CpuState *cpuState) {
    auto rt = opcode.rt();
    auto imm = opcode.imm16();

    spdlog::trace("[opcode] lui ${}, {:#06x}", rt, imm);

    uint32_t value = imm << 16;
    cpuState->setRegister(rt, value);
}

void OpcodeImplementation::ori(Opcode opcode, CpuState *cpuState) {
    auto rt = opcode.rt();
    auto rs = opcode.rs();
    auto imm = opcode.imm16();

    spdlog::trace("[opcode] ori ${}, ${}, {:#06x}", rt, rs, imm);

    uint32_t value = cpuState->getRegister(rs) | imm;
    cpuState->setRegister(rt, value);
}

void OpcodeImplementation::sw(Opcode opcode, CpuState *cpuState, Memory *memory) {
    auto rt = opcode.rt();
    auto rs = opcode.rs();
    auto imm = opcode.imm16();

    spdlog::trace("[opcode] sw ${}, {:#06x}(${})", rt, imm, rs);

    uint32_t address = cpuState->getRegister(rs) + imm;
    uint32_t value = cpuState->getRegister(rt);
    memory->u32Write(address, value);
}

void OpcodeImplementation::sll(Opcode opcode, CpuState *cpuState) {
    auto rt = opcode.rt();
    auto rd = opcode.rd();
    auto imm = opcode.imm5();

    spdlog::trace("[opcode] sll ${}, ${}, {:#06x}", rd, rt, imm);

    uint32_t value = cpuState->getRegister(rt) << imm;
    cpuState->setRegister(rd, value);
}

void OpcodeImplementation::addiu(Opcode opcode, CpuState *cpuState) {
    auto rt = opcode.rt();
    auto rs = opcode.rs();
    auto imm = opcode.imm16();

    spdlog::trace("[opcode] addiu ${}, ${}, {:#06x}", rt, rs, imm);

    uint32_t value = rs + imm;
    cpuState->setRegister(rt, value);
}

void OpcodeImplementation::j(Opcode opcode, CpuState *cpuState) {
    auto imm = opcode.imm26();

    uint32_t address = (cpuState->getProgramCounter() & 0xF0000000) + (imm << 2);
    spdlog::trace("[opcode] j {:#010x}", address);
    cpuState->setProgramCounter(address);
}
