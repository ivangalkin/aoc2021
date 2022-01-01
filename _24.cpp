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
#include <iomanip>
#include <list>
#include <array>
#include <regex>

#define myprint(arg) std::cout << "" #arg << " = " << arg << std::endl;

using namespace std::string_view_literals;

static std::vector<std::vector<std::string>> input_real = {
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "1"},
        {"add", "x", "11"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "8"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "1"},
        {"add", "x", "14"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "13"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "1"},
        {"add", "x", "10"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "2"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "26"},
        {"add", "x", "0"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "7"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "1"},
        {"add", "x", "12"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "11"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "1"},
        {"add", "x", "12"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "4"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "1"},
        {"add", "x", "12"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "13"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "26"},
        {"add", "x", "-8"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "13"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "26"},
        {"add", "x", "-9"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "10"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "1"},
        {"add", "x", "11"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "1"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "26"},
        {"add", "x", "0"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "2"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "26"},
        {"add", "x", "-5"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "14"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "26"},
        {"add", "x", "-6"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "6"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
        {"inp", "w"},
        {"mul", "x", "0"},
        {"add", "x", "z"},
        {"mod", "x", "26"},
        {"div", "z", "26"},
        {"add", "x", "-12"},
        {"eql", "x", "w"},
        {"eql", "x", "0"},
        {"mul", "y", "0"},
        {"add", "y", "25"},
        {"mul", "y", "x"},
        {"add", "y", "1"},
        {"mul", "z", "y"},
        {"mul", "y", "0"},
        {"add", "y", "w"},
        {"add", "y", "14"},
        {"mul", "y", "x"},
        {"add", "z", "y"},
};

static std::vector<std::string> input_test = {

};

static auto &input = input_real;
//static auto& input = input_test;

static void get_previous_serial_number(std::array<int64_t, 14> &number, size_t start_idx) {

    number[start_idx] -= 1;
    for (size_t i = start_idx; i > 0; i--) {
        if (number.at(i) == 0) {
            number.at(i) = 9;
            number.at(i - 1)--;
        }
    }
}

static void get_next_serial_number(std::array<int64_t, 14> &number, size_t start_idx) {

    number[start_idx] += 1;
    for (size_t i = start_idx; i > 0; i--) {
        if (number.at(i) > 9) {
            number.at(i) %= 9;
            number.at(i - 1)++;
        }
    }
}

#pragma GCC optimize ("-O4")

std::tuple<int64_t, int64_t, int64_t> execute(std::array<int64_t, 14> number) {

    return {0, 0, 0};
}

#pragma GCC reset_options

std::tuple<int64_t, int64_t, int64_t, int64_t>
evaluate(const std::vector<std::vector<std::string>> &program, std::array<int64_t, 14> number) {
    int64_t w = 0;
    int64_t x = 0;
    int64_t y = 0;
    int64_t z = 0;

    size_t inp_index = 0;

    auto get_register = [&w, &x, &y, &z](const std::string &operand) -> int64_t * {
        if (operand == "w") {
            return &w;
        } else if (operand == "x") {
            return &x;
        } else if (operand == "y") {
            return &y;
        } else if (operand == "z") {
            return &z;
        } else {
            return nullptr;
        }
    };

    for (auto &line: program) {

        auto &cmd = line.at(0);
        if (cmd == "inp") {
            auto *reg = get_register(line.at(1));
            assert(reg);

            auto input = number.at(inp_index);
            inp_index++;

            *reg = input;
        } else if (cmd == "add") {
            auto *reg_0 = get_register(line.at(1));
            assert(reg_0);
            auto *maybe_reg_1 = get_register(line.at(2));

            int64_t value0 = *reg_0;
            int64_t value1 = (maybe_reg_1) ? *maybe_reg_1 : stoll(line.at(2));
            *reg_0 = value0 + value1;
        } else if (cmd == "mul") {
            auto *reg_0 = get_register(line.at(1));
            assert(reg_0);
            auto *maybe_reg_1 = get_register(line.at(2));

            int64_t value0 = *reg_0;
            int64_t value1 = (maybe_reg_1) ? *maybe_reg_1 : stoll(line.at(2));
            *reg_0 = value0 * value1;
        } else if (cmd == "div") {
            auto *reg_0 = get_register(line.at(1));
            assert(reg_0);
            auto *maybe_reg_1 = get_register(line.at(2));

            int64_t value0 = *reg_0;
            int64_t value1 = (maybe_reg_1) ? *maybe_reg_1 : stoll(line.at(2));
            if (value1 == 0) {
                std::cout << "division by 0" << std::endl;
                return {INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX};
            }

            *reg_0 = value0 / value1;
        } else if (cmd == "mod") {
            auto *reg_0 = get_register(line.at(1));
            assert(reg_0);
            auto *maybe_reg_1 = get_register(line.at(2));

            int64_t value0 = *reg_0;
            int64_t value1 = (maybe_reg_1) ? *maybe_reg_1 : stoll(line.at(2));
            if (value1 < 0 || value0 < 0) {
                std::cout << "invalid modulo operands" << std::endl;
                return {INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX};
            }

            *reg_0 = value0 % value1;
        } else if (cmd == "eql") {
            auto *reg_0 = get_register(line.at(1));
            assert(reg_0);
            auto *maybe_reg_1 = get_register(line.at(2));

            int64_t value0 = *reg_0;
            int64_t value1 = (maybe_reg_1) ? *maybe_reg_1 : stoll(line.at(2));

            *reg_0 = (value0 == value1);
        }
    }

    return {w, x, y, z};
}


