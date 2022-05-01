#include <fstream>
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <string>
#include <sstream>

class Node {
public:
    Node() = default;
    Node(int name)
        : name(name) {}

    int name = -1;
    std::unordered_map<int, double> adjancency_list = std::unordered_map<int, double>();
    
    Node *parent = nullptr;
};

std::unordered_map<Node*, double> djkstra(std::unordered_map<int, Node> &G, Node *start) {
    auto shortest = std::unordered_map<Node *, double>();

    // init
    shortest[start] = 0.0;

    while (shortest.size() < G.size()) {
        // find shortest path from visited to not visited
        auto current_shortest = std::numeric_limits<double>::max();
        Node *current_shortest_node = nullptr;
        Node *current_shortest_node_parent = nullptr;
        for (auto p1 : shortest) {
            for (auto p2 : p1.first->adjancency_list) {
                // ignore p2 if already visited
                auto *second_node = &G[p2.first];
                if (shortest.find(second_node) != shortest.end()) {
                    continue;
                }

                // Get shortest path from start to p1
                if (p1.second + p2.second < current_shortest) {
                    current_shortest = p1.second + p2.second;
                    current_shortest_node = second_node;
                    current_shortest_node_parent = p1.first;
                }
            }
        }

        // Insert found node in shortest and set path length
        current_shortest_node->parent = current_shortest_node_parent;
        shortest[current_shortest_node] = current_shortest;
    }

    return shortest;
}

std::vector<std::string> split(const std::string &s, char delim) {
    auto result = std::vector<std::string>();
    auto sstream = std::stringstream(s, std::ios_base::in);
    auto str = std::string();
    while (std::getline(sstream, str, delim)) {
        result.push_back(str);
    }
    return result;
}

void createNodeIfNotExists(std::unordered_map<int, Node> &G, int name) {
    if (G.find(name) == G.end()) {
        G[name] = Node(name);
    }
}

int main() {
    auto G = std::unordered_map<int, Node>();

    auto stream = std::fstream("data/dijkstraData.txt", std::ios_base::in);
    if (stream.is_open()) {
        std::string line;
        while (std::getline(stream, line)) {
            auto elements = split(line, '\t');
            auto currentElement = std::stoi(elements[0]);
            createNodeIfNotExists(G, currentElement);
            for (int i = 1; i < elements.size(); i++) {
                auto edgeElements = split(elements[i], ',');

                auto edgeDestination = std::stoi(edgeElements[0]);
                createNodeIfNotExists(G, edgeDestination);

                auto edgeLength = std::stoi(edgeElements[1]);
                G[currentElement].adjancency_list[edgeDestination] = edgeLength;
            }
        }
    }

    auto shortest = djkstra(G, &G[1]);

    std::cout << shortest[&G[7  ]] << "\n";
    std::cout << shortest[&G[37 ]] << "\n";
    std::cout << shortest[&G[59 ]] << "\n";
    std::cout << shortest[&G[82 ]] << "\n";
    std::cout << shortest[&G[99 ]] << "\n";
    std::cout << shortest[&G[115]] << "\n";
    std::cout << shortest[&G[133]] << "\n";
    std::cout << shortest[&G[165]] << "\n";
    std::cout << shortest[&G[188]] << "\n";
    std::cout << shortest[&G[197]] << "\n";
}