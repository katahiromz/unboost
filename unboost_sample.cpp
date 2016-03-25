// unboost_sample.cpp --- Unboost sample
// This file is public domain software (PDS).
//////////////////////////////////////////////////////////////////////////////

#include "unboost.hpp"

#include <iostream>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

static_assert(1, "OK");
//static_assert(0, "NG");

int main(void) {
    unboost::shared_ptr<int> spi = unboost::make_shared<int>(2);
    unboost::unique_ptr<int> upi(new int(2));
    unboost::thread t;
    unboost::array<int,2> a;

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

    std::cout << unboost::math::asin(std::complex<int>(2, 3)) << std::endl;

    return 0;
} // main

//////////////////////////////////////////////////////////////////////////////
