#include <vector>
#include <string>
#include <limits>
#include <cstdint>
#include <stack>

#include <gtest/gtest.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {

    }
};

TEST(Leetcode20, DefaultCases) {
    auto solution = Solution();
}