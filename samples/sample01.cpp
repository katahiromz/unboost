// sample01.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_SMART_PTR
#include "unboost.hpp"

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "smart ptr" << std::endl;
    unboost::shared_ptr<int> sp1;
    unboost::shared_ptr<int> sp2(new int(3));
    sp1 = sp2;
    std::cout << sp1.use_count() << std::endl;
    std::cout << *sp1 << std::endl;
    sp2.reset();
    std::cout << sp1.use_count() << std::endl;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////
