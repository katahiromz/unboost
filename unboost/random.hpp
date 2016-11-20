// random.hpp --- Unboost random generator
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_RANDOM_HPP_
#define UNBOOST_RANDOM_HPP_

#include "unboost.h"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_RANDOM) + defined(UNBOOST_USE_BOOST_RANDOM)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_RANDOM
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_RANDOM
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_RANDOM
        #elif defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_RANDOM
                #else
                    #define UNBOOST_USE_BOOST_RANDOM
                #endif
            #else
                #define UNBOOST_USE_BOOST_RANDOM
            #endif
        #else
            #define UNBOOST_USE_BOOST_RANDOM
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_RANDOM
    #include <random>
    namespace unboost {
        namespace random {
            using std::random_device;
            using std::minstd_rand0;
            using std::minstd_rand;
            using std::mt19937;
            using std::mt19937_64;
            using std::ranlux24_base;
            using std::ranlux48_base;
            using std::ranlux24;
            using std::ranlux48;
            using std::knuth_b;
            using std::uniform_int_distribution;
            using std::uniform_real_distribution;
            using std::generate_canonical;
            using std::bernoulli_distribution;
            using std::binomial_distribution;
            using std::negative_binomial_distribution;
            using std::geometric_distribution;
            using std::poisson_distribution;
            using std::exponential_distribution;
            using std::gamma_distribution;
            using std::weibull_distribution;
            using std::extreme_value_distribution;
            using std::normal_distribution;
            using std::lognormal_distribution;
            using std::chi_squared_distribution;
            using std::cauchy_distribution;
            using std::fisher_f_distribution;
            using std::student_t_distribution;
            using std::discrete_distribution;
            using std::piecewise_constant_distribution;
            using std::piecewise_linear_distribution;
            using std::seed_seq;
        } // namespace random
        using namespace random;
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_RANDOM)
    #include <boost/random/random_device.hpp>
    #include <boost/random.hpp>
    namespace unboost {
        namespace random {
            using boost::random::random_device;
            using boost::random::minstd_rand0;
            using boost::random::minstd_rand;
            using boost::random::mt19937;
            using boost::random::mt19937_64;
            using boost::random::ranlux24_base;
            using boost::random::ranlux48_base;
            using boost::random::ranlux24;
            using boost::random::ranlux48;
            using boost::random::knuth_b;
            using boost::random::uniform_int_distribution;
            using boost::random::uniform_real_distribution;
            using boost::random::generate_canonical;
            using boost::random::bernoulli_distribution;
            using boost::random::binomial_distribution;
            using boost::random::negative_binomial_distribution;
            using boost::random::geometric_distribution;
            using boost::random::poisson_distribution;
            using boost::random::exponential_distribution;
            using boost::random::gamma_distribution;
            using boost::random::weibull_distribution;
            using boost::random::extreme_value_distribution;
            using boost::random::normal_distribution;
            using boost::random::lognormal_distribution;
            using boost::random::chi_squared_distribution;
            using boost::random::cauchy_distribution;
            using boost::random::fisher_f_distribution;
            using boost::random::student_t_distribution;
            using boost::random::discrete_distribution;
            using boost::random::piecewise_constant_distribution;
            using boost::random::piecewise_linear_distribution;
            using boost::random::seed_seq;
        } // namespace random
        using namespace random;
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_RANDOM_HPP_
