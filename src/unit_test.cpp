#include <iostream>
#include "kmeans.hpp"
#include "jaroWinkler.hpp"
#include "unit_test.hpp"

void test_jaro_winkler_distance(const std::string& s1, const std::string& s2) {
    static int exampleCount(0);
    std::cout
        << "Example " << ++exampleCount << ": "
        << s1 << " vs " << s2 << std::endl
        << "  Jaro distance:         " << jaroDistance(s1, s2) << std::endl
        << "  Jaro-Winkler distance: " << jaroWinklerDistance(s1, s2) << std::endl
        << std::endl
        ;
}

void test_jaro_winkler_distance() {
    std::string s1 = "abcde";
    std::string s2 = "abcde";

    test_jaro_winkler_distance(s1, s2);

    s2 = "vwxyz";
    test_jaro_winkler_distance(s1, s2);

    s1 = "";
    test_jaro_winkler_distance(s1, s2);
}

void test_string_for_kmean() {

    std::string s1 = "DMv2_orna-vm01_EXP_ACCESS_LOG_20170201010000.gz";
    std::string s2 = "DMv2_orna-vm01_EXP_ACCESS_LOG_20170201050000.gz";
    std::string s3 = "9086595421814992952_vx54_EXP_INSTALLED_PATCHES_20030101050000_COMPLETE.gz";
    
    string_for_kmean strkmean(s1);
    std::cout << "orignal:" << s1 << " string vector:" << strkmean.str() << std::endl;
    strkmean.add(s1);
    std::cout << "after adding new string: " << strkmean.str() << std::endl;
    strkmean.add(s3);
    std::cout << "after adding new string again: " << strkmean.str() << std::endl;
    strkmean = s1;
    std::cout << "after replacing it with a new string: " << strkmean.str() << std::endl;
}
// end of file