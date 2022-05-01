#include <iostream>
#include <fstream>
#include <queue>
#include <list>

struct Node {
    int64_t weight = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    bool isLeaf = false;
};

std::vector<int> calculateHeightsOfLeafs(Node *node, int height) {
    if (node->isLeaf) {
        return std::vector<int> { height };
    }
    else {
        auto left = calculateHeightsOfLeafs(node->left, height + 1);
        auto right = calculateHeightsOfLeafs(node->right, height + 1);

        auto result = std::vector<int> {};
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }
}

int main() {
    auto nodes = std::list<Node> {};

    auto compareNodes = [&](Node *a, Node *b) {
        return a->weight > b->weight;
    };
    auto queue = std::priority_queue<Node *, std::vector<Node *>, decltype(compareNodes)>(compareNodes);

    int numNdoes = 0;

    auto stream = std::fstream("data/huffman_test1.txt", std::ios_base::in);
    stream >> numNdoes;

    for (int i = 0; i < numNdoes; i++) {
        auto n = Node {};
        stream >> n.weight;
        n.isLeaf = true;
        nodes.push_back(n);
        queue.push(&nodes.back());
    }

    while (queue.size() > 1) {
        // Get two smallest elements
        auto *firstNode = queue.top(); queue.pop();
        auto *secondNode = queue.top(); queue.pop();

        auto newNode = Node {};

        newNode.left = firstNode;
        newNode.right = secondNode;
        newNode.weight = firstNode->weight + secondNode->weight;

        nodes.push_back(newNode);
        queue.push(&nodes.back());
    }

    auto heights = calculateHeightsOfLeafs(queue.top(), 0);
    auto minmax = std::minmax_element(heights.begin(), heights.end());
    // 9, 19
    // MWIS: 10100110
    int breakhere = 3;
}