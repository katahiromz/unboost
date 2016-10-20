// conversion.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_CONVERSION
#include <unboost.hpp>

int main(void) {
    std::cout << "conversion" << std::endl;
    assert(unboost::to_string(unboost::stoi("2016")) == "2016");
    assert(unboost::stod("999.99999999999999999999999") == 999.99999999999999999999999);
    assert(unboost::stoull("100000000000000") == 100000000000000ULL);
    return 0;
}
