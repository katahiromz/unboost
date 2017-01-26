// array.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <array>
#elif defined(BOOST)
    #include <boost/array.hpp>
#else
    #include <unboost/array.hpp>
#endif

#include <iostream>
#include <cassert>

int main(void) {
    std::cout << "array" << std::endl;

#ifdef CXX11
    std::array<int, 2> a = {{2, 3}};
#elif defined(BOOST)
    boost::array<int, 2> a = {{2, 3}};
#else
    unboost::array<int, 2> a = {{2, 3}};
#endif

    assert(a[0] == 2);
    assert(a[1] == 3);
    assert(a.size() == 2);
    assert(sizeof(a) == 2 * sizeof(int));

    std::cout << "success" << std::endl;
    return 0;
}
