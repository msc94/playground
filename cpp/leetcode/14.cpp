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
    string longestCommonPrefix(const vector<string> &strs) {
        if (strs.size() == 0) {
            return "";
        }

        if (strs.size() == 1) {
            return strs[0];
        }

        std::vector<int> lengths;
        std::for_each(strs.begin(), strs.end(), [&](const string &s) {
            lengths.push_back(s.length());
        });
        int minLength = *std::min_element(lengths.begin(), lengths.end());

        bool loop = true;
        int i = 0;
        for (; i < minLength; i++) {
            char first = strs[0][i];
            if (std::any_of(strs.begin() + 1, strs.end(), [&](const string &s)
            {
                return s[i] != first;
            })) {
                break;
            }
        }

        return strs[0].substr(0, i);
    }
};

TEST(Leetcode14, DefaultCases) {
    auto solution = Solution();
    ASSERT_EQ(solution.longestCommonPrefix({"flower","flow","flight"}), "fl");
    ASSERT_EQ(solution.longestCommonPrefix({"dog","racecar","car"}), "");
    ASSERT_EQ(solution.longestCommonPrefix({}), "");
    ASSERT_EQ(solution.longestCommonPrefix({"a"}), "a");
    ASSERT_EQ(solution.longestCommonPrefix({"b", "b"}), "b");
}