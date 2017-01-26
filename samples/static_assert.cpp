// static_assert.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    //
#elif defined(BOOST)
    #include <boost/static_assert.hpp>
#else   // Unboost
    #include <unboost/static_assert.hpp>
#endif

#include <iostream>
#include <cassert>

#ifdef CXX11
    static_assert(1, "OK");
    //static_assert(0, "NG");
#elif defined(BOOST)
    BOOST_STATIC_ASSERT_MSG(1, "OK");
    //BOOST_STATIC_ASSERT_MSG(0, "NG");
#else   // Unboost
    UNBOOST_STATIC_ASSERT_MSG(1, "OK");
    //UNBOOST_STATIC_ASSERT_MSG(0, "NG");
#endif

int main(void) {
    std::cout << "static_assert" << std::endl;
    // does nothing
    return 0;
}
