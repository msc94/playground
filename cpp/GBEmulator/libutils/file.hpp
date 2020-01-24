#pragma once

#include <vector>
#include <string>
#include <cstdint>

class File
{
private:
    std::string _path;
public:
    File(std::string path);
    
    std::vector<uint8_t> readAll();
};