#pragma once

#include <string>

#include "memory.hpp"
#include "cpu.hpp"

class GB
{
private:
    Memory _memory;
    CPU _cpu;

public:
    GB() = default;

    void initializeGb();
    void intializeBios(const std::string &path);
    void run();
};