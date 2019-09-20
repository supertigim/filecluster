#pragma once 
#include "utils.hpp"

// String class for K-Mean Clustering  
class string_for_kmean {
public:
    string_for_kmean() {}
    string_for_kmean(const std::string& str) {operator = (str);}

    void add(const std::string& str) ;
    void trim(const size_t len);
    std::string str() const;

    void operator = (const std::string& str);
    void operator = (const string_for_kmean& other) { char_map_list_= other.char_map_list_;str_=other.str_; }
private:
    std::string str_mean_of_characters_() const;
    std::string str_most_freq_chars_() const;

private:
    std::vector<char_map> char_map_list_;
    mutable std::string str_;
};

// end of file