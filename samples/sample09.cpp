#define UNBOOST_USE_CONVERSION
#include <unboost.hpp>

int main(void) {
    std::cout << "conversion" << std::endl;
    std::cout << unboost::to_string(unboost::stoi("2016")) << std::endl;
    std::cout << unboost::stod("999.99999999999999999999999") << std::endl;
    std::cout << unboost::stoull("100000000000000") << std::endl;
    return 0;
}
