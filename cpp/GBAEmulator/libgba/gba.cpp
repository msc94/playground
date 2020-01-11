#include "gba.hpp"

#include <spdlog/spdlog.h>

#include "libutils/file.hpp"

void GBA::initializeGba()
{
    _cpu.setMemory(&_memory);
}

void GBA::intializeBios(const std::string &path)
{
    auto biosFile = File(path);
    auto biosData = biosFile.readAll();

    spdlog::info("Loaded bios file has {} bytes", biosData.size());

    _memory.setBios(biosData);
}

void GBA::run()
{
    while (true) {
        _cpu.step();
    }
}
