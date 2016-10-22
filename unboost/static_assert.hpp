// static_assert.hpp --- Unboost static_assert
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_STATIC_ASSERT_HPP_
#define UNBOOST_STATIC_ASSERT_HPP_

#include "unboost.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_STATIC_ASSERT) + defined(UNBOOST_USE_UNBOOST_STATIC_ASSERT) + defined(UNBOOST_USE_BOOST_STATIC_ASSERT)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_STATIC_ASSERT
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_STATIC_ASSERT
    #else
        #ifdef UNBOOST_CXX11   // C++11
            #define UNBOOST_USE_CXX11_STATIC_ASSERT
        #else
            #define UNBOOST_USE_UNBOOST_STATIC_ASSERT
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_STATIC_ASSERT
    // static_assert is available
    #define UNBOOST_STATIC_ASSERT_MSG static_assert
#elif defined(UNBOOST_USE_BOOST_STATIC_ASSERT)
    #include <boost/static_assert.hpp>
    #define UNBOOST_STATIC_ASSERT_MSG BOOST_STATIC_ASSERT_MSG
    #ifndef static_assert
        #define static_assert BOOST_STATIC_ASSERT_MSG
    #endif
#else
    #define UNBOOST_STATIC_ASSERT_MSG(x,y) \
        typedef char UNBOOST_STATIC_ASSERTION[(x) ? 1 : -1]
    #define static_assert(x,y) UNBOOST_STATIC_ASSERT_MSG((x),(y))
#endif

#endif  // ndef UNBOOST_STATIC_ASSERT_HPP_
