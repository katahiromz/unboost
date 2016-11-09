// rv.hpp --- Unboost rvalue reference
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
// UNBOOST_RV_REF(T)        --- rvalue reference type of T
// UNBOOST_FWD_REF(T)       --- universal reference type of T (for forward)
// UNBOOST_RV(value)        --- gets the real value from rvalue reference type
// UNBOOST_FMD(value)       --- gets the real value from universal reference type

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
        template<class T>
        struct enable_move_utility_emulation {
            enum { value = 0 };
        };
    } // namespace unboost

    #ifndef UNBOOST_NO_RVREF
        #define UNBOOST_RV_REF(...)     __VA_ARGS__&&
        #define UNBOOST_RV(value)       value
        #define UNBOOST_FWD_REF(...)    __VA_ARGS__&&
        #define UNBOOST_FWD(value)      value
    #endif
#elif defined(UNBOOST_USE_BOOST_RVREF)
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
        #else   // ndef UNBOOST_NO_RVREF
            #ifndef UNBOOST_NEED_UNBOOST_RV_REF_IMPL
                #define UNBOOST_NEED_UNBOOST_RV_REF_IMPL
            #endif
        #endif  // ndef UNBOOST_NO_RVREF
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_RVREF)
    #ifndef UNBOOST_NO_CXX11_RVALUE_REFERENCES
        #define UNBOOST_NO_CXX11_RVALUE_REFERENCES
    #endif
    #ifndef UNBOOST_NEED_UNBOOST_RV_REF_IMPL
        #define UNBOOST_NEED_UNBOOST_RV_REF_IMPL
    #endif
#else
    #error Your compiler is not supported yet. You lose.
#endif

// implement Unboost's rvalue reference, move, and forward
#ifdef UNBOOST_NEED_UNBOOST_RV_REF_IMPL
    namespace unboost {
        struct enable_move_utility_emulation {
            enum { value = 1 };
        };

        template <typename T>
        struct rv {
            T& m_ref;
            explicit rv(T& ref)      : m_ref(ref) { }
            explicit rv(rv<T>& ref)  : m_ref(ref.m_ref) { }
        };
        #ifdef UNBOOST_OLD_COMPILER
            #define UNBOOST_RV_REF(type)    unboost::rv<type >
            #define UNBOOST_RV(value)       (value).m_ref
        #else
            #define UNBOOST_RV_REF(...)     unboost::rv<__VA_ARGS__>
            #define UNBOOST_RV(...)         (__VA_ARGS__).m_ref
        #endif

        template <typename T>
        struct fwd {
            union {
                T* m_ptr;
                const T* m_cptr;
            };
            bool m_is_lvalue_ref;

            fwd(const T& ref)
                : m_cptr(&ref), m_is_lvalue_ref(true) { }
            fwd(const fwd<T>& ref) : m_cptr(ref.m_cptr),
                m_is_lvalue_ref(ref.m_is_lvalue_ref) { }
            fwd(rv<T>& ref)
                : m_ptr(&ref.m_ref), m_is_lvalue_ref(false) { }

                  T& _get_()       { return *m_ptr; }
            const T& _get_() const { return *m_cptr; }

            operator rv<T>() {
                return rv<T>(*m_ptr);
            }
        }; // fwd<T>
        #ifdef UNBOOST_OLD_COMPILER
            #define UNBOOST_FWD_REF(type)    unboost::fwd<type >
            #define UNBOOST_FWD(value)       (value)._get_()
        #else
            #define UNBOOST_FWD_REF(...)     unboost::fwd<__VA_ARGS__>
            #define UNBOOST_FWD(...)         (__VA_ARGS__)._get_()
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
        struct remove_reference<fwd<T> >        { typedef T type; };
        template <typename T>
        struct remove_reference<fwd<T>&>        { typedef T type; };
        template <typename T>
        struct remove_reference<const fwd<T>&>  { typedef T type; };

        template <typename T>
        inline rv<typename remove_reference<T>::type>
        move(T& x) {
            typedef typename remove_reference<T>::type type_;
            return static_cast<rv<type_> >(x);
        }

        template <typename T>
        inline const typename remove_reference<T>::type&
        forward(const typename remove_reference<T>::type& t) {
            return t;
        }
        template <typename T>
        inline rv<typename remove_reference<T>::type>&
        forward(rv<typename remove_reference<T>::type> t) {
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
        struct is_reference<fwd<T> >        { enum { value = 1 }; };
        template <typename T>
        struct is_reference<fwd<T>&>        { enum { value = 1 }; };
        template <typename T>
        struct is_reference<const fwd<T>&>  { enum { value = 1 }; };

        template <typename T>
        struct is_rvalue_reference { enum { value = 0 }; };
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
        struct is_rvalue_reference<fwd<T> > {
            enum { value = 1 };
        };
        template <typename T>
        struct is_rvalue_reference<fwd<T>&> {
            enum { value = 1 };
        };
        template <typename T>
        struct is_rvalue_reference<const fwd<T>&> {
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
        struct add_lvalue_reference<fwd<T> > {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<fwd<T>&> {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<const fwd<T>&> {
            typedef T& type;
        };

        template <typename T>
        struct add_rvalue_reference {
            typedef UNBOOST_RV_REF(T) type;
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
        template <typename T>
        struct add_rvalue_reference<fwd<T> > {
            typedef rv<T> type;
        };
        template <typename T>
        struct add_rvalue_reference<fwd<T>&> {
            typedef rv<T> type;
        };
        template <typename T>
        struct add_rvalue_reference<const fwd<T>&> {
            typedef rv<T> type;
        };
    } // namespace unboost
#endif  // def UNBOOST_NEED_UNBOOST_RV_REF_IMPL

#endif  // ndef UNBOOST_RVREF_HPP_
