// complex.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_COMPLEX_FUNCTIONS
#include <unboost.hpp>

int main(void) {
    std::cout << "complex functions" << std::endl;
    std::cout << unboost::math::asin(std::complex<double>(2, 3)).real() << std::endl;
    return 0;
}
