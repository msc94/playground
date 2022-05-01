#include "add_cpu.hpp"
#include "types.hpp"

#include <algorithm>
#include <execution>
#include <stdexcept>

void cpu::add_int(int *a, int *b, int *c, size_t len) {
    for (size_t i = 0; i < len; i++) {
        c[i] = 0;
        for (size_t j = 0; j < 100; j++) {
            c[i] = c[i] + a[i] + b[i];
        }
    }
}

void cpu::add_int_mt(int *a, int *b, int *c, size_t len) {
    std::for_each(std::execution::par_unseq, c, c + len, [&](int &x) {
        auto i = static_cast<size_t>(&x - c);

        c[i] = 0;
        for (size_t j = 0; j < 100; j++) {
            c[i] = c[i] + a[i] + b[i];
        }
    });
}