std::optional<int64_t> maybe_strtoll(const std::string &str) {
    char *end_ptr;
    auto result = strtoll(str.c_str(), &end_ptr, 10);
    return (end_ptr == str.c_str() + str.size()) ? std::make_optional<int64_t>(result) : std::nullopt;

}


using BranchingOptionT = std::map<std::string, std::tuple<int64_t, std::vector<std::string>>>;

std::vector<BranchingOptionT>
optimize_ssa(const std::vector<std::vector<std::string>> &program, BranchingOptionT branching_options) {

    std::cout << "Start with " << branching_options.size() << ":  ";
    for (auto&[key, value]: branching_options) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    int64_t inp_index = -1;

    std::map<std::string, std::vector<std::string>> optimization;
    std::map<std::string, std::tuple<int64_t, int64_t>> ranges;
    std::map<int, std::tuple<std::string, std::string>> original;

    std::map<std::string, int> ssa_map;

    auto ssa = [&ssa_map](const std::string &operand, bool assignment) -> std::string {
        assert(operand != "w");
        if (operand == "x" || operand == "y" || operand == "z") {
            auto &ssa_index = ssa_map[operand];
            if (assignment) {
                ssa_index++;
            }
            return operand + (std::ostringstream() << std::setfill('0') << std::setw(3) << ssa_index).str();
        }
        return operand;
    };

    auto replace_w = [&inp_index, ssa](const std::string &operand) -> std::string {
        if (operand == "w") {
            return std::string("w") + (std::ostringstream() << std::setfill('0') << std::setw(3) << inp_index).str();;
        }
        return ssa(operand, false);
    };


    bool skip_next = false;
    int line_nr = -1;
    for (auto &line: program) {
        ++line_nr;

        if (skip_next) {
            skip_next = false;
            continue;
        }

        auto &cmd = line.at(0);

        if (cmd == "inp") {
            assert(line.at(1) == "w");
            inp_index++;
            continue;
        }


        auto rhs1 = replace_w(line.at(2));
        auto rhs0 = ssa(line.at(1), false);
        auto lhs = ssa(line.at(1), true);

        optimization["z000"] = {"0"};
        optimization["x000"] = {"0"};
        optimization["y000"] = {"0"};


        ranges["z000"] = {0, 0};
        ranges["x000"] = {0, 0};
        ranges["y000"] = {0, 0};

        if (cmd == "add") {
            optimization[lhs] = {rhs0, "+", rhs1};
            original[line_nr] = {lhs, (std::ostringstream() << "const int64_t " << lhs << " = " << rhs0 << " + " << rhs1
                                                            << ";").str()};
        } else if (cmd == "mul") {
            optimization[lhs] = {rhs0, "*", rhs1};
            original[line_nr] = {lhs,
                                 (std::ostringstream() << "const int64_t " << lhs << " = " << rhs0 << " * " << rhs1
                                                       << ";").str()};
        } else if (cmd == "div") {
            optimization[lhs] = {rhs0, "/", rhs1};
            original[line_nr] = {lhs, (std::ostringstream() << "const int64_t " << lhs << " = " << rhs0 << " / " << rhs1
                                                            << ";").str()};
        } else if (cmd == "mod") {
            optimization[lhs] = {rhs0, "%", rhs1};
            original[line_nr] = {lhs, (std::ostringstream() << "const int64_t " << lhs << " = " << rhs0 << " % " << rhs1
                                                            << ";").str()};
        } else if (cmd == "eql") {
            optimization[lhs] = {rhs0, "!=", rhs1};
            original[line_nr] = {lhs,
                                 (std::ostringstream() << "const int64_t " << lhs << " = " << rhs0 << " != " << rhs1
                                                       << ";").str()};
            skip_next = true;
        }

    }

//    for (auto&[line, lhs_original]: original) {
//        auto&[lhs, original] = lhs_original;
//        std::cout << original << std::endl;
//    }

    for (auto&[line, lhs_original]: original) {
        auto&[lhs, original] = lhs_original;

        auto optimization_it = optimization.find(lhs);
        assert(optimization_it != optimization.end());

        auto &expression = optimization_it->second;
        assert(expression.size() == 3);
        auto &first = expression.at(0);
        auto &op = expression.at(1);
        auto &second = expression.at(2);

        auto unwrap_operand = [&optimization](const std::string &r) -> std::vector<std::string> {
            if (r[0] == 'x' || r[0] == 'y' || r[0] == 'z') {
                auto unwrap_it = optimization.find(r);
                assert(unwrap_it != optimization.end());
                return unwrap_it->second;
            }
            return {r};
        };

        auto unwrap_operand_range = [&ranges](const std::string &r) -> std::tuple<int64_t, int64_t> {
            if (r[0] == 'x' || r[0] == 'y' || r[0] == 'z') {
                auto unwrap_it = ranges.find(r);
                assert(unwrap_it != ranges.end());
                return unwrap_it->second;
            } else if (r[0] == 'w') {
                return {1, 9};
            } else if (auto maybe_int = maybe_strtoll(r)) {
                return {*maybe_int, *maybe_int};
            }
            assert(false);
        };

        auto first_unwrapped = unwrap_operand(first);
        auto second_unwrapped = unwrap_operand(second);

        auto first_range = unwrap_operand_range(first);
        auto second_range = unwrap_operand_range(second);


        std::optional<int64_t> maybe_first_unwrapped_int;
        std::optional<int64_t> maybe_second_unwrapped_int;
        if (first_unwrapped.size() == 1) {
            maybe_first_unwrapped_int = maybe_strtoll(first_unwrapped[0]);
        }
        if (second_unwrapped.size() == 1) {
            maybe_second_unwrapped_int = maybe_strtoll(second_unwrapped[0]);
        }

        std::vector<std::string> evaluated_expression;
        if (maybe_first_unwrapped_int && *maybe_first_unwrapped_int == 0) {
            if (op == "+") {
                evaluated_expression = second_unwrapped;
            } else if (op == "*" || op == "/" || op == "%") {
                evaluated_expression = {"0"};
            }
        } else if (maybe_second_unwrapped_int && *maybe_second_unwrapped_int == 0) {
            if (op == "+") {
                evaluated_expression = first_unwrapped;
            } else if (op == "*") {
                evaluated_expression = {"0"};
            }
        } else if (maybe_first_unwrapped_int && *maybe_first_unwrapped_int == 1) {
            if (op == "*") {
                evaluated_expression = {second_unwrapped};
            }
        } else if (maybe_second_unwrapped_int && *maybe_second_unwrapped_int == 1) {
            if (op == "/" || op == "*") {
                evaluated_expression = first_unwrapped;
            } else if (op == "%") {
                evaluated_expression = {"0"};
            }
        }

        std::tuple<int64_t, int64_t> expression_range;
        auto&[expression_range_min, expression_range_max] = expression_range;
        auto&[first_range_min, first_range_max] = first_range;
        auto&[second_range_min, second_range_max] = second_range;
        if (op == "+") {
            expression_range_min = first_range_min + second_range_min;
            expression_range_max = first_range_max + second_range_max;
        } else if (op == "*") {
            expression_range_min = first_range_min * second_range_min;
            expression_range_max = first_range_max * second_range_max;
        } else if (op == "/") {
            assert(second_range_min == second_range_max);
            expression_range_min = first_range_min / second_range_min;
            expression_range_max = first_range_max / second_range_max;
        } else if (op == "%") {
            assert(second_range_min == second_range_max);
            expression_range_min = 0;
            expression_range_max = second_range_max - 1;
        }


        if (evaluated_expression.empty() && maybe_first_unwrapped_int && maybe_second_unwrapped_int) {
            if (op == "+") {
                evaluated_expression = {std::to_string(*maybe_first_unwrapped_int + *maybe_second_unwrapped_int)};
            } else if (op == "*") {
                evaluated_expression = {std::to_string(*maybe_first_unwrapped_int * *maybe_second_unwrapped_int)};
            } else if (op == "/") {
                evaluated_expression = {std::to_string(*maybe_first_unwrapped_int / *maybe_second_unwrapped_int)};
            } else if (op == "%") {
                evaluated_expression = {std::to_string(*maybe_first_unwrapped_int % *maybe_second_unwrapped_int)};
            }
        }

        assert(expression_range_min <= expression_range_max);

        bool non_trivial_comparison_found = false;

        if (op == "!=" && second_unwrapped.size() == 1 && second_unwrapped.at(0).starts_with("w")) {
            if (auto branching_it = branching_options.find(lhs); branching_it != branching_options.end()) {
                auto&[branched_lhs, branched_value] = *branching_it;
                auto&[branched_result, branched_expression] = branched_value;
                std::cout << "\t" << lhs << " " << branched_result << std::endl;
                evaluated_expression = {std::to_string(branched_result)};
                expression_range_min = branched_result;
                expression_range_max = branched_result;

            } else if (first_range_min > 9 || first_range_max < 1) {
                evaluated_expression = {"1"};
                expression_range_min = 1;
                expression_range_max = 1;
            } else {
                // comparison is non-trivial; we have to branch (either 0 or 1) in order to find the branching options where the resulting z == 0
                expression_range_min = 0;
                expression_range_max = 1;
                non_trivial_comparison_found = true;
            }
        }

        ranges[lhs] = expression_range;

        if (evaluated_expression.size()) {
            optimization_it->second = std::move(evaluated_expression);
        } else {
            optimization_it->second.clear();
            if (first_unwrapped.size() > 1) {
                optimization_it->second.push_back("(");
            }
            optimization_it->second.insert(optimization_it->second.end(), first_unwrapped.begin(),
                                           first_unwrapped.end());
            if (first_unwrapped.size() > 1) {
                optimization_it->second.push_back(")");
            }
            optimization_it->second.push_back(op);
            if (second_unwrapped.size() > 1) {
                optimization_it->second.push_back("(");
            }
            optimization_it->second.insert(optimization_it->second.end(), second_unwrapped.begin(),
                                           second_unwrapped.end());
            if (second_unwrapped.size() > 1) {
                optimization_it->second.push_back(")");
            }
        }

        if (non_trivial_comparison_found) {

            auto new_branching_option_one = branching_options;
            assert(new_branching_option_one.find(lhs) == new_branching_option_one.end());
            new_branching_option_one.insert_or_assign(lhs, std::tuple<int64_t, std::vector<std::string>>(
                    {0, optimization_it->second}));

            auto new_branching_option_two = branching_options;
            assert(new_branching_option_two.find(lhs) == new_branching_option_two.end());
            new_branching_option_two.insert_or_assign(lhs, std::tuple<int64_t, std::vector<std::string>>(
                    {1, optimization_it->second}));

            // do a very lazy fork - start the whole evaluation from beginning

            std::cout << "New branch created for " << lhs << ". Number of options = " << new_branching_option_one.size()
                      << "/" << new_branching_option_two.size() << std::endl;

            return {std::move(new_branching_option_one), std::move(new_branching_option_two)};
        }
    }

    auto last_z = ssa("z", false);
    auto[result_min, result_max] = ranges[last_z];
    std::cout << last_z << " " << result_min << " " << result_max << std::endl;

    if (ranges[last_z] == std::tuple<int64_t, int64_t>{0, 0}) {

        for (auto&[line, lhs_original]: original) {
            auto&[lhs, original] = lhs_original;
            std::cout << line << "/" << input_real.size() << ": ";
            std::cout << original << " // ";
            auto opt_it = optimization.find(lhs);
            assert(opt_it != optimization.end());
            for (auto optimized_rhs: opt_it->second) {
                std::cout << optimized_rhs << " ";
            }

            auto range_it = ranges.find(lhs);
            assert(range_it != ranges.end());
            auto&[range_min, range_max] = range_it->second;
            std::cout << "[" << range_min << ", " << range_max << "] ";

            std::cout << std::endl;
        }

        std::cout << "FOUND!" << std::endl;
        // the branching leads to deterministic z == 0
        for (auto&[branching_lhs, branching_result]: branching_options) {
            auto&[branching_value, branching_expression] = branching_result;
            std::cout << " ----------" << std::endl;
            std::cout << "LHS: " << branching_lhs << std::endl;
            std::cout << "EXP: ";
            for (auto expr: branching_expression) {
                std::cout << expr << " ";
            }
            std::cout << std::endl;
            std::cout << "VAL: " << branching_value << std::endl;
        }
    }

    return {};
}


