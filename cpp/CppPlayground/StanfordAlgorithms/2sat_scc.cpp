#include <string>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <vector>
#include <functional>

bool solvable(const std::string &filename) {
    auto fstream = std::fstream(filename);
    if (!fstream.is_open()) {
        exit(-1);
    }

    int num_nodes = 0;
    fstream >> num_nodes;

    auto N = std::unordered_set<int> {};
    auto G = std::unordered_map<int, std::unordered_set<int>> {};
    auto G_t = std::unordered_map<int, std::unordered_set<int>> {};

    for (int i = 0; i < num_nodes; i++) {
        int first = 0, second = 0;
        fstream >> first >> second;

        N.insert(first);
        N.insert(-first);

        N.insert(second);
        N.insert(-second);

        G[-first].insert(second);
        G[-second].insert(first);

        G_t[second].insert(-first);
        G_t[first].insert(-second);
    }

    std::cout << filename << " read.\n";

    // calc scc

    // first iteration (forward)
    auto visited = std::unordered_set<int> {};
    auto L = std::deque<int> {};

    std::function<void(int)> visit = [&](int node) {
        if (visited.contains(node)) {
            return;
        }
        visited.insert(node);

        for (auto adjancent : G[node]) {
            visit(adjancent);
        }

        L.push_front(node);
    };

    for (auto node : N) {
        visit(node);
    }

    std::cout << filename << " scc first pass.\n";

    auto assigned = std::unordered_set<int> {};
    auto components = std::unordered_map<int, std::unordered_set<int>> {};
    std::function<void(int, int)> assign = [&](int node, int root) {
        if (assigned.contains(node)) {
            return;
        }

        assigned.insert(node);
        components[root].insert(node);

        for (auto adjancent : G_t[node]) {
            assign(adjancent, root);
        }
    };

    for (auto node : L) {
        assign(node, node);
    }

    std::cout << filename << " scc second pass.\n";

    // Search for unsolvable connected components
    for (auto scc : components) {
        auto scc_nodes = scc.second;
        for (auto node : scc_nodes) {
            if (scc_nodes.contains(-node)) {
                std::cout << filename << " is not solvable.\n";
                return;
            }
        }
    }

    std::cout << filename << " is solvable.\n";

}

int main() {
    process("data/2sat1.txt");
    process("data/2sat2.txt");
    process("data/2sat3.txt");
    process("data/2sat4.txt");
    process("data/2sat5.txt");
    process("data/2sat6.txt");
    return 0;
}