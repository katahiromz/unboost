// for_each.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_FOREACH
#include <unboost.hpp>

int main(void) {
    std::cout << "foreach" << std::endl;
    {
        std::vector<int> v;
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        UNBOOST_FOREACH(int& i, v) {
            i -= 1;
            std::cout << i << std::endl;
        }
        UNBOOST_FOREACH(int i, v) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
