#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#if (defined(__BORLANDC__) && __BORLANDC__ <= 0x551)
    #define OLD_COMPILER 1
#endif

#if __cplusplus >= 201103L
    #include <utility>      // for std::move, std::forward, ...
    #include <type_traits>  // for std::remove_reference

    #define UNBOOST_RV_REF(type)    type&&
    #define UNBOOST_RV(value)       value
    #define UNBOOST_FWD_REF(type)   type&&
    #define UNBOOST_FWD(value)      value

    namespace unboost {
        using std::remove_reference;
        using std::move;
        using std::forward;
    } // namespace unboost

    #define UNBOOST_MOVE        unboost::move
    #define UNBOOST_FORWARD     unboost::forward
#else
    template <typename T>
    struct rv {
        T m_ref;
        explicit rv(T ref) : m_ref(ref) { }
    };

    template <typename T>
    struct fwd {
        const T *m_ptr;
        bool m_is_lvalue_ref;
        fwd(const T& ref) : m_ptr(&ref), m_is_lvalue_ref(true) { }
        fwd(const rv<T>& ref) : m_ptr(&ref.m_ref), m_is_lvalue_ref(false) { }
        fwd(const fwd<T>& ref) : m_ptr(ref.m_ptr), m_is_lvalue_ref(ref.m_is_lvalue_ref) { }
    };

    #ifdef OLD_COMPILER
        #define UNBOOST_RV_REF(type)    rv<type>
        #define UNBOOST_RV(value)       (value).m_ref
        #define UNBOOST_FWD_REF(type)   fwd<type>
        #define UNBOOST_FWD(value)      *(value).m_ptr
    #else
        #define UNBOOST_RV_REF(...)     const rv<__VA_ARGS__>&
        #define UNBOOST_RV(...)         (__VA_ARGS__).m_ref
        #define UNBOOST_FWD_REF(...)    fwd<__VA_ARGS__>
        #define UNBOOST_FWD(...)        *(__VA_ARGS__).m_ptr
    #endif

    namespace unboost {
        //
        // remove_reference<T>
        //
        template <typename T>
        struct remove_reference {
            typedef T type;
        };
        template <typename T>
        struct remove_reference<T&> {
            typedef T type;
        };
        template <typename T>
        struct remove_reference<const T&> {
            typedef T type;
        };
        template <typename T>
        struct remove_reference<rv<T> > {
            typedef T type;
        };
        template <typename T>
        struct remove_reference<rv<T>&> {
            typedef T type;
        };
        template <typename T>
        struct remove_reference<const rv<T>&> {
            typedef T type;
        };

        //
        // move<T>
        //
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

        #define UNBOOST_MOVE        unboost::move
        #define UNBOOST_FORWARD(f)  unboost::forward
    } // namespace unboost
#endif

// (1)
template <typename ARG1>
void emplace(const ARG1& arg1) {
    std::cout << "(1)" << std::endl;
    std::cout << arg1 << std::endl;
}

// (2)
template <typename ARG1>
void emplace(UNBOOST_RV_REF(ARG1) arg1) {
    std::cout << "(2)" << std::endl;
    std::cout << UNBOOST_RV(arg1) << std::endl;
}

int main(void) {
    emplace("test1");
    emplace(UNBOOST_MOVE(std::string("test2")));
    return 0;
}
