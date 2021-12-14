#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>

#include <iostream>
#include <string_view>
#include <tuple>
#include <set>
#include <map>
#include <array>
#include <algorithm>
#include <sstream>
#include <list>

#include <regex>

#define myprint(arg) std::cout << "" #arg << " = " << arg << std::endl;
#define tab(arg) for (int i = 0; i < arg; i++) std::cout << "\t";

using namespace std::string_view_literals;

static std::map<std::string, std::string> input_test = {
        {"CH", "B"},
        {"HH", "N"},
        {"CB", "H"},
        {"NH", "C"},
        {"HB", "C"},
        {"HC", "B"},
        {"HN", "C"},
        {"NN", "C"},
        {"BH", "H"},
        {"NC", "B"},
        {"NB", "B"},
        {"BN", "B"},
        {"BB", "N"},
        {"BC", "B"},
        {"CC", "N"},
        {"CN", "C"},
};
static std::map<std::string, std::string> input_real = {
        {"OP", "H"},
        {"CF", "C"},
        {"BB", "V"},
        {"KH", "O"},
        {"CV", "S"},
        {"FV", "O"},
        {"FS", "K"},
        {"KO", "C"},
        {"PP", "S"},
        {"SH", "K"},
        {"FH", "O"},
        {"NF", "H"},
        {"PN", "P"},
        {"BO", "H"},
        {"OK", "K"},
        {"PO", "P"},
        {"SF", "K"},
        {"BF", "P"},
        {"HH", "S"},
        {"KP", "H"},
        {"HB", "N"},
        {"NP", "V"},
        {"KK", "P"},
        {"PF", "P"},
        {"BK", "V"},
        {"OF", "H"},
        {"FO", "S"},
        {"VC", "P"},
        {"FK", "B"},
        {"NK", "S"},
        {"CB", "B"},
        {"PV", "C"},
        {"CO", "N"},
        {"BN", "C"},
        {"HV", "H"},
        {"OC", "N"},
        {"NB", "O"},
        {"CS", "S"},
        {"HK", "C"},
        {"VS", "F"},
        {"BH", "C"},
        {"PC", "S"},
        {"KC", "O"},
        {"VO", "P"},
        {"FB", "K"},
        {"BV", "V"},
        {"VN", "N"},
        {"ON", "F"},
        {"VH", "H"},
        {"CN", "O"},
        {"HO", "O"},
        {"SV", "O"},
        {"SS", "H"},
        {"KF", "N"},
        {"SP", "C"},
        {"NS", "V"},
        {"SO", "F"},
        {"BC", "P"},
        {"HC", "C"},
        {"FP", "H"},
        {"OH", "S"},
        {"OB", "S"},
        {"HF", "V"},
        {"SC", "B"},
        {"SN", "N"},
        {"VK", "C"},
        {"NC", "V"},
        {"VV", "S"},
        {"SK", "K"},
        {"PK", "K"},
        {"PS", "N"},
        {"KB", "S"},
        {"KS", "C"},
        {"NN", "C"},
        {"OO", "C"},
        {"BS", "B"},
        {"NV", "H"},
        {"FF", "P"},
        {"FC", "N"},
        {"OS", "H"},
        {"KN", "N"},
        {"VP", "B"},
        {"PH", "N"},
        {"NH", "S"},
        {"OV", "O"},
        {"FN", "V"},
        {"CP", "B"},
        {"NO", "V"},
        {"CK", "C"},
        {"VF", "B"},
        {"HS", "B"},
        {"KV", "K"},
        {"VB", "H"},
        {"SB", "S"},
        {"BP", "S"},
        {"CC", "F"},
        {"HP", "B"},
        {"PB", "P"},
        {"HN", "P"},
        {"CH", "O"},
};

//static std::string formula = "NNCB";
static std::string formula = "KBKPHKHHNBCVCHPSPNHF";
//
static auto &input = input_real;
//static auto& input = input_test;

