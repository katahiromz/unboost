// static_assert.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_STATIC_ASSERT
#include <unboost.hpp>

UNBOOST_STATIC_ASSERT_MSG(1, "OK");
//UNBOOST_STATIC_ASSERT_MSG(0, "NG");

int main(void) {
    std::cout << "static_assert" << std::endl;
    // does nothing
    return 0;
}
