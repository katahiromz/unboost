// ratio.hpp --- Unboost ratio
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_RATIO_HPP_
#define UNBOOST_RATIO_HPP_

#include "unboost.hpp"
#include "static_assert.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_RATIO) + defined(UNBOOST_USE_BOOST_RATIO) + defined(UNBOOST_USE_UNBOOST_RATIO)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_RATIO
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_RATIO
    #else
        #ifdef UNBOOST_CXX11
            #define UNBOOST_USE_CXX11_RATIO
        #elif defined(_MSC_VER)
            #if (_MSC_VER >= 1700)
                // Visual C++ 2012 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_RATIO
                #else
                    #define UNBOOST_USE_UNBOOST_RATIO
                #endif
            #else
                #define UNBOOST_USE_UNBOOST_RATIO
            #endif
        #else
            #define UNBOOST_USE_UNBOOST_RATIO
        #endif
    #endif
#endif

// NOTE: Unboost's unboost::ratio uses 32-bit integers (_ratio_intmax_t).

namespace unboost {
    #if defined(UNBOOST_USE_CXX11_RATIO) || defined(UNBOOST_USE_BOOST_RATIO)
        typedef _int64_t _ratio_intmax_t;
        typedef _uint64_t _ratio_uintmax_t;
    #else
        typedef int _ratio_intmax_t;
        typedef unsigned int _ratio_uintmax_t;
    #endif

    template <_ratio_intmax_t N>
    struct _SIGN {
        enum { value = ((N < 0) ? -1 : 1) };
    };

    template <_ratio_intmax_t N>
    struct _ABS {
        enum { value = ((N < 0) ? -N : N) };
    };

    template <_ratio_intmax_t A, _ratio_intmax_t B>
    struct _GCD0 {
        enum { value = _GCD0<B, A % B>::value };
    };
    template <_ratio_intmax_t A>
    struct _GCD0<A, 0> {
        enum { value = A };
    };
    template <_ratio_intmax_t B>
    struct _GCD0<0, B> {
        enum { value = B };
    };
    template <_ratio_intmax_t A, _ratio_intmax_t B>
    struct _GCD {
        enum { value = _ABS<_GCD0<A, B>::value>::value };
    };

    inline _ratio_intmax_t _sign(_ratio_intmax_t x) {
        return (x < 0 ? -1 : 1);
    }
    inline _ratio_intmax_t _abs(_ratio_intmax_t x) {
        return (x < 0 ? -x : x);
    }
    inline _ratio_intmax_t _gcd0(_ratio_intmax_t x, _ratio_intmax_t y) {
        if (x == 0)
            return y;
        if (y == 0)
            return x;
        return _gcd0(y, x % y);
    }
    inline _ratio_intmax_t _gcd(_ratio_intmax_t x, _ratio_intmax_t y) {
        return _abs(_gcd0(x, y));
    }

    #if !defined(UNBOOST_USE_CXX11_RATIO) && !defined(UNBOOST_USE_BOOST_RATIO)
        inline _int64_t _sign(_int64_t x) {
            return (x < 0 ? -1 : 1);
        }
        inline _int64_t _abs(_int64_t x) {
            return (x < 0 ? -x : x);
        }
        inline _int64_t _gcd0(_int64_t x, _int64_t y) {
            if (x == 0)
                return y;
            if (y == 0)
                return x;
            return _gcd0(y, x % y);
        }
        inline _int64_t _gcd(_int64_t x, _int64_t y) {
            return _abs(_gcd0(x, y));
        }
    #endif
} // namespace unboost

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
    #include <boost/ratio.hpp>
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
        using boost::atto;
        using boost::femto;
        using boost::pico;
        using boost::nano;
        using boost::micro;
        using boost::milli;
        using boost::centi;
        using boost::deci;
        using boost::deca;
        using boost::hecto;
        using boost::kilo;
        using boost::mega;
        using boost::giga;
        using boost::tera;
        using boost::peta;
        using boost::exa;
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
            UNBOOST_STATIC_ASSERT_MSG(R2::num != 0, "division by 0");
            enum {
                _Num = R1::num * R2::den,
                _Den = R1::den * R2::num,
                num = _SIGN<_Num>::value * _SIGN<_Den>::value * _ABS<_Num>::value / _GCD<_Num, _Den>::value,
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

        //typedef ratio<1, 1000000000000000000000000LL> yocto;
        //typedef ratio<1, 1000000000000000000000LL> zepto;
        //typedef ratio<1, 1000000000000000000LL> atto;
        //typedef ratio<1, 1000000000000000LL> femto;
        //typedef ratio<1, 1000000000000LL> pico;
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
        //typedef ratio<1000000000000LL, 1> tera;
        //typedef ratio<1000000000000000LL, 1> peta;
        //typedef ratio<1000000000000000000LL, 1> exa;
        //typedef ratio<1000000000000000000000LL, 1> zetta;
        //typedef ratio<1000000000000000000000000LL, 1> yotta;
    } // namespace unboost
    #define unboost_auto_ratio unboost::auto_ratio
#else
    #error Your compiler is not supported yet. You lose.
#endif

namespace unboost {
    struct auto_ratio {
        typedef auto_ratio type;
        _int64_t num;
        _int64_t den;

