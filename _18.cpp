#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>

#include <iostream>
#include <string>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <list>
#include <variant>
#include <regex>

#define myprint(arg) std::cout << "" #arg << " = " << arg << std::endl;

using namespace std::string_literals;

static std::vector<std::string> input_real = {
        "[[[[6,3],7],0],[[7,0],0]]",
        "[[[4,7],[6,[6,5]]],[4,[[6,5],[9,1]]]]",
        "[[[[3,7],[6,9]],[3,[4,1]]],8]",
        "[[[0,[2,0]],3],2]",
        "[[[[1,3],4],9],[[[1,8],[9,3]],[0,7]]]",
        "[[[5,9],1],[[[4,8],[4,8]],[[9,7],[3,6]]]]",
        "[[[0,7],4],[[[0,4],2],[4,2]]]",
        "[[5,1],[2,5]]",
        "[[[[4,8],[8,3]],[6,[2,3]]],[[6,0],[1,3]]]",
        "[[[[1,7],[8,1]],[2,[3,4]]],[[7,[8,7]],[[8,6],5]]]",
        "[[9,[[8,9],[0,6]]],[[[8,4],5],[0,[1,7]]]]",
        "[[[[9,8],[6,9]],[[3,5],[6,2]]],[[[7,8],5],8]]",
        "[[[[7,1],8],[0,2]],[3,5]]",
        "[[[1,9],3],[8,[8,[7,8]]]]",
        "[[[9,[8,5]],[1,[9,0]]],5]",
        "[9,[[[1,1],8],[[3,5],9]]]",
        "[[[1,[7,8]],2],[8,0]]",
        "[7,[8,[[6,1],[7,9]]]]",
        "[[7,[[4,7],7]],[[8,[5,2]],2]]",
        "[[[[1,7],[9,0]],3],[8,[4,[2,0]]]]",
        "[[4,3],[[9,[7,7]],7]]",
        "[[[[9,5],3],[[8,5],5]],5]",
        "[[[[4,9],2],[[5,6],[9,0]]],[[2,[2,2]],1]]",
        "[[[[7,9],[6,0]],[1,[5,8]]],[8,8]]",
        "[[[[0,5],2],[4,[5,7]]],[8,[[8,1],[6,7]]]]",
        "[9,[7,[[3,7],[6,4]]]]",
        "[[[[5,3],[5,2]],[[5,0],0]],[[[4,6],[6,4]],[8,8]]]",
        "[1,[[8,0],0]]",
        "[[3,[7,9]],[[[1,2],[1,6]],[[9,2],[2,8]]]]",
        "[[[2,8],[3,[8,3]]],[3,[[9,8],[5,6]]]]",
        "[[[[2,0],3],[5,1]],[[[2,9],7],[[0,4],[1,4]]]]",
        "[[3,[[0,0],[9,0]]],[[6,[0,5]],[[5,4],[5,2]]]]",
        "[[8,[[9,4],[6,8]]],[3,[[8,1],4]]]",
        "[[[[4,1],[5,1]],[4,[9,1]]],4]",
        "[2,[[[0,5],[8,7]],[[6,1],[1,0]]]]",
        "[7,[8,8]]",
        "[[[[7,3],5],9],[[[5,9],[3,5]],[[9,4],8]]]",
        "[[[[4,2],[6,1]],[[6,6],7]],[2,2]]",
        "[[[1,1],4],[[[4,8],0],[[6,7],7]]]",
        "[[[[5,9],[0,1]],[9,7]],2]",
        "[[[[6,4],[5,5]],[[2,8],0]],9]",
        "[[7,[4,9]],[5,[[0,2],2]]]",
        "[[2,[9,9]],[[8,5],8]]",
        "[3,[8,[6,[2,8]]]]",
        "[[[0,1],[[8,5],[8,9]]],0]",
        "[[[[1,8],[1,4]],8],[[6,8],[8,[5,7]]]]",
        "[[[[7,1],[2,0]],[2,4]],[[[3,7],[2,2]],1]]",
        "[[[[0,3],[8,0]],[2,6]],[[6,2],[0,4]]]",
        "[[[7,1],[[6,8],[3,2]]],[[8,[3,2]],[1,[0,1]]]]",
        "[[[8,[5,7]],4],[[1,[1,9]],[[4,9],[4,2]]]]",
        "[[[8,5],3],[[9,8],[[4,4],[7,2]]]]",
        "[[5,[5,[8,7]]],[[8,0],[[6,3],6]]]",
        "[[[8,4],[[5,2],[7,0]]],[[[9,7],[8,9]],7]]",
        "[[5,[3,[3,0]]],5]",
        "[[[[0,1],[0,0]],[4,[3,7]]],[8,0]]",
        "[5,[[[8,3],8],5]]",
        "[[[5,[0,6]],4],[4,[3,[6,3]]]]",
        "[[[[4,1],[3,5]],[[5,0],7]],[[[7,9],[8,8]],[[8,0],[5,8]]]]",
        "[[[7,[6,6]],[[6,2],2]],8]",
        "[1,[4,[[2,9],[3,8]]]]",
        "[[[9,[5,4]],[[2,5],7]],[[4,2],9]]",
        "[[9,1],[[0,7],[[4,1],[5,6]]]]",
        "[[[7,[8,6]],[[4,5],1]],[[[2,1],[6,3]],[4,[0,3]]]]",
        "[[0,[2,[7,5]]],[[[5,0],5],3]]",
        "[[[0,[4,1]],7],[[[3,7],5],[[5,9],7]]]",
        "[[4,[[1,3],1]],[[9,6],[[6,2],3]]]",
        "[3,[[[8,5],6],4]]",
        "[[2,7],[[[3,9],3],[[2,1],2]]]",
        "[[4,[5,[9,9]]],[[[3,0],[4,1]],[[6,4],9]]]",
        "[[[7,9],[[5,7],[2,1]]],[[[1,4],6],[3,3]]]",
        "[[[[4,0],3],[3,[6,3]]],[[[6,2],4],5]]",
        "[[9,[[2,4],3]],[[9,[1,0]],[[5,8],[7,1]]]]",
        "[8,[1,5]]",
        "[[[5,5],3],[[[8,9],3],4]]",
        "[[1,[[8,8],[7,4]]],[[[9,1],[9,6]],[7,8]]]",
        "[[[7,2],[[0,1],5]],7]",
        "[[9,3],[7,[1,[9,2]]]]",
        "[[[[8,2],[8,0]],[[7,1],6]],[0,[[9,4],1]]]",
        "[[[[1,3],2],[6,[0,0]]],[[[7,8],[4,3]],[[9,4],1]]]",
        "[[[[2,1],[7,1]],[[5,4],[9,2]]],[[3,0],0]]",
        "[[[8,6],[[2,1],[9,1]]],[[3,[1,8]],[3,3]]]",
        "[[[[6,2],[3,6]],3],[5,9]]",
        "[[[[7,6],7],[[4,2],1]],[[0,4],[[9,8],6]]]",
        "[[8,[[7,6],[8,5]]],[[2,7],[[7,0],[0,0]]]]",
        "[[[0,[0,0]],4],[[[6,1],8],[[5,9],[6,5]]]]",
        "[[[8,[9,9]],9],[[3,[2,8]],[[9,5],[2,9]]]]",
        "[[[7,5],[[0,7],[3,3]]],[[8,[1,5]],9]]",
        "[[[6,[9,0]],[[0,7],[7,5]]],[[[4,9],0],[[2,3],7]]]",
        "[[8,[8,[0,1]]],[[2,6],7]]",
        "[1,[[9,3],1]]",
        "[[[[6,2],[0,8]],5],[[[9,4],7],[[6,3],6]]]",
        "[[[8,[4,2]],[4,9]],[7,[[9,0],8]]]",
        "[1,[[7,3],2]]",
        "[[[3,[5,9]],[7,[0,4]]],[[[3,0],7],4]]",
        "[[[1,[8,3]],[4,[2,3]]],[[3,[1,6]],[[1,6],5]]]",
        "[[[[1,3],2],9],[5,[4,9]]]",
        "[[[7,[0,6]],2],[[[1,5],[0,7]],[4,9]]]",
        "[[[5,0],[0,[1,1]]],5]",
        "[[[[9,3],[0,0]],[[1,3],[7,3]]],[[5,7],[[6,6],[6,5]]]]",
        "[[[8,0],[9,0]],[[[4,7],4],[5,[2,6]]]]"
};

