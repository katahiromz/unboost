// ratio.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <ratio>
#elif defined(BOOST)
    #include <boost/ratio.hpp>
#else   // Unboost
    #include <unboost/ratio.hpp>
#endif

int main(void) {
    std::cout << "ratio" << std::endl;

#ifdef CXX11
    using std::ratio;
    using std::ratio_add;
    using std::ratio_subtract;
    using std::ratio_multiply;
    using std::ratio_divide;
    using std::ratio_equal;
    using std::ratio_less;
#elif defined(BOOST)
    using boost::ratio;
    using boost::ratio_add;
    using boost::ratio_subtract;
    using boost::ratio_multiply;
    using boost::ratio_divide;
    using boost::ratio_equal;
    using boost::ratio_less;
#else   // Unboost
    using unboost::ratio;
    using unboost::ratio_add;
    using unboost::ratio_subtract;
    using unboost::ratio_multiply;
    using unboost::ratio_divide;
    using unboost::ratio_equal;
    using unboost::ratio_less;
#endif  // Unboost

    assert((ratio<7, -21>::num == -1));
    assert((ratio<7, -21>::den == 3));

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
} // main
