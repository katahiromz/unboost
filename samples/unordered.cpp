// unordered_set.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <unordered_set>
#elif defined(BOOST)
    #include <boost/unordered_set.hpp>
#else   // Unboost
    #include <unboost/unordered_set.hpp>
#endif

int main(void) {
    std::cout << "unorderd set" << std::endl;

#ifdef CXX11
    using std::unordered_set;
#elif defined(BOOST)
    using boost::unordered_set;
#else   // Unboost
    using unboost::unordered_set;
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

    return 0;
}
