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

    unordered_set<int> us(1);

    assert(us.empty());
    assert(us.size() == 0);
    assert(us.find(1) == us.end());

    us.insert(1);
    assert(us.size() == 1);
    assert(us.find(1) != us.end());
    assert(us.count(1) == 1);

    us.emplace(2);
    assert(us.size() == 2);
    assert(us.find(2) != us.end());
    assert(us.count(2) == 1);

    {
        unordered_set<int>::iterator it, end = us.end();
        for (it = us.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }

    std::cout << "#" << us.count(1) << std::endl;
    assert(us.count(1) == 1);
    assert(us.count(2) == 1);
    assert(us.count(3) == 0);
    us.rehash(10);

    std::cout << "#" << us.count(1) << std::endl;
    assert(us.count(1) == 1);
    assert(us.count(2) == 1);
    assert(us.count(3) == 0);

    assert(us.find(1) != us.end());
    assert(us.find(2) != us.end());
    assert(us.find(3) == us.end());

    us.clear();
    assert(us.empty());
    assert(us.size() == 0);

    us.emplace(1);
    us.emplace(2);

    assert(us.count(1) == 1);
    assert(us.count(2) == 1);
    assert(us.count(3) == 0);

    assert(us.find(1) != us.end());
    assert(us.find(2) != us.end());
    assert(us.find(3) == us.end());
    assert(us.size() == 2);

    us.erase(2);
    assert(us.find(1) != us.end());
    assert(us.find(2) == us.end());
    assert(us.find(3) == us.end());
    assert(us.size() == 1);

    us.erase(1);
    assert(us.find(1) == us.end());
    assert(us.find(2) == us.end());
    assert(us.find(3) == us.end());

    assert(us.empty());
    assert(us.size() == 0);

    std::cout << "success" << std::endl;

    return 0;
} // main
