#include <vector>
#include <string>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    bool isBetween(int x, int a, int b) {
        return x > a && 
               x < b;
    }

    int thirdMax(const vector<int> &nums) {
        std::set<int> unique(nums.begin(), nums.end());

        if (unique.size() < 3) {
            return *std::max_element(unique.begin(), unique.end());
        }

        int first = INT_MIN;
        int second = INT_MIN;
        int third = INT_MIN;

        auto it = unique.begin();
        first = *it;

        while (it != unique.end()) {
            if (isBetween(*it, INT_MIN, third)) {
                // Ignore
            }
            if (isBetween(*it, third, second)) {
                // New third
                third = *it;
            }
            if (isBetween(*it, second, first)) {
                // New second
                third = second;
                second = *it;
            }
            if (isBetween(*it, first, INT_MAX)) {
                third = second;
                second = first;
                first= *it;
            }

            it++;
        }

        return third;
    }
};

TEST(Leetcode414, DefaultCases) {
    auto solution = Solution();

    ASSERT_EQ(solution.thirdMax({3, 2, 1}), 1);
    ASSERT_EQ(solution.thirdMax({1, 2}), 2);
    ASSERT_EQ(solution.thirdMax({2, 2, 3, 1}), 1);
    ASSERT_EQ(solution.thirdMax({-5, -5, -4, -3, -2, 1}), -3);
    ASSERT_EQ(solution.thirdMax({INT_MAX, INT_MIN}), INT_MAX);
    ASSERT_EQ(solution.thirdMax({INT_MAX, 0, INT_MIN}), INT_MIN);
}