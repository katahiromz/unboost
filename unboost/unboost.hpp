// unboost.hpp --- Unboost core
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_CORE_HPP_
#define UNBOOST_CORE_HPP_

#define UNBOOST_VERSION             33
#define UNBOOST_VERSION_STRING      "Unboost 33 by Katayama Hirofumi MZ"

#ifndef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __cplusplus
    #include <cassert>      // for the assert macro
    #include <string>       // for std::string and std::wstring, ...
    #include <vector>       // for std::vector
    #include <iostream>     // for std::cout, std::endl, ...
    #include <algorithm>    // for std::swap
#else
    #include <assert.h>     // for the assert macro
#endif

//////////////////////////////////////////////////////////////////////////////
// old compiler supports

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x0551)
    #ifndef UNBOOST_OLD_BORLAND
        #define UNBOOST_OLD_BORLAND
    #endif
    #ifndef inline
        #define inline __inline
    #endif
#endif

#ifndef UNBOOST_OLD_COMPILER
    #ifdef UNBOOST_OLD_BORLAND
        #define UNBOOST_OLD_COMPILER
    #endif
    #ifdef __WATCOMC__
        #define UNBOOST_OLD_COMPILER
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

#if (__cplusplus >= 201103L)
    #define UNBOOST_NOEXCEPT noexcept
#else
    #define UNBOOST_NOEXCEPT
#endif

//////////////////////////////////////////////////////////////////////////////
// treat GNU extension

#ifndef __extension__
    #if !defined(__GNUC__) && !defined(__clang__)
        #define __extension__   /**/
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// dependencies

// thread and chrono depends on each other
#ifdef UNBOOST_USE_CXX11_THREAD
    #ifndef UNBOOST_USE_CXX11_CHRONO
        #define UNBOOST_USE_CXX11_CHRONO
    #endif
#endif
#ifdef UNBOOST_USE_BOOST_THREAD
    #ifndef UNBOOST_USE_BOOST_CHRONO
        #define UNBOOST_USE_BOOST_CHRONO
    #endif
#endif
#ifdef UNBOOST_USE_WIN32_THREAD
    #ifndef UNBOOST_USE_WIN32_CHRONO
        #define UNBOOST_USE_WIN32_CHRONO
    #endif
#endif
#ifdef UNBOOST_USE_POSIX_THREAD
    #ifndef UNBOOST_USE_POSIX_CHRONO
        #define UNBOOST_USE_POSIX_CHRONO
    #endif
#endif
#ifdef UNBOOST_USE_CXX11_CHRONO
    #ifndef UNBOOST_USE_CXX11_THREAD
        #define UNBOOST_USE_CXX11_THREAD
    #endif
#endif
#ifdef UNBOOST_USE_BOOST_CHRONO
    #ifndef UNBOOST_USE_BOOST_THREAD
        #define UNBOOST_USE_BOOST_THREAD
    #endif
#endif
#ifdef UNBOOST_USE_WIN32_CHRONO
    #ifndef UNBOOST_USE_WIN32_THREAD
        #define UNBOOST_USE_WIN32_THREAD
    #endif
#endif
#ifdef UNBOOST_USE_POSIX_CHRONO
    #ifndef UNBOOST_USE_POSIX_THREAD
        #define UNBOOST_USE_POSIX_THREAD
    #endif
#endif

// Unboost's chrono depends on Unboost's type_traits and ratio
#ifdef UNBOOST_USE_UNBOOST_CHRONO
    #ifndef UNBOOST_USE_UNBOOST_RATIO
        #define UNBOOST_USE_UNBOOST_RATIO
    #endif
    #ifndef UNBOOST_USE_UNBOOST_TYPE_TRAITS
        #define UNBOOST_USE_UNBOOST_TYPE_TRAITS
    #endif
#endif

// Unboost's filesystem depends on Unboost's smart_ptr
#ifdef UNBOOST_USE_UNBOOST_FILESYSTEM
    #ifndef UNBOOST_USE_UNBOOST_SMART_PTR
        #define UNBOOST_USE_UNBOOST_SMART_PTR
    #endif
#endif

// Unboost's smart_ptr depends on Unboost's type_traits
#ifdef UNBOOST_USE_UNBOOST_SMART_PTR
    #ifndef UNBOOST_USE_UNBOOST_TYPE_TRAITS
        #define UNBOOST_USE_UNBOOST_TYPE_TRAITS
    #endif
#endif

// Unboost's ratio depends on Unboost's static_assert
#ifdef UNBOOST_USE_UNBOOST_RATIO
    #ifndef UNBOOST_USE_UNBOOST_STATIC_ASSERT
        #define UNBOOST_USE_UNBOOST_STATIC_ASSERT
    #endif
#endif

// win32/posix thread and win32/posix event depends each other
#ifdef UNBOOST_USE_WIN32_THREAD
    #ifndef UNBOOST_USE_WIN32_EVENT
        #define UNBOOST_USE_WIN32_EVENT
    #endif
#endif
#ifdef UNBOOST_USE_WIN32_EVENT
    #ifndef UNBOOST_USE_WIN32_THREAD
        #define UNBOOST_USE_WIN32_THREAD
    #endif
#endif
#ifdef UNBOOST_USE_POSIX_THREAD
    #ifndef UNBOOST_USE_POSIX_EVENT
        #define UNBOOST_USE_POSIX_EVENT
    #endif
#endif
#ifdef UNBOOST_USE_POSIX_EVENT
    #ifndef UNBOOST_USE_POSIX_THREAD
        #define UNBOOST_USE_POSIX_THREAD
    #endif
#endif

// Unboost's type_traits depends on Unboost's rvref
#ifdef UNBOOST_USE_UNBOOST_TYPE_TRAITS
    #ifndef UNBOOST_USE_UNBOOST_RV_REF
        #define UNBOOST_USE_UNBOOST_RV_REF
    #endif
#endif

// Unboost's unordered_set depends on Unboost's forward_list
#ifdef UNBOOST_USE_UNBOOST_UNORDERED_SET
    #ifndef UNBOOST_USE_UNBOOST_FORWARD_LIST
        #define UNBOOST_USE_UNBOOST_FORWARD_LIST
    #endif
#endif


//////////////////////////////////////////////////////////////////////////////
// consistency checks

#if ((defined(UNBOOST_USE_CXX11) + defined(UNBOOST_USE_TR1) + defined(UNBOOST_USE_BOOST)) >= 2)
    #error Choose one or none of UNBOOST_USE_CXX11, UNBOOST_USE_TR1 and UNBOOST_USE_BOOST. You lose.
#endif

//////////////////////////////////////////////////////////////////////////////
// swapping

#ifdef __cplusplus
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
#endif  // def __cplusplus

//////////////////////////////////////////////////////////////////////////////
// 64-bit integer

#ifdef _WIN32
    #ifndef _INC_WINDOWS
        #ifndef NOMINMAX
            #define NOMINMAX
        #endif
        #include <windows.h>
    #endif
#endif

#ifdef __cplusplus
namespace unboost {
#endif
    #ifdef _WIN32
        typedef LONGLONG            _int64_t;
        typedef DWORDLONG           _uint64_t;
    #else
        typedef long long           _int64_t;
        typedef unsigned long long  _uint64_t;
    #endif
#ifdef __cplusplus
} // namespace unboost
#endif

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef UNBOOST_CORE_HPP_

//////////////////////////////////////////////////////////////////////////////
