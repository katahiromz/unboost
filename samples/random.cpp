#define UNBOOST_USE_RANDOM
#include <unboost.hpp>

int main(void) {
    std::cout << "random" << std::endl;
    {
        using namespace unboost::random;
        mt19937 engine;
        uniform_int_distribution<int> distribution(1, 6);
        for (int i = 0; i < 5; ++i) {
            std::cout << distribution(engine) << std::endl;
        }
    }
    return 0;
}