static std::vector<std::string> input_test = {
        "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
        "[[[5,[2,8]],4],[5,[[9,9],0]]]",
        "[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
        "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
        "[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
        "[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
        "[[[[5,4],[7,7]],8],[[8,3],8]]",
        "[[9,3],[[9,9],[6,[4,9]]]]",
        "[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
        "[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"
};

struct RecursiveTupleT {
    using NodeT = std::variant<int64_t, RecursiveTupleT *>;
    RecursiveTupleT *parent;

    std::string str;

    NodeT left;
    NodeT right;
};

static auto &input = input_real;
//static auto& input = input_test;

void parser_tuple(RecursiveTupleT *out, size_t nesting);

const char *parse_tuple_side(const char *begin, const char *end, RecursiveTupleT *parent,
                             std::variant<int64_t, RecursiveTupleT *> *side, size_t nesting) {
    char *strtol_end = nullptr;
    auto digit = strtol(begin, &strtol_end, 10);

    if (strtol_end != begin) {
        *side = {(int64_t) digit};
        return strtol_end;
    } else {
        RecursiveTupleT *side_obj = new RecursiveTupleT();
        side_obj->parent = parent;
        *side = side_obj;
        assert(*begin == '[');
        std::list<const char *> tuple_starts{begin};
        for (auto it = begin + 1; it != end; it++) {
            if (*it == ']') {
                auto *tuple_start = tuple_starts.back();
                tuple_starts.pop_back();
                if (tuple_starts.empty()) {
                    side_obj->str = std::string(tuple_start, it - tuple_start + 1);
                    parser_tuple(std::get<RecursiveTupleT *>(*side), nesting + 1);
                    return it + 1;
                }
            } else if (*it == '[') {
                tuple_starts.push_back(it);
            }
        }
    }

    assert(false);
}

