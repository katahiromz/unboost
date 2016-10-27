// regex.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <regex>
#elif defined(BOOST)
    #include <boost/regex.hpp>
#else   // Unboost
    #include <unboost/regex.hpp>
#endif

int main(void) {
    std::cout << "regex" << std::endl;

    std::vector<std::string> items;
    items.push_back("foo.txt");
    items.push_back("bar.txt");
    items.push_back("baz.dat");
    items.push_back("zoidberg");

#ifdef CXX11
    using std::regex;
    using std::regex_match;
#elif defined(BOOST)
    using boost::regex;
    using boost::regex_match;
#else   // Unboost
    using unboost::regex;
    using unboost::regex_match;
#endif

    regex target_regex("[a-z]+\\.txt");

    assert(regex_match(items[0], target_regex));
    assert(regex_match(items[1], target_regex));
    assert(!regex_match(items[2], target_regex));
    assert(!regex_match(items[3], target_regex));

    std::cout << "success" << std::endl;

    return 0;
}
