// unboost.hpp --- Unboost core
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_CORE_HPP_
#define UNBOOST_CORE_HPP_

#define UNBOOST_VERSION             24
#define UNBOOST_VERSION_STRING      "Unboost 24 by Katayama Hirofumi MZ"

#ifndef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>      // for the assert macro
#include <string>       // for std::string and std::wstring, ...
#include <vector>       // for std::vector
#include <iostream>     // for std::cout, std::endl, ...
#include <algorithm>    // for std::swap

//////////////////////////////////////////////////////////////////////////////

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x0551)
    #ifndef UNBOOST_OLD_BORLAND
        #define UNBOOST_OLD_BORLAND
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// Is Unboost on C++11? (UNBOOST_CXX11)

#ifndef UNBOOST_CXX11
    #if (__cplusplus >= 201103L)    // C++11
        #define UNBOOST_CXX11
    #endif
#endif

#ifdef UNBOOST_NO_CXX11
    #undef UNBOOST_CXX11
#endif

//////////////////////////////////////////////////////////////////////////////
// Use all?

#ifdef UNBOOST_USE_ALL
    #ifndef UNBOOST_USE_ARRAY
        #define UNBOOST_USE_ARRAY
    #endif
    #ifndef UNBOOST_USE_ASSERT
        #define UNBOOST_USE_ASSERT
    #endif
    #ifndef UNBOOST_USE_CHRONO
        #define UNBOOST_USE_CHRONO
    #endif
    #ifndef UNBOOST_USE_COMPLEX_FUNCTIONS
        #define UNBOOST_USE_COMPLEX_FUNCTIONS
    #endif
    #ifndef UNBOOST_USE_CONVERSION
        #define UNBOOST_USE_CONVERSION
    #endif
    #ifndef UNBOOST_USE_EMPLACE
        #define UNBOOST_USE_EMPLACE
    #endif
    #ifndef UNBOOST_USE_FOREACH
        #define UNBOOST_USE_FOREACH
    #endif
    #ifndef UNBOOST_USE_RANDOM
        #define UNBOOST_USE_RANDOM
    #endif
    #ifndef UNBOOST_USE_RATIO
        #define UNBOOST_USE_RATIO
    #endif
    #ifndef UNBOOST_USE_REGEX
        #define UNBOOST_USE_REGEX
    #endif
    #ifndef UNBOOST_USE_SAFE_DELETE
        #define UNBOOST_USE_SAFE_DELETE
    #endif
    #ifndef UNBOOST_USE_SMART_PTR
        #define UNBOOST_USE_SMART_PTR
    #endif
    #ifndef UNBOOST_USE_STATIC_ASSERT
        #define UNBOOST_USE_STATIC_ASSERT
    #endif
    #ifndef UNBOOST_USE_STRING_ALGORITHM
        #define UNBOOST_USE_STRING_ALGORITHM
    #endif
    #ifndef UNBOOST_USE_THREAD
        #define UNBOOST_USE_THREAD
    #endif
    #ifndef UNBOOST_USE_TUPLE
        #define UNBOOST_USE_TUPLE
    #endif
    #ifndef UNBOOST_USE_TYPE_TRAITS
        #define UNBOOST_USE_TYPE_TRAITS
    #endif
    #ifndef UNBOOST_USE_UNORDERED_MAP
        #define UNBOOST_USE_UNORDERED_MAP
    #endif
    #ifndef UNBOOST_USE_UNORDERED_SET
        #define UNBOOST_USE_UNORDERED_SET
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// dependency

// thread depends on chrono
#ifdef UNBOOST_USE_THREAD
    #ifndef UNBOOST_USE_CHRONO
        #define UNBOOST_USE_CHRONO
    #endif
    //
    #ifdef UNBOOST_USE_CXX11_THREAD
        #ifndef UNBOOST_USE_CXX11_CHRONO
            #define UNBOOST_USE_CXX11_CHRONO
        #endif
    #elif defined(UNBOOST_USE_BOOST_THREAD)
        #ifndef UNBOOST_USE_BOOST_CHRONO
            #define UNBOOST_USE_BOOST_CHRONO
        #endif
    #elif defined(UNBOOST_USE_WIN32_THREAD)
        #ifndef UNBOOST_USE_WIN32_CHRONO
            #define UNBOOST_USE_WIN32_CHRONO
        #endif
    #elif defined(UNBOOST_USE_POSIX_THREAD)
        #ifndef UNBOOST_USE_POSIX_CHRONO
            #define UNBOOST_USE_POSIX_CHRONO
        #endif
    #endif
#endif

