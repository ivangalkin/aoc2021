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

static std::vector<std::string> input_real = {

};

static std::vector<std::string> input_test = {

};

static auto& input = input_real;
//static auto& input = input_test;

int _x() {
    std::regex r {"(acc|jmp|nop) (\\+|\\-)(\\d+)"};

    for ( auto line : input) {
        std::smatch sm;
        while (std::regex_search(line, sm, r)) {
            for (size_t i = 0; i < sm.size(); ++i) {
                std::cout << i << ": "<< sm[i] << std::endl;
            }
            line = sm.suffix();
        }
    }

    return 0;
}
