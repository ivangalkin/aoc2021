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
#include <array>

#include <regex>

#define myprint(arg) std::cout << "" #arg << " = " << arg << std::endl;


/**
 *
 *  0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10
 *          11      15     19      23
 *          12      16     20      24
 *          13      17     21      25
 *          14      18     22      26
 */

using NodeID = int;

std::map<std::tuple<NodeID, NodeID>, std::vector<NodeID>>
extend_paths(const std::map<std::tuple<NodeID, NodeID>, std::vector<NodeID>> &part1_paths) {
    auto result = part1_paths;
    for (auto&[path_key, path_value]: part1_paths) {
        auto&[path_from, path_to] = path_key;
        auto add_additional_path = [&result, path_to = path_to, path_value = path_value](
                std::vector<NodeID> additional_path) {
            std::vector<NodeID> additional_path_reversed;
            for (NodeID new_from: additional_path) {
                additional_path_reversed.insert(additional_path_reversed.begin(), new_from);

                std::tuple<NodeID, NodeID> new_key{new_from, path_to};
                auto new_path = additional_path_reversed;
                new_path.insert(new_path.end(), path_value.begin(), path_value.end());
                result.insert_or_assign(new_key, new_path);
            }
        };
        if (path_from == 11) {
            add_additional_path({12, 13, 14});
        } else if (path_from == 15) {
            add_additional_path({16, 17, 18});
        } else if (path_from == 19) {
            add_additional_path({20, 21, 22});
        } else if (path_from == 23) {
            add_additional_path({24, 25, 26});
        }
    }
    return result;
}

static const std::map<std::tuple<NodeID, NodeID>, std::vector<NodeID>> paths = extend_paths({

                                                                                                    // 11
                                                                                                    {{11, 0},  {11, 2, 1, 0}},
                                                                                                    {{11, 1},  {11, 2, 1}},
                                                                                                    {{11, 3},  {11, 2, 3}},
                                                                                                    {{11, 5},  {11, 2, 3, 4, 5}},
                                                                                                    {{11, 7},  {11, 2, 3, 4, 5, 6, 7}},
                                                                                                    {{11, 9},  {11, 2, 3, 4, 5, 6, 7, 8, 9}},
                                                                                                    {{11, 10}, {11, 2, 3, 4, 5, 6, 7, 8, 9, 10}},

                                                                                                    // 15
                                                                                                    {{15, 0},  {15, 4, 3, 2, 1, 0}},
                                                                                                    {{15, 1},  {15, 4, 3, 2, 1}},
                                                                                                    {{15, 3},  {15, 4, 3}},
                                                                                                    {{15, 5},  {15, 4, 5}},
                                                                                                    {{15, 7},  {15, 4, 5, 6, 7}},
                                                                                                    {{15, 9},  {15, 4, 5, 6, 7, 8, 9}},
                                                                                                    {{15, 10}, {15, 4, 5, 6, 7, 8, 9, 10}},

                                                                                                    // 19
                                                                                                    {{19, 0},  {19, 6, 5, 4, 3, 2, 1, 0}},
                                                                                                    {{19, 1},  {19, 6, 5, 4, 3, 2, 1}},
                                                                                                    {{19, 3},  {19, 6, 5, 4, 3}},
                                                                                                    {{19, 5},  {19, 6, 5}},
                                                                                                    {{19, 7},  {19, 6, 7}},
                                                                                                    {{19, 9},  {19, 6, 7, 8, 9}},
                                                                                                    {{19, 10}, {19, 6, 7, 8, 9, 10}},

                                                                                                    // 23
                                                                                                    {{23, 0},  {23, 8, 7, 6, 5, 4, 3, 2, 1, 0}},
                                                                                                    {{23, 1},  {23, 8, 7, 6, 5, 4, 3, 2, 1}},
                                                                                                    {{23, 3},  {23, 8, 7, 6, 5, 4, 3}},
                                                                                                    {{23, 5},  {23, 8, 7, 6, 5}},
                                                                                                    {{23, 7},  {23, 8, 7}},
                                                                                                    {{23, 9},  {23, 8, 9}},
                                                                                                    {{23, 10}, {23, 8, 9, 10}}
                                                                                            });


/**

#############
#...........#
###A#D#B#D###
  #B#C#A#C#
  #########

 */

