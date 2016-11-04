// rvref.hpp --- Unboost rvalue reference
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_RVREF_HPP_
#define UNBOOST_RVREF_HPP_

#include "unboost.hpp"

// move<T>
// forward<T>
// remove_reference<T>
// is_reference<T>
// is_rvalue_reference<T>
// add_lvalue_reference<T>
// add_rvalue_reference<T>
// UNBOOST_RVREF(T)
// UNBOOST_RVREF_TYPE(T)

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_RVREF) + defined(UNBOOST_USE_BOOST_RVREF) + defined(UNBOOST_USE_UNBOOST_RVREF)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_RVREF
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_RVREF
    #else
        #ifdef UNBOOST_CXX11
            #define UNBOOST_USE_CXX11_RVREF
        #else
            #define UNBOOST_USE_UNBOOST_RVREF
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_RVREF
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

    #ifndef UNBOOST_NO_RVREF
        #define UNBOOST_RVREF(value)        value
        #define UNBOOST_RVREF_TYPE(...)     __VA_ARGS__&&
    #endif
#elif defined(UNBOOST_USE_BOOST_RVREF)
    #include <boost/move/core.hpp>      // for boost::move
    #include <boost/move/utility.hpp>   // for boost::forward
    #include <boost/type_traits.hpp>

    namespace unboost {
        #ifdef UNBOOST_NO_RVREF
            using boost::move;
            using boost::forward;
            using boost::remove_reference;
            using boost::is_reference;
            using boost::is_rvalue_reference;
            using boost::add_lvalue_reference;
            using boost::add_rvalue_reference;
        #else   // ndef UNBOOST_NO_RVREF
            template <typename T>
            struct rvref {
                T& m_ref;
                rvref(T& ref) : m_ref(ref) { }
            };

            #define UNBOOST_RVREF(value) \
                (value).m_ref

            #ifdef UNBOOST_OLD_COMPILER
                #define UNBOOST_RVREF_TYPE(type) \
                    unboost::rvref<type > /**/
            #else
                #define UNBOOST_RVREF_TYPE(...) \
                    unboost::rvref<__VA_ARGS__ > /**/
            #endif

            template <typename T>
            struct remove_reference { typedef T type; };
            template <typename T>
            struct remove_reference<T&> { typedef T type; };
            template <typename T>
            struct remove_reference<UNBOOST_RVREF_TYPE(T) > {
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
            struct is_reference<UNBOOST_RVREF_TYPE(T) > {
                enum { value = 1 };
            };

            template <typename>
            struct is_rvalue_reference { enum { value = 0 }; };
            template <typename T>
            struct is_rvalue_reference<UNBOOST_RVREF_TYPE(T) >
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
            struct add_lvalue_reference<UNBOOST_RVREF_TYPE(T) > {
                typedef T& type;
            };

            template <typename T>
            struct add_rvalue_reference {
                typedef UNBOOST_RVREF_TYPE(T) type;
            };
            template <typename T>
            struct add_rvalue_reference<T&> {
                typedef T& type;
            };
            template <typename T>
            struct add_rvalue_reference<UNBOOST_RVREF_TYPE(T) > {
                typedef UNBOOST_RVREF_TYPE(T) type;
            };

            template <typename T>
            inline rvref<typename remove_reference<T>::type>
            move(T& t) {
                rvref<typename remove_reference<T>::type> ref(t);
                return ref;
            }

            template <typename T>
            inline UNBOOST_RVREF_TYPE(T)
            forward(typename remove_reference<T>::type& t) {
                return static_cast<UNBOOST_RVREF_TYPE(T) >(t);
            }
            template <typename T>
            inline UNBOOST_RVREF_TYPE(T)
            forward(UNBOOST_RVREF_TYPE(typename remove_reference<T>::type) t) {
                return static_cast<UNBOOST_RVREF_TYPE(T) >(t);
            }
        #endif  // ndef UNBOOST_NO_RVREF
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_RVREF)
    namespace unboost {
        #ifndef UNBOOST_NO_RVREF
            template <typename T>
            struct rvref {
                T& m_ref;
                rvref(T& ref) : m_ref(ref) { }
            };

            #define UNBOOST_RVREF(value) \
                (value).m_ref

            #ifdef UNBOOST_OLD_COMPILER
                #define UNBOOST_RVREF_TYPE(type) \
                    unboost::rvref<type > /**/
            #else
                #define UNBOOST_RVREF_TYPE(...) \
                    unboost::rvref<__VA_ARGS__ > /**/
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

        #ifdef UNBOOST_RVREF
            template <typename T>
            struct remove_reference<UNBOOST_RVREF_TYPE(T) > {
                typedef T type;
            };

            template <typename T>
            struct is_rvalue_reference<UNBOOST_RVREF_TYPE(T) > {
                enum { value = 1 };
            };

            template <typename T>
            struct is_reference<UNBOOST_RVREF_TYPE(T) > {
                enum { value = 1 };
            };

            template <typename T>
            struct add_lvalue_reference<UNBOOST_RVREF_TYPE(T) > {
                typedef T& type;
            };

            template <typename T>
            struct add_rvalue_reference {
                typedef UNBOOST_RVREF_TYPE(T) type;
            };
            template <typename T>
            struct add_rvalue_reference<T&> {
                typedef T& type;
            };
            template <typename T>
            struct add_rvalue_reference<UNBOOST_RVREF_TYPE(T) > {
                typedef UNBOOST_RVREF_TYPE(T) type;
            };

            template <typename T>
            inline rvref<typename remove_reference<T>::type>
            move(T& t) {
                rvref<typename remove_reference<T>::type> ref(t);
                return ref;
            }

            template <typename T>
            inline UNBOOST_RVREF_TYPE(T)
            forward(typename remove_reference<T>::type& t) {
                return static_cast<UNBOOST_RVREF_TYPE(T) >(t);
            }
            template <typename T>
            inline UNBOOST_RVREF_TYPE(T)
            forward(UNBOOST_RVREF_TYPE(typename remove_reference<T>::type) t) {
                return static_cast<UNBOOST_RVREF_TYPE(T) >(t);
            }
        #endif  // def UNBOOST_RVREF
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_RVREF_HPP_
