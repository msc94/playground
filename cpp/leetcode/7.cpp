#include <vector>
#include <string>
#include <limits>
#include <cstdint>

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    int32_t reverse(int32_t x) {
        if (x == 0 || x == INT_MIN) {
            return 0;
        }

        bool isNeg = false;
        if (x < 0) {
            isNeg = true;
            x = -x;
        }

        int32_t r = 0;
        while (x > 0) {
            int32_t d = x % 10;
            if (r > (std::numeric_limits<int32_t>::max() - d) / 10) {
                return 0;
            }
            r = r * 10 + d;
            x /= 10;
        }

        return isNeg ? -r : r;
    }
};

TEST(Leetcode7, DefaultCases) {
    auto solution = Solution();
    ASSERT_EQ(solution.reverse(123), 321);
    ASSERT_EQ(solution.reverse(-123), -321);
    ASSERT_EQ(solution.reverse(120), 21);
    ASSERT_EQ(solution.reverse(1534236469), 0);
    ASSERT_EQ(solution.reverse(-2147483648), 0);
}