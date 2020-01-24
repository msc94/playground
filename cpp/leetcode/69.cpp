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
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }

        for (int64_t k = 1;; k++) {
            if (k * k > x) {
                return k - 1;
            }
        }
    }
};

TEST(Leetcode69, DefaultCases) {
    auto solution = Solution();
    ASSERT_EQ(solution.mySqrt(1), 1);
    ASSERT_EQ(solution.mySqrt(4), 2);
    ASSERT_EQ(solution.mySqrt(8), 2);
    ASSERT_EQ(solution.mySqrt(9), 3);
    ASSERT_EQ(solution.mySqrt(12), 3);
    ASSERT_EQ(solution.mySqrt(16), 4);
}