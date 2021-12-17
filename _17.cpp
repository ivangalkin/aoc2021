#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>

#include <iostream>
#include <string_view>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <list>

#include <regex>

#define myprint(arg) std::cout << "" #arg << " = " << arg << std::endl;

using namespace std::string_view_literals;

using PointT = std::tuple<int, int>;
static std::tuple<int, int> input_real_x = {139, 187};
static std::tuple<int, int> input_real_y = {-148, -89};


static std::vector<std::string> input_test = {

};

static auto &input_x = input_real_x;
static auto &input_y = input_real_y;
//static auto& input = input_test;


std::tuple<bool, int>
calculate_trajectory(PointT velocity, std::tuple<int, int> target_range_x, std::tuple<int, int> target_range_y) {
    PointT start{0, 0};
    PointT position{0, 0};

    int max_y = 0;
    while (true) {
        auto &[x, y] = position;
        auto &[velocity_x, velocity_y] = velocity;

        x += velocity_x;
        y += velocity_y;

//        myprint(x);
//        myprint(y)

        max_y = std::max(max_y, y);

        if (x <= std::get<1>(target_range_x) && x >= std::get<0>(target_range_x) && y <= std::get<1>(target_range_y) &&
            y >= std::get<0>(target_range_y)) {
            return {true, max_y};
        }
        if (y < std::get<0>(target_range_y)) {
            return {false, 0};
        }

        if (velocity_x > 0) {
            velocity_x--;
        } else if (velocity_x < 0) {
            velocity_x++;
        }
        velocity_y--;
    }
}

int selftest() {
    {
        auto[reaches, max_y] =calculate_trajectory({7, 2}, {20, 30}, {-10, -5});
        myprint(reaches);
        myprint(max_y);
        assert(reaches);
    }
    {
        auto[reaches, max_y] =calculate_trajectory({6, 3}, {20, 30}, {-10, -5});
        myprint(reaches);
        myprint(max_y);
        assert(reaches);
    }
    {
        auto[reaches, max_y] =calculate_trajectory({9, 0}, {20, 30}, {-10, -5});
        myprint(reaches);
        myprint(max_y);
        assert(reaches);
    }
    {
        auto[reaches, max_y] =calculate_trajectory({17, -4}, {20, 30}, {-10, -5});
        myprint(reaches);
        myprint(max_y);
        assert(!reaches);
    }
    return 0;
}

int _17_1() {
    selftest();
    int max_max_y = 0;
    for (int y = 1; y < INT16_MAX; y++) {
        for (int x = 1; x < INT16_MAX; x++) {
            auto[reaches, max_y] =calculate_trajectory({x, y}, input_real_x, input_real_y);
            if (reaches) {
                max_max_y = std::max(max_max_y, max_y);
                myprint(max_max_y);
            }
        }
    }

    return 0;
}

int _17_2() {
    selftest();
    int scores = 0;
    for (int y = INT16_MIN; y < INT16_MAX; y++) {
        for (int x = 1; x < INT16_MAX; x++) {
            auto[reaches, max_y] =calculate_trajectory({x, y}, input_real_x, input_real_y);
            if (reaches) {
                scores++;
                myprint(scores);
            }
        }
    }
    return 0;
}