void self_test() {
    const std::vector<std::vector<std::string>> &program = {
            {"inp", "w"},
            {"add", "z", "w"},
            {"mod", "z", "2"},
            {"div", "w", "2"},
            {"add", "y", "w"},
            {"mod", "y", "2"},
            {"div", "w", "2"},
            {"add", "x", "w"},
            {"mod", "x", "2"},
            {"div", "w", "2"},
            {"mod", "w", "2"}};

    std::array<int64_t, 14> serial_number;
    serial_number.fill(0);
    serial_number[0] = 10;

    auto[w, x, y, z] = evaluate(program, serial_number);
    assert(w == 1);
    assert(x == 0);
    assert(y == 1);
    assert(z == 0);
}

/*
int main() {
    self_test();
    jit(input);
    std::array<int64_t, 14> number {9,9,9,9, 9,9,9,9, 9,9,9,9, 9, 9};
    do {
//        auto [w,x,y,z] = evaluate(input, number);
        auto [w,x,y,z] = execute(number);
        for (auto digit: number) {
            std::cout << digit;
        }
        std::cout << std::endl;
        myprint(w);
        myprint(x);
        myprint(y);
        myprint(z);

        if (z == 0) {

            break;
        }
        get_previous_serial_number(number);
    } while (!std::all_of(number.begin(), number.end(), [](auto value) {return value == 1;}));
    return 0;
}
*/

