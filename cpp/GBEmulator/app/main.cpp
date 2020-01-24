#include <iostream>
#include <spdlog/spdlog.h>

#include "libgb/gb.hpp"

int main(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::debug);

    auto gb = GB();
    gb.initializeGb();
    gb.intializeBios("D:/Programmierung/playground/cpp/GBEmulator/files/dmg_boot.bin");
    gb.run();
}