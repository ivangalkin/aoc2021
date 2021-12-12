#include <iostream>
#include <string_view>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <list>
#include <cstring>

#include <regex>

static std::vector<std::pair<std::string, std::string>> input_real = {
        {"bm",    "XY"},
        {"ol",    "JS"},
        {"bm",    "im"},
        {"RD",    "ol"},
        {"bm",    "QI"},
        {"JS",    "ja"},
        {"im",    "gq"},
        {"end",   "im"},
        {"ja",    "ol"},
        {"JS",    "gq"},
        {"bm",    "AF"},
        {"RD",    "start"},
        {"RD",    "ja"},
        {"start", "ol"},
        {"cj",    "bm"},
        {"start", "JS"},
        {"AF",    "ol"},
        {"end",   "QI"},
        {"QI",    "gq"},
        {"ja",    "gq"},
        {"end",   "AF"},
        {"im",    "QI"},
        {"bm",    "gq"},
        {"ja",    "QI"},
        {"gq",    "RD"},
};

static std::vector<std::pair<std::string, std::string>> input_test10 = {
        {"start", "A"},
        {"start", "b"},
        {"A",     "c"},
        {"A",     "b"},
        {"b",     "d"},
        {"A",     "end"},
        {"b",     "end"},
};

static std::vector<std::pair<std::string, std::string>> input_test19 = {
        {"dc",    "end"},
        {"HN",    "start"},
        {"start", "kj"},
        {"dc",    "start"},
        {"dc",    "HN"},
        {"LN",    "dc"},
        {"HN",    "end"},
        {"kj",    "sa"},
        {"kj",    "HN"},
        {"kj",    "dc"},
};

static std::vector<std::pair<std::string, std::string>> input_test226 = {
        {"fs",    "end"},
        {"he",    "DX"},
        {"fs",    "he"},
        {"start", "DX"},
        {"pj",    "DX"},
        {"end",   "zg"},
        {"zg",    "sl"},
        {"zg",    "pj"},
        {"pj",    "he"},
        {"RW",    "he"},
        {"fs",    "DX"},
        {"pj",    "RW"},
        {"zg",    "RW"},
        {"start", "pj"},
        {"he",    "WI"},
        {"zg",    "he"},
        {"pj",    "fs"},
        {"start", "RW"},
};

static auto &input = input_real;
//static auto& input = input_test10;


std::list<std::vector<std::string>> paths;

std::set<std::string> get_tos(const std::string &from) {
    std::set<std::string> result;
    for (auto&[x, y]: input) {
        if (y == from) {
            result.insert(x);
        } else if (x == from) {
            result.insert(y);
        }
    }
    return result;
}

static inline bool all_of_is_lower(const auto &str) {
    return std::all_of(str.begin(), str.end(), [](char c) { return islower(c); });
}

void traverse(std::list<std::vector<std::string>>::iterator path_it) {
    std::vector<std::string> path = std::move(*path_it);
    paths.erase(path_it);

    auto tos = get_tos(path.back());

    for (auto &to: tos) {
        if (to == "start") {
            continue;
        }

        bool allow_to = true;
        if (all_of_is_lower(to)) {
            int max_visited_nr = 0;
            std::map<std::string, int> visited_map;
            for (auto &visited_path_segment: path) {
                if (all_of_is_lower(visited_path_segment)) {
                    auto &nr = visited_map[visited_path_segment];
                    nr++;
                    max_visited_nr = std::max(max_visited_nr, nr);
                }
            }

            int to_visited_nr = visited_map[to];

            // for part 1
            // int allowed_nr_of_visits = 1;
            // for part 2
            int allowed_nr_of_visits = (max_visited_nr == 2) ? 1 : 2;
            allow_to = (to_visited_nr + 1 <= allowed_nr_of_visits);
        }


        if (allow_to) {
            auto new_path = path;
            new_path.push_back(to);
            auto new_path_it = paths.insert(paths.end(), std::move(new_path));

            if (to != "end") {
                traverse(new_path_it);
            }
        }
    }
}

int _12() {
    auto &path = paths.emplace_back();
    path.push_back("start");

    traverse(paths.begin());

    for (auto &result: paths) {
        if (result.empty()) {
            continue;
        }
        for (auto &p: result) {
            std::cout << p << ",";
        }
        std::cout << std::endl;
    }


    size_t nr_results = 0;
    for (auto &p: paths) {
        if (!p.empty() && p.front() == "start" && p.back() == "end") {
            nr_results++;
        }
    }

    std::cout << nr_results << std::endl;

    return 0;
}
