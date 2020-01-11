#pragma once

#include <string>

#include "memory.hpp"
#include "cpu.hpp"

class GBA
{
private:
    Memory _memory;
    CPU _cpu;

public:
    GBA() = default;

    void initializeGba();
    void intializeBios(const std::string &path);
    void run();
};