#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <fstream>

template<typename T>
std::vector<std::vector<T>> array2d(int width, int height) {
    auto result = std::vector<std::vector<T>> {};
    for (int i = 0; i < height; i++) {
        auto row = std::vector<T> {};
        row.resize(width);
        result.push_back(row);
    }
    return result;
}

struct Item {
    int value;
    int weight;
};

int main() {
    auto stream = std::fstream("data/knapsack2.txt");
    if (!stream.is_open()) {
        return -1;
    }

    int64_t knapsack_size = 0;
    int64_t num_items = 0;

    std::vector<Item> items {};

    stream >> knapsack_size >> num_items;
    for (int i = 0; i < num_items; i++) {
        auto item = Item {};
        stream >> item.value;
        stream >> item.weight;
        items.push_back(item);
    }

    auto last = std::vector<int64_t>(knapsack_size + 1);
    for (int i = 0; i <= knapsack_size; i++) {
        last[i] = 0;
    }

    for (int i = 1; i <= num_items; i++) {
        auto current = std::vector<int64_t>(knapsack_size + 1);
        auto item = items[i - 1];
        for (int w = 0; w <= knapsack_size; w++) {
            int64_t do_not_take = last[w];
            int64_t do_take = 0;
            if (item.weight <= w) {
                do_take = last[w - item.weight] + item.value;
            }
            auto max = std::max(do_not_take, do_take);
            current[w] = max;
        }
        last = current;
    }

    // first result: 2493893
    auto result = last[knapsack_size];
    std::cout << result;
    int breakhere = 3;
}