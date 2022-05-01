#include <vector>
#include <string>
#include <limits>
#include <cstdint>
#include <stack>

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    char matching(char character) {
        switch (character) {
        case '(':
            return ')';
        case '{':
            return '}';
        case '[':
            return ']';
        case ')':
            return '(';
        case '}':
            return '{';
        case ']':
            return '[';
        default:
            assert(false);
            return '?';
        }
    }

    bool opening(char character) {
        return character == '(' || character == '{' || character == '[';
    }

    bool isValid(std::string s) {
        std::stack<char> characterStack;

        for (char c : s) {
            if (opening(c)) {
                characterStack.push(c);
            }
            else {
                if (!characterStack.size()) {
                    return false;
                }

                char top = characterStack.top();
                char topMatching = matching(c);

                if (top != topMatching) {
                    return false;
                }

                characterStack.pop();
            }
        }

        return characterStack.empty();
    }
};

TEST(Leetcode20, DefaultCases) {
    auto solution = Solution();
    ASSERT_EQ(solution.isValid("()"), true);
    ASSERT_EQ(solution.isValid("]"), false);
}