#include "file.hpp"

#include <fstream>
#include <fmt/format.h>

File::File(std::string path)
    : _path(path) {}

std::vector<uint8_t> File::readAll()
{
    auto istream = std::ifstream(_path.c_str(), std::ios::binary | std::ios::ate);
    auto size = istream.tellg();
    istream.seekg(0, std::ios::beg);

    auto buffer = std::vector<uint8_t>(size);
    if (istream.read((char *) buffer.data(), size)) {
        return buffer;
    }
    else {
        throw std::runtime_error(
            fmt::format("File {} does not exist", _path)
        );
    }
}