int calculate_conditions() {
    self_test();

    std::list<BranchingOptionT> options_queue;
    options_queue.push_back({});

    while (!options_queue.empty()) {
        auto option = options_queue.back();
        options_queue.pop_back();
        auto result = optimize_ssa(input, std::move(option));
        options_queue.insert(options_queue.begin(), result.begin(), result.end());
    }

//    ----------
//            LHS: x020
//    EXP: ( ( ( ( ( ( w000 + 8 ) * 26 ) + ( w001 + 13 ) ) * 26 ) + ( w002 + 2 ) ) % 26 ) != w003
//    VAL: 0
//        ----------
//    LHS: x040
//    EXP: ( ( ( ( ( ( ( ( ( ( ( ( ( ( w000 + 8 ) * 26 ) + ( w001 + 13 ) ) * 26 ) + ( w002 + 2 ) ) / 26 ) * 26 ) + ( w004 + 11 ) ) * 26 ) + ( w005 + 4 ) ) * 26 ) + ( w006 + 13 ) ) % 26 ) + -8 ) != w007
//    VAL: 0
//        ----------
//    LHS: x045
//    EXP: ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( w000 + 8 ) * 26 ) + ( w001 + 13 ) ) * 26 ) + ( w002 + 2 ) ) / 26 ) * 26 ) + ( w004 + 11 ) ) * 26 ) + ( w005 + 4 ) ) * 26 ) + ( w006 + 13 ) ) / 26 ) % 26 ) + -9 ) != w008
//    VAL: 0
//        ----------
//    LHS: x055
//    EXP: ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( w000 + 8 ) * 26 ) + ( w001 + 13 ) ) * 26 ) + ( w002 + 2 ) ) / 26 ) * 26 ) + ( w004 + 11 ) ) * 26 ) + ( w005 + 4 ) ) * 26 ) + ( w006 + 13 ) ) / 26 ) / 26 ) * 26 ) + ( w009 + 1 ) ) % 26 ) != w010
//    VAL: 0
//        ----------
//    LHS: x060
//    EXP: ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( w000 + 8 ) * 26 ) + ( w001 + 13 ) ) * 26 ) + ( w002 + 2 ) ) / 26 ) * 26 ) + ( w004 + 11 ) ) * 26 ) + ( w005 + 4 ) ) * 26 ) + ( w006 + 13 ) ) / 26 ) / 26 ) * 26 ) + ( w009 + 1 ) ) / 26 ) % 26 ) + -5 ) != w011
//    VAL: 0
//        ----------
//    LHS: x065
//    EXP: ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( w000 + 8 ) * 26 ) + ( w001 + 13 ) ) * 26 ) + ( w002 + 2 ) ) / 26 ) * 26 ) + ( w004 + 11 ) ) * 26 ) + ( w005 + 4 ) ) * 26 ) + ( w006 + 13 ) ) / 26 ) / 26 ) * 26 ) + ( w009 + 1 ) ) / 26 ) / 26 ) % 26 ) + -6 ) != w012
//    VAL: 0
//        ----------
//    LHS: x070
//    EXP: ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( w000 + 8 ) * 26 ) + ( w001 + 13 ) ) * 26 ) + ( w002 + 2 ) ) / 26 ) * 26 ) + ( w004 + 11 ) ) * 26 ) + ( w005 + 4 ) ) * 26 ) + ( w006 + 13 ) ) / 26 ) / 26 ) * 26 ) + ( w009 + 1 ) ) / 26 ) / 26 ) / 26 ) % 26 ) + -12 ) != w013
//    VAL: 0

    return 0;
}

