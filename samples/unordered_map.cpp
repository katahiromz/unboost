// unordered_map.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <unordered_map>
#elif defined(BOOST)
    #include <boost/unordered_map.hpp>
#else   // Unboost
    #include <unboost/unordered_map.hpp>
#endif

int main(void) {
    std::cout << "unorderd map" << std::endl;

#ifdef CXX11
    using std::unordered_map;
#elif defined(BOOST)
    using boost::unordered_map;
#else   // Unboost
    using unboost::unordered_map;
#endif

    unordered_map<int, int> um1, um2;

    assert(um1.empty());
    assert(um1.size() == 0);

    um1.insert(std::make_pair(2, 3));
    assert(!um1.empty());
    assert(um1.size() == 1);
    assert(um1.at(2) == 3);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 0);
    assert(um1.count(5) == 0);

    um1.insert(std::make_pair(4, 5));
    assert(!um1.empty());
    assert(um1.size() == 2);
    assert(um1.at(2) == 3);
    assert(um1.at(4) == 5);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 1);
    assert(um1.count(5) == 0);

    um1.emplace(4, 6);
    assert(!um1.empty());
    assert(um1.size() == 2);
    assert(um1.at(2) == 3);
    assert(um1.at(4) == 5);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 1);
    assert(um1.count(5) == 0);

    assert(um2.empty());

    um2 = um1;
    um1.clear();
    assert(um1.empty());
    assert(um1.size() == 0);

    assert(!um2.empty());
    assert(um2.size() == 2);
    assert(um2.at(2) == 3);
    assert(um2.at(4) == 5);
    assert(um2.count(2) == 1);
    assert(um2.count(4) == 1);
    assert(um2.count(5) == 0);

    um1.swap(um2);
    assert(um1.size() == 2);
    assert(um1.find(2) != um1.end());
    assert(um1.find(3) == um1.end());
    assert(um1.find(4) != um1.end());
    assert(um2.empty());

    {
        unordered_map<int, int>::iterator it, end = um1.end();
        for (it = um1.begin(); it != end; ++it) {
            std::cout << it->first << ", " << it->second << std::endl;
        }
    }

    std::cout << "success" << std::endl;

    return 0;
} // main
