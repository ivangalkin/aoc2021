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
 *          11      13     15      17
 *          12      14     16      18
 */

using NodeID = int;
static const std::map<std::tuple<NodeID, NodeID>, std::vector<NodeID>> paths{
        // 12
        {{12, 0},  {12, 11, 2, 1, 0}},
        {{12, 1},  {12, 11, 2, 1}},
        {{12, 3},  {12, 11, 2, 3}},
        {{12, 5},  {12, 11, 2, 3, 4, 5}},
        {{12, 7},  {12, 11, 2, 3, 4, 5, 6, 7}},
        {{12, 9},  {12, 11, 2, 3, 4, 5, 6, 7, 8, 9}},
        {{12, 10}, {12, 11, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
        // 11
        {{11, 0},  {11, 2,  1, 0}},
        {{11, 1},  {11, 2,  1}},
        {{11, 3},  {11, 2,  3}},
        {{11, 5},  {11, 2,  3, 4, 5}},
        {{11, 7},  {11, 2,  3, 4, 5, 6, 7}},
        {{11, 9},  {11, 2,  3, 4, 5, 6, 7, 8, 9}},
        {{11, 10}, {11, 2,  3, 4, 5, 6, 7, 8, 9, 10}},
        // 14
        {{14, 0},  {14, 13, 4, 3, 2, 1, 0}},
        {{14, 1},  {14, 13, 4, 3, 2, 1}},
        {{14, 3},  {14, 13, 4, 3}},
        {{14, 5},  {14, 13, 4, 5}},
        {{14, 7},  {14, 13, 4, 5, 6, 7}},
        {{14, 9},  {14, 13, 4, 5, 6, 7, 8, 9}},
        {{14, 10}, {14, 13, 4, 5, 6, 7, 8, 9, 10}},
        // 13
        {{13, 0},  {13, 4,  3, 2, 1, 0}},
        {{13, 1},  {13, 4,  3, 2, 1}},
        {{13, 3},  {13, 4,  3}},
        {{13, 5},  {13, 4,  5}},
        {{13, 7},  {13, 4,  5, 6, 7}},
        {{13, 9},  {13, 4,  5, 6, 7, 8, 9}},
        {{13, 10}, {13, 4,  5, 6, 7, 8, 9, 10}},
        // 16
        {{16, 0},  {16, 15, 6, 5, 4, 3, 2, 1, 0}},
        {{16, 1},  {16, 15, 6, 5, 4, 3, 2, 1}},
        {{16, 3},  {16, 15, 6, 5, 4, 3}},
        {{16, 5},  {16, 15, 6, 5}},
        {{16, 7},  {16, 15, 6, 7}},
        {{16, 9},  {16, 15, 6, 7, 8, 9}},
        {{16, 10}, {16, 15, 6, 7, 8, 9, 10}},
        // 15
        {{15, 0},  {15, 6,  5, 4, 3, 2, 1, 0}},
        {{15, 1},  {15, 6,  5, 4, 3, 2, 1}},
        {{15, 3},  {15, 6,  5, 4, 3}},
        {{15, 5},  {15, 6,  5}},
        {{15, 7},  {15, 6,  7}},
        {{15, 9},  {15, 6,  7, 8, 9}},
        {{15, 10}, {15, 6,  7, 8, 9, 10}},
        // 18
        {{18, 0},  {18, 17, 8, 7, 6, 5, 4, 3, 2, 1, 0}},
        {{18, 1},  {18, 17, 8, 7, 6, 5, 4, 3, 2, 1}},
        {{18, 3},  {18, 17, 8, 7, 6, 5, 4, 3}},
        {{18, 5},  {18, 17, 8, 7, 6, 5}},
        {{18, 7},  {18, 17, 8, 7}},
        {{18, 9},  {18, 17, 8, 9}},
        {{18, 10}, {18, 17, 8, 9, 10}},
        // 17
        {{17, 0},  {17, 8,  7, 6, 5, 4, 3, 2, 1, 0}},
        {{17, 1},  {17, 8,  7, 6, 5, 4, 3, 2, 1}},
        {{17, 3},  {17, 8,  7, 6, 5, 4, 3}},
        {{17, 5},  {17, 8,  7, 6, 5}},
        {{17, 7},  {17, 8,  7}},
        {{17, 9},  {17, 8,  9}},
        {{17, 10}, {17, 8,  9, 10}},
};


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
            return (fish_id[1] == '1') ? 0 : 1;
        case 'B':
            return (fish_id[1] == '1') ? 2 : 3;
        case 'C':
            return (fish_id[1] == '1') ? 4 : 5;
        case 'D':
            return (fish_id[1] == '1') ? 6 : 7;
    }
    assert(false);
}