        auto_ratio() : num(0), den(1) { }
        auto_ratio(_int64_t N, _int64_t D) {
            num = _sign(N) * _sign(D) * _abs(N) / _gcd(N, D);
            den = _abs(D) / _gcd(N, D);
        }
        auto_ratio(const auto_ratio& ar) : num(ar.num), den(ar.den) { }

        template <_ratio_intmax_t Num, _ratio_intmax_t Den>
        auto_ratio(const ratio<Num, Den>& r) {
            num = ratio<Num, Den>::num;
            den = ratio<Num, Den>::den;
        }
        template <class R1, class R2>
        auto_ratio(const ratio_add<R1, R2>& r) {
            num = ratio_add<R1, R2>::num;
            den = ratio_add<R1, R2>::den;
        }
        template <class R1, class R2>
        auto_ratio(const ratio_subtract<R1, R2>& r) {
            num = ratio_subtract<R1, R2>::num;
            den = ratio_subtract<R1, R2>::den;
        }
        template <class R1, class R2>
        auto_ratio(const ratio_multiply<R1, R2>& r) {
            num = ratio_multiply<R1, R2>::num;
            den = ratio_multiply<R1, R2>::den;
        }
        template <class R1, class R2>
        auto_ratio(const ratio_divide<R1, R2>& r) {
            num = ratio_divide<R1, R2>::num;
            den = ratio_divide<R1, R2>::den;
        }

        auto_ratio& operator=(const auto_ratio& ar) {
            num = ar.num;
            den = ar.den;
            return *this;
        }
        template <_ratio_intmax_t Num, _ratio_intmax_t Den>
        auto_ratio& operator=(const ratio<Num, Den>& r) {
            num = ratio<Num, Den>::num;
            den = ratio<Num, Den>::den;
            return *this;
        }
        template <class R1, class R2>
        auto_ratio& operator=(const ratio_add<R1, R2>& r) {
            num = ratio_add<R1, R2>::num;
            den = ratio_add<R1, R2>::den;
            return *this;
        }
        template <class R1, class R2>
        auto_ratio& operator=(const ratio_subtract<R1, R2>& r) {
            num = ratio_subtract<R1, R2>::num;
            den = ratio_subtract<R1, R2>::den;
            return *this;
        }
        template <class R1, class R2>
        auto_ratio& operator=(const ratio_multiply<R1, R2>& r) {
            num = ratio_multiply<R1, R2>::num;
            den = ratio_multiply<R1, R2>::den;
            return *this;
        }
        template <class R1, class R2>
        auto_ratio& operator=(const ratio_divide<R1, R2>& r) {
            num = ratio_divide<R1, R2>::num;
            den = ratio_divide<R1, R2>::den;
            return *this;
        }
    }; // struct auto_ratio

    inline auto_ratio
    operator+(const auto_ratio& ar1, const auto_ratio& ar2) {
        _int64_t _Num = ar1.num * ar2.den + ar2.num * ar1.den;
        _int64_t _Den = ar1.den * ar2.den;
        _int64_t num = _sign(_Num) * _sign(_Den) *
                              _abs(_Num) / _gcd(_Num, _Den);
        _int64_t den = _abs(_Den) / _gcd(_Num, _Den);
        return auto_ratio(num, den);
    }
    inline auto_ratio
    operator-(const auto_ratio& ar1, const auto_ratio& ar2) {
        _int64_t _Num = ar1.num * ar2.den - ar2.num * ar1.den;
        _int64_t _Den = ar1.den * ar2.den;
        _int64_t num = _sign(_Num) * _sign(_Den) *
                              _abs(_Num) / _gcd(_Num, _Den);
        _int64_t den = _abs(_Den) / _gcd(_Num, _Den);
        return auto_ratio(num, den);
    }
    inline auto_ratio
    operator*(const auto_ratio& ar1, const auto_ratio& ar2) {
        _int64_t _Num = ar1.num * ar2.num;
        _int64_t _Den = ar1.den * ar2.den;
        _int64_t num = _sign(_Num) * _sign(_Den) * _abs(_Num) /
                              _gcd(_Num, _Den);
        _int64_t den = _abs(_Den) / _gcd(_Num, _Den);
        return auto_ratio(num, den);
    }
    inline auto_ratio
    operator/(const auto_ratio& ar1, const auto_ratio& ar2) {
        _int64_t _Num = ar1.num * ar2.den;
        _int64_t _Den = ar1.den * ar2.num;
        _int64_t num = _sign(_Num) * _sign(_Den) * _abs(_Num) /
                              _gcd(_Num, _Den);
        _int64_t den = _abs(_Den) / _gcd(_Num, _Den);
        return auto_ratio(num, den);
    }
    inline bool
    operator==(const auto_ratio& ar1, const auto_ratio& ar2) {
        return ar1.num == ar2.num && ar1.den == ar2.den;
    }
    inline bool
    operator!=(const auto_ratio& ar1, const auto_ratio& ar2) {
        return ar1.num == ar2.num && ar1.den == ar2.den;
    }
} // namespace unboost

#endif  // ndef UNBOOST_RATIO_HPP_
