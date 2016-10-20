#define UNBOOST_USE_REGEX
#include <unboost.hpp>

int main(void) {
    std::cout << "regex" << std::endl;

    std::vector<std::string> fnames;
    fnames.push_back("foo.txt");
    fnames.push_back("bar.txt");
    fnames.push_back("baz.dat");
    fnames.push_back("zoidberg");
    using unboost::regex;
    regex txt_regex("[a-z]+\\.txt");
 
    for (size_t i = 0; i < fnames.size(); ++i) {
        using namespace unboost;
        std::string& fname = fnames[i];
        std::cout << fname << ": " << regex_match(fname, txt_regex) << '\n';
    }

    return 0;
}