/**
 *
 *  0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10
 *          11      13     15      17
 *          12      14     16      18
 *
 */

/**

#############
#...........#
###A#D#B#D###
  #B#C#A#C#
  #########

 */

static std::array<FishHash, 19> get_initial_map() {
    std::array<size_t, 19> state;
    state.fill(NOBODY);
    state.at(11) = my_hash("A1");
    state.at(12) = my_hash("B1");
    state.at(13) = my_hash("D1");
    state.at(14) = my_hash("C1");
    state.at(15) = my_hash("B2");
    state.at(16) = my_hash("A2");
    state.at(17) = my_hash("D2");
    state.at(18) = my_hash("C2");
    return state;
}

static std::array<NodeID, 8> get_initial_fish_position() {
    std::array<NodeID, 8> state;
    state.at(my_hash("A1")) = 11;
    state.at(my_hash("B1")) = 12;
    state.at(my_hash("D1")) = 13;
    state.at(my_hash("C1")) = 14;
    state.at(my_hash("B2")) = 15;
    state.at(my_hash("A2")) = 16;
    state.at(my_hash("D2")) = 17;
    state.at(my_hash("C2")) = 18;
    return state;
}


static FishHash is_trapped_by(FishHash fish_hash) {
    switch (fish_hash) {
        case my_hash("A1"):
            return NOBODY;
        case my_hash("A2"):
            return my_hash("B2");
        case my_hash("B1"):
            return my_hash("A1");
        case my_hash("B2"):
            return NOBODY;
        case my_hash("C1"):
            return my_hash("D1");
        case my_hash("C2"):
            return my_hash("D2");
        case my_hash("D1"):
            return NOBODY;
        case my_hash("D2"):
            return NOBODY;
    }
    assert(false);
}

static const std::array<FishHash, 19> initial_map = get_initial_map();
static const std::array<NodeID, 8> initial_fish_position = get_initial_fish_position();


static bool path_is_free(const std::array<FishHash, 19> &map, const std::vector<NodeID> &path) {
    for (size_t i = 1; i < path.size(); i++) {
        if (map.at(path.at(i)) != NOBODY) {
            return false;
        }
    }
    return true;
}

static bool reverse_path_is_free(const std::array<FishHash, 19> &map, const std::vector<NodeID> &path) {
    for (size_t i = 0; i < path.size() - 1; i++) {
        if (map.at(path.at(i)) != NOBODY) {
            return false;
        }
    }
    return true;
}


static std::vector<std::tuple<FishHash, NodeID>> getNextLeaveCaveOption(std::vector<int> &node_indexes) {
    static const std::vector<NodeID> targets{0, 1, 3, 5, 7, 9, 10};

    assert(node_indexes.size() == 8); // nr or fishes
    node_indexes.back() += 1;
    for (size_t i = node_indexes.size() - 1; i > 0; i--) {
        if (node_indexes.at(i) > 6) {
            node_indexes.at(i) %= 6;
            node_indexes.at(i - 1)++;
        }
    }

    std::vector<std::tuple<FishHash, NodeID>> result(8);
    for (int i = 0; i < node_indexes.size(); i++) {
        result.at(i) = {i, targets.at(node_indexes.at(i))};
    }
    return result;
}


static bool is_return_step(const std::tuple<FishHash, NodeID> &step) {
    auto&[fish_hash, node_id] = step;
    switch (fish_hash) {
        case my_hash("A1"):
        case my_hash("A2"):
            return node_id == 11 || node_id == 12;
        case my_hash("B1"):
        case my_hash("B2"):
            return node_id == 13 || node_id == 14;
        case my_hash("C1"):
        case my_hash("C2"):
            return node_id == 15 || node_id == 16;
        case my_hash("D1"):
        case my_hash("D2"):
            return node_id == 17 || node_id == 18;
    }
    assert(false);
}

static std::array<NodeID, 2> get_target_node(FishHash fish_hash) {

    switch (fish_hash) {
        case my_hash("A1"):
        case my_hash("A2"):
            return {12, 11};
        case my_hash("B1"):
        case my_hash("B2"):
            return {14, 13};
        case my_hash("C1"):
        case my_hash("C2"):
            return {16, 15};
        case my_hash("D1"):
        case my_hash("D2"):
            return {18, 17};
    }
    assert(false);
}

