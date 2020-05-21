#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

class Heap {
public:
    bool min;
    std::vector<int> elements;

    Heap(bool min) 
        : min(min) {}

    void push(int i) {
        elements.push_back(i);
        std::make_heap(elements.begin(), elements.end(), [&](int a, int b) {
            return min ? a > b : a < b;
        });
    }

    int pop() {
        int i = peek();
        std::pop_heap(elements.begin(), elements.end(), [&](int a, int b) {
            return min ? a > b : a < b;
        });
        elements.pop_back();
        return i;
    }

    int peek() {
        return elements[0];
    }

    int size() {
        return elements.size();
    }
};

int main() {
    //auto stream = std::fstream("data/Median.txt");
    //if (!stream.is_open()) {
    //    return -1;
    //}

    //auto left = Heap(false);
    //auto right = Heap(true);

    //int i = 0;

    //int sum = 0;

    //stream >> i;
    //right.push(i);
    //sum += i;

    //while (stream >> i) {
    //    if (i < right.peek()) {
    //        left.push(i);
    //    }
    //    else {
    //        right.push(i);
    //    }

    //    if (right.size() > left.size()) {
    //        left.push(right.pop());
    //    }

    //    if (left.size() > right.size() + 1) {
    //        right.push(left.pop());
    //    }

    //    std::cout << "minHeap: " << left.size() << " maxHeap: " << right.size() << "\n"
    //        << "Median: " << left.peek() << "\n";

    //    sum += left.peek();
    //    sum %= 10000;
    //}

    //std::cout << "Sum: " << sum << "\n";

    auto string = std::string("Hello World");
    auto hash = std::hash<std::string>()(string);
    auto hash = std::hash<int>()(string);
}