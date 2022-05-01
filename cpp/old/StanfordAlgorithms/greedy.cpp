#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ctime>

struct Job {
    int weight;
    int length;

    int difference() {
        return weight - length;
    }

    double ratio() {
        return static_cast<double>(weight) / length;
    }
};

void first() {
    auto stream = std::fstream("data/greedy_1.txt");
    if (!stream.is_open()) {
        return;
    }

    int num_jobs;
    stream >> num_jobs;

    auto jobs = std::vector<Job> {};
    auto j = Job {};
    while (stream >> j.weight >> j.length) {
        jobs.push_back(j);
    }

    assert(jobs.size() == num_jobs);

    std::sort(jobs.begin(), jobs.end(), [&](auto &a, auto &b) {
        //if (a.difference() == b.difference()) {
        //    return a.weight < b.weight;
        //}

        //return a.difference() < b.difference();
         return a.ratio() < b.ratio();
    });

    int64_t weighted_completition_times = 0;
    int64_t current_completition_time = 0;
    for (auto it = jobs.rbegin(); it != jobs.rend(); it++) {
        current_completition_time += it->length;
        weighted_completition_times += current_completition_time * it->weight;
    }

    std::cout << weighted_completition_times;
}

struct Edge {
    int from;
    int to;
    int cost;
};

void second() {
    auto stream = std::fstream("data/greedy_2.txt");
    if (!stream.is_open()) {
        return;
    }

    int num_nodes, num_edges;
    stream >> num_nodes >> num_edges;

    auto adjacency_list = std::unordered_map<int, std::vector<Edge>> {};
    int first, second, cost;
    while (stream >> first >> second >> cost) {
        auto e = Edge {};
        e.from = first;
        e.to = second;
        e.cost = cost;
        adjacency_list[first].push_back(e);
        e.from = second;
        e.to = first;
        e.cost = cost;
        adjacency_list[second].push_back(e);
    }

    auto nodes_visited = std::unordered_set<int> {};

    auto first_edge = adjacency_list.begin();
    nodes_visited.insert(first_edge->first);

    auto total_cost = 0;

    while (nodes_visited.size() < adjacency_list.size()) {

        // Search outgoing edge with minimal costs
        auto minimal_cost = std::numeric_limits<int>::max();
        Edge minimal_edge = Edge {};

        for (auto n : nodes_visited) {
            for (auto e : adjacency_list[n]) {
                if (!nodes_visited.contains(e.to) &&
                    e.cost < minimal_cost) {
                    minimal_cost = e.cost;
                    minimal_edge = e;
                }
            }
        }

        total_cost += minimal_edge.cost;
        nodes_visited.insert(minimal_edge.to);
    }

    std::cout << total_cost << "\n";
}

int main() {
    //first();
    // 1: 69119377652
    // 2: 67311454237
    second();
    // -3612829
}