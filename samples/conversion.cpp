// conversion.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_CONVERSION
#include <unboost.hpp>

int main(void) {
    std::cout << "conversion" << std::endl;
    std::cout << unboost::to_string(unboost::stoi("2016")).c_str() << std::endl;
    assert(unboost::to_string(unboost::stoi("2016")) == "2016");
    assert(unboost::stod("999.99999999999999999999999") == 999.99999999999999999999999);
#ifndef __WATCOMC__
    assert(unboost::stoull("100000000000000") == 100000000000000);
#endif
    assert(unboost::lexical_cast<int>(1.2) == 1);
    std::cout << "success" << std::endl;
    return 0;
}
