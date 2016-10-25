// regex.hpp --- Unboost regular expression
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_REGEX_HPP_
#define UNBOOST_REGEX_HPP_

#include "unboost.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_REGEX) + defined(UNBOOST_USE_BOOST_REGEX)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_REGEX
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_REGEX
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_REGEX
        #elif defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_REGEX
                #else
                    #define UNBOOST_USE_BOOST_REGEX
                #endif
            #else
                #define UNBOOST_USE_BOOST_REGEX
            #endif
        #else
            #define UNBOOST_USE_BOOST_REGEX
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_REGEX
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
#elif defined(UNBOOST_USE_BOOST_REGEX)
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
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_REGEX_HPP_