static int64_t get_energy_coefficient(FishHash fish_hash) {
    switch (fish_hash) {
        case my_hash("A1"):
        case my_hash("A2"):
            return 1;
        case my_hash("B1"):
        case my_hash("B2"):
            return 10;
        case my_hash("C1"):
        case my_hash("C2"):
            return 100;
        case my_hash("D1"):
        case my_hash("D2"):
            return 1000;
    }
    assert(false);
}

static bool play(const std::vector<std::tuple<FishHash, NodeID>> &option) {

    // if same node in a row
    for (int i = 0; i < option.size() - 1; i++) {
        auto&[current_fish, current_node] = option.at(i);
        auto&[next_fish, next_node] = option.at(i + 1);
        if (current_node == next_node) {
            return false;
        }
        // same fish CAN do consecutive steps
    }

    // if return step is before the leave step
    // if trapped fish tries to escape first
    std::array<bool, 8> leave_step_detected;
    leave_step_detected.fill(false);

    for (auto &step: option) {
        auto&[fish_hash, node_id] = step;
        if (is_return_step(step)) {
            if (!leave_step_detected.at(fish_hash)) {
                return false;
            }
        } else {
            leave_step_detected.at(fish_hash) = true;
            auto who_am_I_trapped_by = is_trapped_by(fish_hash);
            if (who_am_I_trapped_by != NOBODY) {
                if (!leave_step_detected.at(who_am_I_trapped_by)) {
                    return false;
                }
            }
        }
    }


    std::array<NodeID, 8> current_position;
    current_position.fill(-1);

    auto map = initial_map;

    for (auto[fish_hash, node_id]: option) {
        if (!is_return_step({fish_hash, node_id})) {
            auto start_position = initial_fish_position.at(fish_hash);
            auto destination_position = node_id;
            assert(current_position.at(fish_hash) == -1);
            current_position.at(fish_hash) = destination_position;
            auto &path = paths.at({start_position, destination_position});
            if (path_is_free(map, path)) {
                map.at(start_position) = NOBODY;
                map.at(destination_position) = fish_hash;
            } else {
                return false;
            }
        } else {
            auto start_position = current_position.at(fish_hash);
            assert(start_position != -1);
            auto destination_position = node_id;
            auto &path = paths.at({destination_position, start_position});
            if (reverse_path_is_free(map, path)) {
                map.at(start_position) = NOBODY;
                map.at(destination_position) = fish_hash;
            } else {
                return false;
            }
        }
    }


    bool success = true;
    return success;
}

static FishID get_fish_name(FishHash fish_hash) {
    static const std::vector<FishID> fishes{"A1", "A2", "B1", "B2", "C1", "C2", "D1", "D2"};
    return fishes.at(fish_hash);
}

static int64_t calculate_costs(const std::vector<std::tuple<FishHash, NodeID>> &option) {
    std::array<size_t, 8> steps_done;
    steps_done.fill(0);


    std::array<NodeID, 8> current_position;
    current_position.fill(-1);

//    std::cout << "costs calculation" << std::endl;

    for (auto[fish_hash, node_id]: option) {
        if (!is_return_step({fish_hash, node_id})) {
            auto start_position = initial_fish_position.at(fish_hash);
            auto destination_position = node_id;
            assert(current_position.at(fish_hash) == -1);
            current_position.at(fish_hash) = destination_position;
            auto leave_steps = paths.at({start_position, destination_position}).size() - 1;
//            std::cout << get_fish_name(fish_hash) << " " << start_position << " -> " << destination_position << " == " << leave_steps << std::endl;
            steps_done.at(fish_hash) += leave_steps;
        } else {
            auto start_position = current_position.at(fish_hash);
            assert(start_position != -1);
            auto destination_position = node_id;
            auto return_steps = paths.at({destination_position, start_position}).size() - 1;
//            std::cout << get_fish_name(fish_hash) << " " << start_position << " -> " << destination_position << " == " << return_steps << std::endl;
            steps_done.at(fish_hash) += return_steps;
        }
    }

    int64_t costs = 0;
    for (FishHash fish_hash = 0; fish_hash < steps_done.size(); fish_hash++) {
        costs += (steps_done.at(fish_hash) * get_energy_coefficient(fish_hash));
    }
    return costs;
}

static void print(const std::vector<std::tuple<FishHash, NodeID>> &option) {

    std::cout << "-------" << std::endl;

    for (size_t i = 0; i < option.size(); i++) {
        auto&[fish_hash, node_id] = option.at(i);
        std::cout << i << ": " << get_fish_name(fish_hash) << " -> " << node_id << std::endl;
    }
}

