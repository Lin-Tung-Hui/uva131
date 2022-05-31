#include <cstring>
#include <string.h>
#include <stack>
#include <deque>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <algorithm>
#include <vector>

//（C=Clubs, D=Diamonds, H=Hearts, S=Spades）
enum Flush {
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

struct Poker {
    Flush flush;
    int number;
};

// straight_flush > four_of_a_kind > full_house > flush > straight > three_of_a_kind > two_pairs > one_pair > high_card
std::string poker_hand[9] = {
    "straight-flush",
    "four-of-a-kind",
    "full-house",
    "flush",
    "straight",
    "three-of-a-kind",
    "two-pairs",
    "one-pair",
    "highest-card"
};

std::vector< Poker > sort_porkers(std::stringstream &ss)
{
    std::vector< Poker > pokers;
    for (int i = 0; i < 10; i++) {
        std::string str;
        ss >> str;
        struct Poker myPoker;
        if (str.compare(0, 1, "A") == 0) {
            myPoker.number = 1;
        } else if (str.compare(0, 1, "T") == 0) {
            myPoker.number = 10;
        } else if (str.compare(0, 1, "J") == 0) {
            myPoker.number = 11;
        } else if (str.compare(0, 1, "Q") == 0) {
            myPoker.number = 12;
        } else if (str.compare(0, 1, "K") == 0) {
            myPoker.number = 13;
        } else {
            myPoker.number = std::stoi(str.substr(0, 1));
        }

        if (str.compare(1, 1, "C") == 0) {
            myPoker.flush = Clubs;
        } else if (str.compare(1, 1, "D") == 0) {
            myPoker.flush = Diamonds;
        } else if (str.compare(1, 1, "H") == 0) {
            myPoker.flush = Hearts;
        } else {
            myPoker.flush = Spades;
        }
        pokers.push_back(myPoker);
    }

    return pokers;
}

bool is_straight(int num[])
{
    bool flag;
    for (int i = 1; i < 10; i++) {
        if (num[i] > 1)
            return false;
        if (num[i] == 1) {
            flag = true;
            for (int j = 1; j < 5; j++) {
                if (num[i + j] != 1) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return true;
        }
    }
    if (num[10] == 1 && num[11] == 1 && num[12] == 1 && num[13] == 1 && num[1] == 1)
        return true;
    return false;
}

// straight_flush > four_of_a_kind > full_house > flush > straight > three_of_a_kind > two_pairs > one_pair > high_card
int find_best_hand(std::vector< Poker > &pokers, int cur)
{

    int poker_number[16];
    int poker_suit[8];
    int change_hand_card[8];

    memset(change_hand_card, 0, sizeof(change_hand_card));
    memset(poker_number, 0, sizeof(poker_number));
    memset(poker_suit, 0, sizeof(poker_suit));
    int base_two[] = { 16, 8, 4, 2, 1 };

    for (int i = 0; i < 5; i++) {
        if (cur / base_two[i])
            change_hand_card[i] = 0;
        else
            change_hand_card[i] = 1;
        cur %= base_two[i];
    }

    int cnt = 0;
    for (int i = 0; cnt < 5; i++) {
        if (!change_hand_card[i]) {
            poker_number[pokers[i].number]++;
            poker_suit[pokers[i].flush]++;
            cnt++;
        }
    }

    int max_same_number = 0;
    int different_number = 0;

    for (int i = 1; i < 14; i++) {
        if (poker_number[i] > max_same_number)
            max_same_number = poker_number[i];
        if (poker_number[i])
            different_number++;
    }

    int number_color = 0;
    for (int i = 0; i < 4; i++) {
        if (poker_suit[i])
            number_color++;
    }

    bool link = is_straight(poker_number);

    if (number_color == 1 && link)
        return 0;
    if (max_same_number == 4)
        return 1;
    if (max_same_number == 3 && different_number == 2)
        return 2;
    if (number_color == 1)
        return 3;
    if (link)
        return 4;
    if (max_same_number == 3)
        return 5;
    if (max_same_number == 2 && different_number == 3)
        return 6;
    if (max_same_number == 2)
        return 7;
    return 8;
}

void uva131(std::istream &is, std::ostream &os)
{
    while (true) {
        std::string line;
        std::getline(is, line);
        if (line == "")
            break;
        std::stringstream ss;
        ss << line;
        std::vector< Poker > my_pokers = sort_porkers(ss);

        int best_hand = 9;
        for (int i = 0; i < 32; i++) {
            int tmp_best_hand = find_best_hand(my_pokers, i);
            if (tmp_best_hand < best_hand)
                best_hand = tmp_best_hand;
        }
        os << "Hand: " << line.substr(0, 15) << "Deck: " << line.substr(15, 30) << " Best hand: " << poker_hand[best_hand] << std::endl;
    }
}

int main(int argc, char **argv)
{

#ifdef GTEST
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    //    uva131(iss, std::cout);
    uva131(std::cin, std::cout);
#endif
    return 0;
}
