// static_assert.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_STATIC_ASSERT
#include <unboost.hpp>

static_assert(1, "OK");
//static_assert(0, "NG");

int main(void) {
    std::cout << "static_assert" << std::endl;
    // does nothing
    return 0;
}
