#pragma once 
#include<random>
#include<algorithm>
#include<vector>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

/* char map class */
class char_map{
public:
    char_map(char c):map_(){ map_[(int)(c)] = 1;}

    uint &operator[] (const int index) { return map_[index]; } 
    const uint &operator[] (const int index) const { return map_[index]; } 
    uint &operator[] (const char c) { return map_[(int)(c)]; } 
    const uint &operator[] (const char c) const { return map_[(int)(c)]; } 

    void get_most_freq_chars(std::vector<char>& chars) const {
        uint most_freq_ch = *std::max_element(map_, map_+256);
        chars.clear();
        for (int i = 0; i < 256; ++i) {
            if (map_[i] == most_freq_ch) chars.emplace_back((char)(i));
        }
    }
private:
    uint map_[256];  // 2^8
};

// end of file 