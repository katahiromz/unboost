// string_algorithm.hpp --- Unboost string algorithm
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_STRING_ALGORITHM_HPP_
#define UNBOOST_STRING_ALGORITHM_HPP_

#include "unboost_core.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_BOOST_STRING_ALGORITHM) + defined(UNBOOST_USE_UNBOOST_STRING_ALGORITHM)) == 0)
    #if defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_STRING_ALGORITHM
    #else
        #define UNBOOST_USE_UNBOOST_STRING_ALGORITHM
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_BOOST_STRING_ALGORITHM
    #include <boost/algorithm/string.hpp>
    namespace unboost {
        using boost::is_space;
        using boost::is_alpha;
        using boost::is_alnum;
        using boost::is_digit;
        using boost::is_xdigit;
        using boost::is_lower;
        using boost::is_upper;
        using boost::is_from_range;
        using boost::is_cntrl;
        using boost::is_punct;
        using boost::is_any_of;
        using boost::to_upper;
        using boost::to_lower;
        using boost::trim;
        using boost::trim_left;
        using boost::trim_right;
        using boost::trim_if;
        using boost::trim_left_if;
        using boost::trim_right_if;
        using boost::to_upper_copy;
        using boost::to_lower_copy;
        using boost::trim_copy;
        using boost::trim_left_copy;
        using boost::trim_right_copy;
        using boost::trim_copy_if;
        using boost::trim_left_copy_if;
        using boost::trim_right_copy_if;
        using boost::split;
        using boost::join;
        using boost::replace_all;
        using boost::replace_all_copy;
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_STRING_ALGORITHM)
    #include <cctype>
    namespace unboost {
        // TODO: be locale aware
        namespace char_set {
            // ansi
            static const char *spaces = " \t\n\r\f\v";
            static const char *alphas = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            static const char *alnums = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            static const char *digits = "0123456789";
            static const char *xdigits = "0123456789ABCDEFabcdef";
            static const char *uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            static const char *lowers = "abcdefghijklmnopqrstuvwxyz";
            static const char *puncts = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
            // wide
            static const wchar_t *wspaces = L" \t\n\r\f\v\u3000";
            static const wchar_t *walphas = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            static const wchar_t *walnums = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            static const wchar_t *wdigits = L"0123456789";
            static const wchar_t *wxdigits = L"0123456789ABCDEFabcdef";
            static const wchar_t *wuppers = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            static const wchar_t *wlowers = L"abcdefghijklmnopqrstuvwxyz";
            static const wchar_t *wpuncts = L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        } // namespace char_set
        struct char_set_predicate {
            std::string     m_char_set;
            std::wstring    m_wchar_set;
            char_set_predicate() { }
            char_set_predicate(const std::string& str) : m_char_set(str) {
                for (size_t i = 0; i < str.size(); ++i) {
                    m_wchar_set += wchar_t(str[i]);
                }
            }
            char_set_predicate(const std::wstring& str) : m_wchar_set(str) {
                for (size_t i = 0; i < str.size(); ++i) {
                    if (str[i] <= 0x7F) {
                        m_char_set += char(str[i]);
                    }
                }
            }
            char_set_predicate(const std::string& str, const std::wstring& wstr)
                : m_char_set(str), m_wchar_set(wstr) { }
        }; // struct char_set_predicate
        struct is_space : public char_set_predicate {
            is_space() : char_set_predicate(char_set::spaces, char_set::wspaces) { }
        };
        struct is_alpha : public char_set_predicate {
            is_alpha() : char_set_predicate(char_set::alphas, char_set::walphas) { }
        };
        struct is_alnum : public char_set_predicate {
            is_alnum() : char_set_predicate(char_set::alnums, char_set::walnums) { }
        };
        struct is_digit : public char_set_predicate {
            is_digit() : char_set_predicate(char_set::digits, char_set::wdigits) { }
        };
        struct is_xdigit : public char_set_predicate {
            is_xdigit() : char_set_predicate(char_set::xdigits, char_set::wxdigits) { }
        };
        struct is_lower : public char_set_predicate {
            is_lower() : char_set_predicate(char_set::lowers, char_set::wlowers) { }
        };
        struct is_upper : public char_set_predicate {
            is_upper() : char_set_predicate(char_set::uppers, char_set::wuppers) { }
        };
        struct is_from_range : public char_set_predicate {
            is_from_range(char from, char to) {
                for (int ch = from; ch <= to; ++ch) {
                    m_char_set += char(ch);
                    m_wchar_set += wchar_t(ch);
                }
            }
        };
        struct is_cntrl : public is_from_range {
            is_cntrl(char from, char to) : is_from_range(0, '\x1F') {
                m_char_set += '\x7F';
                m_wchar_set += static_cast<wchar_t>(0x7F);
            }
        };
        struct is_punct : public char_set_predicate {
            is_punct() : char_set_predicate(char_set::puncts, char_set::wpuncts) { }
        };
        struct is_any_of : public char_set_predicate {
            is_any_of(const std::string& str) : char_set_predicate(str) { }
            is_any_of(const std::wstring& str) : char_set_predicate(str) { }
        };
        inline void to_upper(std::string& str) {
            using namespace std;
            const size_t count = str.size();
            for (size_t i = 0; i < count; ++i) {
                char& ch = str[i];
                if (islower(ch)) {
                    ch = toupper(ch);
                }
            }
        }
        inline void to_lower(std::string& str) {
            using namespace std;
            const size_t count = str.size();
            for (size_t i = 0; i < count; ++i) {
                char& ch = str[i];
                if (isupper(ch)) {
                    ch = tolower(ch);
                }
            }
        }
        inline void to_upper(std::wstring& str) {
            using namespace std;
            const size_t count = str.size();
            for (size_t i = 0; i < count; ++i) {
                wchar_t& ch = str[i];
                if (iswlower(ch)) {
                    ch = towupper(ch);
                }
            }
        }
        inline void to_lower(std::wstring& str) {
            using namespace std;
            const size_t count = str.size();
            for (size_t i = 0; i < count; ++i) {
                wchar_t& ch = str[i];
                if (iswupper(ch)) {
                    ch = towlower(ch);
                }
            }
        }
        inline void trim_if(std::string& str, const char_set_predicate& pred) {
            size_t i = str.find_first_not_of(pred.m_char_set);
            size_t j = str.find_last_not_of(pred.m_char_set);
            if ((i == std::string::npos) || (j == std::string::npos)) {
                str.clear();
            } else {
                str = str.substr(i, j - i + 1);
            }
        }
        inline void trim_left_if(std::string& str, const char_set_predicate& pred) {
            size_t i = str.find_first_not_of(pred.m_char_set);
            if (i == std::string::npos) {
                str.clear();
            } else {
                str = str.substr(i);
            }
        }
        inline void trim_right_if(std::string& str, const char_set_predicate& pred) {
            size_t j = str.find_last_not_of(pred.m_char_set);
            if (j == std::string::npos) {
                str.clear();
            } else {
                str = str.substr(0, j + 1);
            }
        }
        inline void trim(std::string& str) {
            trim_if(str, is_space());
        }
        inline void trim_left(std::string& str) {
            trim_left_if(str, is_space());
        }
        inline void trim_right(std::string& str) {
            trim_right_if(str, is_space());
        }
        inline void trim_if(std::wstring& str, const char_set_predicate& pred) {
            size_t i = str.find_first_not_of(pred.m_wchar_set);
            size_t j = str.find_last_not_of(pred.m_wchar_set);
            if ((i == std::wstring::npos) || (j == std::wstring::npos)) {
                str.clear();
            } else {
                str = str.substr(i, j - i + 1);
            }
        }
        inline void trim_left_if(std::wstring& str, const char_set_predicate& pred) {
            size_t i = str.find_first_not_of(pred.m_wchar_set);
            if (i == std::wstring::npos) {
                str.clear();
            } else {
                str = str.substr(i);
            }
        }
        inline void trim_right_if(std::wstring& str, const char_set_predicate& pred) {
            size_t j = str.find_last_not_of(pred.m_wchar_set);
            if (j == std::wstring::npos) {
                str.clear();
            } else {
                str = str.substr(0, j + 1);
            }
        }
        inline void trim(std::wstring& str) {
            trim_if(str, is_space());
        }
        inline void trim_left(std::wstring& str) {
            trim_left_if(str, is_space());
        }
        inline void trim_right(std::wstring& str) {
            trim_right_if(str, is_space());
        }
        template <typename T_STRING>
        inline T_STRING to_upper_copy(const T_STRING& str) {
            T_STRING copy(str);
            to_upper(copy);
            return copy;
        }
        template <typename T_STRING>
        inline T_STRING to_lower_copy(const T_STRING& str) {
            T_STRING copy(str);
            to_lower(copy);
            return copy;
        }
        template <typename T_STRING>
        inline T_STRING trim_copy(const T_STRING& str) {
            T_STRING copy(str);
            trim(copy);
            return copy;
        }
        template <typename T_STRING>
        inline T_STRING trim_left_copy(const T_STRING& str) {
            T_STRING copy(str);
            trim_left(copy);
            return copy;
        }
        template <typename T_STRING>
        inline T_STRING trim_right_copy(const T_STRING& str) {
            T_STRING copy(str);
            trim_right(copy);
            return copy;
        }
        template <typename T_STRING_CONTAINER>
        void split(T_STRING_CONTAINER& container,
                   const std::string& str,
                   const char_set_predicate& pred)
        {
            container.clear();
            size_t i = 0, j = str.find_first_of(pred.m_char_set);
            while (j != T_STRING_CONTAINER::value_type::npos) {
                container.push_back(str.substr(i, j - i));
                i = j + 1;
                j = str.find_first_of(pred.m_char_set, i);
            }
            container.push_back(str.substr(i));
        }
        template <typename T_STRING_CONTAINER>
        void split(T_STRING_CONTAINER& container,
                   const std::wstring& str,
                   const char_set_predicate& pred)
        {
            container.clear();
            size_t i = 0, j = str.find_first_of(pred.m_wchar_set);
            while (j != T_STRING_CONTAINER::value_type::npos) {
                container.push_back(str.substr(i, j - i));
                i = j + 1;
                j = str.find_first_of(pred.m_wchar_set, i);
            }
            container.push_back(str.substr(i));
        }
        template <typename T_STRING_CONTAINER>
        typename T_STRING_CONTAINER::value_type
        join(const T_STRING_CONTAINER& container,
             const typename T_STRING_CONTAINER::value_type& sep)
        {
            typename T_STRING_CONTAINER::value_type result;
            typename T_STRING_CONTAINER::const_iterator it = container.begin();
            typename T_STRING_CONTAINER::const_iterator end = container.end();
            if (it != end) {
                result = *it;
                for (++it; it != end; ++it) {
                    result += sep;
                    result += *it;
                }
            }
            return result;
        }
        template <typename T_STRING>
        void replace_all(T_STRING& str,
                         const T_STRING& from, const T_STRING& to)
        {
            size_t i = 0;
            for (;;) {
                i = str.find(from, i);
                if (i == T_STRING::npos)
                    break;
                str.replace(i, from.size(), to);
                i += to.size();
            }
        }
        template <typename T_STRING>
        inline void replace_all(T_STRING& str,
            const typename T_STRING::value_type *from,
            const typename T_STRING::value_type *to)
        {
            replace_all(str, T_STRING(from), T_STRING(to));
        }
        template <typename T_STRING>
        inline T_STRING replace_all_copy(
            const T_STRING& str,
            const T_STRING& from, const T_STRING& to)
        {
            T_STRING copy(str);
            replace_all(copy, from, to);
            return copy;
        }
        template <typename T_STRING>
        inline T_STRING replace_all_copy(const T_STRING& str,
            const typename T_STRING::value_type *from,
            const typename T_STRING::value_type *to)
        {
            T_STRING copy(str);
            replace_all(copy, from, to);
            return copy;
        }
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_STRING_ALGORITHM_HPP_
