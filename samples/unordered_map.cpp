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