// chrono depends on type_traits and ratio
#ifdef UNBOOST_USE_CHRONO
    #ifndef UNBOOST_USE_TYPE_TRAITS
        #define UNBOOST_USE_TYPE_TRAITS
    #endif
    #ifndef UNBOOST_USE_RATIO
        #define UNBOOST_USE_RATIO
    #endif
    //
    #ifdef UNBOOST_USE_CXX11_CHRONO
        #ifndef UNBOOST_USE_CXX11_TYPE_TRAITS
            #define UNBOOST_USE_CXX11_TYPE_TRAITS
        #endif
        #ifndef UNBOOST_USE_CXX11_RATIO
            #define UNBOOST_USE_CXX11_RATIO
        #endif
    #elif defined(UNBOOST_USE_BOOST_CHRONO)
        #ifndef UNBOOST_USE_BOOST_TYPE_TRAITS
            #define UNBOOST_USE_BOOST_TYPE_TRAITS
        #endif
        #ifndef UNBOOST_USE_BOOST_RATIO
            #define UNBOOST_USE_BOOST_RATIO
        #endif
    #else
        #ifndef UNBOOST_USE_UNBOOST_TYPE_TRAITS
            #define UNBOOST_USE_UNBOOST_TYPE_TRAITS
        #endif
        #ifndef UNBOOST_USE_UNBOOST_RATIO
            #define UNBOOST_USE_UNBOOST_RATIO
        #endif
    #endif
#endif

// filesystem depends on smart_ptr
#ifdef UNBOOST_USE_FILESYSTEM
    #ifndef UNBOOST_USE_SMART_PTR
        #define UNBOOST_USE_SMART_PTR
    #endif
    //
    #ifdef UNBOOST_USE_BOOST_FILESYSTEM
        #ifndef UNBOOST_USE_BOOST_SMART_PTR
            #define UNBOOST_USE_BOOST_SMART_PTR
        #endif
    #endif
    #ifdef UNBOOST_USE_UNBOOST_FILESYSTEM
        #ifndef UNBOOST_USE_UNBOOST_SMART_PTR
            #define UNBOOST_USE_UNBOOST_SMART_PTR
        #endif
    #endif
#endif

// smart pointer depends on type traits
#ifdef UNBOOST_USE_SMART_PTR
    #ifndef UNBOOST_USE_TYPE_TRAITS
        #define UNBOOST_USE_TYPE_TRAITS
    #endif
    //
    #ifdef UNBOOST_USE_CXX11_SMART_PTR
        #ifndef UNBOOST_USE_CXX11_TYPE_TRAITS
            #define UNBOOST_USE_CXX11_TYPE_TRAITS
        #endif
    #endif
    #ifdef UNBOOST_USE_BOOST_SMART_PTR
        #ifndef UNBOOST_USE_BOOST_TYPE_TRAITS
            #define UNBOOST_USE_BOOST_TYPE_TRAITS
        #endif
    #endif
    #ifdef UNBOOST_USE_UNBOOST_SMART_PTR
        #ifndef UNBOOST_USE_UNBOOST_TYPE_TRAITS
            #define UNBOOST_USE_UNBOOST_TYPE_TRAITS
        #endif
    #endif
#endif

// ratio depends on static_assert
#ifdef UNBOOST_USE_RATIO
    #ifndef UNBOOST_USE_STATIC_ASSERT
        #define UNBOOST_USE_STATIC_ASSERT
    #endif
    //
    #ifdef UNBOOST_USE_CXX11_RATIO
        #ifndef UNBOOST_USE_CXX11_STATIC_ASSERT
            #define UNBOOST_USE_CXX11_STATIC_ASSERT
        #endif
    #endif
    #ifdef UNBOOST_USE_BOOST_RATIO
        #ifndef UNBOOST_USE_BOOST_STATIC_ASSERT
            #define UNBOOST_USE_BOOST_STATIC_ASSERT
        #endif
    #endif
    #ifdef UNBOOST_USE_UNBOOST_RATIO
        #ifndef UNBOOST_USE_UNBOOST_STATIC_ASSERT
            #define UNBOOST_USE_UNBOOST_STATIC_ASSERT
        #endif
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// consistency checks

#if ((defined(UNBOOST_USE_CXX11) + defined(UNBOOST_USE_TR1) + defined(UNBOOST_USE_BOOST)) >= 2)
    #error Choose one or none of UNBOOST_USE_CXX11, UNBOOST_USE_TR1 and UNBOOST_USE_BOOST. You lose.
#endif

//////////////////////////////////////////////////////////////////////////////
// swapping

namespace unboost {
    using std::swap;

    #ifndef UNBOOST_CXX11
        #if !(__cplusplus >= 201103L)    // not C++11
            template <typename T2, size_t N>
            inline void swap(T2 (&a)[N], T2 (&b)[N]) {
                std::swap_ranges(a, a + N, b);
            }
        #endif
    #endif
} // namespace unboost

//////////////////////////////////////////////////////////////////////////////
// 64-bit integer

#ifdef _WIN32
    #ifndef _INC_WINDOWS
        #include <windows.h>
    #endif
#endif

namespace unboost {
    #ifdef _WIN32
        typedef LONGLONG            _int64_t;
        typedef DWORDLONG           _uint64_t;
    #else
        typedef long long           _int64_t;
        typedef unsigned long long  _uint64_t;
    #endif
} // namespace unboost

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef UNBOOST_CORE_HPP_

//////////////////////////////////////////////////////////////////////////////
