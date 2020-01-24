#include "playstation.hpp"

// #include <spdlog/spdlog.h>

#include "libutils/file.hpp"

void Playstation::initialize()
{
    _cpu.setMemory(&_memory);
    _cpu.initializeState();
}

void Playstation::intializeBios(const std::string &path)
{
    auto biosFile = File(path);
    auto biosData = biosFile.readAll();

    printf("Loaded bios file has %d bytes", biosData.size());

    _memory.setBios(biosData);
}

void Playstation::run()
{
    while (true) {
        _cpu.step();
    }
}
