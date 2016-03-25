// unboost.hpp --- Unboost by katahiromz <katayama.hirofumi.mz@gmail.com>
// This file is public domain software (PDS).
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_HPP_
#define UNBOOST_HPP_    1 /* Version 1 */

//////////////////////////////////////////////////////////////////////////////
// Unboost configuration (optional)

#ifdef UNBOOST_HAVE_CONFIG_HPP
    #include "unboost_config.hpp"
#endif

//////////////////////////////////////////////////////////////////////////////
// UNBOOST_USE_CXX11 or UNBOOST_USE_BOOST?

#ifndef UNBOOST_CXX11
    #if (__cplusplus >= 201103L) // C++11
        #ifndef UNBOOST_CXX03
            #define UNBOOST_CXX11
        #endif
    #endif
#endif

#if !defined(UNBOOST_USE_BOOST)
    #if defined(UNBOOST_CXX11) && !defined(UNBOOST_USE_CXX11)
        #define UNBOOST_USE_CXX11
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// consistency checks

#if defined(UNBOOST_CXX11) && defined(UNBOOST_CXX03)
    #error Choose either UNBOOST_CXX11 or UNBOOST_CXX03. You lose.
#endif

#if defined(UNBOOST_USE_CXX11) && defined(UNBOOST_USE_BOOST)
    #error Choose either UNBOOST_USE_CXX11 or UNBOOST_USE_BOOST. You lose.
#endif

#if defined(UNBOOST_USE_CXX11) && !defined(UNBOOST_CXX11)
    #error Please #define UNBOOST_CXX11 before #inclusion of "unboost.hpp". You lose.
#endif

//////////////////////////////////////////////////////////////////////////////
// static_assert

#ifndef UNBOOST_NO_STATIC_ASSERT
    #ifdef UNBOOST_USE_CXX11
        // NOTE: In C++11, static_assert is available.
    #else
        #ifndef UNBOOST_CXX11
            #include <boost/static_assert.hpp>
            #ifndef static_assert
                #define static_assert BOOST_STATIC_ASSERT_MSG
            #endif
        #endif
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// smart pointers

#ifndef UNBOOST_NO_SMARTPTR
    #include <memory>       // for std::shared_ptr, ...

    #ifdef UNBOOST_USE_CXX11
        namespace unboost {
            using std::shared_ptr;
            using std::make_shared;
            using std::static_pointer_cast;
            using std::dynamic_pointer_cast;
            using std::unique_ptr;
        } // namespace unboost
    #else   // ndef UNBOOST_USE_CXX11
        #include <boost/shared_ptr.hpp>
        #include <boost/make_shared.hpp>
        #include <boost/interprocess/smart_ptr/unique_ptr.hpp>
        #include <boost/checked_delete.hpp>
        #ifdef UNBOOST_FIX_UNIQUE_PTR
            namespace boost {
                namespace interprocess {
                    template<typename T>
                    struct default_delete : checked_deleter<T> { };
                    template<typename T>
                    struct default_delete<T[]> : checked_array_deleter<T> { };

                    template<typename T, typename D = default_delete<T> >
                    class unique_ptr;
                } // namespace interprocess
            } // namespace boost
        #endif  // def UNBOOST_FIX_UNIQUE_PTR
        namespace unboost {
            using boost::shared_ptr;
            using boost::make_shared;
            using boost::static_pointer_cast;
            using boost::dynamic_pointer_cast;
            using boost::interprocess::unique_ptr;
        } // namespace unboost
    #endif  // ndef UNBOOST_USE_CXX11
#endif  // ndef UNBOOST_NO_SMARTPTR

//////////////////////////////////////////////////////////////////////////////
// modern thread

#ifndef UNBOOST_NO_THREAD
    #ifdef UNBOOST_USE_CXX11
        #include <thread>
        namespace unboost {
            using std::thread;
        }
    #else
        #include <boost/thread.hpp>
        namespace unboost {
            using boost::thread;
        }
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// modern array

