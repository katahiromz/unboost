// regex.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_REGEX
#include <unboost.hpp>

int main(void) {
    std::cout << "regex" << std::endl;

    std::vector<std::string> items;
    items.push_back("foo.txt");
    items.push_back("bar.txt");
    items.push_back("baz.dat");
    items.push_back("zoidberg");

    using unboost::regex;
    regex target_regex("[a-z]+\\.txt");

    assert(regex_match(items[0], target_regex));
    assert(regex_match(items[1], target_regex));
    assert(regex_match(items[2], target_regex));
    assert(!regex_match(items[3], target_regex));

    return 0;
}
