#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
    auto filename = "data/tsp_nn.txt";
    std::cout << "Reading " << filename << "\n";

    auto num_cities = 0;
    auto fstream = std::fstream(filename, std::ios_base::in);
    if (!fstream.is_open()) {
        std::cerr << "File could not be opened.\n";
        return -1;
    }

    auto cities = std::vector<City> {};

    // subproblems[S, k]
    // Shortest path from 1 to k visiting all edges
    fstream >> num_cities;
    for (int i = 0; i < num_cities; i++) {
        int index = 0;
        City c;
        fstream >> index >> c.x >> c.y;
        cities.push_back(c);
    }
    fstream.close();

    std::cout << "Read " << num_cities << " cities.\n";

    auto get_distance_squared = [&](int first_city, int second_city) -> double {
        return std::pow(cities[first_city].x - cities[second_city].x, 2) +
            std::pow(cities[first_city].y - cities[second_city].y, 2);
    };

    auto get_distance = [&](int first_city, int second_city) -> double {
        return std::sqrt(
            get_distance_squared(first_city, second_city)
        );
    };

    auto cities_added = std::unordered_set<int> {};
    cities_added.insert(0);

    double total_distance = 0.0;
    int last_added = 0;

    std::cout << std::fixed;

    while (cities_added.size() != num_cities) {
        // Search the nearest city
        double min_distance = std::numeric_limits<double>::max();
        int min_index = -1;

        for (int i = 0; i < num_cities; i++) {
            if (cities_added.contains(i)) {
                continue;
            }
            double distance = get_distance_squared(last_added, i);
            if (distance < min_distance) {
                min_distance = distance;
                min_index = i;
            }
        }

        total_distance += get_distance(last_added, min_index);
        cities_added.insert(min_index);
        last_added = min_index;

        std::cout << cities_added.size() << " / " << num_cities << " " << total_distance << "\n";
    }

    total_distance += get_distance(last_added, 0);

    std::cout << total_distance << std::endl;
    std::cin.get();
}