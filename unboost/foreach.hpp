// foreach.hpp --- Unboost foreach
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_FOREACH_HPP_
#define UNBOOST_FOREACH_HPP_

#include "unboost.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_FOREACH) + defined(UNBOOST_USE_BOOST_FOREACH)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_FOREACH
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_FOREACH
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_FOREACH
        #else
            #if defined(_MSC_VER) && (_MSC_VER >= 1700)
                // Visual C++ 2012 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_FOREACH
                #else
                    #define UNBOOST_USE_BOOST_FOREACH
                #endif
            #else
                #define UNBOOST_USE_BOOST_FOREACH
            #endif
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_FOREACH
    #define UNBOOST_FOREACH(x,y) for (x : y)
#elif defined(UNBOOST_USE_BOOST_FOREACH)
    #include <boost/foreach.hpp>
    #define UNBOOST_FOREACH BOOST_FOREACH
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_FOREACH_HPP_