static bool is_target_destination_reached(const std::array<FishHash, 19> &map) {
    for (FishHash fish_hash = 0; fish_hash < 8; fish_hash++) {
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

static void make_return_step(std::array<bool, 8> leave_step_done, std::array<bool, 8> return_step_done,
                             std::array<NodeID, 8> fish_position, std::array<FishHash, 19> map, int64_t current_costs);

static void make_leave_step(std::array<bool, 8> leave_step_done, std::array<bool, 8> return_step_done,
                            std::array<NodeID, 8> fish_position, std::array<FishHash, 19> map, int64_t current_costs) {
    if (is_target_destination_reached(map)) {
        std::cout << "done! current costs " << current_costs;
        min_costs = std::min(min_costs, current_costs);
        std::cout << " , min costs " << min_costs << std::endl;
        return;
    }

    for (size_t fish_hash = 0; fish_hash < 8; fish_hash++) {
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


void make_return_step(std::array<bool, 8> leave_step_done, std::array<bool, 8> return_step_done,
                      std::array<NodeID, 8> fish_position, std::array<FishHash, 19> map, int64_t current_costs) {

    if (is_target_destination_reached(map)) {
        std::cout << "done! current costs " << current_costs;
        min_costs = std::min(min_costs, current_costs);
        std::cout << " , min costs " << min_costs << std::endl;
        return;
    }

    for (size_t fish_hash = 0; fish_hash < 8; fish_hash++) {
        if (leave_step_done.at(fish_hash) && !return_step_done.at(fish_hash)) {
            for (auto target_position: get_target_node(fish_hash)) {
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

static int _23_brute_force(int argc, char **argv) {
    int start = 0;
    if (argc == 2) {
        // value [0, 5]
        start = std::stoi(argv[1], nullptr, 10);
    }
    std::cout << "starting node " << start << std::endl;

    // first step: every fish to any  node
    // second step every fish - to one of its caves
    // mix all permutations of first and second step

    static const std::vector<std::vector<std::tuple<FishHash, NodeID>>> a_returns
            {
                    {{my_hash("A1"), 11}, {my_hash("A2"), 12}},
                    {{my_hash("A2"), 11}, {my_hash("A1"), 12}}
            };

    static const std::vector<std::vector<std::tuple<FishHash, NodeID>>> b_returns
            {
                    {{my_hash("B1"), 13}, {my_hash("B2"), 14}},
                    {{my_hash("B2"), 13}, {my_hash("B1"), 14}}
            };
    static const std::vector<std::vector<std::tuple<FishHash, NodeID>>> c_returns
            {
                    {{my_hash("C1"), 15}, {my_hash("C2"), 16}},
                    {{my_hash("C2"), 15}, {my_hash("C1"), 16}}
            };
    static const std::vector<std::vector<std::tuple<FishHash, NodeID>>> d_returns
            {
                    {{my_hash("D1"), 17}, {my_hash("D2"), 18}},
                    {{my_hash("D2"), 17}, {my_hash("D1"), 18}}
            };

    std::vector<int> node_indexes{start, start, start, start, start, start, start, start};
    int64_t min_costs = INT64_MAX;
    do {
        auto leave_option = getNextLeaveCaveOption(node_indexes);
        for (auto &a_return: a_returns) {
            for (auto &b_return: b_returns) {
                for (auto &c_return: c_returns) {
                    for (auto &d_return: d_returns) {
                        auto options = leave_option;
                        options.insert(options.end(), a_return.begin(), a_return.end());
                        options.insert(options.end(), b_return.begin(), b_return.end());
                        options.insert(options.end(), c_return.begin(), c_return.end());
                        options.insert(options.end(), d_return.begin(), d_return.end());

                        std::sort(options.begin(), options.end());
                        do {
                            auto success = play(options);
                            if (success) {
                                print(options);
                                auto costs = calculate_costs(options);
                                myprint(costs);
                                if (costs < min_costs) {
                                    min_costs = costs;
                                    std::cout << "NEW MIN COSTS FOUND: " << min_costs << std::endl;
                                }
                            }
                        } while (std::next_permutation(options.begin(), options.end()));
                    }
                }
            }
        }
//        for (auto index : node_indexes) {
//            std::cout << index << " ";
//        }
//        std::cout << std::endl;
        if (std::all_of(node_indexes.begin(), node_indexes.end(), [](int value) { return value == 6; })) {
            break;
        }
    } while (true);


    return 0;
}

int _23_1() {
    std::array<bool, 8> leave_step_done;
    leave_step_done.fill(false);

    std::array<bool, 8> return_step_done;
    return_step_done.fill(false);

    make_leave_step(leave_step_done, return_step_done, initial_fish_position, initial_map, 0);
    return 0;
}
