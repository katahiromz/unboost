#define UNBOOST_USE_ASSERT
#define UNBOOST_USE_STATIC_ASSERT
#include <boost.hpp>

static_assert(1, "OK");
//static_assert(0, "NG");

int main(void) {
    std::cout << "assertion" << std::endl;
    UNBOOST_ASSERT(1);
    UNBOOST_ASSERT_MSG(1, "OK");
    UNBOOST_ASSERT_MSG(0, "NG");
    return 0;
}
