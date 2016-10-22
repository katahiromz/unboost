// assert.hpp --- Unboost assertion
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_ASSERT_HPP_
#define UNBOOST_ASSERT_HPP_

#include "unboost_core.hpp"

#if ((defined(UNBOOST_USE_UNBOOST_ASSERT) + defined(UNBOOST_USE_BOOST_ASSERT)) == 0)
    #ifdef UNBOOST_USE_BOOST
        #define UNBOOST_USE_BOOST_ASSERT
    #endif
#endif

#if defined(UNBOOST_USE_BOOST_ASSERT)
    #ifdef UNBOOST_DISABLE_ASSERTS
        #define BOOST_DISABLE_ASSERTS
    #endif
    #include <boost/assert.hpp>
    #define UNBOOST_ASSERT          BOOST_ASSERT
    #define UNBOOST_ASSERT_MSG      BOOST_ASSERT_MSG
    #define UNBOOST_VERIFY          BOOST_VERIFY
    #define UNBOOST_VERIFY_MSG      BOOST_VERIFY_MSG
    #ifdef BOOST_ASSERT_IS_VOID
        #define UNBOOST_ASSERT_IS_VOID
    #endif
#else
    #if defined(UNBOOST_DISABLE_ASSERTS)
        #define UNBOOST_ASSERT(exp)             ((void)0)
        #define UNBOOST_ASSERT_MSG(exp,msg)     ((void)0)
        #define UNBOOST_VERIFY(exp)             ((void)(exp))
        #define UNBOOST_VERIFY_MSG(exp,msg)     ((void)(exp))
    #else
        #define UNBOOST_ASSERT(exp)             assert(exp)
        #define UNBOOST_ASSERT_MSG(exp,msg)     assert((exp) && (msg))
        #define UNBOOST_VERIFY                  UNBOOST_ASSERT
        #define UNBOOST_VERIFY_MSG              UNBOOST_ASSERT_MSG
    #endif
    #if defined(NDEBUG)
        #define UNBOOST_ASSERT_IS_VOID
    #endif
#endif

#endif  // ndef UNBOOST_ASSERT_HPP_
