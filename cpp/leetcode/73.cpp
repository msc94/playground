#include <vector>
#include <string>
#include <limits>
#include <cstdint>
#include <type_traits>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:

    void setZeroes(vector<vector<int>> &matrix) {
        int height = matrix.size();
        int width = matrix[0].size();

        bool clearFirstRow = std::any_of(matrix[0].begin(), matrix[0].end(),
            [](int x) { return x == 0; });

        bool clearFirstColumn = std::any_of(matrix.begin(), matrix.end(),
            [](std::vector<int> x) { return x[0] == 0; });

        for (int i = 1; i < height; i++) {
            for (int j = 1; j < width; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < height; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < width; j++) {
                    matrix[i][j] = 0;
                }
            }
        }

        for (int j = 1; j < width; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < height; i++) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (clearFirstColumn) {
            for (int i = 0; i < height; i++) {
                matrix[i][0] = 0;
            }
        }

        if (clearFirstRow) {
            for (int j = 0; j < width; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};

TEST(Leetcode73, DefaultCases) {
    auto solution = Solution();
    auto matrix = std::vector<std::vector<int>> {
        {1,1,1},
        {1,0,1},
        {1,1,1}
    };
    // solution.setZeroes(matrix);

    matrix = std::vector<std::vector<int>> {
        {0,1,2,0},
        {3,4,5,2},
        {1,3,1,5}
    };
    solution.setZeroes(matrix);
    int breakhere = 3;
}