int _24_1() {
    std::array<int64_t, 14> number;
    number.fill(9);


    while (true) {

        int64_t &w000 = number[0];
        int64_t &w001 = number[1];
        int64_t &w002 = number[2];
        int64_t &w003 = number[3];
        int64_t &w004 = number[4];
        int64_t &w005 = number[5];
        int64_t &w006 = number[6];
        int64_t &w007 = number[7];
        int64_t &w008 = number[8];
        int64_t &w009 = number[9];
        int64_t &w010 = number[10];
        int64_t &w011 = number[11];
        int64_t &w012 = number[12];
        int64_t &w013 = number[13];


        auto condition0 = [&]() {
            return ((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) % 26) == w003;
        };

        goto_condition0:
        while (!condition0()) {
            get_previous_serial_number(number, 3);
        }

        auto condition1 = [&]() {
            return ((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) * 26) +
                        (w005 + 4)) * 26) + (w006 + 13)) % 26) + -8) == w007;
        };

        goto_condition1:
        while (!condition1()) {
            get_previous_serial_number(number, 7);
            if (!condition0()) {
                goto goto_condition0;
            }
        }

        auto condition2 = [&]() {
            return (((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) * 26) +
                         (w005 + 4)) * 26) + (w006 + 13)) / 26) % 26) + -9) == w008;
        };

        goto_condition2:
        while (!condition2()) {
            get_previous_serial_number(number, 8);
            if (!condition1()) {
                goto goto_condition1;
            }
        }

        auto condition3 = [&]() {
            return (((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                            26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) % 26) == w010;
        };

        goto_condition3:
        while (!condition3()) {
            get_previous_serial_number(number, 10);
            if (!condition2()) {
                goto goto_condition2;
            }
        }

        auto condition4 = [&]() {
            return (((((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                              26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) / 26) % 26) +
                    -5) == w011;
        };

        goto_condition4:
        while (!condition4()) {
            get_previous_serial_number(number, 11);
            if (!condition3()) {
                goto goto_condition3;
            }
        }

        auto condition5 = [&]() {
            return ((((((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                               26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) / 26) / 26) %
                     26) + -6) == w012;
        };

        goto_condition5:
        while (!condition5()) {
            get_previous_serial_number(number, 12);
            if (!condition4()) {
                goto goto_condition4;
            }
        }

        auto condition6 = [&]() {
            return (((((((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                                26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) / 26) / 26) /
                      26) % 26) + -12) == w013;
        };

        goto_condition6:
        while (!condition6()) {
            get_previous_serial_number(number, 13);
            if (!condition5()) {
                goto goto_condition5;
            }
        }

        assert(condition0());
        assert(condition1());
        assert(condition2());
        assert(condition3());
        assert(condition4());
        assert(condition5());
        assert(condition6());

        for (auto digit: number) {
            std::cout << digit;
        }
        std::cout << std::endl;

        break;
    }


    return 0;
}


int _24_2() {
    std::array<int64_t, 14> number;
    number.fill(1);


    while (true) {

        int64_t &w000 = number[0];
        int64_t &w001 = number[1];
        int64_t &w002 = number[2];
        int64_t &w003 = number[3];
        int64_t &w004 = number[4];
        int64_t &w005 = number[5];
        int64_t &w006 = number[6];
        int64_t &w007 = number[7];
        int64_t &w008 = number[8];
        int64_t &w009 = number[9];
        int64_t &w010 = number[10];
        int64_t &w011 = number[11];
        int64_t &w012 = number[12];
        int64_t &w013 = number[13];


        auto condition0 = [&]() {
            return ((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) % 26) == w003;
        };

        goto_condition0:
        while (!condition0()) {
            get_next_serial_number(number, 3);
        }

        auto condition1 = [&]() {
            return ((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) * 26) +
                        (w005 + 4)) * 26) + (w006 + 13)) % 26) + -8) == w007;
        };

        goto_condition1:
        while (!condition1()) {
            get_next_serial_number(number, 7);
            if (!condition0()) {
                goto goto_condition0;
            }
        }

        auto condition2 = [&]() {
            return (((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) * 26) +
                         (w005 + 4)) * 26) + (w006 + 13)) / 26) % 26) + -9) == w008;
        };

        goto_condition2:
        while (!condition2()) {
            get_next_serial_number(number, 8);
            if (!condition1()) {
                goto goto_condition1;
            }
        }

        auto condition3 = [&]() {
            return (((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                            26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) % 26) == w010;
        };

        goto_condition3:
        while (!condition3()) {
            get_next_serial_number(number, 10);
            if (!condition2()) {
                goto goto_condition2;
            }
        }

        auto condition4 = [&]() {
            return (((((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                              26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) / 26) % 26) +
                    -5) == w011;
        };

        goto_condition4:
        while (!condition4()) {
            get_next_serial_number(number, 11);
            if (!condition3()) {
                goto goto_condition3;
            }
        }

        auto condition5 = [&]() {
            return ((((((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                               26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) / 26) / 26) %
                     26) + -6) == w012;
        };

        goto_condition5:
        while (!condition5()) {
            get_next_serial_number(number, 12);
            if (!condition4()) {
                goto goto_condition4;
            }
        }

        auto condition6 = [&]() {
            return (((((((((((((((((((((w000 + 8) * 26) + (w001 + 13)) * 26) + (w002 + 2)) / 26) * 26) + (w004 + 11)) *
                                26) + (w005 + 4)) * 26) + (w006 + 13)) / 26) / 26) * 26) + (w009 + 1)) / 26) / 26) /
                      26) % 26) + -12) == w013;
        };

        goto_condition6:
        while (!condition6()) {
            get_next_serial_number(number, 13);
            if (!condition5()) {
                goto goto_condition5;
            }
        }

        assert(condition0());
        assert(condition1());
        assert(condition2());
        assert(condition3());
        assert(condition4());
        assert(condition5());
        assert(condition6());

        for (auto digit: number) {
            std::cout << digit;
        }
        std::cout << std::endl;

        break;
    }


    return 0;
}

