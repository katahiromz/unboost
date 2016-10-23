// ratio.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_RATIO
#include <unboost.hpp>

int main(void) {
    std::cout << "ratio" << std::endl;

    using namespace unboost;

    assert((ratio<3, 12>::num == 1));
    assert((ratio<3, 12>::den == 4));

    typedef ratio<2, 3> two_third;
    typedef ratio<1, 6> one_sixth;

    typedef ratio_add<two_third, one_sixth> sum;    // 5/6
    assert(sum::num == 5);
    assert(sum::den == 6);

    typedef ratio_subtract<two_third, one_sixth> diff;  // 1/2
    assert(diff::num == 1);
    assert(diff::den == 2);

    typedef ratio_multiply<two_third, one_sixth> prod;  // 1/9
    assert(prod::num == 1);
    assert(prod::den == 9);

    typedef ratio_divide<two_third, one_sixth> quot;    // 4/1
    assert(quot::num == 4);
    assert(quot::den == 1);

    typedef ratio_equal<two_third, two_third> eq;
    assert(eq::value);

    typedef ratio_equal<two_third, one_sixth> neq;
    assert(!neq::value);

    typedef ratio_less<ratio<23,37>, ratio<57,90> > less;
    assert(less::value);

    std::cout << "success" << std::endl;
    return 0;
}
