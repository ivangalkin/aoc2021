#include <iostream>
#include <string_view>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>

#include <regex>


using namespace std::string_view_literals;

static std::vector<int64_t> input{
        3, 5, 4, 1, 2, 1, 5, 5, 1, 1, 1, 1, 4, 1, 4, 5, 4, 5, 1, 3, 1, 1, 1, 4, 1, 1, 3, 1, 1, 5, 3, 1, 1, 3, 1, 3, 1,
        1, 1, 4, 1, 2, 5, 3, 1, 4, 2, 3, 1, 1, 2, 1, 1, 1, 4, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 4, 1, 4, 1, 5, 1, 4, 2,
        1, 1, 5, 4, 4, 4, 1, 4, 1, 1, 1, 1, 3, 1, 5, 1, 4, 5, 3, 1, 4, 1, 5, 2, 2, 5, 1, 3, 2, 2, 5, 4, 2, 3, 4, 1, 2,
        1, 1, 2, 1, 1, 5, 4, 1, 1, 1, 1, 3, 1, 5, 4, 1, 5, 1, 1, 4, 3, 4, 3, 1, 5, 1, 1, 2, 1, 1, 5, 3, 1, 1, 1, 1, 1,
        5, 1, 1, 1, 1, 1, 1, 1, 2, 2, 5, 5, 1, 2, 1, 2, 1, 1, 5, 1, 3, 1, 5, 2, 1, 4, 1, 5, 3, 1, 1, 1, 2, 1, 3, 1, 4,
        4, 1, 1, 5, 1, 1, 4, 1, 4, 2, 3, 5, 2, 5, 1, 3, 1, 2, 1, 4, 1, 1, 1, 1, 2, 1, 4, 1, 3, 4, 1, 1, 1, 1, 1, 1, 1,
        2, 1, 5, 1, 1, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 1, 2, 1, 3, 2, 3, 1, 1, 3, 5, 1, 1,
        5, 5, 1, 2, 1, 2, 2, 1, 1, 1, 5, 3, 1, 1, 3, 5, 1, 3, 1, 5, 3, 4, 2, 3, 2, 1, 3, 1, 1, 3, 4, 2, 1, 1, 3, 1, 1,
        1, 1, 1, 1
};

static std::string input2[] = {

};

static std::string input3[] = {

};

int _6_1() {
    input.reserve(1000000000);
    for (int i = 0; i < 80; i++) {
        std::vector<int64_t> new_fishes;
        for (auto &existing_fish: input) {
            if (existing_fish == 0) {
                new_fishes.push_back(8);
                existing_fish = 6;
            } else {
                existing_fish--;
            }
        }
        input.insert(input.end(), new_fishes.begin(), new_fishes.end());
    }

    // old model: 374927
    // new model: 374927
    std::cout << input.size() << std::endl;
    return 0;
}

// 80 days are right
// produces 399127614607 for 256 (correct answer is 1687617803407)
int _6_2_naive_optimization() {
    std::vector<int64_t> fake_fish = {0};
    fake_fish.reserve(1000000000);

    constexpr int total_days = 256;
    int incs[7]{};


    for (int i = 0; i < total_days; i++) {
        std::vector<int64_t> new_fishes;
        for (auto &existing_fish: fake_fish) {
            if (existing_fish == 0) {
                new_fishes.push_back(8);
                existing_fish = 6;
            } else {
                existing_fish--;
            }
        }
        fake_fish.insert(fake_fish.end(), new_fishes.begin(), new_fishes.end());
        if (i >= total_days - 6) {
            int index = total_days - i - 1;
            incs[index] = fake_fish.size();
        }
    }

    size_t total = 0;
    for (auto existing_fish: input) {
        total += incs[existing_fish];
    }

    std::cout << total << std::endl;
    return 0;
}

int _6_2() {
    std::map<size_t, size_t> map_before, map_after;
    for (auto existing_fish: input) {
        map_before[existing_fish]++;
    }
    constexpr int total_days = 256;
    for (int i = 0; i < total_days; i++) {
        map_after = {};
        for (size_t age = 1; age <= 8; age++) {
            map_after[age - 1] = map_before[age];
        }
        map_after[8] += map_before[0];
        map_after[6] += map_before[0];
        map_before = map_after;
    }

    size_t total = 0;

    for (auto&[key, value]: map_after) {
        total += value;
    }
    std::cout << total << std::endl;

    return 0;
}