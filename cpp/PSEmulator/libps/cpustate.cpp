#include "cpustate.hpp"

#include <algorithm>
#include <spdlog/spdlog.h>

void CpuState::initialize() {
    _pc = 0xBFC00000;

    std::fill(std::begin(_registers) + 1, std::end(_registers), 0xDEADBEEF);
    _registers[0] = 0;
}

void CpuState::incrementProgramCounter() {
    _pc += sizeof(uint32_t);
}

void CpuState::setProgramCounter(uint32_t value) {
    _pc = value;
}

uint32_t CpuState::getProgramCounter() {
    return _pc;
}

void CpuState::setRegister(uint8_t index, uint32_t value) {
    if (index == 0) {
        spdlog::warn("[reg] ignore set $0");
        return;
    }

    spdlog::trace("[reg] write ${} = {:#010x}", index, value);
    _registers[index] = value;
}

uint32_t CpuState::getRegister(uint8_t index) {
    auto value = _registers[index];
    spdlog::trace("[reg] read ${} = {:#010x}", index, value);
    return value;
}