typedef std::tuple<char, char, size_t> MemorizeKeyT; // pair of characters and iteration step
typedef std::array<int64_t, 'Z' - 'A' + 1> CharMapT; // map between character and its number of appearances
typedef CharMapT MemorizeValueT;
std::map<MemorizeKeyT, MemorizeValueT> memorize;


void merge(CharMapT &target, const CharMapT &other) {
    for (size_t i = 0; i < target.size(); i++) {
        target[i] += other[i];
    }
}

MemorizeValueT unfold_map(char first, char second, size_t times) {
//    tab(times);
//    myprint(str);
//    tab(times);
//    myprint(times);

    MemorizeValueT m;
    m.fill(0);

    if (times == 0) {
        m[first - 'A']++;
        m[second - 'A']++;
        return m;
    } else if (auto it = memorize.find(MemorizeKeyT(first, second, times)); it != memorize.end()) {
        return it->second;
    }

    const char formula_lookup_key[3]{first, second, 0};

    auto formula_lookup = input[formula_lookup_key];
    assert(formula_lookup.size() == 1);

    auto unfold_map_result_left = unfold_map(first, formula_lookup[0], times - 1);
    auto unfold_map_result_right = unfold_map(formula_lookup[0], second, times - 1);
    merge(m, unfold_map_result_left);
    merge(m, unfold_map_result_right);
    m[formula_lookup[0] - 'A']--;

    memorize[MemorizeKeyT(first, second, times)] = m;

    return m;
}

int _14_1() {

    std::map<char, int64_t> count;

    for (size_t formula_pos = 0; formula_pos < formula.size() - 1; formula_pos++) {
        std::string formula_subset = formula.substr(formula_pos, 2);

        for (int iteration = 0; iteration < 10; iteration++) {
            std::string formula_subset_after;
            for (size_t i = 0; i < formula_subset.size() - 1; i++) {
                std::string pair = formula_subset.substr(i, 2);
                std::string result = input[pair];
                assert(!result.empty());
                formula_subset_after.append(&formula_subset[i], 1);
                formula_subset_after.append(result);
                if (i + 1 == formula_subset.size() - 1) {
                    formula_subset_after.append(&formula_subset[i + 1], 1);
                }
            }
            formula_subset = std::move(formula_subset_after);
        }

        for (char c: formula_subset) {
            auto &new_count = count[c];
            new_count++;
        }
    }

    for (int i = 1; i < formula.size() - 1; i++) {
        count[formula[i]]--;
    }

    int64_t min = INT64_MAX;
    int64_t max = 0;
    for (auto[key, value]: count) {
        min = std::min(min, value);
        max = std::max(max, value);
    }

    myprint(min);
    myprint(max);
    std::cout << max - min << std::endl;

    return 0;
}

CharMapT create(const std::string &str) {
    CharMapT result;
    result.fill(0);
    for (auto c: str) {
        result[c - 'A']++;
    }
    return result;
}

void print(const CharMapT &m) {
    std::cout << "--------" << std::endl;
    for (char c = 'A'; c <= 'Z'; c++) {
        auto count = m[c - 'A'];
        if (count != 0) {
            std::cout << c << ": " << count << std::endl;
        }
    }
}

int _14_2() {
    CharMapT result;
    result.fill(0);
    for (size_t i = 0; i < formula.size() - 1; i++) {
        auto pair_result = unfold_map(formula[i], formula[i + 1], 40);
        if (i != 0) {
            pair_result[formula[i] - 'A']--;
        }
        merge(result, pair_result);
    }

    print(result);
//    print(create("NCNBCHB"));
//    print(create("NBCCNBBBCBHCB"));
//    print(create("NBBBCNCCNBBNBNBBCHBHHBCHB"));
//    print(create("NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB"));

    auto max = *std::max_element(result.begin(), result.end());
    int64_t min = INT64_MAX;
    for (auto count: result) {
        if (count != 0) {
            min = std::min(min, count);
        }
    }
    myprint(min);
    myprint(max);
    std::cout << max - min << std::endl;

    return 0;
}