#ifndef UNBOOST_NO_ARRAY
    #ifdef UNBOOST_USE_CXX11
        #include <array>
        namespace unboost {
            using std::array;
        }
    #else
        #include <boost/array.hpp>
        namespace unboost {
            using boost::array;
        }
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// regular expression (regex)

#ifndef UNBOOST_NO_REGEX
    #ifdef UNBOOST_USE_CXX11
        #include <regex>
        namespace unboost {
            using std::regex;
            using std::regex_match;
            using std::regex_search;
            using std::regex_replace;
            using std::cmatch;
            using std::wcmatch;
            using std::smatch;
            using std::wsmatch;
            using std::regex_iterator;
            using std::cregex_iterator;
            using std::wcregex_iterator;
            using std::sregex_iterator;
            using std::wsregex_iterator;
            using std::regex_traits;
            using std::regex_error;
            using std::regex_token_iterator;
            namespace regex_constants {
                typedef std::regex_constants::error_type error_type;
                static constexpr error_type error_collate = std::regex_constants::error_collate;
                static constexpr error_type error_ctype = std::regex_constants::error_ctype;
                static constexpr error_type error_escape = std::regex_constants::error_escape;
                static constexpr error_type error_backref = std::regex_constants::error_backref;
                static constexpr error_type error_brack = std::regex_constants::error_brack;
                static constexpr error_type error_paren = std::regex_constants::error_paren;
                static constexpr error_type error_brace = std::regex_constants::error_brace;
                static constexpr error_type error_badbrace = std::regex_constants::error_badbrace;
                static constexpr error_type error_range = std::regex_constants::error_range;
                static constexpr error_type error_space = std::regex_constants::error_space;
                static constexpr error_type error_badrepeat = std::regex_constants::error_badrepeat;
                static constexpr error_type error_complexity = std::regex_constants::error_complexity;
                static constexpr error_type error_stack = std::regex_constants::error_stack;

                typedef std::regex_constants::match_flag_type match_flag_type;
                static constexpr match_flag_type match_default = std::regex_constants::match_default;
                static constexpr match_flag_type match_not_bol = std::regex_constants::match_not_bol;
                static constexpr match_flag_type match_not_eol = std::regex_constants::match_not_eol;
                static constexpr match_flag_type match_not_bow = std::regex_constants::match_not_bow;
                static constexpr match_flag_type match_not_eow = std::regex_constants::match_not_eow;
                static constexpr match_flag_type match_any = std::regex_constants::match_any;
                static constexpr match_flag_type match_not_null = std::regex_constants::match_not_null;
                static constexpr match_flag_type match_continuous = std::regex_constants::match_continuous;
                static constexpr match_flag_type match_prev_avail = std::regex_constants::match_prev_avail;
                static constexpr match_flag_type format_default = std::regex_constants::format_default;
                static constexpr match_flag_type format_sed = std::regex_constants::format_sed;
                static constexpr match_flag_type format_no_copy = std::regex_constants::format_no_copy;
                static constexpr match_flag_type format_first_only = std::regex_constants::format_first_only;

                typedef std::regex_constants::syntax_option_type syntax_option_type;
                static constexpr syntax_option_type icase = std::regex_constants::icase;
                static constexpr syntax_option_type nosubs = std::regex_constants::nosubs;
                static constexpr syntax_option_type optimize = std::regex_constants::optimize;
                static constexpr syntax_option_type collate = std::regex_constants::collate;
                static constexpr syntax_option_type ECMAScript = std::regex_constants::ECMAScript;
                static constexpr syntax_option_type basic = std::regex_constants::basic;
                static constexpr syntax_option_type extended = std::regex_constants::extended;
                static constexpr syntax_option_type awk = std::regex_constants::awk;
                static constexpr syntax_option_type grep = std::regex_constants::grep;
                static constexpr syntax_option_type egrep = std::regex_constants::egrep;
            } // namespace regex_constants
        } // namespace unboost
    #else   // ndef UNBOOST_USE_CXX11
        #include <boost/regex.hpp>
        namespace unboost {
            using boost::regex;
            using boost::regex_match;
            using boost::regex_search;
            using boost::regex_replace;
            using boost::cmatch;
            using boost::wcmatch;
            using boost::smatch;
            using boost::wsmatch;
            using boost::regex_iterator;
            using boost::cregex_iterator;
            using boost::wcregex_iterator;
            using boost::sregex_iterator;
            using boost::wsregex_iterator;
            using boost::regex_traits;
            using boost::regex_error;
            using boost::regex_token_iterator;
            namespace regex_constants {
                typedef boost::regex_constants::error_type error_type;
                static const error_type error_collate = boost::regex_constants::error_collate;
                static const error_type error_ctype = boost::regex_constants::error_ctype;
                static const error_type error_escape = boost::regex_constants::error_escape;
                static const error_type error_backref = boost::regex_constants::error_backref;
                static const error_type error_brack = boost::regex_constants::error_brack;
                static const error_type error_paren = boost::regex_constants::error_paren;
                static const error_type error_brace = boost::regex_constants::error_brace;
                static const error_type error_badbrace = boost::regex_constants::error_badbrace;
                static const error_type error_range = boost::regex_constants::error_range;
                static const error_type error_space = boost::regex_constants::error_space;
                static const error_type error_badrepeat = boost::regex_constants::error_badrepeat;
                static const error_type error_complexity = boost::regex_constants::error_complexity;
                static const error_type error_stack = boost::regex_constants::error_stack;

                typedef boost::regex_constants::match_flag_type match_flag_type;
                static const match_flag_type match_default = boost::regex_constants::match_default;
                static const match_flag_type match_not_bol = boost::regex_constants::match_not_bol;
                static const match_flag_type match_not_eol = boost::regex_constants::match_not_eol;
                static const match_flag_type match_not_bow = boost::regex_constants::match_not_bow;
                static const match_flag_type match_not_eow = boost::regex_constants::match_not_eow;
                static const match_flag_type match_any = boost::regex_constants::match_any;
                static const match_flag_type match_not_null = boost::regex_constants::match_not_null;
                static const match_flag_type match_continuous = boost::regex_constants::match_continuous;
                static const match_flag_type match_prev_avail = boost::regex_constants::match_prev_avail;
                static const match_flag_type format_default = boost::regex_constants::format_default;
                static const match_flag_type format_sed = boost::regex_constants::format_sed;
                static const match_flag_type format_no_copy = boost::regex_constants::format_no_copy;
                static const match_flag_type format_first_only = boost::regex_constants::format_first_only;

                typedef boost::regex_constants::syntax_option_type syntax_option_type;
                static const syntax_option_type icase = boost::regex_constants::icase;
                static const syntax_option_type nosubs = boost::regex_constants::nosubs;
                static const syntax_option_type optimize = boost::regex_constants::optimize;
                static const syntax_option_type collate = boost::regex_constants::collate;
                static const syntax_option_type ECMAScript = boost::regex_constants::ECMAScript;
                static const syntax_option_type basic = boost::regex_constants::basic;
                static const syntax_option_type extended = boost::regex_constants::extended;
                static const syntax_option_type awk = boost::regex_constants::awk;
                static const syntax_option_type grep = boost::regex_constants::grep;
                static const syntax_option_type egrep = boost::regex_constants::egrep;
            } // namespace regex_constants
        } // namespace unboost
    #endif  // ndef UNBOOST_USE_CXX11
