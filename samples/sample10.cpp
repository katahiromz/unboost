#define UNBOOST_USE_RATIO
#include <unboost.hpp>

int main(void) {
    std::cout << "ratio" << std::endl;

    std::cout << unboost::ratio<7,-21>::num << std::endl;   // 7;
    std::cout << unboost::ratio<7,-21>::den << std::endl;   // -21;

    typedef unboost::ratio<2, 3> two_third;
    typedef unboost::ratio<1, 6> one_sixth;

    typedef unboost::ratio_add<two_third, one_sixth> sum;
    std::cout << sum::num << "/" << sum::den << std::endl;  // 5/6

    typedef unboost::ratio_subtract<two_third, one_sixth> diff;
    std::cout << diff::num << '/' << diff::den << std::endl;    // 1/2

    typedef unboost::ratio_multiply<two_third, one_sixth> prod;
    std::cout << prod::num << '/' << prod::den << std::endl;    // 1/9

    typedef unboost::ratio_divide<two_third, one_sixth> quot;
    std::cout << quot::num << '/' << quot::den << std::endl;    // 4/1

    typedef unboost::ratio_equal<two_third, two_third> eq;
    typedef unboost::ratio_equal<two_third, one_sixth> neq;
    std::cout << "eq: " << eq() << std::endl;
    std::cout << "neq: " << neq() << std::endl;

    std::cout << "less: " <<
        unboost::ratio_less<unboost::ratio<23,37>,
                            unboost::ratio<57,90> >::value << std::endl;

    return 0;
}
