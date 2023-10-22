
#include <cstddef>
#include <cstdint>
#include <iostream>

#include <string>
#include <unistd.h>

constexpr std::size_t iterations = 500'000'000;

constexpr std::size_t buffer_size = 1024 * 1024;

void write(const std::string &str, std::string &buffer) {
  if (buffer.size() + str.size() > buffer_size) {
    if (write(STDOUT_FILENO, buffer.data(), buffer.size()) != buffer.size()) {
      exit(1);
    }
    buffer.clear();
    if (buffer.capacity() != buffer_size) {
      exit(1);
    }
  }

  buffer.insert(buffer.end(), str.begin(), str.end());
  buffer.insert(buffer.end(), '\n');
}

int main() {
  std::string buffer;
  buffer.reserve(buffer_size);

  for (std::size_t i = 1; i <= iterations; i++) {
    if (i % 5 == 0 && i % 3 == 0) {
      write("FizzBuzz", buffer);
    } else if (i % 5 == 0) {
      write("Buff", buffer);
    } else if (i % 3 == 0) {
      write("Fizz", buffer);
    } else {
      write(std::to_string(i), buffer);
    }
  }
}