using FishID = std::string;
using FishHash = size_t;

static constexpr size_t NOBODY = -1;

constexpr FishHash my_hash(std::string_view fish_id) {
    switch (fish_id[0]) {
        case 'A':
            switch (fish_id[1]) {
                case '1':
                    return 0;
                case '2':
                    return 1;
                case '3':
                    return 2;
                case '4':
                    return 3;
            }
            assert(false);
        case 'B':
            switch (fish_id[1]) {
                case '1':
                    return 4;
                case '2':
                    return 5;
                case '3':
                    return 6;
                case '4':
                    return 7;
            }
            assert(false);
        case 'C':
            switch (fish_id[1]) {
                case '1':
                    return 8;
                case '2':
                    return 9;
                case '3':
                    return 10;
                case '4':
                    return 11;
            }
            assert(false);
        case 'D':
            switch (fish_id[1]) {
                case '1':
                    return 12;
                case '2':
                    return 13;
                case '3':
                    return 14;
                case '4':
                    return 15;
            }
    }
    assert(false);
}


const std::function<bool(NodeID)> &check_same_family(FishHash fish_hash) {
    static const std::function<bool(NodeID)> check_a = [](FishHash fish_hash) {
        return fish_hash == my_hash("A1") || fish_hash == my_hash("A2") || fish_hash == my_hash("A3") ||
               fish_hash == my_hash("A4");
    };

    static const std::function<bool(NodeID)> check_b = [](FishHash fish_hash) {
        return fish_hash == my_hash("B1") || fish_hash == my_hash("B2") || fish_hash == my_hash("B3") ||
               fish_hash == my_hash("B4");
    };

    static const std::function<bool(NodeID)> check_c = [](FishHash fish_hash) {
        return fish_hash == my_hash("C1") || fish_hash == my_hash("C2") || fish_hash == my_hash("C3") ||
               fish_hash == my_hash("C4");
    };

    static const std::function<bool(NodeID)> check_d = [](FishHash fish_hash) {
        return fish_hash == my_hash("D1") || fish_hash == my_hash("D2") || fish_hash == my_hash("D3") ||
               fish_hash == my_hash("D4");
    };
    switch (fish_hash) {
        case my_hash("A1"):
        case my_hash("A2"):
        case my_hash("A3"):
        case my_hash("A4"):
            return check_a;
        case my_hash("B1"):
        case my_hash("B2"):
        case my_hash("B3"):
        case my_hash("B4"):
            return check_b;
        case my_hash("C1"):
        case my_hash("C2"):
        case my_hash("C3"):
        case my_hash("C4"):
            return check_c;
        case my_hash("D1"):
        case my_hash("D2"):
        case my_hash("D3"):
        case my_hash("D4"):
            return check_d;
    }
    assert(false);

}


/**
 *
 *  0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10
 *          11      15     19      23
 *          12      16     20      24
 *          13      17     21      25
 *          14      18     22      26
 */

/**

#############
#...........#
###A#D#B#D###
  #D#C#B#A#
  #D#B#A#C#
  #B#C#A#C#
  #########

 */

using FishMap = std::array<FishHash, 27>;

static FishMap get_initial_map() {
    std::map<char, size_t> inc;
    auto next = [&inc](char c) {
        std::string result((size_t) 2, c);
        auto &nr = inc[c];
        nr++;

        switch (nr) {
            case 1:
                result[1] = '1';
                break;
            case 2:
                result[1] = '2';
                break;
            case 3:
                result[1] = '3';
                break;
            case 4:
                result[1] = '4';
                break;
        }
        return result;
    };
    FishMap state;
    state.fill(NOBODY);
    state.at(11) = my_hash(next('A'));
    state.at(12) = my_hash(next('D'));
    state.at(13) = my_hash(next('D'));
    state.at(14) = my_hash(next('B'));

    state.at(15) = my_hash(next('D'));
    state.at(16) = my_hash(next('C'));
    state.at(17) = my_hash(next('B'));
    state.at(18) = my_hash(next('C'));

    state.at(19) = my_hash(next('B'));
    state.at(20) = my_hash(next('B'));
    state.at(21) = my_hash(next('A'));
    state.at(22) = my_hash(next('A'));

    state.at(23) = my_hash(next('D'));
    state.at(24) = my_hash(next('A'));
    state.at(25) = my_hash(next('C'));
    state.at(26) = my_hash(next('C'));

    return state;
}

