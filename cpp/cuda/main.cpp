#include <fmt/format.h>
#include <chrono>
#include <random>
#include <functional>
#include <future>

#include "types.hpp"
#include "add_cpu.hpp"

namespace chrono = std::chrono;

class TimedBlock {
private:
    chrono::time_point<chrono::steady_clock> _start;
public:
    TimedBlock() {
        _start = chrono::high_resolution_clock::now();
    }

    int64_t getElapsedTimeMs() {
        auto now = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - _start).count();
    }
};

int intRand() {
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(0, 100);
    return distribution(generator);
}

std::vector<int_t> randomVector(size_t len) {
    auto result = std::vector<int_t>();
    result.reserve(len);

    for (size_t i = 0; i < len; i++) {
        result.push_back(intRand());
    }

    return result;
}

int main(int argc, char **argv) {
    fmt::print("Hello CUDA!\n");

    size_t len = 100'000'000;
    auto af = std::async(std::launch::async, [&]() { return randomVector(len); });
    auto bf = std::async(std::launch::async, [&]() { return randomVector(len); });

    auto a = af.get();
    auto b = bf.get();

    fmt::print("Init done\n");

    {
        auto c = std::vector<int_t>(len);
        auto tb = TimedBlock();
        cpu::add_int(a.data(), b.data(), c.data(), len);

        auto number = c[std::atoi(argv[1])];
        fmt::print("CPU took {} ms, kth element: {}\n", tb.getElapsedTimeMs(), number);
    }

    {
        auto c = std::vector<int_t>(len);
        auto tb = TimedBlock();
        cpu::add_int_mt(a.data(), b.data(), c.data(), len);

        auto number = c[std::atoi(argv[1])];
        fmt::print("CPU SIMD took {} ms, kth element: {}\n", tb.getElapsedTimeMs(), number);
    }

}