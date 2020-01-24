#pragma once

#include <vector>
#include <cstdint>

#include "libutils/data.hpp"

// Allocate only Size for the BIOS as a first step
constexpr size_t MEMORY_SIZE = 0x00003FFF + 1;

class Memory
{
private:
    ByteBuffer _memory = std::vector<uint8_t>(MEMORY_SIZE);

public:
    Memory() = default;

    void setBios(const ByteBuffer &data);

    // Memory access
    uint8_t uint8(uint16_t address);
};