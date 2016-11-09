// rv_ref.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <utility>                      // for std::move, std::forward
    #define UNBOOST_RV_REF(type)    type&&
    #define UNBOOST_RV(value)       value
    #define UNBOOST_FWD_REF(type)   type&&
    #define UNBOOST_FWD(value)      value
#elif defined(BOOST)
    #include <boost/move/core.hpp>          // for boost::move
    #include <boost/move/utility.hpp>       // for boost::forward
    #define UNBOOST_RV_REF(type)    BOOST_RV_REF(type)
    #define UNBOOST_RV(value)       value
    #define UNBOOST_FWD_REF(type)   BOOST_FWD_REF(type)
    #define UNBOOST_FWD(value)      value
#else   // Unboost
    #include "unboost/move/core.hpp"        // for unboost::move
    #include "unboost/move/utility.hpp"     // for unboost::forward
#endif

#ifdef CXX11
    using std::move;
    using std::forward;
#elif defined(BOOST)
    using boost::move;
    using boost::forward;
#else
    using unboost::move;
    using unboost::forward;
#endif

struct X {
    int *m_px;

    X(int x) : m_px(new int(x)) {
        std::cout << "ctor" << std::endl;
    }
    X(const X& x) : m_px(new int(*x.m_px)) {
        std::cout << "copy ctor" << std::endl;
    }
    X(UNBOOST_RV_REF(X) x) : m_px(UNBOOST_RV(x).m_px) {
        UNBOOST_RV(x).m_px = NULL;
        std::cout << "move ctor" << std::endl;
    }

    X& operator=(const X& x) {
        std::cout << "copy assignment" << std::endl;
        if (this != &x) {
            delete m_px;
            m_px = new int(*x.m_px);
        }
        return *this;
    }
    X& operator=(UNBOOST_RV_REF(X) x) {
        std::cout << "move assignment" << std::endl;
        if (this != &UNBOOST_RV(x)) {
            delete m_px;
            m_px = UNBOOST_RV(x).m_px;
            UNBOOST_RV(x).m_px = NULL;
        }
        return *this;
    }
    ~X() {
        delete m_px;
    }

    template <typename T>
    void do_it(UNBOOST_FWD_REF(T) t) {
        make_great_america_again(forward<T>(UNBOOST_FWD(t)));
    }

    void make_great_america_again(const X& x) {
        std::cout << "(1)" << *x.m_px << std::endl;
    }
    void make_great_america_again(UNBOOST_RV_REF(X) x) {
        std::cout << "(2)" << *UNBOOST_RV(x).m_px << std::endl;
    }
};

int main(void) {
    std::cout << "rv_ref" << std::endl;

    X x1(2);
    X x2(move(x1));
    x1 = move(x2);
    X x3(x1);
    x3.do_it(x1);
    x3.do_it(move(x1));

    std::cout << "success" << std::endl;
    return 0;
}
