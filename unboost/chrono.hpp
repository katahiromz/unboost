// chrono.hpp --- Unboost chrono
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_CHRONO_HPP_
#define UNBOOST_CHRONO_HPP_

#include <unboost/core.hpp>
#include <unboost/ratio.hpp>

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_CHRONO) + defined(UNBOOST_USE_BOOST_CHRONO) + defined(UNBOOST_USE_WIN32_CHRONO) + defined(UNBOOST_USE_POSIX_CHRONO)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_CHRONO
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_CHRONO
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_CHRONO
        #elif defined(_MSC_VER)
            #if (_MSC_VER >= 1700)
                // Visual C++ 2012 and later
                #define UNBOOST_USE_CXX11_CHRONO
            #else
                #ifdef _WIN32
                    #define UNBOOST_USE_WIN32_CHRONO
                #else
                    #define UNBOOST_USE_POSIX_CHRONO
                #endif
            #endif
        #else
            #ifdef _WIN32
                #define UNBOOST_USE_WIN32_CHRONO
            #else
                #define UNBOOST_USE_POSIX_CHRONO
            #endif
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_CHRONO
    #include <chrono>
    namespace unboost {
        namespace chrono {
            using std::chrono::duration;
            using std::chrono::duration_cast;
            using std::chrono::system_clock;
            using std::chrono::steady_clock;
            using std::chrono::high_resolution_clock;
            using std::chrono::time_point;
            using std::chrono::treat_as_floating_point;
            using std::chrono::duration_values;
            using std::chrono::nanoseconds;
            using std::chrono::microseconds;
            using std::chrono::milliseconds;
            using std::chrono::seconds;
            using std::chrono::minutes;
            using std::chrono::hours;
            using std::chrono::time_point_cast;
        } // namespace chrono
    } // namespace unboost
    #define unboost_auto_duration auto
#elif defined(UNBOOST_USE_BOOST_CHRONO)
    #include <boost/chrono/include.hpp>
    namespace unboost {
        namespace chrono {
            using boost::chrono::duration;
            using boost::chrono::duration_cast;
            using boost::chrono::system_clock;
            using boost::chrono::steady_clock;
            using boost::chrono::high_resolution_clock;
            using boost::chrono::time_point;
            using boost::chrono::treat_as_floating_point;
            using boost::chrono::duration_values;
            using boost::chrono::nanoseconds;
            using boost::chrono::microseconds;
            using boost::chrono::milliseconds;
            using boost::chrono::seconds;
            using boost::chrono::minutes;
            using boost::chrono::hours;
            using boost::chrono::time_point_cast;
        } // namespace chrono
    } // namespace unboost
    #define unboost_auto_duration auto
