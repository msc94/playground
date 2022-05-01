#include <iostream>
#include <fstream>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <string>

// so that it is picked up by argument-dependent name lookup (ADL).
namespace std {
    namespace
    {

        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy
        //     and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine:
        //     https://stackoverflow.com/questions/4948780

        template <class T>
        inline void hash_combine(std::size_t &seed, T const &v) {
            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl {
            static void apply(size_t &seed, Tuple const &tuple) {
                HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
                hash_combine(seed, get<Index>(tuple));
            }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple, 0> {
            static void apply(size_t &seed, Tuple const &tuple) {
                hash_combine(seed, get<0>(tuple));
            }
        };
    }

    template <typename ... TT>
    struct hash<std::tuple<TT...>> {
        size_t
            operator()(std::tuple<TT...> const &tt) const {
            size_t seed = 0;
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
            return seed;
        }

    };
}

int shortest_path(std::string filename) {
    auto subproblems_last = std::unordered_map<std::tuple<int, int>, int64_t> {};
    auto subproblems = std::unordered_map<std::tuple<int, int>, int64_t> {};

    std::unordered_map<std::tuple<int, int>, int64_t> edges;

    // Read file.
    std::cout << "Reading " << filename << "\n";

    int num_vertices = 0;
    int num_edges = 0;
    auto fstream = std::fstream(filename, std::ios_base::in);
    if (!fstream.is_open()) {
        std::cerr << "File could not be opened.\n";
        return -1;
    }

    fstream >> num_vertices >> num_edges;
    for (int i = 0; i < num_edges; i++) {
        int tail, head, weight;
        fstream >> tail >> head >> weight;
        auto index_tuple = std::make_tuple(tail, head);
        edges[index_tuple] = weight;
    }

    std::cout << "Read " << num_edges << " edges.\n";

    // Initialize for k = -1
    for (int i = 1; i <= num_vertices; i++) {
        for (int j = 1; j <= num_vertices; j++) {
            auto subproblem_index = std::make_tuple(i, j);
            if (i == j) {
                subproblems[subproblem_index] = 0;
            }
            else {
                auto index_tuple = std::make_tuple(i, j);
                auto edge = edges.find(index_tuple);
                if (edge != edges.end()) {
                    subproblems[subproblem_index] = edge->second;
                }
                else {
                    subproblems[subproblem_index] = std::numeric_limits<int>::max();
                }
            }
        }
    }

    for (size_t k = 1; k <= num_vertices; k++) {
        std::cout << "k = " << k << "\n";
        subproblems_last = subproblems;
        subproblems = std::unordered_map<std::tuple<int, int>, int64_t> {};

        for (int i = 1; i <= num_vertices; i++) {
            for (int j = 1; j <= num_vertices; j++) {
                auto without = subproblems_last[std::make_tuple(i, j)];
                auto with = subproblems_last[std::make_tuple(i, k)] + subproblems_last[std::make_tuple(k, j)];
                subproblems[std::make_tuple(i, j)] = std::min(without, with);
            }
        }
    }

    auto paths = std::vector<int64_t> {};
    for (int i = 1; i <= num_vertices; i++) {
        for (int j = 1; j <= num_vertices; j++) {
            auto subproblem_index = std::make_tuple(i, j);
            auto length = subproblems[subproblem_index];

            if (i == j && length < 0) {
                std::cerr << "Negative cycle!\n";
                return -1;
            }

            paths.push_back(length);
        }
    }

    auto min = std::min_element(paths.begin(), paths.end());
    std::cout << *min << "\n";
    return *min;
}

int main(int argc, char **argv) {
    shortest_path(argv[1]);
    return 0;
}