constexpr FishHash FISH_NR = 16;

using FishPositionMap = std::array<NodeID, FISH_NR>;

static FishPositionMap get_initial_fish_position() {
    std::map<char, size_t> inc;
    auto next = [&inc](char c) {
        std::string result((size_t) 2, c);
        auto &nr = inc[c];
        nr++;

        switch (nr) {
            case 1:
                result[1] = '1';
                break;
            case 2:
                result[1] = '2';
                break;
            case 3:
                result[1] = '3';
                break;
            case 4:
                result[1] = '4';
                break;
        }
        return result;
    };

    FishPositionMap state;
    state.at(my_hash(next('A'))) = 11;
    state.at(my_hash(next('D'))) = 12;
    state.at(my_hash(next('D'))) = 13;
    state.at(my_hash(next('B'))) = 14;

    state.at(my_hash(next('D'))) = 15;
    state.at(my_hash(next('C'))) = 16;
    state.at(my_hash(next('B'))) = 17;
    state.at(my_hash(next('C'))) = 18;

    state.at(my_hash(next('B'))) = 19;
    state.at(my_hash(next('B'))) = 20;
    state.at(my_hash(next('A'))) = 21;
    state.at(my_hash(next('A'))) = 22;

    state.at(my_hash(next('D'))) = 23;
    state.at(my_hash(next('A'))) = 24;
    state.at(my_hash(next('C'))) = 25;
    state.at(my_hash(next('C'))) = 26;
    return state;
}

static const FishMap initial_map = get_initial_map();
static const FishPositionMap initial_fish_position = get_initial_fish_position();

static bool path_is_free(const FishMap &map, const std::vector<NodeID> &path) {
    for (size_t i = 1; i < path.size(); i++) {
        if (map.at(path.at(i)) != NOBODY) {
            return false;
        }
    }
    return true;
}

static bool reverse_path_is_free(const FishMap &map, const std::vector<NodeID> &path) {
    for (size_t i = 0; i < path.size() - 1; i++) {
        if (map.at(path.at(i)) != NOBODY) {
            return false;
        }
    }
    return true;
}


/**
 *
 *  0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10
 *          11      15     19      23
 *          12      16     20      24
 *          13      17     21      25
 *          14      18     22      26
 */

static std::array<NodeID, 4> get_target_node(FishHash fish_hash) {

    switch (fish_hash) {
        case my_hash("A1"):
        case my_hash("A2"):
        case my_hash("A3"):
        case my_hash("A4"):
            return {14, 13, 12, 11};
        case my_hash("B1"):
        case my_hash("B2"):
        case my_hash("B3"):
        case my_hash("B4"):
            return {18, 17, 16, 15};
        case my_hash("C1"):
        case my_hash("C2"):
        case my_hash("C3"):
        case my_hash("C4"):
            return {22, 21, 20, 19};
        case my_hash("D1"):
        case my_hash("D2"):
        case my_hash("D3"):
        case my_hash("D4"):
            return {26, 25, 24, 23};
    }
    assert(false);
}

static std::vector<NodeID> get_suitable_targets(FishHash fish_hash, const FishMap &map) {
    auto target_nodes = get_target_node(fish_hash);
    for (int i = 0; i < target_nodes.size(); i++) {
        auto occupant = map.at(target_nodes.at(i));
        if (occupant == NOBODY) {
            return {target_nodes.at(i)};
        } else if (!check_same_family(fish_hash)(occupant)) {
            return {};
        }
    }
    return {};
}

static int64_t get_energy_coefficient(FishHash fish_hash) {
    switch (fish_hash) {
        case my_hash("A1"):
        case my_hash("A2"):
        case my_hash("A3"):
        case my_hash("A4"):
            return 1;
        case my_hash("B1"):
        case my_hash("B2"):
        case my_hash("B3"):
        case my_hash("B4"):
            return 10;
        case my_hash("C1"):
        case my_hash("C2"):
        case my_hash("C3"):
        case my_hash("C4"):
            return 100;
        case my_hash("D1"):
        case my_hash("D2"):
        case my_hash("D3"):
        case my_hash("D4"):
            return 1000;
    }
    assert(false);
}

