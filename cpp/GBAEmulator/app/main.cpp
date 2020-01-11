#include <iostream>
#include <spdlog/spdlog.h>

#include "libgba/gba.hpp"

int main(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::debug);

    auto gba = GBA();
    gba.initializeGba();
    gba.intializeBios("/home/marcel/Programming/playground/cpp/GBAEmulator/files/gba_bios.bin");
    gba.run();
}