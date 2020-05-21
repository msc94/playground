#include <chrono>
#include <random>
#include <vector>
#include <list>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS
#include "csv.h"

namespace chrono = std::chrono;

class TimedBlock {
private:
    chrono::time_point<chrono::steady_clock> _start;
public:
    TimedBlock() {
        _start = chrono::high_resolution_clock::now();
    }

    int64_t get_elapsed_time_ms() {
        auto now = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - _start).count();
    }
};

int main(int argc, char **argv) {
    {
        TimedBlock timed_block;

        std::vector<std::string> strings;
        auto reader = csv::CSVReader(R"(E:\Windows10_Arbeit\share\ms\projects\SLR_Analyse\in\Strukturbericht_PLM_R_LKS_20180313_ungefiltert.csv)");
        for (csv::CSVRow& row: reader) {
            for (csv::CSVField &field: row) {
                strings.push_back(field.get<>());
            }
        }

        std::cout << "Took " << timed_block.get_elapsed_time_ms() << "ms\n";
    }

    std::cin.get();
}