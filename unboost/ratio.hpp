// ratio.hpp --- Unboost ratio
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_RATIO_HPP_
#define UNBOOST_RATIO_HPP_

#include "unboost.hpp"

namespace unboost {
    typedef int _ratio_intmax_t;
    typedef unsigned int _ratio_uintmax_t;

    template <_ratio_intmax_t N>
    struct _SIGN {
        enum { value = (N < 0 ? -1 : 1) };
    };

    template <_ratio_intmax_t N>
    struct _ABS {
        enum { value = (N < 0 ? -N : N) };
    };

    template <_ratio_intmax_t A, _ratio_intmax_t B>
    struct _GCD {
        enum { value = _GCD<B, A % B>::value };
    };
    template <_ratio_intmax_t A>
    struct _GCD<A, 0> {
        enum { value = A };
    };
    template <_ratio_intmax_t B>
    struct _GCD<0, B> {
        enum { value = B };
    };

    inline _ratio_intmax_t _gcd(_ratio_intmax_t x, _ratio_intmax_t y) {
        if (x == 0 && y == 0)
            return 1;
        if (x == 0)
            return y;
        if (y == 0)
            return x;
        return _gcd(y, x % y);
    }
} // namespace unboost

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_RATIO) + defined(UNBOOST_USE_BOOST_RATIO) + defined(UNBOOST_USE_UNBOOST_RATIO)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_RATIO
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_RATIO
    #else
        #define UNBOOST_USE_UNBOOST_RATIO
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_RATIO
    #include <ratio>
    namespace unboost {
        using std::ratio;
        using std::ratio_add;
        using std::ratio_subtract;
        using std::ratio_multiply;
        using std::ratio_divide;
        using std::ratio_equal;
        using std::ratio_not_equal;
        using std::ratio_less;
        using std::ratio_less_equal;
        using std::ratio_greater;
        using std::ratio_greater_equal;
        //yocto
        //zepto
        typedef ratio<1, 1000000000000000000> atto;
        typedef ratio<1, 1000000000000000> femto;
        typedef ratio<1, 1000000000000> pico;
        typedef ratio<1, 1000000000> nano;
        typedef ratio<1, 1000000> micro;
        typedef ratio<1, 1000> milli;
        typedef ratio<1, 100> centi;
        typedef ratio<1, 10> deci;
        typedef ratio<10, 1> deca;
        typedef ratio<100, 1> hecto;
        typedef ratio<1000, 1> kilo;
        typedef ratio<1000000, 1> mega;
        typedef ratio<1000000000, 1> giga;
        typedef ratio<1000000000000, 1> tera;
        typedef ratio<1000000000000000, 1> peta;
        typedef ratio<1000000000000000000, 1> exa;
        //zetta
        //yotta
    } // namespace unboost
    #define unboost_auto_ratio auto
#elif defined(UNBOOST_USE_BOOST_RATIO)
    #include <boost/ratio/ratio.hpp>
    #include <boost/ratio/ratio_io.hpp>
    namespace unboost {
        using boost::ratio;
        using boost::ratio_add;
        using boost::ratio_subtract;
        using boost::ratio_multiply;
        using boost::ratio_divide;
        using boost::ratio_equal;
        using boost::ratio_not_equal;
        using boost::ratio_less;
        using boost::ratio_less_equal;
        using boost::ratio_greater;
        using boost::ratio_greater_equal;
        //yocto
        //zepto
        typedef ratio<1, 1000000000000000000> atto;
        typedef ratio<1, 1000000000000000> femto;
        typedef ratio<1, 1000000000000> pico;
        typedef ratio<1, 1000000000> nano;
        typedef ratio<1, 1000000> micro;
        typedef ratio<1, 1000> milli;
        typedef ratio<1, 100> centi;
        typedef ratio<1, 10> deci;
        typedef ratio<10, 1> deca;
        typedef ratio<100, 1> hecto;
        typedef ratio<1000, 1> kilo;
        typedef ratio<1000000, 1> mega;
        typedef ratio<1000000000, 1> giga;
        typedef ratio<1000000000000, 1> tera;
        typedef ratio<1000000000000000, 1> peta;
        typedef ratio<1000000000000000000, 1> exa;
        //zetta
        //yotta
    } // namespace unboost
    #define unboost_auto_ratio auto
