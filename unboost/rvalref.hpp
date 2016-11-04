// rvalref.hpp --- Unboost rvalue reference
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_RVALREF_HPP_
#define UNBOOST_RVALREF_HPP_

#include "unboost.hpp"

// move<T>
// forward<T>
// remove_reference<T>
// is_reference<T>
// is_rvalue_reference<T>
// add_lvalue_reference<T>
// add_rvalue_reference<T>
// UNBOOST_RVALREF(T)
// UNBOOST_RVALREF_TYPE(T)

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_RVALREF) + defined(UNBOOST_USE_BOOST_RVALREF) + defined(UNBOOST_USE_UNBOOST_RVALREF)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_RVALREF
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_RVALREF
    #else
        #ifdef UNBOOST_CXX11
            #define UNBOOST_USE_CXX11_RVALREF
        #else
            #define UNBOOST_USE_UNBOOST_RVALREF
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_RVALREF
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
    } // namespace unboost

    #ifndef UNBOOST_NO_RVALREF
        #define UNBOOST_RVALREF(value)        value
        #define UNBOOST_RVALREF_TYPE(...)     __VA_ARGS__&&
    #endif
#elif defined(UNBOOST_USE_BOOST_RVALREF)
    #include <boost/move/core.hpp>      // for boost::move
    #include <boost/move/utility.hpp>   // for boost::forward
    #include <boost/type_traits.hpp>

    namespace unboost {
        #ifdef UNBOOST_NO_RVALREF
            using boost::move;
            using boost::forward;
            using boost::remove_reference;
            using boost::is_reference;
            using boost::is_rvalue_reference;
            using boost::add_lvalue_reference;
            using boost::add_rvalue_reference;
        #else   // ndef UNBOOST_NO_RVALREF
            template <typename T>
            struct rvalref {
                T& m_ref;
                rvalref(T& ref) : m_ref(ref) { }
            };

            #define UNBOOST_RVALREF(value) \
                (value).m_ref

            #ifdef UNBOOST_OLD_COMPILER
                #define UNBOOST_RVALREF_TYPE(type) \
                    unboost::rvalref<type > /**/
            #else
                #define UNBOOST_RVALREF_TYPE(...) \
                    unboost::rvalref<__VA_ARGS__ > /**/
            #endif

            template <typename T>
            struct remove_reference { typedef T type; };
            template <typename T>
            struct remove_reference<T&> { typedef T type; };
            template <typename T>
            struct remove_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef T type;
            };

            template <typename T>
            struct is_reference {
                enum { value = 0 };
            };
            template <typename T>
            struct is_reference<T&> {
                enum { value = 1 };
            };
            template <typename T>
            struct is_reference<UNBOOST_RVALREF_TYPE(T) > {
                enum { value = 1 };
            };

            template <typename>
            struct is_rvalue_reference { enum { value = 0 }; };
            template <typename T>
            struct is_rvalue_reference<UNBOOST_RVALREF_TYPE(T) >
                { enum { value = 1 }; };

            template <typename T>
            struct add_lvalue_reference {
                typedef T& type;
            };
            template <typename T>
            struct add_lvalue_reference<T&> {
                typedef T& type;
            };
            template <typename T>
            struct add_lvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef T& type;
            };

            template <typename T>
            struct add_rvalue_reference {
                typedef UNBOOST_RVALREF_TYPE(T) type;
            };
            template <typename T>
            struct add_rvalue_reference<T&> {
                typedef T& type;
            };
            template <typename T>
            struct add_rvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef UNBOOST_RVALREF_TYPE(T) type;
            };

            template <typename T>
            inline rvalref<typename remove_reference<T>::type> move(T& t) {
                rvalref<typename remove_reference<T>::type> ref(t);
                return ref;
            }

            template <typename T>
            inline UNBOOST_RVALREF_TYPE(T)
            forward(typename remove_reference<T>::type& t) {
                return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
            }
            template <typename T>
            inline UNBOOST_RVALREF_TYPE(T)
            forward(UNBOOST_RVALREF_TYPE(typename remove_reference<T>::type) t) {
                return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
            }
        #endif  // ndef UNBOOST_NO_RVALREF
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_RVALREF)
    namespace unboost {
        #ifndef UNBOOST_NO_RVALREF
            template <typename T>
            struct rvalref {
                T& m_ref;
                rvalref(T& ref) : m_ref(ref) { }
            };

            #define UNBOOST_RVALREF(value) \
                (value).m_ref

            #ifdef UNBOOST_OLD_COMPILER
                #define UNBOOST_RVALREF_TYPE(type) \
                    unboost::rvalref<type > /**/
            #else
                #define UNBOOST_RVALREF_TYPE(...) \
                    unboost::rvalref<__VA_ARGS__ > /**/
            #endif
        #endif

        template <typename T>
        struct remove_reference { typedef T type; };
        template <typename T>
        struct remove_reference<T&> { typedef T type; };

        template <typename T>
        struct is_rvalue_reference { enum { value = 0 }; };

        template <typename T>
        struct is_reference { enum { value = 0 }; };
        template <typename T>
        struct is_reference<T&> { enum { value = 1 }; };

        template <typename T>
        struct add_lvalue_reference {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<T&> {
            typedef T& type;
        };

        #ifdef UNBOOST_RVALREF
            template <typename T>
            struct remove_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef T type;
            };

            template <typename T>
            struct is_rvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
                enum { value = 1 };
            };

            template <typename T>
            struct is_reference<UNBOOST_RVALREF_TYPE(T) > {
                enum { value = 1 };
            };

            template <typename T>
            struct add_lvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef T& type;
            };

            template <typename T>
            struct add_rvalue_reference {
                typedef UNBOOST_RVALREF_TYPE(T) type;
            };
            template <typename T>
            struct add_rvalue_reference<T&> {
                typedef T& type;
            };
            template <typename T>
            struct add_rvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef UNBOOST_RVALREF_TYPE(T) type;
            };

            template <typename T>
            inline rvalref<typename remove_reference<T>::type>
            move(T& t) {
                rvalref<T> ref(t);
                return ref;
            }

            template <typename T>
            inline UNBOOST_RVALREF_TYPE(T)
            forward(typename remove_reference<T>::type& t) {
                return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
            }
            template <typename T>
            inline UNBOOST_RVALREF_TYPE(T)
            forward(UNBOOST_RVALREF_TYPE(typename remove_reference<T>::type) t) {
                return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
            }
        #endif  // def UNBOOST_RVALREF
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_RVALREF_HPP_
