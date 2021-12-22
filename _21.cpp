#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <array>

#include <iostream>
#include <string_view>
#include <tuple>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <list>

#include <regex>

#define myprint(arg) std::cout << "" #arg << " = " << arg << std::endl;


int64_t dice = 0;
int64_t rolls = 0;

int64_t DICE() {
    ++dice;
    ++rolls;
    if (dice > 100) {
        dice %= 100;
    }
    myprint(dice);
    return dice;
}


void STEP(int64_t &pos, int64_t moves) {
    for (int i = 0; i < moves; i++) {
        ++pos;
        if (pos > 10) {
            pos %= 10;
        }
    }
}

using PairOfInt = std::array<int64_t, 2>;

struct Snapshot {
    int64_t current_player = 0;
    PairOfInt rolls_remained;
    PairOfInt position;
    PairOfInt score;
};

bool operator<(const Snapshot &a, const Snapshot &b) {
    return std::tie(a.current_player, a.rolls_remained, a.position, a.score) <
           std::tie(b.current_player, b.rolls_remained, b.position, b.score);
}

bool operator==(const Snapshot &a, const Snapshot &b) {
    return std::tie(a.current_player, a.rolls_remained, a.position, a.score) ==
           std::tie(b.current_player, b.rolls_remained, b.position, b.score);
}

template<class T>
inline void hash_combine(std::size_t &seed, const T &v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<>
struct std::hash<Snapshot> {
    std::size_t operator()(Snapshot const &s) const noexcept {
        std::size_t hash = 0;
        hash_combine(hash, s.current_player);
        hash_combine(hash, s.rolls_remained[0]);
        hash_combine(hash, s.rolls_remained[1]);
        hash_combine(hash, s.position[0]);
        hash_combine(hash, s.position[1]);
        hash_combine(hash, s.score[0]);
        hash_combine(hash, s.score[1]);

        return hash;
    }
};

std::ostream &operator<<(std::ostream &stream, const Snapshot &p) {
    stream << "[current_player = " << p.current_player << ", rolls_remained = " << p.rolls_remained[0] << " "
           << p.rolls_remained[1]
           << ", position = " << p.position[0] << " " << p.position[1]
           << ", score = " << p.score[0] << " " << p.score[1] << "]";
    return stream;
}


int _21_1() {
    std::vector<int64_t> position{8, 10};
    std::vector<int64_t> score{0, 0};
    while (true) {
        auto d0 = DICE();
        auto d1 = DICE();
        auto d2 = DICE();
        STEP(position[0], d0 + d1 + d2);
        score[0] += position[0];

        if (score[0] >= 1000) {
            break;
        }

        auto d3 = DICE();
        auto d4 = DICE();
        auto d5 = DICE();

        STEP(position[1], d3 + d4 + d5);
        score[1] += position[1];

        if (score[1] >= 1000) {
            break;
        }
    }

    myprint(rolls);
    myprint(score[0]);
    myprint(score[1]);
    myprint(rolls * *std::min_element(score.begin(), score.end()));
    return 0;
}

// {pos & score}0 {pos & score}1 -> how many
using KeyT = std::tuple<std::tuple<int64_t, int64_t>, std::tuple<int64_t, int64_t>>;
using ValueT = int64_t;
std::list<std::tuple<KeyT, ValueT>> pos_and_scores_per_player;

bool is_ready() {
    for (auto&[key, value]: pos_and_scores_per_player) {
        if (value > 0) {
            return false;
        }
    }
    return true;
}

PairOfInt nr_of_wins = {0, 0};

void do_3_dices(int64_t player) {
    auto &pos_and_scores = pos_and_scores_per_player;

    for (int64_t dice_attempt = 0; dice_attempt < 3; dice_attempt++) {
        std::list<std::tuple<KeyT, ValueT>> temp;

        for (auto&[key, value]: pos_and_scores) {
            for (int64_t dice = 1; dice <= 2; dice++) {
                auto[pair0, pair1] = key;
                auto&[new_pos, new_scores] = (player == 0) ? pair0 : pair1;
                STEP(new_pos, dice);
                if (dice_attempt == 2) {
                    new_scores += new_pos;
                }
                temp.insert(temp.end(), {{pair0, pair1}, value});
            }

            {
                // dice 3 on existing node
                auto&[pair0, pair1] = key;
                auto&[pos, scores] = (player == 0) ? pair0 : pair1;
                STEP(pos, 3);
                if (dice_attempt == 2) {
                    scores += pos;
                }
            }
        }
        for (auto&[new_key, new_value]: temp) {
            if (auto it = std::find_if(pos_and_scores.begin(), pos_and_scores.end(),
                                       [new_key = new_key](const auto &elem) {
                                           auto&[key, value] = elem;
                                           return key == new_key;
                                       }); it != pos_and_scores.end()) {
                auto&[key, value] = *it;
                value += new_value;
            } else {
                pos_and_scores.insert(pos_and_scores.end(), {new_key, new_value});
            }
        }
    }

    auto it = pos_and_scores.begin();
    while (it != pos_and_scores.end()) {
        auto&[key, value] = *it;
        auto&[pair0, pair1] = key;
        auto&[pos, score] = (player == 0) ? pair0 : pair1;

        if (score >= 21) {
            nr_of_wins[player] += value;
            it = pos_and_scores.erase(it);
        } else {
            ++it;
        }
    }
}

int _21() {
//    pos_and_scores_per_player = {{ KeyT {{4,0},{8,0}}, ValueT {1}}};
    pos_and_scores_per_player = {{KeyT{{8, 0},
                                       {10, 0}}, ValueT{1}}};
    while (!is_ready()) {
        do_3_dices(0);
        do_3_dices(1);
        myprint(nr_of_wins[0]);
        myprint(nr_of_wins[1]);
    }
    return 0;
}
