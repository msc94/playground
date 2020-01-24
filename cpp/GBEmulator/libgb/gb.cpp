#include "gb.hpp"

#include <spdlog/spdlog.h>

#include "libutils/file.hpp"

void GB::initializeGb()
{
    _cpu.setMemory(&_memory);
    _cpu.initializeState();
}

void GB::intializeBios(const std::string &path)
{
    auto biosFile = File(path);
    auto biosData = biosFile.readAll();

    spdlog::info("Loaded bios file has {} bytes", biosData.size());

    _memory.setBios(biosData);
}

void GB::run()
{
    while (true) {
        _cpu.step();
    }
}
