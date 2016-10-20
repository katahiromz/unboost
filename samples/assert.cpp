// assert.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_ASSERT
#include <unboost.hpp>

int main(void) {
    std::cout << "assert" << std::endl;
    UNBOOST_ASSERT(1);
    UNBOOST_ASSERT(0);
    return 0;
}
