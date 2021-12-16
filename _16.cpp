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

static std::string input_real =
        "E054831006016008CF01CED7CDB2D495A473336CF7B8C8318021C00FACFD3125B9FA624BD3DBB7968C0179DFDBD196FAE5400974A974B55C24DC580085925D5007E2D49C6579E49252E28600B580272379054AF57A54D65E1586A951D860400434E36080410926624D25458890A006CA251006573D2DFCBF4016919CC0A467302100565CF24B7A9C36B0402840002150CA3E46000042621C108F0200CC5C8551EA47F79FC28401C20042E0EC288D4600F42585F1F88010C8C709235180272B3DCAD95DC005F6671379988A1380372D8FF1127BDC0D834600BC9334EA5880333E7F3C6B2FBE1B98025600A8803F04E2E45700043E34C5F8A72DDC6B7E8E400C01797D02D002052637263CE016CE5E5C8CC9E4B369E7051304F3509627A907C97BCF66008500521395A62553A9CAD312A9CCCEAF63A500A2631CCD8065681D2479371E4A90E024AD69AAEBE20002A84ACA51EE0365B74A6BF4B2CC178153399F3BACC68CF3F50840095A33CBD7EF1393459E2C3004340109596AB6DEBF9A95CACB55B6F5FCD4A24580400A8586009C70C00D44401D8AB11A210002190DE1BC43872C006C45299463005EC0169AFFF6F9273269B89F4F80100507C00A84EB34B5F2772CB122D26016CA88C9BCC8BD4A05CA2CCABF90030534D3226B32D040147F802537B888CD59265C3CC01498A6B7BA7A1A08F005C401C86B10A358803D1FE24419300524F32AD2C6DA009080330DE2941B1006618450822A009C68998C1E0C017C0041A450A554A582D8034797FD73D4396C1848FC0A6F14503004340169D96BE1B11674A4804CD9DC26D006E20008747585D0AC001088550560F9019B0E004080160058798012804E4801232C0437B00F70A005100CFEE007A8010C02553007FC801A5100530C00F4B0027EE004CA64A480287C005E27EEE13DD83447D3009E754E29CDB5CD3C";

static std::vector<std::string> input_test = {

};

static auto &input = input_real;
//static auto& input = input_test;


std::string hextobin(char c) {
    switch (c) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
    }
    assert(c && false);
}

std::string hextobin(const std::string &s) {
    std::stringstream binary;
    for (char c: s) {
        binary << hextobin(c);
    }
    return binary.str();
}

struct PacketT {
    long version = 0;
    long type_ID = 0;
    long value = 0;
    std::list<PacketT *> subpackets;
};

const char *parsepaket(const char *input_begin, const char *input_end, size_t &version_sum, PacketT *packet_output) {

    auto *it = input_begin;

    assert(input_end - it >= 3);
    std::string version_str{it, it + 3};
    auto version = stol(version_str, nullptr, 2);
    packet_output->version = version;
    version_sum += version;
    myprint(version);
    it += 3;

    assert(input_end - it >= 3);
    std::string type_ID_str{it, it + 3};
    auto type_ID = stol(type_ID_str, nullptr, 2);
    packet_output->type_ID = type_ID;
    myprint(type_ID);
    it += 3;

    if (type_ID == 4) {

        bool is_last_nibble = false;
        std::string value_str;
        do {
            assert(input_end - it >= 5);
            std::string nibble{it, it + 5};
            is_last_nibble = nibble.starts_with('0');
            nibble = nibble.substr(1);
            value_str += nibble;
            it += 5;
        } while (!is_last_nibble);
        auto value = stol(value_str, nullptr, 2);
        packet_output->value = value;
        myprint(value);
    } else {
        assert(input_end - it >= 1);
        char length_type = *it;
        it++;

        if (length_type == '0') {
            assert(input_end - it >= 15);
            std::string total_length_of_subpackets_in_bits_str = {it, it + 15};
            auto total_length_of_subpackets_in_bits = stol(total_length_of_subpackets_in_bits_str, nullptr, 2);
            myprint(total_length_of_subpackets_in_bits);
            it += 15;

            auto *end_of_subpackets = it + total_length_of_subpackets_in_bits;
            auto remaining_length_of_subpackets = total_length_of_subpackets_in_bits;
            do {
                PacketT *subpacket = packet_output->subpackets.emplace_back(new PacketT());
                auto *subpacket_end = parsepaket(it, end_of_subpackets, version_sum, subpacket);
                remaining_length_of_subpackets -= (subpacket_end - it);
                it = subpacket_end;
            } while (remaining_length_of_subpackets >= 11);
            it = end_of_subpackets;

        } else {
            assert(input_end - it >= 11);
            std::string number_of_subpackets_str = {it, it + 11};
            auto number_of_subpackets = stol(number_of_subpackets_str, nullptr, 2);
            myprint(number_of_subpackets);
            it += 11;

            for (int i = 0; i < number_of_subpackets; i++) {
                PacketT *subpacket = packet_output->subpackets.emplace_back(new PacketT());
                auto *subpacket_end = parsepaket(it, input_end, version_sum, subpacket);
                it = subpacket_end;
            }
        }
    }

    return it;
}


long evaluate(PacketT *root) {
    PacketT *p = root;
    if (p->type_ID == 4) {
        return p->value;
    }
    std::vector<long> value_subpackets;
    for (auto *subpacket: p->subpackets) {
        value_subpackets.push_back(evaluate(subpacket));
    }

    if (p->type_ID == 0) {
        long result = 0;
        for (auto value: value_subpackets) {
            result += value;
        }
        return result;
    } else if (p->type_ID == 1) {
        long result = 1;
        for (auto value: value_subpackets) {
            result *= value;
        }
        return result;
    } else if (p->type_ID == 2) {
        long result = 0;
        result = *std::min_element(value_subpackets.begin(), value_subpackets.end());
        return result;
    } else if (p->type_ID == 3) {
        long result = 0;
        result = *std::max_element(value_subpackets.begin(), value_subpackets.end());
        return result;
    } else if (p->type_ID == 5) {
        long result = 0;
        result = value_subpackets.at(0) > value_subpackets.at(1);
        return result;
    } else if (p->type_ID == 6) {
        long result = 0;
        result = value_subpackets.at(0) < value_subpackets.at(1);
        return result;
    } else if (p->type_ID == 7) {
        long result = 0;
        result = value_subpackets.at(0) == value_subpackets.at(1);
        return result;
    }

    __builtin_unreachable();

}

void test(const std::string &str) {

    PacketT *root = new PacketT();

    size_t version_sum = 0;
    std::cout << "test " << str << std::endl;
    auto bin = hextobin(str);
    auto *end = parsepaket(bin.data(), bin.data() + bin.size(), version_sum, root);
//    assert(end == bin.data() + bin.size());
    std::cout << "--- SUM  " << version_sum << std::endl;
    std::cout << "--- VALUE  " << evaluate(root) << std::endl;
}


int _16() {
//    test("D2FE28");
//    test("38006F45291200");
//    test("EE00D40C823060");
//    test("8A004A801A8002F478");
//    test("620080001611562C8802118E34");
//    test("C0015000016115A2E0802F182340");
//    test("A0016C880162017C3686B18A3D4780");

    test(input);
    return 0;
}
