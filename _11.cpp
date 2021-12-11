#include <iostream>
#include <string_view>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <list>

#include <regex>


using namespace std::string_view_literals;

static std::vector<std::string> input_real = {
        "3322874652",
        "5636588857",
        "7755117548",
        "5854121833",
        "2856682477",
        "3124873812",
        "1541372254",
        "8634383236",
        "2424323348",
        "2265635842"
};

static std::vector<std::string> input_test = {
        "5483143223",
        "2745854711",
        "5264556173",
        "6141336146",
        "6357385478",
        "4167524645",
        "2176841721",
        "6882881134",
        "4846848554",
        "5283751526"
};

static auto &input = input_real;
//static auto& input = input_test;

constexpr int DIMENSION = 10;


int64_t get_int2(int x, int y) {
    return input[y][x] - '0';
}

static std::vector<std::vector<int64_t>> matrix;

size_t nr_of_flashes = 0;

void inc_neighbors(int x, int y) {
    matrix[y][x]++;

    auto start_x = std::max(0, x - 1);
    auto start_y = std::max(0, y - 1);
    auto stop_x = std::min(DIMENSION - 1, x + 1);
    auto stop_y = std::min(DIMENSION - 1, y + 1);
    for (int j = start_y; j <= stop_y; j++) {
        for (int i = start_x; i <= stop_x; i++) {
            if (matrix[j][i] != INT32_MAX) {
                matrix[j][i]++;
            }
            if (matrix[j][i] > 9 && matrix[j][i] < INT32_MAX) {
                matrix[j][i] = INT32_MAX;
                nr_of_flashes++;
                inc_neighbors(i, j);
            }
        }
    }
}

void generation() {
    for (int y = 0; y < DIMENSION; y++) {
        for (int x = 0; x < DIMENSION; x++) {
            matrix[y][x]++;
        }
    }
    for (int y = 0; y < DIMENSION; y++) {
        for (int x = 0; x < DIMENSION; x++) {
            if (matrix[y][x] > 9 && matrix[y][x] < INT32_MAX) {
                nr_of_flashes++;
                matrix[y][x] = INT32_MAX;
            }
        }
    }

    for (int y = 0; y < DIMENSION; y++) {
        for (int x = 0; x < DIMENSION; x++) {
            if (matrix[y][x] == INT32_MAX) {
                inc_neighbors(x, y);
            }
        }
    }

    for (int y = 0; y < DIMENSION; y++) {
        for (int x = 0; x < DIMENSION; x++) {
            if (matrix[y][x] >= INT32_MAX) {
                matrix[y][x] = 0;
            }
        }
    }
}

void print() {
    for (int y = 0; y < DIMENSION; y++) {
        for (int x = 0; x < DIMENSION; x++) {
            std::cout << matrix[y][x];
        }
        std::cout << std::endl;

    }
}

int _11() {

    for (int y = 0; y < input.size(); y++) {
        auto &line = input[y];
        matrix.push_back({});
        for (int x = 0; x < line.size(); x++) {
            matrix[y].push_back(get_int2(x, y));
        }
    }


    for (int i = 0; i < 1000; i++) {
        generation();
        std::cout << i + 1 << std::endl;
        print();
        bool all_flashed = true;
        for (auto &line: matrix) {
            all_flashed &= std::all_of(line.begin(), line.end(), [](auto val) { return val == 0; });
        }
        if (all_flashed) {
            std::cout << "all flashed at " << i + 1 << std::endl;
            break;
        }
    }

    std::cout << "nr_of_flashes " << nr_of_flashes << std::endl;

    return 0;
}
