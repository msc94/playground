#include <vector>
#include <string>

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    const bool useStrings = true;

    bool stringImplementation(int x) {
        auto front = std::to_string(x);
        auto back = front;
        std::reverse(back.begin(), back.end());
        return front == back;
    }

    bool nonStringImplementation(int x) {
        if (x < 0) {
            return false;
        }

        // Split into digits
        auto digits = std::vector<int>();
        while (x > 0) {
            digits.push_back(x % 10);
            x /= 10;
        }

        int i = 0;
        int j = digits.size() - 1;

        while (i < j) {
            if (digits[i] != digits[j]) {
                return false;
            }
            i++;
            j--;
        }

        return true;
    }

    bool isPalindrome(int x) {
        if (useStrings) {
            return stringImplementation(x);
        }
        else {
            return nonStringImplementation(x);
        }
    }
};

TEST(DISABLED_Leetcode9, DefaultCases) {
    auto solution = Solution();
    ASSERT_TRUE(solution.isPalindrome(121));
    ASSERT_FALSE(solution.isPalindrome(-121));
    ASSERT_FALSE(solution.isPalindrome(10));
}