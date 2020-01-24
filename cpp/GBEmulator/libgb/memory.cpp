#include "memory.hpp"

#include <cstring>
#include <stdexcept>
#include <spdlog/spdlog.h>

void Memory::setBios(const ByteBuffer &data) 
{
    spdlog::debug("Setting BIOS ({} bytes). Memory buffer size: {}.", data.size(), _memory.size());

    if (data.size() > _memory.size()) {
        throw std::runtime_error("Memory buffer is too small to copy BIOS into.");
    }
    
    std::memcpy(_memory.data(), data.data(), data.size());
}

uint8_t Memory::uint8(uint16_t address)
{
    return _memory[address];
}

