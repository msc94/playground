#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

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

int main() {
    auto subproblems = array2d<float>(7, 7);
    auto probabilities = std::vector<float> {0.2f, 0.05f, 0.17f, 0.1f, 0.2f, 0.03f, 0.25f};

    for (int i = 0; i < 7; i++)
        subproblems[i][i] = probabilities[i];

    // s = subproblem size
    for (int s = 1; s < 7; s++) {
        // i = start node
        for (int i = 0; i <= 7 - s - 1; i++) {
            // j == end node
            int j = i + s;

            auto sum_of_probabilities = 0.0f;
            for (int r = i; r <= j; r++) {
                sum_of_probabilities += probabilities[r];
            }

            auto possible_roots = std::vector<float> {};
            // r = current node
            for (int r = i; r <= j; r++) {
                auto left = 0.0f;
                if (r - 1 >= i) {
                    left = subproblems[i][r - 1];
                }
                auto right = 0.0f;
                if (r + 1 <= j) {
                    right = subproblems[r + 1][j];
                }
                possible_roots.push_back(sum_of_probabilities + left + right);
            }

            auto minimal = *std::min_element(possible_roots.begin(), possible_roots.end());
            subproblems[i][j] = minimal;
        }
    }

    int breakhere = 3;
}