#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

int main() {
    auto stream = std::fstream("data/2sum.txt", std::ios_base::in);
    if (!stream.is_open()) {
        return -1;
    }

    std::set<int64_t> numbers;
    int64_t number;
    while (stream >> number) {
        numbers.insert(number);
    }

    int64_t t_min = -10000;
    int64_t t_max = 10000;

    std::unordered_set<int64_t> found;

    for (auto i : numbers) {
        // Search for range of numbers
        int64_t range_min = t_min - i;
        int64_t range_max = t_max - i;

        // Get all numbers in that range from the set
        // This is 2*log(n) + O(t_max - t_min) iterating
        for (auto it = numbers.lower_bound(range_min);
            it != numbers.upper_bound(range_max);
            it++) {

            if (*it == i) {
                // Numbers not distinct
                continue;
            }

            int64_t result = *it + i;
            found.insert(result);
        }
    }

    std::cout << "Found: " << found.size() << "\n";
} 