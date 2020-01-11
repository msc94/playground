#include <filesystem>
#include <iostream>
#include <spdlog/spdlog.h>

#include "libttf/ttf_file.hpp"

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    spdlog::set_level(spdlog::level::debug);

    auto workingDirectory = fs::current_path();
    spdlog::info("Working directory is {}", workingDirectory.string());

    auto ttfFilePath = workingDirectory / ".." / "files" / "OpenSans-Regular.ttf";
    ttfFilePath = fs::canonical(ttfFilePath);

    auto ttfFile = TTFFile::loadFile(ttfFilePath);
    ttfFile.initializeTables();
}