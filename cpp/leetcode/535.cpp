#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

class Solution {
    std::vector<char> possible;
    std::random_device device = std::random_device();
    std::mt19937 gen = std::mt19937(device());
    std::unordered_map<string, string> map;

    string randomString(int size) {
        std::string str = "";
        std::sample(possible.begin(), possible.end(),
            std::back_inserter(str), size, gen);
        return str;
    }

public:
    Solution() {
        for (char i = 'A'; i != 'Z'; i++) {
            possible.push_back(i);
        }

        for (char i = 'a'; i != 'z'; i++) {
            possible.push_back(i);
        }
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string rand = "";
        do {
            rand = randomString(10);
        } while (map.find(rand) != map.end());

        string shortUrl = "http://tinyurl.com/" + rand;
        map[shortUrl] = longUrl;
        return shortUrl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        auto result = map.find(shortUrl);
        if (result == map.end()) {
            return "";
        }

        return map[shortUrl];
    }
};

TEST(DISABLED_Leetcode535, DefaultCases) {
    auto solution = Solution();

    auto str = "https://leetcode.com/problems/design-tinyurl";
    ASSERT_EQ(
        solution.decode(solution.encode(str)),
        str
    );
}