static bool is_target_destination_reached(const FishMap &map) {
    for (FishHash fish_hash = 0; fish_hash < FISH_NR; fish_hash++) {
        bool fish_hash_reached_target = false;
        for (auto target_node: get_target_node(fish_hash)) {
            fish_hash_reached_target |= (map.at(target_node) == fish_hash);
        }
        if (!fish_hash_reached_target) {
            return false;
        }
    }
    return true;
}


static int64_t min_costs = INT64_MAX;

static void make_return_step(std::array<bool, FISH_NR> leave_step_done, std::array<bool, FISH_NR> return_step_done,
                             FishPositionMap fish_position, FishMap map, int64_t current_costs);

static void make_leave_step(std::array<bool, FISH_NR> leave_step_done, std::array<bool, FISH_NR> return_step_done,
                            FishPositionMap fish_position, FishMap map, int64_t current_costs) {
    if (is_target_destination_reached(map)) {
        std::cout << "done! current costs " << current_costs;
        min_costs = std::min(min_costs, current_costs);
        std::cout << " , min costs " << min_costs << std::endl;
        return;
    }

    for (size_t fish_hash = 0; fish_hash < FISH_NR; fish_hash++) {
        if (!leave_step_done.at(fish_hash)) {
            assert(!return_step_done.at(fish_hash));
            for (auto&[path_key, path_value]: paths) {
                auto&[path_from, path_to] = path_key;
                if (path_from == fish_position.at(fish_hash)) {
                    if (path_is_free(map, path_value)) {
                        auto new_leave_step_done = leave_step_done;
                        new_leave_step_done.at(fish_hash) = true;
                        auto new_fish_position = fish_position;
                        new_fish_position.at(fish_hash) = path_to;
                        auto new_map = map;
                        new_map.at(path_from) = NOBODY;
                        new_map.at(path_to) = fish_hash;

                        auto steps_done = path_value.size() - 1;
                        auto steps_costs = steps_done * get_energy_coefficient(fish_hash);

                        make_leave_step(new_leave_step_done, return_step_done, new_fish_position, new_map,
                                        current_costs + steps_costs);
                        make_return_step(new_leave_step_done, return_step_done, new_fish_position, new_map,
                                         current_costs + steps_costs);
                    }
                }
            }
        }
    }
}


void make_return_step(std::array<bool, FISH_NR> leave_step_done, std::array<bool, FISH_NR> return_step_done,
                      FishPositionMap fish_position, FishMap map, int64_t current_costs) {

    if (is_target_destination_reached(map)) {
        std::cout << "done! current costs " << current_costs;
        min_costs = std::min(min_costs, current_costs);
        std::cout << " , min costs " << min_costs << std::endl;
        return;
    }

    for (size_t fish_hash = 0; fish_hash < FISH_NR; fish_hash++) {
        if (leave_step_done.at(fish_hash) && !return_step_done.at(fish_hash)) {
            for (auto target_position: get_suitable_targets(fish_hash, map)) {
                auto &path = paths.at({target_position, fish_position.at(fish_hash)});
                if (reverse_path_is_free(map, path)) {
                    auto new_return_step_done = return_step_done;
                    new_return_step_done.at(fish_hash) = true;

                    auto new_fish_position = fish_position;
                    new_fish_position.at(fish_hash) = target_position;
                    auto new_map = map;
                    new_map.at(fish_position.at(fish_hash)) = NOBODY;
                    new_map.at(target_position) = fish_hash;

                    auto steps_done = path.size() - 1;
                    auto steps_costs = steps_done * get_energy_coefficient(fish_hash);

                    make_leave_step(leave_step_done, new_return_step_done, new_fish_position, new_map,
                                    current_costs + steps_costs);
                    make_return_step(leave_step_done, new_return_step_done, new_fish_position, new_map,
                                     current_costs + steps_costs);
                }
            }
        }
    }
}


int _23_2() {
    std::array<bool, FISH_NR> leave_step_done;
    leave_step_done.fill(false);

    std::array<bool, FISH_NR> return_step_done;
    return_step_done.fill(false);

    make_leave_step(leave_step_done, return_step_done, initial_fish_position, initial_map, 0);
    return 0;
}
