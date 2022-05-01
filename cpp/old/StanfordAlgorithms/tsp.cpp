#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <limits>
#include <exception>

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

struct City {
    double x = 0.0;
    double y = 0.0;
};

int main() {
    // Read file.
    auto filename = "data/tsp.txt";
    std::cout << "Reading " << filename << "\n";

    auto num_cities = 0;
    auto fstream = std::fstream(filename, std::ios_base::in);
    if (!fstream.is_open()) {
        std::cerr << "File could not be opened.\n";
        return -1;
    }

    auto cities = std::unordered_map<int, City> {};

    // subproblems[S, k]
    // Shortest path from 1 to k visiting all edges
    fstream >> num_cities;
    for (int i = 0; i < num_cities; i++) {
        City c;
        fstream >> c.x >> c.y;
        cities[i] = c;
    }
    fstream.close();

    auto distances = std::unordered_map<std::tuple<int, int>, double> {};
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            auto index = std::make_tuple(i, j);
            distances[index] = std::sqrt(
                std::pow(cities[i].x - cities[j].x, 2) +
                std::pow(cities[i].y - cities[j].y, 2)
            );
        }
    }

    std::cout << "Read " << num_cities << " cities.\n";

    auto to_uint32 = [](const std::vector<bool> &bitset) -> uint32_t {
        return std::accumulate<decltype(bitset.rbegin()), uint32_t>(
            bitset.rbegin(), bitset.rend(), 0, [](uint32_t x, uint32_t y) {
            return (x << 1) | y;
        });
    };

    auto to_bitstring = [](const uint32_t integer) {
        return std::bitset<25>(integer).to_string();
    };

    auto subproblems = std::unordered_map<std::tuple<uint32_t, int>, double> {};
    auto get_subproblem = [&](const std::tuple<uint32_t, int> &index) -> double {
        auto iterator = subproblems.find(index);
        if (iterator != subproblems.end()) {
            return iterator->second;
        }

        if (std::get<1>(index) != 0) {
            // Not trying to visit node 0?
            // Then all values should be initialized already
            throw std::runtime_error("error");
        }

        if (std::get<0>(index) == 1) {
            // From 1 to 1 is only possible if visiting only 1
            // Then the distance would be 0
            return 0;
        }

        // There is no path from 1 to 1 while visiting other nodes.
        // Since then we would visited 1 twice!
        return std::numeric_limits<double>::max();
    };

    // Loop through subset sizes
    for (int subset_size = 2; subset_size <= num_cities; ++subset_size) {
        std::cout << "subset_size = " << subset_size << "\n";

        auto bitset = std::vector<bool>(num_cities);
        for (int i = 0; i < subset_size; i++) {
            bitset[i] = 1;
        }

        do {
            // std::cout << to_bitstring(to_uint32(bitset)) << "\n";
            auto bitset_int = to_uint32(bitset);
            for (int j = 1; j < num_cities; j++) {
                if (!bitset[j]) {
                    continue;
                }

                auto min = std::numeric_limits<double>::max();
                for (int k = 0; k < num_cities; k++) {
                    if (!bitset[k] || k == j) {
                        continue;
                    }

                    auto subset_without_j = bitset_int & ~(1 << j);
                    auto distance_with_hop_kj =
                        get_subproblem(std::make_tuple(subset_without_j, k))
                        + distances[std::make_tuple(k, j)];

                    min = std::min(min, distance_with_hop_kj);
                }

                subproblems[std::make_tuple(bitset_int, j)] = min;
            }
        } while (std::prev_permutation(bitset.begin() + 1, bitset.end()));
    }

    // Find min element
    auto min = std::numeric_limits<double>::max();
    uint32_t full_subset = 0;
    for (int i = 0; i < num_cities; i++) {
        full_subset = (full_subset << 1) | 1;
    }

    for (int j = 1; j < num_cities; j++) {
        auto distance = get_subproblem(std::make_tuple(full_subset, j)) + distances[std::make_tuple(j, 0)];
        min = std::min(min, distance);
    }

    std::cout << min << std::endl;
    std::cin.get();
}