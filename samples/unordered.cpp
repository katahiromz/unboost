// unordered.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <unordered_set>
    #include <unordered_map>
#elif defined(BOOST)
    #include <boost/unordered_set.hpp>
    #include <boost/unordered_map.hpp>
#else   // Unboost
    #include <unboost/unordered_set.hpp>
    #include <unboost/unordered_map.hpp>
#endif

int main(void) {
    std::cout << "unorderd set" << std::endl;

#ifdef CXX11
    using std::unordered_set;
    using std::unordered_map;
#elif defined(BOOST)
    using boost::unordered_set;
    using boost::unordered_map;
#else   // Unboost
    using unboost::unordered_set;
    using unboost::unordered_map;
#endif

    unordered_set<int> us;
    us.insert(1);
    us.insert(2);
    {
        unordered_set<int>::iterator it, end = us.end();
        for (it = us.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }
    assert(us.count(1) == 1);
    assert(us.count(2) == 1);
    assert(us.count(3) == 0);

    std::cout << "unorderd map" << std::endl;

    unordered_map<int, int> um;
    um.insert(std::make_pair(2, 3));
    um.insert(std::make_pair(4, 5));
    {
        unordered_map<int, int>::iterator it, end = um.end();
        for (it = um.begin(); it != end; ++it) {
            std::cout << it->first << ", " << it->second << std::endl;
        }
    }
    assert(um.count(2) == 1);
    assert(um.count(4) == 1);
    assert(um.count(5) == 0);
    std::cout << "success" << std::endl;

    return 0;
}