void parser_tuple(RecursiveTupleT *out, size_t nesting) {
    assert(out->str.size() > 2);
    assert(out->str.starts_with('['));
    assert(out->str.ends_with(']'));

    auto *begin = out->str.data() + 1;
    auto *end = out->str.data() + out->str.size() - 1;

    auto *it = parse_tuple_side(begin, end, out, &out->left, nesting);
    assert(*it == ',');
    parse_tuple_side(it + 1, end, out, &out->right, nesting);
}

int64_t calculate_magnitude(RecursiveTupleT *tuple) {
    assert(tuple);

    int64_t value_left = 1;
    {
        auto *maybe_left_int = std::get_if<int64_t>(&tuple->left);
        if (maybe_left_int) {
            value_left = *maybe_left_int;
        } else {
            value_left = calculate_magnitude(*std::get_if<RecursiveTupleT *>(&tuple->left));
        }
    }

    int64_t value_right = 1;
    {
        auto *maybe_right_int = std::get_if<int64_t>(&tuple->right);
        if (maybe_right_int) {
            value_right = *maybe_right_int;
        } else {
            value_right = calculate_magnitude(*std::get_if<RecursiveTupleT *>(&tuple->right));
        }
    }

    return 3 * value_left + 2 * value_right;
}

RecursiveTupleT *add(RecursiveTupleT *left, RecursiveTupleT *right) {
    RecursiveTupleT *result = new RecursiveTupleT();
    left->parent = result;
    right->parent = result;
    result->left = left;
    result->right = right;
    return result;
}

RecursiveTupleT *parse(const std::string &str) {
    RecursiveTupleT *tuple = new RecursiveTupleT();
    tuple->str = std::string(str.data(), str.length());
    parser_tuple(tuple, 0);
    return tuple;
}

int64_t parse_and_calculate(const std::string &str) {
    return calculate_magnitude(parse(str));
}


std::tuple<RecursiveTupleT *, RecursiveTupleT::NodeT *>
find_tuple_nested_5_times(RecursiveTupleT *root, size_t current_nesting) {
    std::vector<RecursiveTupleT *> levels[5]{};
    levels[0].push_back(root);

    std::vector<RecursiveTupleT::NodeT *> levels_as_nodes[5]{};

    for (size_t i = 1; i < 5; i++) {
        for (auto &previous_level: levels[i - 1]) {
            auto **left_is_tuple = std::get_if<RecursiveTupleT *>(&previous_level->left);
            if (left_is_tuple) {
                levels[i].push_back(*left_is_tuple);
                levels_as_nodes[i].push_back(&previous_level->left);
            }
            auto **right_is_tuple = std::get_if<RecursiveTupleT *>(&previous_level->right);
            if (right_is_tuple) {
                levels[i].push_back(*right_is_tuple);
                levels_as_nodes[i].push_back(&previous_level->right);
            }
        }
    }
    if (!levels[4].empty()) {
        return {levels[4].front(), levels_as_nodes[4].front()};
    }
    return {nullptr, nullptr};
}

std::string print(RecursiveTupleT *tuple, bool print_depth = false);

