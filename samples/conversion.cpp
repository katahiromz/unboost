// conversion.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <string>
#elif defined(BOOST)
    #include <boost/exception/to_string.hpp>
#else
    #include <unboost/exception/to_string.hpp>
#endif

int main(void) {
    std::cout << "conversion" << std::endl;

#ifdef CXX11
    assert(std::to_string(2016) == "2016");
#elif defined(BOOST)
    assert(boost::to_string(2016) == "2016");
#else
    assert(unboost::to_string(2016) == "2016");
#endif

    std::cout << "success" << std::endl;
    return 0;
}