#endif  // ndef UNBOOST_NO_REGEX

//////////////////////////////////////////////////////////////////////////////
// conversion between number and string

#ifndef UNBOOST_NO_CONVERSION
    #ifdef UNBOOST_USE_CXX11
        #include <string>
        namespace unboost {
            using std::stoi;
            using std::stol;
            using std::stoul;
            using std::stoll;
            using std::stoull;
            using std::stof;
            using std::stod;
            using std::stold;
            using std::to_string;
            using std::to_wstring;
        } // namespace unboost
    #else // ndef UNBOOST_USE_CXX11
        #include <boost/lexical_cast.hpp>
        #include <boost/exception/to_string.hpp>
        namespace unboost {
            inline long stol(const std::string& str, size_t *pos = NULL, int base = 10) {
                long ret;
                if (pos || (base != 10)) {
                    char *end = NULL;
                    ret = std::strtol(str.c_str(), &end, base);
                    *pos = end - str.c_str();
                } else {
                    ret = std::atol(str.c_str());
                }
                return ret;
            }
            inline long stoul(const std::string& str, size_t *pos = NULL, int base = 10) {
                long ret;
                if (pos) {
                    char *end = NULL;
                    ret = std::strtoul(str.c_str(), &end, base);
                    *pos = end - str.c_str();
                } else {
                    ret = std::strtoul(str.c_str(), NULL, base);
                }
                return ret;
            }
            inline int stoi(const std::string& str, size_t *pos = NULL, int base = 10) {
                return static_cast<int>(unboost::stol(str, pos, base));
            }
            #ifdef UNBOOST_CXX11
                inline long long stoll(const std::string& str, size_t *pos = NULL, int base = 10) {
                    long long ret;
                    if (pos) {
                        char *end = NULL;
                        ret = std::strtoll(str.c_str(), &end, base);
                        *pos = end - str.c_str();
                    } else {
                        ret = std::strtoll(str.c_str(), NULL, base);
                    }
                    return ret;
                }
                inline unsigned long long stoull(const std::string& str, size_t *pos = NULL, int base = 10) {
                    unsigned long long ret;
                    if (pos) {
                        char *end = NULL;
                        ret = std::strtoull(str.c_str(), &end, base);
                        *pos = end - str.c_str();
                    } else {
                        ret = std::strtoull(str.c_str(), NULL, base);
                    }
                    return ret;
                }
                inline float stof(const std::string& str, size_t *pos = NULL) {
                    float ret;
                    if (pos) {
                        char *end = NULL;
                        ret = std::strtof(str.c_str(), &end);
                        *pos = end - str.c_str();
                    } else {
                        ret = static_cast<float>(std::atof(str.c_str()));
                    }
                    return ret;
                }
                inline long double stold(const std::string& str, size_t *pos = NULL) {
                    long double ret;
                    if (pos) {
                        char *end = NULL;
                        ret = std::strtold(str.c_str(), &end);
                        *pos = end - str.c_str();
                    } else {
                        ret = std::strtold(str.c_str(), NULL);
                    }
                    return ret;
                }
            #else
                inline __int64 stoll(const std::string& str) {
                    // TODO: support pos and base parameters
                    return boost::lexical_cast<__int64>(str.c_str());
                }
                inline unsigned __int64 stoull(const std::string& str) {
                    // TODO: support pos and base parameters
                    return boost::lexical_cast<unsigned __int64>(str.c_str());
                }
                inline float stof(const std::string& str, size_t *pos = NULL) {
                    float ret;
                    if (pos) {
                        char *end = NULL;
                        ret = static_cast<float>(std::strtod(str.c_str(), &end));
                        *pos = end - str.c_str();
                    } else {
                        ret = static_cast<float>(std::atof(str.c_str()));
                    }
                    return ret;
                }
            #endif
            inline double stod(const std::string& str, size_t *pos = NULL) {
                double ret;
                if (pos) {
                    char *end = NULL;
                    ret = std::strtod(str.c_str(), &end);
                    *pos = end - str.c_str();
                } else {
                    ret = std::atof(str.c_str());
                }
                return ret;
            }
            using boost::to_string;
            // NOTE: There is no boost::to_wstring.
        } // namespace unboost
    #endif  // ndef UNBOOST_USE_CXX11
