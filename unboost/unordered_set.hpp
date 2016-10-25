// unordered_set.hpp --- Unboost unordered_set and unordered_multiset
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_UNORDERED_SET_HPP_
#define UNBOOST_UNORDERED_SET_HPP_

#include "unboost.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_UNORDERED_SET) + defined(UNBOOST_USE_TR1_UNORDERED_SET) + defined(UNBOOST_USE_BOOST_UNORDERED_SET)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_UNORDERED_SET
    #elif defined(UNBOOST_USE_TR1)
        #define UNBOOST_USE_TR1_UNORDERED_SET
    #else
        #if defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_UNORDERED_SET
                #else
                    #ifndef UNBOOST_NO_TR1
                        #define UNBOOST_USE_TR1_UNORDERED_SET
                    #else
                        #define UNBOOST_USE_BOOST_UNORDERED_SET
                    #endif
                #endif
            #elif (_MSC_VER >= 1500)
                // Visual C++ 2008
                #ifndef UNBOOST_NO_TR1
                    #define UNBOOST_USE_TR1_UNORDERED_SET
                #else
                    #define UNBOOST_USE_BOOST_UNORDERED_SET
                #endif
            #else
                #define UNBOOST_USE_BOOST_UNORDERED_SET
            #endif
        #elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
            // GCC 4.3 and later
            #ifndef UNBOOST_NO_TR1
                #define UNBOOST_USE_TR1_UNORDERED_SET
            #else
                #define UNBOOST_USE_BOOST_UNORDERED_SET
            #endif
        #else
            #define UNBOOST_USE_BOOST_UNORDERED_SET
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_UNORDERED_SET
    #include <unordered_set>            // for std::unordered_set, ...
    namespace unboost {
        using std::unordered_set;
        using std::unordered_multiset;
    }
#elif defined(UNBOOST_USE_TR1_UNORDERED_SET)
    #ifdef _MSC_VER
        #include <unordered_set>
    #else
        #include <tr1/unordered_set>    // for std::tr1::unordered_set, ...
    #endif
    namespace unboost {
        using std::tr1::unordered_set;
        using std::tr1::unordered_multiset;
    }
#elif defined(UNBOOST_USE_BOOST_UNORDERED_SET)
    #include <boost/unordered_set.hpp>  // for boost::unordered_set, ...
    namespace unboost {
        using boost::unordered_set;
        using boost::unordered_multiset;
    }
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_UNORDERED_SET_HPP_
