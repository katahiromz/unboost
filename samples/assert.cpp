// assert.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <cassert>
#elif defined(BOOST)
    #include <boost/assert.hpp>
#else
    #include <unboost/assert.hpp>
#endif

int main(void) {
    std::cout << "assert" << std::endl;

#ifdef CXX11
    assert(1);
    assert(0);
#elif defined(BOOST)
    BOOST_ASSERT(1);
    BOOST_ASSERT(0);
#else
    UNBOOST_ASSERT(1);
    UNBOOST_ASSERT(0);
#endif

    return 0;
}