#elif defined(UNBOOST_USE_WIN32_CHRONO) || defined(UNBOOST_USE_POSIX_CHRONO)
    #include <limits>
    #include <cfloat>
    #include <ctime>
    #ifdef _WIN32
        #ifndef _INC_WINDOWS
            #include <windows.h>
        #endif
    #endif
    namespace unboost {
        namespace chrono {
            template <class Rep>
            struct treat_as_floating_point {
                static const bool value = false;
            };

            template <class Rep>
            struct duration_values {
                static const Rep zero() { return Rep(0); }
                static const Rep min() {
                    Rep r = 0.1;
                    if ((int)r == 0) {
                        return std::numeric_limits<Rep>::min();
                    } else {
                        if (sizeof(Rep) == sizeof(float)) {
                            return -FLT_MAX;
                        }
                        if (sizeof(Rep) == sizeof(double)) {
                            return -DBL_MAX;
                        }
                        if (sizeof(Rep) == sizeof(long double)) {
                            return -LDBL_MAX;
                        }
                    }
                    return 0;
                }
                static const Rep max() {
                    return std::numeric_limits<Rep>::max();
                }
            };

            template <class Rep, class Period>
            class duration;

            struct auto_duration {
                typedef uintmax_t       rep;
                typedef auto_ratio      period;
                typedef auto_duration   type;

                rep             m_rep;
                period          m_period;

                auto_duration() : m_rep(), m_period(unboost::ratio<1>()) { }

                explicit auto_duration(const rep& r) :
                    m_rep(r), m_period(unboost::ratio<1>()) { }

                auto_duration(const rep& r, const auto_ratio& ar) :
                    m_rep(r), m_period(ar) { }

                auto_duration(const auto_duration& ad) :
                    m_rep(ad.m_rep), m_period(ad.m_period) { }

                template <class Rep, class Period>
                auto_duration(const duration<Rep, Period>& d) :
                    m_rep(d.m_rep), m_period(Period()) { }

                template <class Rep, class Period>
                auto_duration& operator=(const duration<Rep, Period>& d) {
                    m_rep = d.m_rep;
                    m_period = Period();
                    return *this;
                }

                rep count() const { return m_rep; }
                static const type zero() {
                    return type(duration_values<rep>::zero());
                }
                static const type min() {
                    return type(duration_values<rep>::min());
                }
                static const type max() {
                    return type(duration_values<rep>::max());
                }

                type& operator++() {
                    ++m_rep;
                    return *this;
                }
                type& operator--() {
                    --m_rep;
                    return *this;
                }
                type operator++(int) {
                    return type(m_rep++, m_period);
                }
                type operator--(int) {
                    return type(m_rep--, m_period);
                }
                type& operator+=(const type& d) {
                    if (d.m_period.num == m_period.num && d.m_period.den == m_period.den) {
                        m_rep += d.count();
                    } else {
                        m_rep += d.count() * d.m_period.num / m_period.num
                                           * d.m_period.den / m_period.den;
                    }
                    return *this;
                }
                type& operator-=(const type& d) {
                    if (d.m_period.num == m_period.num && d.m_period.den == m_period.den) {
                        m_rep -= d.count();
                    } else {
                        m_rep -= d.count() * d.m_period.num / m_period.num
                                           * d.m_period.den / m_period.den;
                    }
                    return *this;
                }
                type& operator*=(const rep& rhs) {
                    m_rep *= rhs;
                    return *this;
                }
                type& operator/=(const rep& rhs) {
                    m_rep /= rhs;
                    return *this;
                }
                type& operator%=(const rep& rhs) {
                    m_rep %= rhs;
                    return *this;
                }
                type& operator%=(const type& rhs) {
                    m_rep %= rhs.count();
                    return *this;
                }
            };

            template <class Rep, class Period = unboost::ratio<1> >
            class duration {
            public:
                typedef Rep rep;
                typedef Period period;
                typedef duration<Rep, Period> type;

                rep m_rep;

                duration() { }

                template <class Rep2>
                explicit duration(const Rep2& r) : m_rep(r) { }

                template <class Rep2, class Period2>
                duration(const duration<Rep2, Period2>& d) :
                    m_rep((d.m_rep * Period2::num) / Period2::den) { }

                rep count() const { return m_rep; }
                static const type zero() {
                    return type(duration_values<rep>::zero());
                }
                static const type min() {
                    return type(duration_values<rep>::min());
                }
                static const type max() {
                    return type(duration_values<rep>::max());
                }
                type& operator++() {
                    ++m_rep;
                    return *this;
                }
                type& operator--() {
                    --m_rep;
                    return *this;
                }
                type operator++(int) {
                    return type(m_rep++);
                }
                type operator--(int) {
                    return type(m_rep--);
                }
                type& operator+=(const type& d) {
                    m_rep += d.count();
                    return *this;
                }
                type& operator-=(const type& d) {
                    m_rep -= d.count();
                    return *this;
                }
                type& operator*=(const rep& rhs) {
                    m_rep *= rhs;
                    return *this;
                }
                type& operator/=(const rep& rhs) {
                    m_rep /= rhs;
                    return *this;
                }
                type& operator%=(const rep& rhs) {
                    m_rep %= rhs;
                    return *this;
                }
                type& operator%=(const type& rhs) {
                    m_rep %= rhs.count();
                    return *this;
                }
            }; // class duration

            inline auto_duration operator+(const auto_duration& ad) {
                return ad;
            }
            inline auto_duration operator-(const auto_duration& ad) {
                return auto_duration(-(intmax_t)ad.m_rep, ad.m_period);
            }

            inline auto_duration operator+(const auto_duration& lhs, const auto_duration& rhs) {
                auto_ratio ar(1, _gcd(lhs.m_period.den, rhs.m_period.den));
                auto_duration ret(0, ar);
                ret += lhs;
                ret += rhs;
                return ret;
            }
            inline auto_duration operator-(const auto_duration& lhs, const auto_duration& rhs) {
                return lhs + (-rhs);
            }
            inline auto_duration operator*(const auto_duration& d, uintmax_t r) {
                auto_duration ret;
                ret.m_rep = d.m_rep * r;
                ret.m_period = d.m_period;
                return ret;
            }
            inline auto_duration operator*(uintmax_t r, const auto_duration& d) {
                auto_duration ret;
                ret.m_rep = d.m_rep * r;
                ret.m_period = d.m_period;
                return ret;
            }
            inline auto_duration operator/(const auto_duration& d, uintmax_t r) {
                auto_duration ret;
                ret.m_rep = d.m_rep / r;
                ret.m_period = d.m_period;
                return ret;
            }
            inline auto_duration operator%(const auto_duration& d, uintmax_t r) {
                auto_duration ret;
                ret.m_rep = d.m_rep % r;
                ret.m_period = d.m_period;
                return ret;
            }

            typedef duration<uintmax_t, ratio<1, 1000000> > microseconds;
            typedef duration<uintmax_t, ratio<1, 1000> >    milliseconds;
            typedef duration<uintmax_t>                     seconds;
            typedef duration<uintmax_t, ratio<60> >         minutes;
            typedef duration<uintmax_t, ratio<3600> >       hours;

            inline auto_duration _duration_cast_inner(const auto_ratio& r, const auto_duration& d) {
                auto_duration ad(d.m_rep * r.den * d.m_period.num
                                 / d.m_period.den / r.num, r);
                return ad;
            }

            template <class D>
            inline auto_duration duration_cast(const auto_duration& d) {
                typename D::period p;
                auto_ratio r(p);
                return _duration_cast_inner(r, d);
            }

            template <class D, class Rep2, class Period2>
            inline auto_duration duration_cast(const duration<Rep2, Period2>& d) {
                typedef typename D::period Period1;
                Period1 p;
                auto_duration ad(d.m_rep * Period1::den * Period2::num
                                 / Period2::den / Period1::num, p);
                return ad;
            }

            #ifdef UNBOOST_USE_WIN32_CHRONO
                // FIXME: define time_point
            #elif defined(UNBOOST_USE_POSIX_CHRONO)
                // FIXME: define time_point
            #else
                #error You lose.
            #endif
        } // namespace chrono
    } // namespace unboost
    #define unboost_auto_duration unboost::chrono::auto_duration
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_CHRONO_HPP_