#endif  // ndef UNBOOST_NO_CONVERSION

//////////////////////////////////////////////////////////////////////////////
// math functions

#ifndef UNBOOST_NO_COMPLEX_FUNCTIONS
    #include <cmath>
    #include <complex>
    #ifdef UNBOOST_USE_CXX11
        namespace unboost {
            namespace math {
                using std::complex;
                using std::fabs;
                using std::asin;
                using std::acos;
                using std::atan;
                using std::asinh;
                using std::acosh;
                using std::atanh;
            } // namespace math
        } // namespace unboost
    #else
        #include <boost/math/complex.hpp>
        namespace unboost {
            namespace math {
                using boost::math::fabs;
                using boost::math::asin;
                using boost::math::acos;
                using boost::math::atan;
                using boost::math::asinh;
                using boost::math::acosh;
                using boost::math::atanh;
            } // namespace math
        } // namespace unboost
    #endif
#endif  // ndef UNBOOST_NO_COMPLEX_FUNCTIONS

//////////////////////////////////////////////////////////////////////////////
// random generation

#ifndef UNBOOST_NO_RANDOM
    #ifdef UNBOOST_USE_CXX11
        #include <random>
        namespace unboost {
            namespace random {
                using std::random_device;
                using std::minstd_rand0;
                using std::minstd_rand;
                using std::mt19937;
                using std::mt19937_64;
                using std::ranlux24_base;
                using std::ranlux48_base;
                using std::ranlux24;
                using std::ranlux48;
                using std::knuth_b;
                using std::uniform_int_distribution;
                using std::uniform_real_distribution;
                using std::generate_canonical;
                using std::bernoulli_distribution;
                using std::binomial_distribution;
                using std::negative_binomial_distribution;
                using std::geometric_distribution;
                using std::poisson_distribution;
                using std::exponential_distribution;
                using std::gamma_distribution;
                using std::weibull_distribution;
                using std::extreme_value_distribution;
                using std::normal_distribution;
                using std::lognormal_distribution;
                using std::chi_squared_distribution;
                using std::cauchy_distribution;
                using std::fisher_f_distribution;
                using std::student_t_distribution;
                using std::discrete_distribution;
                using std::piecewise_constant_distribution;
                using std::piecewise_linear_distribution;
                using std::seed_seq;
            } // namespace random
        } // namespace unboost
    #else   // ndef UNBOOST_USE_CXX11
        #include <boost/random/random_device.hpp>
        #include <boost/random.hpp>
        namespace unboost {
            namespace random {
                using boost::random::random_device;
                using boost::random::minstd_rand0;
                using boost::random::minstd_rand;
                using boost::random::mt19937;
                using boost::random::mt19937_64;
                using boost::random::ranlux24_base;
                using boost::random::ranlux48_base;
                using boost::random::ranlux24;
                using boost::random::ranlux48;
                using boost::random::knuth_b;
                using boost::random::uniform_int_distribution;
                using boost::random::uniform_real_distribution;
                using boost::random::generate_canonical;
                using boost::random::bernoulli_distribution;
                using boost::random::binomial_distribution;
                using boost::random::negative_binomial_distribution;
                using boost::random::geometric_distribution;
                using boost::random::poisson_distribution;
                using boost::random::exponential_distribution;
                using boost::random::gamma_distribution;
                using boost::random::weibull_distribution;
                using boost::random::extreme_value_distribution;
                using boost::random::normal_distribution;
                using boost::random::lognormal_distribution;
                using boost::random::chi_squared_distribution;
                using boost::random::cauchy_distribution;
                using boost::random::fisher_f_distribution;
                using boost::random::student_t_distribution;
                using boost::random::discrete_distribution;
                using boost::random::piecewise_constant_distribution;
                using boost::random::piecewise_linear_distribution;
                using boost::random::seed_seq;
            } // namespace random
        } // namespace unboost
    #endif  // ndef UNBOOST_USE_CXX11
#endif  // ndef UNBOOST_NO_RANDOM

//////////////////////////////////////////////////////////////////////////////
// chrono

#ifndef UNBOOST_NO_CHRONO
    #ifdef UNBOOST_USE_CXX11
        #include <chrono>
        namespace unboost {
            namespace chrono {
                using std::chrono::duration;
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
    #else
        #include <boost/chrono/include.hpp>
        namespace unboost {
            namespace chrono {
                using boost::chrono::duration;
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
    #endif
#endif  // ndef UNBOOST_NO_CHRONO

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef UNBOOST_HPP_

//////////////////////////////////////////////////////////////////////////////
