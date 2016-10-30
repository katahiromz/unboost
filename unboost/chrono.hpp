// chrono.hpp --- Unboost chrono
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_CHRONO_HPP_
#define UNBOOST_CHRONO_HPP_

#include "unboost.hpp"
#include "ratio.hpp"
#include "type_traits.hpp"
#include <cmath>
#undef min
#undef max
// NOTE: Use UNBOOST_MAKE_COMMON_DURATION instead of common_type<duration, duration>.

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
                #ifndef UNBOOST_NO_CXX11
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
            using std::common_type;
        } // namespace chrono
    } // namespace unboost
    #define unboost_auto_duration       auto
    #define unboost_auto_time_point     auto
    #define UNBOOST_MAKE_COMMON_DURATION(new_dur, dur1, dur2) \
        typedef std::common_type<dur1, dur2> new_dur
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
    #define unboost_auto_duration       auto
    #define unboost_auto_time_point     auto
    #define UNBOOST_MAKE_COMMON_DURATION(new_dur, dur1, dur2) \
        typedef boost::common_type<dur1, dur2> new_dur
#elif defined(UNBOOST_USE_WIN32_CHRONO) || defined(UNBOOST_USE_POSIX_CHRONO)
    #include <limits>   // for std::numeric_limits
    #include <cfloat>   // for FLT_MAX
    #include <ctime>    // for time_t
    #include <cmath>    // for std::fmod
    #ifdef _WIN32
        #ifndef _INC_WINDOWS
            #ifndef NOMINMAX
                #define NOMINMAX
            #endif
            #include <windows.h>
        #endif
    #endif
    namespace unboost {
        namespace chrono {
            //
            // treat_as_floating_point
            //
            template <typename Rep>
            struct treat_as_floating_point {
                enum { value = 0 };
            };
            template <>
            struct treat_as_floating_point<float> {
                enum { value = 1 };
            };
            template <>
            struct treat_as_floating_point<double> {
                enum { value = 1 };
            };
            template <>
            struct treat_as_floating_point<long double> {
                enum { value = 1 };
            };

            //
            // _numeric_limits_lowest
            //
            template <class Rep>
            inline Rep _numeric_limits_lowest() {
                #ifdef UNBOOST_CXX11
                    return std::numeric_limits<Rep>::lowest();
                #else
                    Rep r = (Rep)0.1;
                    if ((int)r != 0) {
                        if (sizeof(Rep) == sizeof(float)) {
                            r = (Rep)FLT_MAX;
                            return -r;
                        }
                        if (sizeof(Rep) == sizeof(double)) {
                            r = (Rep)DBL_MAX;
                            return -r;
                        }
                        if (sizeof(Rep) == sizeof(long double)) {
                            r = (Rep)LDBL_MAX;
                            return -r;
                        }
                    }
                    return std::numeric_limits<Rep>::min();
                #endif
            } // _numeric_limits_lowest

            //
            // duration_values
            //
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

            auto_duration
            auto_duration_cast(const auto_duration& ad1,
                               const auto_duration& ad2);
            auto_duration
            create_common_duration(const auto_duration& ad1,
                                   const auto_duration& ad2);

            #define UNBOOST_MAKE_COMMON_DURATION(new_dur,dur1,dur2) \
                auto_duration new_dur = create_common_duration(dur1(), dur2())

            //
            // auto_duration
            //
            typedef long double     _auto_duration_rep;
            class auto_duration {
            public:
                typedef _auto_duration_rep  rep;
                typedef auto_ratio          period;
                typedef auto_duration       type;

                auto_duration() : rep_(), period_(1, 1), is_floating_(false) { }

                explicit auto_duration(float r) : rep_(r), period_() {
                    is_floating_ = true;
                    fix_floating();
                }
                explicit auto_duration(double r) : rep_(r), period_() {
                    is_floating_ = true;
                    fix_floating();
                }
                explicit auto_duration(long double r) : rep_(r), period_() {
                    is_floating_ = true;
                    fix_floating();
                }
                explicit auto_duration(_ratio_intmax_t r) : rep_(r), period_() {
                    is_floating_ = false;
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
                    is_floating_ = (bool)treat_as_floating_point<Rep2>::value;
                    fix_floating();
                }

                template <class Rep2, class Period2>
                auto_duration& operator=(const duration<Rep2, Period2>& d) {
                    rep_ = static_cast<rep>(d.count());
                    period_ = Period2();
                    is_floating_ = (bool)treat_as_floating_point<Rep2>::value;
                    fix_floating();
                    return *this;
                }

                auto_duration(const auto_duration& ad) {
                    rep_ = ad.rep_;
                    period_ = ad.period_;
                    is_floating_ = ad.is_floating_;
                    fix_floating();
                }

                auto_duration& operator=(const auto_duration& ad) {
                    rep_ = ad.rep_;
                    period_ = ad.period_;
                    is_floating_ = ad.is_floating_;
                    fix_floating();
                    return *this;
                }

                rep count() const { return rep_; }

                static const type zero() {
                    rep z = duration_values<rep>::zero();
                    return type(z);
                }
                static const type min() {
                    rep m = duration_values<rep>::min();
                    return type(m);
                }
                static const type max() {
                    rep m = duration_values<rep>::max();
                    return type(m);
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
                    rep_ = std::fmod(rep_, rhs);
                    fix_floating();
                    return *this;
                }
                type& operator%=(const type& rhs) {
                    rep_ = std::fmod(rep_, auto_duration_cast(*this, rhs).count());
                    fix_floating();
                    return *this;
                }

                void fix_floating() {
                    if (!is_floating_)
                        rep_ = rep(_int64_t(rep_));
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
                        to_period, ad1.is_floating_ || ad2.is_floating_);
                }

                auto_ratio get_period() const { return period_; }
                bool is_floating() const { return is_floating_; }

                auto_duration operator()(const auto_duration& other) const {
                    return auto_duration_cast(*this, other);
                }
                auto_duration operator()(rep r) const {
                    return auto_duration(r, period_);
                }

            protected:
                rep         rep_;
                auto_ratio  period_;
                bool        is_floating_;
            }; // class auto_duration

            //
            // create_common_duration
            //
            inline auto_duration
            create_common_duration(const auto_duration& ad1,
                                   const auto_duration& ad2)
            {
                auto_ratio period1 = ad1.get_period();
                auto_ratio period2 = ad2.get_period();
                _ratio_intmax_t _gcd_num = _gcd(period1.num, period2.num);
                _ratio_intmax_t _gcd_den = _gcd(period1.den, period2.den);
                auto_ratio r(_gcd_num, (period1.den / _gcd_den) * period2.den);
                return auto_duration(0, r);
            }

            template <typename ToDur, typename Rep, typename Period>
            ToDur duration_cast(const duration<Rep, Period>& d);
            template <typename ToDur>
            ToDur duration_cast(const auto_duration& ad);

            //
            // duration
            //
            template <class Rep, class Period = unboost::ratio<1> >
            class duration {
            public:
                typedef Rep rep;
                typedef Period period;
                typedef duration<Rep, Period> type;

                duration() { }

                explicit duration(const Rep& r) : rep_(r) { }

                template <class Rep2, class Period2>
                duration(const duration<Rep2, Period2>& d) {
                    rep_ = duration_cast<type>(d).count();
                }

                duration(const auto_duration& ad) {
                    rep_ = duration_cast<type>(ad).count();
                }
                duration& operator=(const auto_duration& ad) {
                    rep_ = duration_cast<type>(ad).count();
                    return *this;
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
            inline bool operator==(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                typedef duration<Rep1, Period1> dur1;
                typedef duration<Rep2, Period2> dur2;
                UNBOOST_MAKE_COMMON_DURATION(CT, dur1, dur2);
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
                typedef duration<Rep1, Period1> dur1;
                typedef duration<Rep2, Period2> dur2;
                UNBOOST_MAKE_COMMON_DURATION(CT, dur1, dur2);
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
                typedef duration<Rep1, Period1> dur1;
                typedef duration<Rep2, Period2> dur2;
                UNBOOST_MAKE_COMMON_DURATION(CT, dur1, dur2);
                return CT(lhs).count() > CT(rhs).count();
            }
            template <class Rep1, class Period1, class Rep2, class Period2>
            inline bool operator<=(const duration<Rep1, Period1>& lhs,
                                   const duration<Rep2, Period2>& rhs)
            {
                return !(lhs > rhs);
            }

            //
            // auto_duration operators
            //
            inline auto_duration
            operator+(const auto_duration& lhs, const auto_duration& rhs) {
                auto_duration CD = create_common_duration(lhs, rhs);
                return CD(CD(lhs).count() + CD(rhs).count());
            }
            inline auto_duration
            operator-(const auto_duration& lhs, const auto_duration& rhs) {
                auto_duration CD = create_common_duration(lhs, rhs);
                return CD(CD(lhs).count() - CD(rhs).count());
            }
            inline auto_duration
            operator*(_auto_duration_rep s, const auto_duration& d) {
                return d(d.count() * s);
            }
            template <typename Rep, typename Period>
            inline auto_duration
            operator*(_auto_duration_rep s, const duration<Rep, Period>& d) {
                auto_duration ad = d;
                return ad(ad.count() * s);
            }
            inline auto_duration
            operator*(const auto_duration& d, _auto_duration_rep s) {
                return d(d.count() * s);
            }
            template <typename Rep, typename Period>
            inline auto_duration
            operator*(const duration<Rep, Period>& d, _auto_duration_rep s) {
                auto_duration ad = d;
                return ad(ad.count() * s);
            }
            inline auto_duration
            operator/(const auto_duration& d, _auto_duration_rep s) {
                return d(d.count() / s);
            }
            inline _auto_duration_rep
            operator/(const auto_duration& lhs, const auto_duration& rhs) {
                return lhs.count() / rhs.count();
            }
            inline auto_duration
            operator%(const auto_duration& d, _auto_duration_rep s) {
                return d(std::fmod(d.count(), s));
            }
            inline auto_duration
            operator%(const auto_duration& lhs, const auto_duration& rhs) {
                auto_duration CD = create_common_duration(lhs, rhs);
                return CD(std::fmod(CD(lhs).count(), CD(rhs).count()));
            }

            inline bool
            operator==(const auto_duration& lhs, const auto_duration& rhs) {
                auto_duration CT = create_common_duration(lhs, rhs);
                return CT(lhs).count() == CT(rhs).count();
            }
            inline bool
            operator!=(const auto_duration& lhs, const auto_duration& rhs) {
                return !(lhs == rhs);
            }
            inline bool
            operator<(const auto_duration& lhs, const auto_duration& rhs) {
                auto_duration CT = create_common_duration(lhs, rhs);
                return CT(lhs).count() < CT(rhs).count();
            }
            inline bool
            operator>=(const auto_duration& lhs, const auto_duration& rhs) {
                return !(lhs < rhs);
            }
            inline bool
            operator>(const auto_duration& lhs, const auto_duration& rhs) {
                auto_duration CT = create_common_duration(lhs, rhs);
                return CT(lhs).count() > CT(rhs).count();
            }
            inline bool
            operator<=(const auto_duration& lhs, const auto_duration& rhs) {
                return !(lhs > rhs);
            }

            typedef duration<_int64_t, ratio<1, 1000000000> >   nanoseconds;
            typedef duration<_int64_t, ratio<1, 1000000> >      microseconds;
            typedef duration<_int64_t, ratio<1, 1000> >         milliseconds;
            typedef duration<_int64_t>                          seconds;
            typedef duration<_int64_t, ratio<60> >              minutes;
            typedef duration<_int64_t, ratio<3600> >            hours;

            //
            // duration_cast
            //
            template <typename ToDur, typename Rep, typename Period>
            inline ToDur duration_cast(const duration<Rep, Period>& d) {
                typedef typename ToDur::period  to_period;
                auto_ratio p0(Period::num, Period::den);
                auto_ratio p1 = to_period();
                auto_ratio CF = p0 / p1;
                typedef typename ToDur::rep     to_rep;
                typedef typename common_type<to_rep, Rep>::type cr0;
                typedef typename common_type<cr0, _int64_t>::type CR;
                if (CF.num == 1 && CF.den == 1)
                    return ToDur(to_rep(d.count()));
                if (CF.num != 1 && CF.den == 1)
                    return ToDur(to_rep(CR(d.count()) * CR(CF.num)));
                if (CF.num == 1 && CF.den != 1)
                    return ToDur(to_rep(CR(d.count()) / CR(CF.den)));
                return ToDur(to_rep(CR(d.count()) * CR(CF.num) / CR(CF.den)));
            }
            template <typename ToDur>
            inline ToDur duration_cast(const auto_duration& ad) {
                typedef typename ToDur::period  to_period;
                auto_ratio p0 = ad.get_period();
                auto_ratio p1 = to_period();
                auto_ratio CF = p0 / p1;
                typedef typename ToDur::rep     to_rep;
                typedef _auto_duration_rep CR;
                if (CF.num == 1 && CF.den == 1)
                    return ToDur(to_rep(ad.count()));
                if (CF.num != 1 && CF.den == 1)
                    return ToDur(to_rep(CR(ad.count()) * CR(CF.num)));
                if (CF.num == 1 && CF.den != 1)
                    return ToDur(to_rep(CR(ad.count()) / CR(CF.den)));
                return ToDur(to_rep(CR(ad.count()) * CR(CF.num) / CR(CF.den)));
            }

            struct system_clock;

            template <typename Clock, typename Dur>
            struct time_point;

            struct auto_time_point {
                typedef system_clock            clock;
                typedef auto_duration           duration;
                typedef _auto_duration_rep      rep;
                typedef auto_ratio              period;
                typedef auto_time_point         self_type;
                typedef auto_time_point         time_point;
                typedef auto_time_point         local_time_point;

                auto_time_point() : m_d(auto_duration::zero()) { }
                auto_time_point(const auto_duration& ad) : m_d(ad) { }

                template <typename Clock2, typename Dur2>
                auto_time_point(const unboost::chrono::time_point<Clock2, Dur2>& t)
                    : m_d(t.time_since_epoch()) { }

                duration time_since_epoch() const { return m_d; }

                self_type& operator=(const self_type& d) {
                    m_d = duration(d.m_d);
                    return *this;
                }
                self_type& operator+=(const duration& d) {
                    m_d += d;
                    return *this;
                }
                self_type& operator-=(const duration& d) {
                    m_d -= d;
                    return *this;
                }

                static self_type min() {
                    auto_duration d = auto_duration::min();
                    return self_type(d);
                }
                static self_type max() {
                    auto_duration d = auto_duration::max();
                    return self_type(d);
                }

                duration get_duration() const { return m_d; }

            protected:
                auto_duration m_d;
            }; // struct auto_time_point
            #define unboost_auto_time_point unboost::chrono::auto_time_point

            template <typename Clock, typename Dur = typename Clock::duration>
            struct time_point {
                typedef Clock                       clock;
                typedef Dur                         duration;
                typedef typename Dur::rep           rep;
                typedef typename Dur::period        period;
                typedef time_point<Clock, Dur>      self_type;

                // NOTE: ISO C++ forbids nested type:
                //typedef time_point<Clock, Dur> time_point;

                time_point() : m_d(Dur::zero()) { }
                explicit time_point(const duration& d) : m_d(d) { }

                time_point(const auto_duration& d) : m_d(d) { }

                template <typename Dur2>
                time_point(const unboost::chrono::time_point<clock, Dur2>& t)
                    : m_d(t.time_since_epoch()) { }

                time_point(const auto_time_point& t) : m_d(t.get_duration()) { }

                duration time_since_epoch() const { return m_d; }

                self_type& operator=(const auto_time_point& other) {
                    m_d = other.get_duration();
                    return *this;
                }

                self_type& operator+=(const duration& d) {
                    m_d += d;
                    return *this;
                }
                self_type& operator-=(const duration& d) {
                    m_d -= d;
                    return *this;
                }

                static self_type min() {
                    Dur d = Dur::min();
                    return self_type(d);
                }
                static self_type max() {
                    Dur d = Dur::max();
                    return self_type(d);
                }
            protected:
                duration m_d;
            }; // struct time_point

            template <typename ToDur, typename Clock, typename Dur>
            inline time_point<Clock, ToDur>
            time_point_cast(const time_point<Clock, Dur>& t) {
                typedef time_point<Clock, ToDur> TP;
                const ToDur to_dur = duration_cast<ToDur>(t.time_since_epoch());
                return TP(to_dur);
            }

            // NOTE: epoch is 1970.01.01
            #ifdef UNBOOST_USE_WIN32_CHRONO
                typedef ratio<1, 10000000>  _nano100;
                typedef chrono::duration<_int64_t, _nano100>     _system_duration;
                typedef chrono::duration<_int64_t, nanoseconds> _steady_duration;
                inline _int64_t _get_system_clock_time(void) {
                    // in 100-nanoseconds
                    FILETIME ft;
                    ::GetSystemTimeAsFileTime(&ft);
                    LONGLONG n = ft.dwHighDateTime;
                    n <<= 32;
                    n |= ft.dwLowDateTime;
                    return n - 0x19DB1DED53E8000;
                }
                inline LARGE_INTEGER *_get_perf_freq() {
                    static LARGE_INTEGER s_freq;
                    if (!::QueryPerformanceFrequency(&s_freq))
                        assert(0);
                    return &s_freq;
                }
                inline _int64_t _get_steady_clock_time(void) {
                    // in nanoseconds
                    static LARGE_INTEGER *s_pfreq = _get_perf_freq();
                    LARGE_INTEGER counter;
                    ::QueryPerformanceCounter(&counter);
                    return counter.QuadPart * (1000000000 / s_pfreq->QuadPart);
                }
            #elif defined(UNBOOST_USE_POSIX_CHRONO)
                typedef chrono::duration<_int64_t, microseconds> _system_duration;
                typedef chrono::duration<_int64_t, microseconds> _steady_duration;
                inline _int64_t _get_system_clock_time(void) {
                    // in microseconds
                    struct timeval tv;
                    struct timezone tz;
                    gettimeofday(&tv);
                    return tv.tv_sec * 1000000 + tv.tv_usec;
                }
                inline _int64_t _get_steady_clock_time(void) {
                    // in microseconds
                    struct timeval tv;
                    struct timezone tz;
                    gettimeofday(&tv);
                    return tv.tv_sec * 1000000 + tv.tv_usec;
                }
            #else
                #error You lose.
            #endif

            struct system_clock {
                // duration in 100-nanoseconds
                typedef _system_duration                            duration;
                typedef _system_duration::rep                       rep;
                typedef _system_duration::period                    period;
                typedef chrono::time_point<system_clock, duration>  time_point;
                typedef chrono::time_point<system_clock, duration>  local_time_point;
                typedef system_clock                                self_type;
                enum { is_steady = 0 };

                static local_time_point now() {
                    local_time_point::duration d(_get_system_clock_time());
                    local_time_point tp(d);
                    return tp;
                }

                static std::time_t to_time_t(const local_time_point& t) {
                    duration tse = t.time_since_epoch();
                    chrono::seconds sec = duration_cast<chrono::seconds>(tse);
                    return std::time_t(sec.count());
                }
                static time_point from_time_t(std::time_t t) {
                    chrono::seconds sec = chrono::seconds(t);
                    chrono::time_point<system_clock, chrono::seconds> f(sec);
                    return time_point_cast<system_clock::duration>(f);
                }
            }; // struct system_clock

            struct steady_clock {
                typedef _steady_duration            duration;
                typedef _steady_duration::rep       rep;
                typedef _steady_duration::period    period;
                typedef chrono::time_point<steady_clock, duration> time_point;
                typedef chrono::time_point<steady_clock, duration> local_time_point;
                typedef steady_clock                self_type;
                enum { is_steady = true };

                static local_time_point now() {
                    local_time_point::duration d(_get_steady_clock_time());
                    local_time_point tp(d);
                    return tp;
                }
            };
            typedef steady_clock high_resolution_clock;

            inline auto_time_point
            operator+(const auto_time_point& lhs, const auto_duration& rhs) {
                auto_duration d = create_common_duration(lhs.get_duration(), rhs);
                d = d(lhs.time_since_epoch()) + d(rhs);
                auto_time_point ret(d);
                return ret;
            }
            inline auto_time_point
            operator+(const auto_duration& lhs, const auto_time_point& rhs) {
                auto_duration d = create_common_duration(rhs.get_duration(), lhs);
                d = d(rhs.time_since_epoch()) + d(lhs);
                auto_time_point ret(d);
                return ret;
            }
            inline auto_time_point
            operator-(const auto_time_point& lhs, const auto_duration& rhs) {
                auto_duration d = create_common_duration(lhs.get_duration(), rhs);
                d = d(lhs.time_since_epoch()) - d(rhs);
                auto_time_point ret(d);
                return ret;
            }
            inline auto_duration
            operator-(const auto_time_point& lhs, const auto_time_point& rhs) {
                auto_duration d = create_common_duration(lhs.get_duration(), rhs.get_duration());
                d = d(lhs.time_since_epoch()) - d(rhs.time_since_epoch());
                return d;
            }

            template <typename Clock, typename Dur1, typename Dur2>
            inline bool
            operator==(const time_point<Clock, Dur1>& lhs,
                       const time_point<Clock, Dur2>& rhs)
            {
                return lhs.time_since_epoch() == rhs.time_since_epoch();
            }
            template <typename Clock, typename Dur1, typename Dur2>
            inline bool
            operator!=(const time_point<Clock, Dur1>& lhs,
                       const time_point<Clock, Dur2>& rhs)
            {
                return !(lhs == rhs);
            }
            template <typename Clock, typename Dur1, typename Dur2>
            inline bool
            operator<(const time_point<Clock, Dur1>& lhs,
                      const time_point<Clock, Dur2>& rhs)
            {
                return lhs.time_since_epoch() < rhs.time_since_epoch();
            }
            template <typename Clock, typename Dur1, typename Dur2>
            inline bool
            operator>=(const time_point<Clock, Dur1>& lhs,
                       const time_point<Clock, Dur2>& rhs)
            {
                return !(lhs < rhs);
            }
            template <typename Clock, typename Dur1, typename Dur2>
            inline bool
            operator>(const time_point<Clock, Dur1>& lhs,
                      const time_point<Clock, Dur2>& rhs)
            {
                return lhs.time_since_epoch() > rhs.time_since_epoch();
            }
            template <typename Clock, typename Dur1, typename Dur2>
            inline bool
            operator<=(const time_point<Clock, Dur1>& lhs,
                       const time_point<Clock, Dur2>& rhs)
            {
                return !(lhs > rhs);
            }

            inline bool
            operator==(const auto_time_point& lhs, const auto_time_point& rhs) {
                return lhs.time_since_epoch() == rhs.time_since_epoch();
            }
            inline bool
            operator!=(const auto_time_point& lhs, const auto_time_point& rhs) {
                return !(lhs == rhs);
            }
            inline bool
            operator<(const auto_time_point& lhs, const auto_time_point& rhs) {
                return lhs.time_since_epoch() < rhs.time_since_epoch();
            }
            inline bool
            operator>=(const auto_time_point& lhs, const auto_time_point& rhs) {
                return !(lhs < rhs);
            }
            inline bool
            operator>(const auto_time_point& lhs, const auto_time_point& rhs) {
                return lhs.time_since_epoch() > rhs.time_since_epoch();
            }
            inline bool
            operator<=(const auto_time_point& lhs, const auto_time_point& rhs) {
                return !(lhs > rhs);
            }
        } // namespace chrono
    } // namespace unboost
    #define unboost_auto_duration unboost::chrono::auto_duration
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_CHRONO_HPP_
