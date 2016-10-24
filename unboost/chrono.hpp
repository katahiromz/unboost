// chrono.hpp --- Unboost chrono
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_CHRONO_HPP_
#define UNBOOST_CHRONO_HPP_

#include "unboost.hpp"
#include "type_traits.hpp"
#include "ratio.hpp"
#include <cmath>
#undef min
#undef max

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
    #include <limits>   // for std::numeric_limits
    #include <cfloat>   // for FLT_MAX
    #include <ctime>    // for time_t
    #ifdef _WIN32
        #ifndef _INC_WINDOWS
            #include <windows.h>
        #endif
    #endif
    namespace unboost {
        namespace chrono {
            template <class Rep>
            struct treat_as_floating_point : is_floating_point<Rep> { };

            template <class Rep>
            inline Rep _numeric_limits_lowest() {
                #ifdef UNBOOST_CXX11
                    return std::numeric_limits<Rep>::lowest();
                #else
                    Rep r = (Rep)0.1;
                    if ((int)r != 0) {
                        if (sizeof(Rep) == sizeof(float)) {
                            r = FLT_MAX;
                            return -r;
                        }
                        if (sizeof(Rep) == sizeof(double)) {
                            r = DBL_MAX;
                            return -r;
                        }
                        if (sizeof(Rep) == sizeof(long double)) {
                            r = LDBL_MAX;
                            return -r;
                        }
                    }
                    return std::numeric_limits<Rep>::min();
                #endif
            } // _numeric_limits_lowest

            template <class Rep>
            struct duration_values {
                static const Rep zero() { return Rep(0); }
                static const Rep min() {
                    return _numeric_limits_lowest<Rep>();
                }
                static const Rep max() {
                    return std::numeric_limits<Rep>::max();
                }
            };

            template <class Rep, class Period>
            class duration;

            class auto_duration;

            template <typename CT, typename Period1, typename Period2>
            struct _duration_common_type_helper {
            private:
                typedef _GCD<Period1::num, Period2::num> _gcd_num;
                typedef _GCD<Period1::den, Period2::den> _gcd_den;
                typedef typename CT::type _cr;
                typedef ratio<_gcd_num::value,
                    (Period1::den / _gcd_den::value) * Period2::den> _r;
            public:
                typedef duration<_cr, _r> type;
            };

            template <typename T1, typename T2>
            struct duration_common_type { };

            template <typename Rep1, typename Period1, typename Rep2, typename Period2>
            struct duration_common_type<duration<Rep1, Period1>,
                                        duration<Rep2, Period2> >
            {
                typedef typename _duration_common_type_helper<
                    common_type<Rep1, Rep2>, Period1, Period2>::type type;
            };

            auto_duration
            auto_duration_cast(const auto_duration& ad1,
                               const auto_duration& ad2);

            class auto_duration {
            public:
                typedef double rep;
                typedef auto_ratio period;
                typedef auto_duration type;

                auto_duration() : rep_(), period_(1, 1), is_floating_(false) { }

                template <class Rep2>
                explicit auto_duration(const Rep2& r) : rep_(r), period_() {
                    is_floating_ = (bool)is_floating_point<Rep2>::value;
                    fix_floating();
                }

                template <class Rep2, class Period2>
                auto_duration(const Rep2& r, Period2& p, bool is_floating = false) {
                    rep_ = r;
                    period_ = p;
                    is_floating_ = is_floating;
                    fix_floating();
                }

                template <class Rep2, class Period2>
                auto_duration(const duration<Rep2, Period2>& d) {
                    rep_ = static_cast<rep>(d.count());
                    period_ = Period2();
                    is_floating_ = (bool)unboost::is_floating_point<Rep2>::value;
                    fix_floating();
                }

                template <class Rep2, class Period2>
                auto_duration& operator=(const duration<Rep2, Period2>& d) {
                    rep_ = static_cast<rep>(d.count());
                    period_ = Period2();
                    is_floating_ = (bool)unboost::is_floating_point<Rep2>::value;
                    fix_floating();
                    return *this;
                }

                auto_duration(const auto_duration& ad) {
                    rep_ = auto_duration_cast(*this, ad).count();
                    period_ = ad.period_;
                    is_floating_ = ad.is_floating_;
                    fix_floating();
                }

                rep count() const { return rep_; }

                static const type zero() {
                    return type(duration_values<rep>::zero());
                }
                static const type min() {
                    return type(duration_values<rep>::min());
                }
                static const type max() {
                    return type(duration_values<rep>::max());
                }

                type operator+() const {
                    return *this;
                }
                type operator-() const {
                    return type(-rep_, period_, is_floating_);
                }

                type& operator++() {
                    rep_ += 1;
                    return *this;
                }
                type& operator--() {
                    rep_ -= 1;
                    return *this;
                }
                type operator++(int) {
                    type ad = *this;
                    rep_ += 1;
                    return ad;
                }
                type operator--(int) {
                    type ad = *this;
                    rep_ -= 1;
                    return ad;
                }

                type& operator+=(const type& d) {
                    rep_ += auto_duration_cast(*this, d).count();
                    fix_floating();
                    return *this;
                }
                type& operator-=(const type& d) {
                    rep_ -= auto_duration_cast(*this, d).count();
                    fix_floating();
                    return *this;
                }

                type& operator*=(rep rhs) {
                    rep_ *= rhs;
                    fix_floating();
                    return *this;
                }
                type& operator/=(rep rhs) {
                    rep_ /= rhs;
                    fix_floating();
                    return *this;
                }
                type& operator%=(const rep& rhs) {
                    rep_ = fmod(rep_, rhs);
                    return *this;
                }
                type& operator%=(const type& rhs) {
                    rep_ = fmod(rep_, auto_duration_cast(*this, rhs).count());
                    return *this;
                }

                void fix_floating() {
                    if (!is_floating_)
                        rep_ = rep(int(rep_));
                }

                friend inline auto_duration
                auto_duration_cast(const auto_duration& ad1,
                                   const auto_duration& ad2)
                {
                    typedef rep to_rep;
                    auto_ratio to_period = ad1.period_;
                    auto_ratio cf = ad2.period_ / to_period;
                    return auto_duration(
                        static_cast<to_rep>(ad2.count() * cf.num / cf.den),
                        to_period, ad1.is_floating_);
                }

                auto_ratio get_period() const { return period_; }
                bool is_floating() const { return is_floating_; }

            protected:
                rep         rep_;
                auto_ratio  period_;
                bool        is_floating_;
            }; // class auto_duration

            template <typename ToDur, class Rep, class Period>
            ToDur duration_cast(const duration<Rep, Period>& d);
            template <typename ToDur>
            ToDur duration_cast(const auto_duration& ad);

            template <class Rep, class Period = unboost::ratio<1> >
            class duration {
            public:
                typedef Rep rep;
                typedef Period period;
                typedef duration<Rep, Period> type;

                duration() { }

                template <class Rep2>
                explicit duration(const Rep2& r) : rep_(r) { }

                template <class Rep2, class Period2>
                duration(const duration<Rep2, Period2>& d) {
                    rep_ = duration_cast<type>(d).count();
                }

                explicit duration(const auto_duration& ad) {
                    rep_ = duration_cast<type>(ad).count();
                }

                rep count() const { return rep_; }
                static const type zero() {
                    return type(duration_values<rep>::zero());
                }
                static const type min() {
                    return type(duration_values<rep>::min());
                }
                static const type max() {
                    return type(duration_values<rep>::max());
                }

                type operator+() const {
                    return *this;
                }
                type operator-() const {
                    return type(-rep_);
                }

                type& operator++() {
                    ++rep_;
                    return *this;
                }
                type& operator--() {
                    --rep_;
                    return *this;
                }
                type operator++(int) {
                    return type(rep_++);
                }
                type operator--(int) {
                    return type(rep_--);
                }

                type& operator+=(const type& d) {
                    rep_ += d.count();
                    return *this;
                }
                type& operator-=(const type& d) {
                    rep_ -= d.count();
                    return *this;
                }

                type& operator*=(const rep& rhs) {
                    rep_ *= rhs;
                    return *this;
                }
                type& operator/=(const rep& rhs) {
                    rep_ /= rhs;
                    return *this;
                }
                type& operator%=(rep rhs) {
                    rep_ %= rhs;
                    return *this;
                }
                type& operator%=(const type& rhs) {
                    rep_ %= rhs.count();
                    return *this;
                }

            protected:
                rep rep_;
            }; // class duration

            template <class Rep1, class Period1, class Rep2, class Period2>
            typename duration_common_type<duration<Rep1, Period1>,
                                          duration<Rep2, Period2> >::type
            inline operator+(const duration<Rep1, Period1>& lhs,
                             const duration<Rep2, Period2>& rhs)
            {
                typedef typename duration_common_type<
                    duration<Rep1, Period1>,
                    duration<Rep2, Period2> >::type CD;
                return CD(CD(lhs).count() + CD(rhs).count());
            }

            template <class Rep1, class Period1, class Rep2, class Period2>
            inline typename common_type<duration<Rep1, Period1>,
                                        duration<Rep2, Period2> >::type
            operator-(const duration<Rep1, Period1>& lhs,
                      const duration<Rep2, Period2>& rhs)
            {
                typedef typename duration_common_type<
                    duration<Rep1, Period1>,
                    duration<Rep2, Period2> >::type CD;
                return CD(CD(lhs).count() - CD(rhs).count());
            }

            template <class Rep1, class Period, class Rep2>
            inline duration<typename common_type<Rep1, Rep2>::type, Period>
            operator*(const duration<Rep1, Period>& d, const Rep2& s) {
                typedef duration<typename common_type<Rep1, Rep2>::type, Period> CD;
                return CD(CD(d).count() * s);
            }

            template <class Rep1, class Period, class Rep2>
            inline duration<typename common_type<Rep1, Rep2>::type, Period>
            operator*(const Rep1& s, const duration<Rep2, Period>& d) {
                typedef duration<typename common_type<Rep1, Rep2>::type, Period> CD;
                return CD(CD(d).count() * s);
            }

            template <class Rep1, class Period, class Rep2>
            inline duration<typename common_type<Rep1, Rep2>::type, Period>
            operator/(const duration<Rep1, Period>& d, const Rep2& s ) {
                typedef duration<typename common_type<Rep1,Rep2>::type, Period> CD;
                return CD(CD(d).count() / s);
            }

            template <class Rep1, class Period1, class Rep2, class Period2>
            inline typename common_type<Rep1, Rep2>::type
            operator/(const duration<Rep1,Period1>& lhs,
                      const duration<Rep2,Period2>& rhs)
            {
                typedef typename common_type<Rep1, Rep2>::type CD;
                return CD(lhs).count() / CD(rhs).count();
            }

            template <class Rep1, class Period, class Rep2>
            inline duration<typename common_type<Rep1,Rep2>::type, Period>
            operator%(const duration<Rep1, Period>& d, const Rep2& s) {
                typedef duration<typename common_type<Rep1,Rep2>::type, Period> CD;
                return CD(CD(d).count() % s);
            }

            template <class Rep1, class Period1, class Rep2, class Period2>
            inline typename duration_common_type<duration<Rep1, Period1>,
                                                 duration<Rep2, Period2> >::type
            operator%(const duration<Rep1,Period1>& lhs,
                      const duration<Rep2,Period2>& rhs)
            {
                typedef typename duration_common_type<
                    duration<Rep1, Period1>,
                    duration<Rep2, Period2> >::type CD;
                return CD(CD(lhs).count() % CD(rhs).count());
            }

            template <class Rep1, class Period1, class Rep2, class Period2>
            inline bool operator==(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                typedef typename duration_common_type<duration<Rep1, Period1>,
                                                      duration<Rep2, Period2>>::type CT;
                return CT(lhs).count() == CT(rhs).count();
            }
            template <class Rep1, class Period1, class Rep2, class Period2>
            inline bool operator!=(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                return !(lhs == rhs);
            }

            template <class Rep1, class Period1, class Rep2, class Period2>
            inline bool operator<(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                typedef typename duration_common_type<duration<Rep1, Period1>,
                                                      duration<Rep2, Period2>>::type CT;
                return CT(lhs).count() < CT(rhs).count();
            }
            template <class Rep1, class Period1, class Rep2, class Period2>
            inline bool operator>=(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                return !(lhs < rhs);
            }

            template <class Rep1, class Period1, class Rep2, class Period2>
            inline bool operator>(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                typedef typename duration_common_type<duration<Rep1, Period1>,
                                                      duration<Rep2, Period2>>::type CT;
                return CT(lhs).count() > CT(rhs).count();
            }
            template <class Rep1, class Period1, class Rep2, class Period2>
            inline bool operator<=(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                return !(lhs > rhs);
            }

            typedef duration<_int64_t, ratio<1, 1000000> > microseconds;
            typedef duration<_int64_t, ratio<1, 1000> >    milliseconds;
            typedef duration<_int64_t>                     seconds;
            typedef duration<_int64_t, ratio<60> >         minutes;
            typedef duration<_int64_t, ratio<3600> >       hours;

            template <typename ToDur, typename CF, typename CR>
            struct _duration_cast_impl {
                template <typename Rep, typename Period>
                static ToDur _cast(const duration<Rep, Period>& d) {
                    typedef typename ToDur::rep  to_rep;
                    return ToDur(static_cast<to_rep>(
                        static_cast<CR>(d.count())
                            * static_cast<CR>(CF::num)
                            / static_cast<CR>(CF::den)));
                }
            };

            template <typename ToDur, class Rep, class Period>
            inline ToDur duration_cast(const duration<Rep, Period>& d) {
                typedef typename ToDur::rep     to_rep;
                typedef typename ToDur::period  to_period;
                typedef ratio_divide<Period, to_period> cf;
                typedef typename common_type<to_rep, Rep>::type cr0;
                typedef typename common_type<cr0, _int64_t>::type cr;
                typedef _duration_cast_impl<ToDur, cf, cr> dc;
                return dc::_cast(d);
            }

            template <typename ToDur>
            inline ToDur duration_cast(const auto_duration& ad) {
                typedef typename ToDur::rep     to_rep;
                typedef typename ToDur::period  to_period;
                auto_ratio cf = ad.get_period() / to_period();
                typedef double cr;
                return ToDur(static_cast<to_rep>(
                    static_cast<cr>(ad.count())
                        * static_cast<cr>(cf.num)
                        / static_cast<cr>(cf.den)));
            }

            // FIXME: define time_point
            #ifdef UNBOOST_USE_WIN32_CHRONO
                ;
            #elif defined(UNBOOST_USE_POSIX_CHRONO)
                ;
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
