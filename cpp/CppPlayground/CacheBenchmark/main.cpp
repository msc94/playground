#include <chrono>
#include <random>
#include <vector>
#include <list>
#include <iostream>

namespace chrono = std::chrono;

class TimedBlock {
private:
	chrono::time_point<chrono::steady_clock> _start;
public:
	TimedBlock() {
		_start = chrono::high_resolution_clock::now();
	}

	int64_t get_elapsed_time_ms() {
		auto now = chrono::high_resolution_clock::now();
		return chrono::duration_cast<chrono::milliseconds>(now - _start).count();
	}
};

static unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned long xorshf96(void) {          //period 2^96-1
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}

class RandomBool {
private:
	std::mt19937 _gen;
	std::uniform_int_distribution<> _dist;
public:
	RandomBool() {
		_gen = std::mt19937();
		_dist = std::uniform_int_distribution<>(0, 1);
	}

	bool get_random_bool() {
		return xorshf96() % 1 == 0;
	}
};

class TestClass {
private:
	bool _valid;
public:
	TestClass(RandomBool randomBool) {
		_valid = randomBool.get_random_bool();
	}

	bool is_valid() {
		return _valid;
	}
};

bool dont_optimize = true;

template<
	template<class...> class T
>
void test() {
	const int count = 100'000'000;
	T<TestClass> container;
	RandomBool random_bool;

	{
		TimedBlock timed_block;
		for (int i = 0; i < count; i++) {
			container.emplace_back(random_bool);
		}
		std::cout << "Adding took " << timed_block.get_elapsed_time_ms() << "ms\n";
	}

	{
		TimedBlock timed_block;
		for (auto rb : container) {
			if (rb.is_valid() && dont_optimize) {
				std::cout << "Hello!";
			}
		}
		std::cout << "Iterating took " << timed_block.get_elapsed_time_ms() << "ms\n";
	}
}

int main(int argc, char** argv) {
	if (argc == 1) {
		dont_optimize = false;
	}

	test<std::list>();
	test<std::vector>();

	std::cin.get();
}