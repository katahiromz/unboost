// ilist.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <list>

#ifdef CXX11
    #include <initializer_list>
#else   // Unboost
    #include <unboost/ilist.hpp>
#endif  // Unboost

#ifdef CXX11
    std::vector<std::string> strs = {
        "test1",
        "test2",
        "test3"
    };
#else   // Unboost
    UNBOOST_ILIST_DEFINE(std::string, strs_contents) = {
        "test1",
        "test2",
        "test3"
    };
    std::vector<std::string> strs;
    UNBOOST_ILIST_INIT(strs, strs_contents);
#endif  // Unboost

int main(void) {
    std::cout << "ilist" << std::endl;

    assert(strs[0] == "test1");
    assert(strs[1] == "test2");
    assert(strs[2] == "test3");
    assert(strs.size() == 3);

#ifdef CXX11
    strs = {
        "new_value1", "new_value2"
    };
#else   // Unboost
    UNBOOST_ILIST_DEFINE(std::string, strs_new_contents) = {
        "new_value1", "new_value2"
    };
    UNBOOST_ILIST_ASSIGN(strs, strs_new_contents);
#endif  // Unboost

    assert(strs[0] == "new_value1");
    assert(strs[1] == "new_value2");
    assert(strs.size() == 2);

    std::cout << "success" << std::endl;

    return 0;
} // main
