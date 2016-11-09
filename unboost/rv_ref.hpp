// rv.hpp --- Unboost rvalue reference
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_RV_REF_HPP_
#define UNBOOST_RV_REF_HPP_

#include "unboost.hpp"

// This file defines:
// move<T>
// forward<T>
// remove_reference<T>
// is_reference<T>
// is_rvalue_reference<T>
// add_lvalue_reference<T>
// add_rvalue_reference<T>
// UNBOOST_RV_REF(T)        --- rvalue reference type of T
// UNBOOST_FWD_REF(T)       --- universal reference type of T (for forwarding)
// UNBOOST_RV(value)        --- gets the real value from rvalue reference type
// UNBOOST_FMD(value)       --- gets the real value from universal reference type

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_RV_REF) + defined(UNBOOST_USE_BOOST_RV_REF) + defined(UNBOOST_USE_UNBOOST_RV_REF)) == 0)
    #if (__cplusplus >= 201103L)
        #define UNBOOST_USE_CXX11_RV_REF
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_RV_REF
    #else
        #define UNBOOST_USE_UNBOOST_RV_REF
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_RV_REF
    #include <utility>          // for std::move, std::forward
    #include <type_traits>
    namespace unboost {
        using std::move;
        using std::forward;
        using std::remove_reference;
        using std::is_reference;
        using std::is_rvalue_reference;
        using std::add_lvalue_reference;
        using std::add_rvalue_reference;
        template<class T>
        struct enable_move_utility_emulation {
            enum { value = 0 };
        };
    } // namespace unboost

    #ifndef UNBOOST_NO_RV_REF
        #define UNBOOST_RV_REF(...)     __VA_ARGS__&&
        #define UNBOOST_RV(value)       value
        #define UNBOOST_FWD_REF(...)    __VA_ARGS__&&
        #define UNBOOST_FWD(value)      value
    #endif
#elif defined(UNBOOST_USE_BOOST_RV_REF)
    #include <boost/move/core.hpp>      // for boost::move
    #include <boost/move/utility.hpp>   // for boost::forward
    #include <boost/type_traits.hpp>

    namespace unboost {
        #ifndef UNBOOST_NO_CXX11_RVALUE_REFERENCES
            struct enable_move_utility_emulation {
                enum { value = 0 };
            };
            using boost::move;
            using boost::forward;
            using boost::remove_reference;
            using boost::is_reference;
            using boost::is_rvalue_reference;
            using boost::add_lvalue_reference;
            using boost::add_rvalue_reference;

            #define UNBOOST_RV_REF(...)     __VA_ARGS__&&
            #define UNBOOST_RV(value)       value
            #define UNBOOST_FWD_REF(...)    __VA_ARGS__&&
            #define UNBOOST_FWD(value)      value
        #else   // ndef UNBOOST_NO_RV_REF
            #ifndef UNBOOST_NEED_UNBOOST_RV_REF_EMU
                #define UNBOOST_NEED_UNBOOST_RV_REF_EMU
            #endif
        #endif  // ndef UNBOOST_NO_RV_REF
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_RV_REF)
    #ifndef UNBOOST_NO_CXX11_RVALUE_REFERENCES
        #define UNBOOST_NO_CXX11_RVALUE_REFERENCES
    #endif
    #ifndef UNBOOST_NEED_UNBOOST_RV_REF_EMU
        #define UNBOOST_NEED_UNBOOST_RV_REF_EMU
    #endif
#else
    #error Your compiler is not supported yet. You lose.
#endif

// implement Unboost's rvalue reference, move, and forward
#ifdef UNBOOST_NEED_UNBOOST_RV_REF_EMU
    namespace unboost {
        struct enable_move_utility_emulation {
            enum { value = 1 };
        };

        template <typename T>
        struct rv {
            T m_ref;
            explicit rv(T ref) : m_ref(ref) { }
            operator T&() { return m_ref; }
        };

        #ifdef UNBOOST_OLD_COMPILER
            #define UNBOOST_RV_REF(type)    unboost::rv<type>
            #define UNBOOST_RV(value)       (value).m_ref
            #define UNBOOST_FWD_REF(type)   type
            #define UNBOOST_FWD(value)      (value)
        #else
            #define UNBOOST_RV_REF(...)     const unboost::rv<__VA_ARGS__>&
            #define UNBOOST_RV(...)         (__VA_ARGS__).m_ref
            #define UNBOOST_FWD_REF(...)    __VA_ARGS__
            #define UNBOOST_FWD(...)        (__VA_ARGS__)
        #endif

        template <typename T>
        struct remove_reference                 { typedef T type; };
        template <typename T>
        struct remove_reference<T&>             { typedef T type; };
        template <typename T>
        struct remove_reference<rv<T> >         { typedef T type; };
        template <typename T>
        struct remove_reference<rv<T>&>         { typedef T type; };
        template <typename T>
        struct remove_reference<const rv<T>&>   { typedef T type; };

        template <typename T>
        inline rv<typename remove_reference<T>::type>
        move(const T& t) {
            return static_cast<rv<typename remove_reference<T>::type> >(t);
        }
        template <typename T>
        inline rv<typename remove_reference<T>::type>
        move(T t) {
            return static_cast<rv<typename remove_reference<T>::type> >(t);
        }

        template <typename T>
        inline T&
        forward(T& t) {
            return t;
        }
        template <typename T>
        inline const T&
        forward(const T& t) {
            return t;
        }

        template <typename T>
        struct is_reference { enum { value = 0 }; };
        template <typename T>
        struct is_reference<T&> { enum { value = 1 }; };
        template <typename T>
        struct is_reference<rv<T> >         { enum { value = 1 }; };
        template <typename T>
        struct is_reference<rv<T>&>         { enum { value = 1 }; };
        template <typename T>
        struct is_reference<const rv<T>&>   { enum { value = 1 }; };

        template <typename T>
        struct is_rvalue_reference {
            enum { value = 0 };
        };
        template <typename T>
        struct is_rvalue_reference<rv<T> > {
            enum { value = 1 };
        };
        template <typename T>
        struct is_rvalue_reference<rv<T>&> {
            enum { value = 1 };
        };
        template <typename T>
        struct is_rvalue_reference<const rv<T>&> {
            enum { value = 1 };
        };

        template <typename T>
        struct add_lvalue_reference {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<T&> {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<rv<T> > {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<rv<T>&> {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<const rv<T>&> {
            typedef T& type;
        };

        template <typename T>
        struct add_rvalue_reference {
            typedef rv<T> type;
        };
        template <typename T>
        struct add_rvalue_reference<T&> {
            typedef T& type;
        };
        template <typename T>
        struct add_rvalue_reference<rv<T> > {
            typedef rv<T> type;
        };
        template <typename T>
        struct add_rvalue_reference<rv<T>&> {
            typedef rv<T> type;
        };
        template <typename T>
        struct add_rvalue_reference<const rv<T>&> {
            typedef rv<T> type;
        };
    } // namespace unboost
#endif  // def UNBOOST_NEED_UNBOOST_RV_REF_EMU

#endif  // ndef UNBOOST_RV_REF_HPP_
