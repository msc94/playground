
#include <cstddef>
#include <cstdint>
#include <iostream>

constexpr std::size_t iterations = 500'000'000;

int main() {
  for (std::size_t i = 1; i <= iterations; i++) {
    if (i % 5 == 0 && i % 3 == 0) {
      std::cout << "FizzBuzz\n";
    } else if (i % 5 == 0) {
      std::cout << "Buff\n";
    } else if (i % 3 == 0) {
      std::cout << "Fizz\n";
    } else {
      std::cout << i << "\n";
    }
  }
}