int64_t *find_nearest_left_digit(RecursiveTupleT *tuple) {
    // step up as long this tuple is the left child of the parent
    auto *parent = tuple->parent;
    RecursiveTupleT::NodeT *neighbor = nullptr;
    while (parent) {
        auto *left_is_tuple = std::get_if<RecursiveTupleT *>(&parent->left);
        if (!left_is_tuple) {
            return std::get_if<int64_t>(&parent->left);
        } else if (*left_is_tuple != tuple) {
            neighbor = &parent->left;
            break;
        }
        tuple = parent;
        parent = parent->parent;

    }
    if (neighbor == nullptr) {
        return nullptr;
    }

    while (true) {
        if (auto *most_right_child_is_int = std::get_if<int64_t>(neighbor)) {
            return most_right_child_is_int;
        }
        neighbor = &(*std::get_if<RecursiveTupleT *>(neighbor))->right;
    }

    assert(false);
}


int64_t *find_nearest_right_digit(RecursiveTupleT *tuple) {
    // step up as long this tuple is the right child of the parent
    auto *parent = tuple->parent;
    RecursiveTupleT::NodeT *neighbor = nullptr;
    while (parent) {
        auto *right_is_tuple = std::get_if<RecursiveTupleT *>(&parent->right);
        if (!right_is_tuple) {
            return std::get_if<int64_t>(&parent->right);
        } else if (*right_is_tuple != tuple) {
            neighbor = &parent->right;
            break;
        }
        tuple = parent;
        parent = parent->parent;

    }
    if (neighbor == nullptr) {
        return nullptr;
    }

    while (true) {
        if (auto *most_left_child_is_int = std::get_if<int64_t>(neighbor)) {
            return most_left_child_is_int;
        }
        neighbor = &(*std::get_if<RecursiveTupleT *>(neighbor))->left;
    }

    assert(false);
}

RecursiveTupleT *explode(RecursiveTupleT *tuple) {
    auto[tuple_to_explode, node_t_explode] =  find_tuple_nested_5_times(tuple, 0);
    if (tuple_to_explode) {
        auto *parent = tuple_to_explode->parent;
        assert(parent);

        if (auto *nearest_right_digit = find_nearest_right_digit(tuple_to_explode)) {
            *nearest_right_digit += std::get<int64_t>(tuple_to_explode->right);
        }
        if (auto *nearest_left_digit = find_nearest_left_digit(tuple_to_explode)) {
            *nearest_left_digit += std::get<int64_t>(tuple_to_explode->left);
        }

        *node_t_explode = 0;
        return tuple;
    }
    return nullptr;
}

RecursiveTupleT *split(RecursiveTupleT *tuple) {
    auto *maybe_left_int = std::get_if<int64_t>(&tuple->left);
    if (maybe_left_int) {
        if (*maybe_left_int >= 10) {
            auto *new_tuple = new RecursiveTupleT();
            new_tuple->parent = tuple;
            new_tuple->left = *maybe_left_int / 2;
            new_tuple->right = *maybe_left_int - *maybe_left_int / 2;
            tuple->left = new_tuple;
            return tuple;
        }
    } else {
        auto *result = split(*std::get_if<RecursiveTupleT *>(&tuple->left));
        if (result) {
            return result;
        }
    }
    auto *maybe_right_int = std::get_if<int64_t>(&tuple->right);
    if (maybe_right_int) {
        if (*maybe_right_int >= 10) {
            auto *new_tuple = new RecursiveTupleT();
            new_tuple->parent = tuple;
            new_tuple->left = *maybe_right_int / 2;
            new_tuple->right = *maybe_right_int - *maybe_right_int / 2;
            tuple->right = new_tuple;
            return tuple;
        }
    } else {
        auto *result = split(*std::get_if<RecursiveTupleT *>(&tuple->right));
        if (result) {
            return result;
        }
    }
    return nullptr;
}


void print(RecursiveTupleT *tuple, std::ostringstream &out, size_t depth, bool print_depth) {
    out << "[";
    auto *maybe_left_int = std::get_if<int64_t>(&tuple->left);
    if (maybe_left_int) {
        out << *maybe_left_int;
    } else {
        print(*std::get_if<RecursiveTupleT *>(&tuple->left), out, depth + 1, print_depth);
    }
    out << ",";
    auto *maybe_right_int = std::get_if<int64_t>(&tuple->right);
    if (maybe_right_int) {
        out << *maybe_right_int;
    } else {
        print(*std::get_if<RecursiveTupleT *>(&tuple->right), out, depth + 1, print_depth);
    }
    out << "]";
    if (print_depth) {
        out << "{" << depth << "}";
    }
}

