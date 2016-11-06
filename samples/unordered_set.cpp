// unordered_set.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cassert>

#ifdef CXX11
    #include <unordered_set>
#elif defined(BOOST)
    #include <boost/unordered_set.hpp>
#else   // Unboost
    #include <unboost/unordered_set.hpp>
#endif

int main(void) {
    std::cout << "unorderd_set" << std::endl;

#ifdef CXX11
    using std::unordered_set;
#elif defined(BOOST)
    using boost::unordered_set;
#else   // Unboost
    using unboost::unordered_set;
#endif

    unordered_set<int> usi1;
    unordered_set<int> usi2;
    unordered_set<std::string> uss;

    assert(usi1.empty());
    assert(usi1.size() == 0);
    assert(usi1.find(1) == usi1.end());

    usi1.insert(1);
    assert(usi1.size() == 1);
    assert(usi1.find(1) != usi1.end());
    assert(usi1.count(1) == 1);

    usi1.emplace(2);
    assert(usi1.size() == 2);
    assert(usi1.find(2) != usi1.end());
    assert(usi1.count(2) == 1);

    {
        unordered_set<int>::iterator it, end = usi1.end();
        for (it = usi1.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }

    std::cout << "#" << usi1.count(1) << std::endl;
    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 1);
    assert(usi1.count(3) == 0);
    usi1.rehash(10);

    std::cout << "#" << usi1.count(1) << std::endl;
    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 1);
    assert(usi1.count(3) == 0);

    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) != usi1.end());
    assert(usi1.find(3) == usi1.end());

    usi1.clear();
    assert(usi1.empty());
    assert(usi1.size() == 0);

    usi1.emplace(1);
    usi1.emplace(2);
    usi1.emplace(2);

    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 1);
    assert(usi1.count(3) == 0);

    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) != usi1.end());
    assert(usi1.find(3) == usi1.end());
    assert(usi1.size() == 2);

    usi2 = usi1;

    assert(usi2.count(1) == 1);
    assert(usi2.count(2) == 1);
    assert(usi2.count(3) == 0);

    assert(usi2.find(1) != usi1.end());
    assert(usi2.find(2) != usi1.end());
    assert(usi2.find(3) == usi1.end());
    assert(usi2.size() == 2);

    usi1.erase(2);
    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) == usi1.end());
    assert(usi1.find(3) == usi1.end());
    assert(usi1.size() == 1);

    usi1.erase(1);
    assert(usi1.find(1) == usi1.end());
    assert(usi1.find(2) == usi1.end());
    assert(usi1.find(3) == usi1.end());

    assert(usi1.empty());
    assert(usi1.size() == 0);

    uss.emplace("1");
    uss.emplace("2");
    uss.emplace("2");
    assert(uss.find("1") != uss.end());
    assert(uss.find("2") != uss.end());
    assert(uss.find("3") == uss.end());
    assert(uss.count("1") == 1);
    assert(uss.count("2") == 1);
    assert(uss.count("3") == 0);

    uss.erase("2");
    uss.emplace("3");
    assert(uss.find("1") != uss.end());
    assert(uss.find("2") == uss.end());
    assert(uss.find("3") != uss.end());
    assert(uss.count("1") == 1);
    assert(uss.count("2") == 0);
    assert(uss.count("3") == 1);

    std::cout << "success" << std::endl;

    return 0;
} // main
