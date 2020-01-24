#include <vector>
#include <string>
#include <limits>
#include <cstdint>
#include <type_traits>
#include <deque>
#include <algorithm>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

class Solution {
    std::unordered_map<char, string> _number_to_chars = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };

public:
    vector<string> getCombinations(string start, string digits) {
        std::vector<string> result = {};
        
        if (digits.size() == 0) {
            return { start };
        }

        // Take first digit
        std::vector<string> starts;

        char first = digits[0];

        for (char c : _number_to_chars[first]) {
            string _start = start + c;
            auto new_strings = getCombinations(_start, digits.substr(1));
            result.insert(result.end(), new_strings.begin(), new_strings.end());
        }

        return result;
    }

    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) {
            return {};
        }

        auto result = getCombinations("", digits);
        return result;
    }
};

TEST(Leetcode17, DefaultCases) {
    auto solution = Solution();

    auto rightSolution = std::vector<string>({"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"});
    ASSERT_EQ(solution.letterCombinations("23"), rightSolution);
}