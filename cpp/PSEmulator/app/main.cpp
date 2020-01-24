#include <iostream>
// #include <spdlog/spdlog.h>

#include "libps/playstation.hpp"

int main(int argc, char** argv)
{
    printf("Hello playstation!\n");

    // spdlog::set_level(spdlog::level::debug);

    auto ps = Playstation();
    ps.initialize();
    ps.intializeBios("/files/SCPH-1001.bin");
    // ps.run();
}