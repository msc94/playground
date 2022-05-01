#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>

struct UnionFindNode {
    int id;
    int parent;
    int rank;
};

class UnionFind {
    // node -> parent map
    std::unordered_map<int, UnionFindNode> _nodes;
    int _num_clusters = 0;

    int _num_root_nodes() {
        int num = 0;
        for (auto node_iterator : _nodes) {
            auto node = node_iterator.second;
            if (node.id == node.parent) {
                num++;
            }
        }
        return num;
    }

public:
    int num_clusters() {
        return _num_clusters;
    }

    void create_note_if_not_exists(int id) {
        if (_nodes.find(id) == _nodes.end()) {
            auto new_node = UnionFindNode {};
            new_node.id = id;
            new_node.parent = id;
            new_node.rank = 0;
            _nodes[id] = new_node;
            _num_clusters++;
        }
    }

    int find(int id) {
        create_note_if_not_exists(id);

        auto visited = std::vector<UnionFindNode *> {};

        auto *current = &_nodes[id];
        auto *parent = &_nodes[current->parent];
        visited.push_back(current);

        while (current->id != parent->id) {
            current = parent;
            parent = &_nodes[current->parent];
            visited.push_back(current);
        }

        for (auto node : visited) {
            node->parent = parent->id;
        }

        return parent->id;
    }

    void merge(int a, int b) {
        create_note_if_not_exists(a);
        create_note_if_not_exists(b);

        auto *first = &_nodes[a];
        auto *second = &_nodes[b];

        auto *first_root = &_nodes[find(a)];
        auto *second_root = &_nodes[find(b)];

        if (first_root->id == second_root->id) {
            return;
        }

        if (first_root->rank > second_root->rank) {
            second_root->parent = first_root->id;
        }
        else if (first_root->rank < second_root->rank) {
            first_root->parent = second_root->id;
        }
        else if (first_root->rank == second_root->rank) {
            first_root->parent = second_root->id;
            second_root->rank++;
        }

        _num_clusters--;
        assert(_num_clusters == _num_root_nodes());
    }
};

struct Edge {
    int a;
    int b;
    int weight;
};

void test_uf() {
    auto uf = UnionFind {};
    uf.create_note_if_not_exists(1);
    uf.create_note_if_not_exists(2);
    uf.create_note_if_not_exists(3);

    int a = uf.find(1);
    uf.merge(2, 3);
    int b = uf.find(2);
    int c = uf.find(3);
}

int main() {
    // test_uf();
    // First answer: 106

    auto file = std::fstream("data/clustering1.txt", std::ios_base::in);
    if (!file.is_open()) {
        return -1;
    }

    auto uf = UnionFind {};

    auto edges = std::vector<Edge> {};
    int num_edges;
    file >> num_edges;

    int a, b, weight;
    while (file >> a >> b >> weight) {
        auto e = Edge {};
        e.a = a;
        e.b = b;
        e.weight = weight;
        edges.push_back(e);

        uf.create_note_if_not_exists(a);
        uf.create_note_if_not_exists(b);
    }

    std::sort(edges.begin(), edges.end(), [](auto &a, auto &b) {
        return a.weight < b.weight;
    });

    int current_edge = 0;
    while (uf.num_clusters() > 4) {
        auto edge = edges[current_edge++];
        uf.merge(edge.a, edge.b);
    }

    while (true) {
        auto edge = edges[current_edge++];
        if (uf.find(edge.a) != uf.find(edge.b)) {
            return edge.weight;
        }
    }

    int breakhere = 3;
}