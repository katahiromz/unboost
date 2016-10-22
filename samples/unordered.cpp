// unordered.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_UNORDERED_SET
#define UNBOOST_USE_UNORDERED_MAP
#include <unboost.hpp>

int main(void) {
    std::cout << "unorderd set" << std::endl;
    unboost::unordered_set<int> us;
    us.insert(1);
    us.insert(2);
    {
        unboost::unordered_set<int>::iterator it, end = us.end();
        for (it = us.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }
    assert(us.count(1) == 1);
    assert(us.count(2) == 1);
    assert(us.count(3) == 0);

    std::cout << "unorderd map" << std::endl;
    unboost::unordered_map<int, int> um;
    um.insert(std::make_pair(2, 3));
    um.insert(std::make_pair(4, 5));
    {
        unboost::unordered_map<int, int>::iterator it, end = um.end();
        for (it = um.begin(); it != end; ++it) {
            std::cout << it->first << ", " << it->second << std::endl;
        }
    }
    assert(um.count(2) == 1);
    assert(um.count(4) == 1);
    assert(um.count(5) == 0);
    std::cout << "success" << std::endl;

    return 0;
}
