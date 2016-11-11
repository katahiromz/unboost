// for_each.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <cassert>

#ifdef CXX11
    //
#elif defined(BOOST)
    #include <boost/foreach.hpp>
#else   // Unboost
    #include <unboost/foreach.hpp>
#endif

int main(void) {
    std::cout << "foreach" << std::endl;
    {
        std::vector<int> v;
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
#ifdef CXX11
        for (int& i : v) {
            i -= 1;
            std::cout << i << std::endl;
        }
        for (int i : v) {
            std::cout << i << std::endl;
        }
#elif defined(BOOST)
        BOOST_FOREACH(int& i, v) {
            i -= 1;
            std::cout << i << std::endl;
        }
        BOOST_FOREACH(int i, v) {
            std::cout << i << std::endl;
        }
#else   // Unboost
        UNBOOST_FOREACH(int& i, v) {
            i -= 1;
            std::cout << i << std::endl;
        }
        UNBOOST_FOREACH(int i, v) {
            std::cout << i << std::endl;
        }
#endif  // Unboost
    }
    return 0;
}
