// complex_functions.hpp --- Unboost complex functions
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_COMPLEX_FUNCTIONS_HPP_
#define UNBOOST_COMPLEX_FUNCTIONS_HPP_

#include <cmath>
#include <complex>
#include <unboost/core.hpp>

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_COMPLEX_FUNCTIONS) + defined(UNBOOST_USE_BOOST_COMPLEX_FUNCTIONS)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_COMPLEX_FUNCTIONS
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_COMPLEX_FUNCTIONS
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_COMPLEX_FUNCTIONS
        #else
            #define UNBOOST_USE_BOOST_COMPLEX_FUNCTIONS
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_COMPLEX_FUNCTIONS
    namespace unboost {
        namespace math {
            using std::complex;
            using std::fabs;
            using std::asin;
            using std::acos;
            using std::atan;
            using std::asinh;
            using std::acosh;
            using std::atanh;
        } // namespace math
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_COMPLEX_FUNCTIONS)
    #include <boost/math/complex.hpp>
    namespace unboost {
        namespace math {
            using boost::math::fabs;
            using boost::math::asin;
            using boost::math::acos;
            using boost::math::atan;
            using boost::math::asinh;
            using boost::math::acosh;
            using boost::math::atanh;
        } // namespace math
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_COMPLEX_FUNCTIONS_HPP_
