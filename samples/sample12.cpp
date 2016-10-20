#define UNBOOST_USE_ARRAY
#include <unboost.hpp>

int main(void) {
    std::cout << "array" << std::endl;
    unboost::array<int, 2> a = {2, 3};
    std::cout << a[0] << std::endl;
    std::cout << a[1] << std::endl;
    return 0;
}