#elif defined(UNBOOST_USE_UNBOOST_RATIO)
    namespace unboost {
        template <_ratio_intmax_t N, _ratio_intmax_t D = 1>
        class ratio {
        public:
            typedef ratio<N, D> type;
            enum {
                num = _SIGN<N>::value * _SIGN<D>::value *
                      _ABS<N>::value / _GCD<N, D>::value,
                den = _ABS<D>::value / _GCD<N, D>::value
            };
        };

        template <class R1, class R2>
        class ratio_add {
        public:
            typedef ratio_add<R1, R2> type;
            enum {
                _Num = R1::num * R2::den + R2::num * R1::den,
                _Den = R1::den * R2::den,
                num = _SIGN<_Num>::value * _SIGN<_Den>::value *
                      _ABS<_Num>::value / _GCD<_Num, _Den>::value,
                den = _ABS<_Den>::value / _GCD<_Num, _Den>::value
            };
        };

        template <class R1, class R2>
        class ratio_subtract {
        public:
            typedef ratio_subtract<R1, R2> type;
            enum {
                _Num = R1::num * R2::den - R2::num * R1::den,
                _Den = R1::den * R2::den,
                num = _SIGN<_Num>::value * _SIGN<_Den>::value *
                      _ABS<_Num>::value / _GCD<_Num, _Den>::value,
                den = _ABS<_Den>::value / _GCD<_Num, _Den>::value
            };
        };

        template <class R1, class R2>
        class ratio_multiply {
        public:
            typedef ratio_multiply<R1, R2> type;
            enum {
                _Num = R1::num * R2::num,
                _Den = R1::den * R2::den,
                num = _SIGN<_Num>::value * _SIGN<_Den>::value * _ABS<_Num>::value /
                      _GCD<_Num, _Den>::value,
                den = _ABS<_Den>::value / _GCD<_Num, _Den>::value
            };
        };

        template <class R1, class R2>
        class ratio_divide {
        public:
            typedef ratio_divide<R1, R2> type;
            enum {
                _Num = R1::num * R2::den,
                _Den = R1::den * R2::num,
                num = _SIGN<_Num>::value * _SIGN<_Den>::value *
                      _ABS<_Num>::value / _GCD<_Num, _Den>::value,
                den = _ABS<_Den>::value / _GCD<_Num, _Den>::value
            };
        };

        template <class R1, class R2>
        struct ratio_equal {
            typedef ratio_equal<R1, R2> type;
            enum {
                value = ((_ratio_intmax_t)R1::num == (_ratio_intmax_t)R2::num &&
                         (_ratio_intmax_t)R1::den == (_ratio_intmax_t)R2::den)
            };
            typedef bool value_type;
            operator value_type() const { return value; }
            value_type operator()() const { return value; }
        };

        template <class R1, class R2>
        struct ratio_not_equal {
            typedef ratio_not_equal<R1, R2> type;
            enum {
                value = (R1::num != R2::num || R1::den != R2::den)
            };
            typedef bool value_type;
            operator value_type() const { return value; }
        };

        template <class R1, class R2>
        struct ratio_less {
            typedef ratio_less<R1, R2> type;
            enum {
                value = (R1::num * R2::den < R2::num * R1::den)
            };
            typedef bool value_type;
            operator value_type() const { return value; }
        };

        template <class R1, class R2>
        struct ratio_less_equal {
            typedef ratio_less_equal<R1, R2> type;
            enum {
                value = (R1::num * R2::den <= R2::num * R1::den)
            };
            typedef bool value_type;
            operator value_type() const { return value; }
        };

        template <class R1, class R2>
        struct ratio_greater {
            typedef ratio_greater<R1, R2> type;
            enum {
                value = (R1::num * R2::den > R2::num * R1::den)
            };
            typedef bool value_type;
            operator value_type() const { return value; }
        };

        template <class R1, class R2>
        struct ratio_greater_equal {
            typedef ratio_greater_equal<R1, R2> type;
            enum {
                value = (R1::num * R2::den >= R2::num * R1::den)
            };
            typedef bool value_type;
            operator value_type() const { return value; }
        };

        //static const ratio<1, 1000000000000000000000000LL> yocto;
        //static const ratio<1, 1000000000000000000000LL> zepto;
        //static const ratio<1, 1000000000000000000LL> atto;
        //static const ratio<1, 1000000000000000LL> femto;
        //static const ratio<1, 1000000000000LL> pico;
        static const ratio<1, 1000000000> nano;
        static const ratio<1, 1000000> micro;
        static const ratio<1, 1000> milli;
        static const ratio<1, 100> centi;
        static const ratio<1, 10> deci;
        static const ratio<10, 1> deca;
        static const ratio<100, 1> hecto;
        static const ratio<1000, 1> kilo;
        static const ratio<1000000, 1> mega;
        static const ratio<1000000000, 1> giga;
        //static const ratio<1000000000000LL, 1> tera;
        //static const ratio<1000000000000000LL, 1> peta;
        //static const ratio<1000000000000000000LL, 1> exa;
        //static const ratio<1000000000000000000000LL, 1> zetta;
        //static const ratio<1000000000000000000000000LL, 1> yotta;

        struct auto_ratio {
            typedef auto_ratio type;
            _ratio_intmax_t num;
            _ratio_intmax_t den;

            auto_ratio() : num(1), den(1) { }
            auto_ratio(_ratio_intmax_t n, _ratio_intmax_t d) : num(n), den(d) { }
            auto_ratio(const auto_ratio& ar) : num(ar.num), den(ar.den) { }

            template <_ratio_intmax_t Num, _ratio_intmax_t Den>
            auto_ratio(const ratio<Num, Den>&) {
                num = ratio<Num, Den>::num;
                den = ratio<Num, Den>::den;
            }
            template <class R1, class R2>
            auto_ratio(const ratio_add<R1, R2>&) {
                num = ratio_add<R1, R2>::num;
                den = ratio_add<R1, R2>::den;
            }
            template <class R1, class R2>
            auto_ratio(const ratio_subtract<R1, R2>&) {
                num = ratio_subtract<R1, R2>::num;
                den = ratio_subtract<R1, R2>::den;
            }
            template <class R1, class R2>
            auto_ratio(const ratio_multiply<R1, R2>&) {
                num = ratio_multiply<R1, R2>::num;
                den = ratio_multiply<R1, R2>::den;
            }
            template <class R1, class R2>
            auto_ratio(const ratio_divide<R1, R2>&) {
                num = ratio_divide<R1, R2>::num;
                den = ratio_divide<R1, R2>::den;
            }

            auto_ratio& operator=(const auto_ratio& ar) {
                num = ar.num;
                den = ar.den;
                return *this;
            }
            template <_ratio_intmax_t Num, _ratio_intmax_t Den>
            auto_ratio& operator=(const ratio<Num, Den>&) {
                num = ratio<Num, Den>::num;
                den = ratio<Num, Den>::den;
                return *this;
            }
            template <class R1, class R2>
            auto_ratio& operator=(const ratio_add<R1, R2>&) {
                num = ratio_add<R1, R2>::num;
                den = ratio_add<R1, R2>::den;
                return *this;
            }
            template <class R1, class R2>
            auto_ratio& operator=(const ratio_subtract<R1, R2>&) {
                num = ratio_subtract<R1, R2>::num;
                den = ratio_subtract<R1, R2>::den;
                return *this;
            }
            template <class R1, class R2>
            auto_ratio& operator=(const ratio_multiply<R1, R2>&) {
                num = ratio_multiply<R1, R2>::num;
                den = ratio_multiply<R1, R2>::den;
                return *this;
            }
            template <class R1, class R2>
            auto_ratio& operator=(const ratio_divide<R1, R2>&) {
                num = ratio_divide<R1, R2>::num;
                den = ratio_divide<R1, R2>::den;
                return *this;
            }
        }; // struct auto_ratio
    } // namespace unboost
    #define unboost_auto_ratio unboost::auto_ratio
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_RATIO_HPP_
