#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>

struct Node {
    int weight = 0;
};

int main() {
    auto nodes = std::vector<Node> {};
    int numNodes = 0;

    auto stream = std::fstream("data/mwis.txt", std::ios_base::in);
    stream >> numNodes;

    for (int i = 0; i < numNodes; i++) {
        auto n = Node {};
        stream >> n.weight;
        nodes.push_back(n);
    }

    auto problems = std::unordered_map<int, int> {};

    problems[-2] = 0;
    problems[-1] = 0;
    problems[0] = nodes[0].weight;

    for (int i = 1; i < numNodes; i++) {
        problems[i] = std::max(
            problems[i - 1],
            problems[i - 2] + nodes[i].weight
        );
    }

    auto MWISIndices = std::unordered_set<int> {};
    for (int i = numNodes - 1; i >= 0;) {
        if (problems[i - 1] > problems[i - 2] + nodes[i].weight) {
            i--;
        }
        else {
            MWISIndices.insert(i);
            i -= 2;
        }
    }

    for (auto i : std::vector<int> {0, 1, 2, 3, 16, 116, 516, 996}) {
        auto contained = MWISIndices.contains(i);
        std::cout << contained ? "1" : "0";
    }
    // 10100110
    int breakhere = 3;
}