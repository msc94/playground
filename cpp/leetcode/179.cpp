#include <vector>
#include <string>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int> &nums) {
        if (nums.size() == 0) {
            return "";
        }

        // Sort array by having the biggest leftmost digit
        // TODO: Is there a nicer way to do this?
        std::sort(nums.begin(), nums.end(), [](int a, int b) {
            return std::to_string(a) > std::to_string(b);
            });

        std::string result = "";
        for (int i : nums) {
            result += std::to_string(i);
        }

        return result;
    }
};

TEST(DISABLED_Leetcode179, DefaultCases) {
    auto solution = Solution();

    auto vec = vector<int> {10, 2};
    ASSERT_EQ(solution.largestNumber(vec), "210");

    vec = vector<int> {3,30,34,5,9};
    ASSERT_EQ(solution.largestNumber(vec), "9534330");

    vec = vector<int> {0, 0};
    ASSERT_EQ(solution.largestNumber(vec), "0");

    vec = vector<int> {};
    ASSERT_EQ(solution.largestNumber(vec), "");
}