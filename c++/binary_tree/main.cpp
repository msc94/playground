#include <random>
#include <thread>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <execution>

#include "binary_tree.h"
#include "direct_iterator.h"

int main() {
	auto binary_tree = BinaryTree<int>();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0);

	for (size_t i = 0; i < 100'000; i++) {
		binary_tree.add(dis(gen));
	}

	binary_tree.add(1337);
	bool has1337 = binary_tree.has(1337);
	bool has1338 = binary_tree.has(1338);

	std::cout << "Binary tree has height " << binary_tree.height() << "\n";

	// std::vector<int> v(std::numeric_limits<int>::max());
	// std::iota(v.begin(), v.end(), 0);

	std::for_each(
		std::execution::par_unseq,
		ez::make_direct_iterator(0),
		ez::make_direct_iterator(std::numeric_limits<int>::max()),
		[&](auto&& i)
		{
			if (binary_tree.has(i)) {
				std::cout << "Binary tree has " << i << "\n";
			}
		});

	std::cin.get();
}