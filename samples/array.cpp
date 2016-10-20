// array.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_ARRAY
#include <unboost.hpp>

int main(void) {
    std::cout << "array" << std::endl;
    unboost::array<int, 2> a = {2, 3};
    assert(a[0] == 2);
    assert(a[1] == 3);
    assert(a.size() == 2);
    assert(sizeof(a) == 2 * sizeof(int));
    std::cout << "success" << std::endl;
    return 0;
}
