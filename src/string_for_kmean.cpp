#include "string_for_kmean.hpp"

void string_for_kmean::add(const std::string& str) {
    size_t i = 0;
    str_.clear();
    for (;i < char_map_list_.size() && i < str.size(); ++i) {
        char_map_list_[i][str[i]] += 1;
    }
    if (str.size() == i) return;
    for (; i < str.size(); ++i) {
        char_map_list_.emplace_back(char_map(str[i]));
    }
}

void string_for_kmean::trim(const size_t len) {
    str_.clear();
    while (char_map_list_.size()>len) {
        char_map_list_.pop_back();
    }
}

inline std::string string_for_kmean::str_mean_of_characters_() const {
    if (str_.size()) return str_;
    for (auto& c_m: char_map_list_) {
        float tmp = 0.0;
        int add_num = 0;
        for(int i = 0; i < 256; ++i) {
            add_num += c_m[i];
            tmp += (float)(i*c_m[i])/100.0;
        }
        str_ += (char)((int)(tmp*100.0/(float)(add_num)+0.5)%256);
    }
    return str_;
}
    
inline std::string string_for_kmean::str_most_freq_chars_() const {
    if (str_.size()) return str_;
    for (auto& c_m: char_map_list_) {
        std::vector<char> chars;
        c_m.get_most_freq_chars(chars);
        str_ += *select_randomly(chars.begin(), chars.end()); // random selection among chars
    }
    return str_;
}

std::string string_for_kmean::str() const {
    return str_most_freq_chars_();
    //return str_mean_of_characters_(); // doesn't make sense 
}

void string_for_kmean::operator = (const std::string& str) {
    if (str.size() == 0) return;
    str_.clear();
    char_map_list_.clear();
    char_map_list_.reserve(str.size());
    for (auto& c: str) {
        char_map_list_.emplace_back(char_map(c));
    }
}

// end of file