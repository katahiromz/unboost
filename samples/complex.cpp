// complex.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <complex>
#elif defined(BOOST)
    #include <boost/math/complex.hpp>
#else
    #include <unboost/math/complex.hpp>
#endif

int main(void) {
    std::cout << "complex functions" << std::endl;

#ifdef CXX11
    std::cout << std::asin(std::complex<double>(2, 3)).real() << std::endl;
#elif defined(BOOST)
    std::cout << boost::math::asin(std::complex<double>(2, 3)).real() << std::endl;
#else
    std::cout << unboost::math::asin(std::complex<double>(2, 3)).real() << std::endl;
#endif

    return 0;
}
