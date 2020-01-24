#pragma once

#include <functional>
#include <vector>

#include "cpustate.hpp"

std::vector<std::function<void(CpuState *)>> initializeOpcodeTable();