std::string print(RecursiveTupleT *tuple, bool print_depth) {
    std::ostringstream out;
    print(tuple, out, 0, print_depth);
    return out.str();
}


RecursiveTupleT *sum_loop(RecursiveTupleT *first, RecursiveTupleT *second) {
    auto *s = add(first, second);
    while (true) {
        auto *did_explode = explode(s);
        if (did_explode) {
            continue;
        }
        auto *did_split = split(s);
        if (did_split) {
            continue;
        }
        break;
    }
    return s;
}


int _18() {
    assert(parse_and_calculate("[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]") == 4140);
    assert(parse_and_calculate("[[1,2],[[3,4],5]]") == 143);
    assert(parse_and_calculate("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]") == 1384);
    assert(parse_and_calculate("[[[[1,1],[2,2]],[3,3]],[4,4]]") == 445);
    assert(parse_and_calculate("[[[[3,0],[5,3]],[4,4]],[5,5]]") == 791);
    assert(parse_and_calculate("[[[[5,0],[7,4]],[5,5]],[6,6]]") == 1137);
    assert(parse_and_calculate("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]") == 3488);

    for (const auto &line: input) {
        parse_and_calculate(line);
    }

    {
        auto *sum = add(parse("[1,2]"), parse("[[3,4],5]"));
        myprint(print(sum))
    }

    {
        auto *sum = add(parse("[[[[4,3],4],4],[7,[[8,4],9]]]"), parse("[1,1]"));
        auto[tuple_to_explode, _] = find_tuple_nested_5_times(sum, 0);
        assert(tuple_to_explode);
        assert(print(tuple_to_explode) == "[4,3]");
        auto *exploded = explode(sum);
        myprint(print(exploded));
    }
    {
        auto *sum = parse("[[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]");
        myprint(print(sum, true));
        auto *exploded = explode(sum);
        myprint(print(exploded));
        assert(print(exploded) == "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
    }
    {
        auto *sum = parse("[[[[0,7],4],[7,[[8,4],9]]],[1,1]]");
        myprint(print(sum, true));
        auto[tuple_to_explode, _] = find_tuple_nested_5_times(sum, 0);
        assert(tuple_to_explode);
        assert(print(tuple_to_explode) == "[8,4]");
        auto *exploded = explode(sum);
        myprint(print(exploded));
        assert(print(exploded) == "[[[[0,7],4],[15,[0,13]]],[1,1]]");
    }
    {
        auto *t = parse("[[[[0,7],4],[15,[0,13]]],[1,1]]");
        auto *s = split(t);
        assert(s);
        myprint(print(t));
    }
    {
        auto *s = sum_loop(parse("[[[[4,3],4],4],[7,[[8,4],9]]]"), parse("[1,1]"));
        myprint(print(s));
    }

    {
        RecursiveTupleT *left = nullptr;
        RecursiveTupleT *result = nullptr;
        for (auto str: {"[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]",
                        "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]",
                        "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]",
                        "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]",
                        "[7,[5,[[3,8],[1,4]]]]",
                        "[[2,[2,2]],[8,[8,1]]]",
                        "[2,9]",
                        "[1,[[[9,3],9],[[9,0],[0,7]]]]",
                        "[[[5,[7,4]],7],1]",
                        "[[[[4,2],2],6],[8,7]]"}) {
            if (left == nullptr) {
                left = parse(str);
                continue;
            }
            auto *right = parse(str);
            result = sum_loop(left, right);
            myprint(print(result));
            myprint(calculate_magnitude(result));
            left = result;
        }
    }

    std::cout << "--- PART1--" << std::endl;
    {
        RecursiveTupleT *left = nullptr;
        RecursiveTupleT *result = nullptr;
        for (auto &str: input) {
            if (left == nullptr) {
                left = parse(str);
                continue;
            }
            auto *right = parse(str);
            result = sum_loop(left, right);
            left = result;
        }
        myprint(calculate_magnitude(result));
    }

    std::cout << "--- PART2--" << std::endl;
    int64_t max = INT64_MIN;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            if (i == j) continue;
            auto *left0 = parse(input[i]);
            auto *right0 = parse(input[j]);
            auto *res0 = sum_loop(left0, right0);
            auto res0_magnitude = calculate_magnitude(res0);
            max = std::max(max, res0_magnitude);

            auto *left1 = parse(input[j]);
            auto *right1 = parse(input[i]);
            auto *res1 = sum_loop(left1, right1);
            auto res1_magnitude = calculate_magnitude(res1);
            max = std::max(max, res1_magnitude);
        }
    }

    myprint(max);
    return 0;
}
