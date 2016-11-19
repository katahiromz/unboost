// string_algorithm.hpp --- Unboost string algorithm
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_STRING_ALGORITHM_HPP_
#define UNBOOST_STRING_ALGORITHM_HPP_

#include "../unboost.hpp"

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
        using boost::algorithm::is_alnum;
        using boost::algorithm::is_alpha;
        using boost::algorithm::is_any_of;
        using boost::algorithm::is_classified;
        using boost::algorithm::is_cntrl;
        using boost::algorithm::is_digit;
        using boost::algorithm::is_from_range;
        using boost::algorithm::is_lower;
        using boost::algorithm::is_punct;
        using boost::algorithm::is_space;
        using boost::algorithm::is_upper;
        using boost::algorithm::is_xdigit;
        using boost::algorithm::join;
        using boost::algorithm::replace_all;
        using boost::algorithm::replace_all_copy;
        using boost::algorithm::split;
        using boost::algorithm::to_lower;
        using boost::algorithm::to_lower_copy;
        using boost::algorithm::to_upper;
        using boost::algorithm::to_upper_copy;
        using boost::algorithm::trim;
        using boost::algorithm::trim_copy;
        using boost::algorithm::trim_copy_if;
        using boost::algorithm::trim_if;
        using boost::algorithm::trim_left;
        using boost::algorithm::trim_left_copy;
        using boost::algorithm::trim_left_copy_if;
        using boost::algorithm::trim_left_if;
        using boost::algorithm::trim_right;
        using boost::algorithm::trim_right_copy;
        using boost::algorithm::trim_right_copy_if;
        using boost::algorithm::trim_right_if;
        namespace algorithm {
            using boost::algorithm::is_alnum;
            using boost::algorithm::is_alpha;
            using boost::algorithm::is_any_of;
            using boost::algorithm::is_classified;
            using boost::algorithm::is_cntrl;
            using boost::algorithm::is_digit;
            using boost::algorithm::is_from_range;
            using boost::algorithm::is_lower;
            using boost::algorithm::is_punct;
            using boost::algorithm::is_space;
            using boost::algorithm::is_upper;
            using boost::algorithm::is_xdigit;
            using boost::algorithm::join;
            using boost::algorithm::replace_all;
            using boost::algorithm::replace_all_copy;
            using boost::algorithm::split;
            using boost::algorithm::to_lower;
            using boost::algorithm::to_lower_copy;
            using boost::algorithm::to_upper;
            using boost::algorithm::to_upper_copy;
            using boost::algorithm::trim;
            using boost::algorithm::trim_copy;
            using boost::algorithm::trim_copy_if;
            using boost::algorithm::trim_if;
            using boost::algorithm::trim_left;
            using boost::algorithm::trim_left_copy;
            using boost::algorithm::trim_left_copy_if;
            using boost::algorithm::trim_left_if;
            using boost::algorithm::trim_right;
            using boost::algorithm::trim_right_copy;
            using boost::algorithm::trim_right_copy_if;
            using boost::algorithm::trim_right_if;
        } // namespace algorithm
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_STRING_ALGORITHM)
    #include <locale>   // for std::locale
    #include <cstring>  // for std::strlen, ...
    #include <cwchar>   // for std::wcslen, ...
    namespace unboost {
        template <typename Derived>
        struct predicate_facade { };

        namespace detail {
            struct is_classifiedF
                : public predicate_facade<is_classifiedF>
            {
                typedef bool result_type;

                is_classifiedF(std::ctype_base::mask Type,
                               const std::locale& Locale = std::locale())
                    : m_Type(Type), m_Locale(Locale)
                {
                }

                template <typename CharT>
                bool operator()(CharT ch) const {
                    const std::ctype<CharT>& ct =
                        std::use_facet<std::ctype<CharT> >(m_Locale);
                    return ct.is(m_Type, ch);
                }

            protected:
                std::ctype_base::mask   m_Type;
                std::locale             m_Locale;
            }; // struct is_classifiedF

            template <typename CharT>
            inline size_t slen(const CharT *str) {
                size_t count = 0;
                while (*str) {
                    ++str;
                    ++count;
                }
                return count;
            }
            template <>
            inline size_t slen<char>(const char *str) {
                using namespace std;
                return strlen(str);
            }
            template <>
            inline size_t slen<wchar_t>(const wchar_t *str) {
                using namespace std;
                return wcslen(str);
            }

            template <typename CharT>
            inline CharT *sdup(const CharT *str, size_t count) {
                using namespace std;
                size_t size = count * sizeof(CharT);
                CharT *ptr = reinterpret_cast<CharT *>(malloc(size));
                if (ptr) {
                    memcpy(ptr, str, size);
                } else {
                    throw bad_alloc();
                }
                return ptr;
            }

            template <typename CharT>
            inline CharT *sdup(const CharT *str) {
                using namespace std;
                size_t count = slen(str);
                return sdup(str, count);
            }

            template <typename CharT>
            inline CharT *schr(const CharT *str, CharT ch, size_t len) {
                while (len > 0) {
                    if (*str == ch) {
                        return const_cast<CharT *>(str);
                    }
                    ++str;
                    --len;
                }
                return NULL;
            }
            template <typename CharT>
            inline CharT *schr(const CharT *str, CharT ch) {
                while (*str) {
                    if (*str == ch) {
                        return const_cast<CharT *>(str);
                    }
                    ++str;
                }
                return NULL;
            }
            template <>
            inline char *schr<char>(const char *str, char ch) {
                using namespace std;
                return strchr(str, ch);
            }
            template <>
            inline wchar_t *schr<wchar_t>(const wchar_t *str, wchar_t ch) {
                using namespace std;
                return wcschr(str, ch);
            }

            template <typename CharT>
            struct is_any_ofF : public predicate_facade<is_any_ofF<CharT> > {
                typedef bool result_type;
                typedef is_any_ofF<CharT> self_type;

                is_any_ofF(const CharT *str) : m_str(NULL), m_len(0) {
                    *this = str;
                }

                template <typename Traits>
                is_any_ofF(const std::basic_string<CharT, Traits>& str)
                    : m_str(NULL), m_len(0)
                {
                    *this = str;
                }

                is_any_ofF(const self_type& other) : m_str(NULL), m_len(0) {
                    *this = other;
                }

                self_type& operator=(const CharT *str) {
                    std::free(m_str);
                    m_str = sdup(str);
                    m_len = slen(str);
                    return *this;
                }

                template <typename Traits>
                self_type&
                operator=(const std::basic_string<CharT, Traits>& str) {
                    std::free(m_str);
                    m_str = sdup(str.c_str(), str.size());
                    m_len = str.size();
                    return *this;
                }

                self_type& operator=(const self_type& other) {
                    if (this != &other) {
                        std::free(m_str);
                        m_str = sdup(other.m_str, other.m_len);
                        m_len = other.m_len;
                    }
                    return *this;
                }

                ~is_any_ofF() {
                    std::free(m_str);
                }

                bool operator()(CharT ch) const {
                    return schr(m_str, ch, m_len) != NULL;
                }

            protected:
                CharT *     m_str;
                size_t      m_len;
            }; // struct is_any_ofF<CharT>

            template <typename CharT>
            struct is_from_rangeF
                : public predicate_facade<is_from_rangeF<CharT> >
            {
                typedef bool result_type;

                is_from_rangeF(CharT from, CharT to)
                    : m_From(from), m_To(to) { }

                template <typename Char2T>
                bool operator()(Char2T ch) const {
                    return (m_From <= ch && ch <= m_To);
                }

            protected:
                CharT m_From;
                CharT m_To;
            };

            template <typename Pred1, typename Pred2>
            struct pred_andF
                : public predicate_facade<pred_andF<Pred1, Pred2> >
            {
                typedef bool result_type;

                pred_andF(Pred1 pred1, Pred2 pred2)
                    : m_Pred1(pred1), m_Pred2(pred2) { }

                template <typename CharT>
                bool operator()(CharT ch) const {
                    return (m_Pred1(ch) && m_Pred2(ch));
                }

            protected:
                Pred1   m_Pred1;
                Pred2   m_Pred2;
            };

            template <typename Pred1, typename Pred2>
            struct pred_orF
                : public predicate_facade<pred_orF<Pred1, Pred2> >
            {
                typedef bool result_type;

                pred_orF(Pred1 pred1, Pred2 pred2)
                    : m_Pred1(pred1), m_Pred2(pred2) { }

                template <typename CharT>
                bool operator()(CharT ch) const {
                    return (m_Pred1(ch) || m_Pred2(ch));
                }

            protected:
                Pred1   m_Pred1;
                Pred2   m_Pred2;
            };

            template <typename Pred1>
            struct pred_notF
                : public predicate_facade<pred_notF<Pred1> >
            {
                typedef bool result_type;

                pred_notF(Pred1 pred1) : m_Pred1(pred1) { }

                template <typename CharT>
                bool operator()(CharT ch) const {
                    return !m_Pred1(ch);
                }

            protected:
                Pred1   m_Pred1;
            };
        } // namespace detail

        inline detail::is_classifiedF
        is_classified(std::ctype_base::mask Type,
                      const std::locale& Locale = std::locale())
        {
            return detail::is_classifiedF(Type, Locale);
        }

        inline detail::is_classifiedF 
        is_space(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::space, Locale);
        }
        inline detail::is_classifiedF 
        is_digit(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::digit, Locale);
        }
        inline detail::is_classifiedF 
        is_alpha(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::alpha, Locale);
        }
        inline detail::is_classifiedF 
        is_alnum(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::alnum, Locale);
        }
        inline detail::is_classifiedF 
        is_lower(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::lower, Locale);
        }
        inline detail::is_classifiedF 
        is_upper(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::upper, Locale);
        }
        inline detail::is_classifiedF 
        is_cntrl(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::cntrl, Locale);
        }
        inline detail::is_classifiedF 
        is_graph(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::graph, Locale);
        }
        inline detail::is_classifiedF 
        is_print(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::print, Locale);
        }
        inline detail::is_classifiedF 
        is_punct(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::punct, Locale);
        }
        inline detail::is_classifiedF 
        is_xdigit(const std::locale& Locale = std::locale()) {
            return is_classified(std::ctype_base::xdigit, Locale);
        }

        template <typename CharT>
        inline detail::is_any_ofF<CharT>
        is_any_of(const CharT *ptr) {
            return detail::is_any_ofF<CharT>(ptr);
        }
        template <typename CharT, typename Traits>
        inline detail::is_any_ofF<CharT>
        is_any_of(const std::basic_string<CharT, Traits>& str) {
            return detail::is_any_ofF<CharT>(str);
        }

        template <typename CharT>
        inline detail::is_from_rangeF<CharT>
        is_from_range(CharT from, CharT to) {
            return detail::is_from_rangeF<CharT>(from, to); 
        }

        template<typename Pred1, typename Pred2>
        inline detail::pred_andF<Pred1, Pred2>
        operator&&(const predicate_facade<Pred1>& pred1,
                   const predicate_facade<Pred2>& pred2)
        {
            return detail::pred_andF<Pred1, Pred2>(
                *static_cast<const Pred1*>(&pred1), 
                *static_cast<const Pred2*>(&pred2));
        }
        template<typename Pred1, typename Pred2>
        inline detail::pred_orF<Pred1, Pred2>
        operator||(const predicate_facade<Pred1>& pred1,
                   const predicate_facade<Pred2>& pred2)
        {
            return detail::pred_orF<Pred1, Pred2>(
                *static_cast<const Pred1*>(&pred1), 
                *static_cast<const Pred2*>(&pred2));
        }
        template<typename Pred1>
        inline detail::pred_notF<Pred1>
        operator!(const predicate_facade<Pred1>& pred1) {
            return detail::pred_notF<Pred1>(
                *static_cast<const Pred1*>(&pred1));
        }

        namespace detail {
            template <typename T_STRING, typename Pred>
            inline size_t
            find_first_of(const T_STRING& str,
                          const Pred& pred, size_t i = 0)
            {
                size_t ret = T_STRING::npos;
                while (i < str.size()) {
                    if (pred(str[i])) {
                        ret = i;
                        break;
                    }
                    ++i;
                }
                return ret;
            }
            template <typename T_STRING, typename Pred>
            inline size_t
            find_first_not_of(const T_STRING& str, const Pred& pred,
                              size_t i = 0)
            {
                return find_first_of(str, !pred, i);
            }

            template <typename T_STRING, typename Pred>
            inline size_t
            find_last_of(const T_STRING& str, const Pred& pred) {
                size_t i = 0, ret = T_STRING::npos;
                while (i < str.size()) {
                    if (pred(str[i])) {
                        ret = i;
                    }
                    ++i;
                }
                return ret;
            }

            template <typename T_STRING, typename Pred>
            inline size_t
            find_last_not_of(const T_STRING& str,
                             const predicate_facade<Pred>& pred)
            {
                return find_last_of(str, !pred);
            }
        } // namespace detail

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
        template <typename Pred>
        inline void trim_if(std::string& str, const Pred& pred) {
            size_t i = detail::find_first_not_of(str, pred);
            size_t j = detail::find_last_not_of(str, pred);
            if ((i == std::string::npos) || (j == std::string::npos)) {
                str.clear();
            } else {
                str = str.substr(i, j - i + 1);
            }
        }
        template <typename Pred>
        inline void trim_left_if(std::string& str, const Pred& pred) {
            size_t i = detail::find_first_not_of(str, pred);
            if (i == std::string::npos) {
                str.clear();
            } else {
                str = str.substr(i);
            }
        }
        template <typename Pred>
        inline void trim_right_if(std::string& str, const Pred& pred) {
            size_t j = detail::find_first_not_of(str, pred);
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
        template <typename Pred>
        inline void trim_if(std::wstring& str, const Pred& pred) {
            size_t i = detail::find_first_not_of(str, pred);
            size_t j = detail::find_last_not_of(str, pred);
            if ((i == std::wstring::npos) || (j == std::wstring::npos)) {
                str.clear();
            } else {
                str = str.substr(i, j - i + 1);
            }
        }
        template <typename Pred>
        inline void trim_left_if(std::wstring& str, const Pred& pred) {
            size_t i = detail::find_first_not_of(str, pred);
            if (i == std::wstring::npos) {
                str.clear();
            } else {
                str = str.substr(i);
            }
        }
        template <typename Pred>
        inline void trim_right_if(std::wstring& str, const Pred& pred) {
            size_t j = detail::find_last_not_of(str, pred);
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
        template <typename T_STRING, typename Pred>
        inline T_STRING
        trim_copy_if(const T_STRING& str, const Pred& pred) {
            T_STRING copy(str);
            trim_if(copy, pred);
            return copy;
        }
        template <typename T_STRING>
        inline T_STRING trim_left_copy(const T_STRING& str) {
            T_STRING copy(str);
            trim_left(copy);
            return copy;
        }
        template <typename T_STRING, typename Pred>
        inline T_STRING
        trim_left_copy_if(const T_STRING& str, const Pred& pred) {
            T_STRING copy(str);
            trim_left_if(copy, pred);
            return copy;
        }
        template <typename T_STRING>
        inline T_STRING trim_right_copy(const T_STRING& str) {
            T_STRING copy(str);
            trim_right(copy);
            return copy;
        }
        template <typename T_STRING, typename Pred>
        inline T_STRING
        trim_right_copy_if(const T_STRING& str, const Pred& pred) {
            T_STRING copy(str);
            trim_right_if(copy, pred);
            return copy;
        }
        template <typename T_STRING_CONTAINER, typename Pred>
        void split(T_STRING_CONTAINER& container,
                   const std::string& str, const Pred& pred)
        {
            container.clear();
            size_t i = 0, j = detail::find_first_of(str, pred);
            while (j != T_STRING_CONTAINER::value_type::npos) {
                container.push_back(str.substr(i, j - i));
                i = j + 1;
                j = detail::find_first_of(str, pred, i);
            }
            container.push_back(str.substr(i));
        }
        template <typename T_STRING_CONTAINER, typename Pred>
        void split(T_STRING_CONTAINER& container,
                   const std::wstring& str, const Pred& pred)
        {
            container.clear();
            size_t i = 0, j = detail::find_first_of(str, pred);
            while (j != T_STRING_CONTAINER::value_type::npos) {
                container.push_back(str.substr(i, j - i));
                i = j + 1;
                j = detail::find_first_of(str, pred, i);
            }
            container.push_back(str.substr(i));
        }
        template <typename T_STRING_CONTAINER>
        typename T_STRING_CONTAINER::value_type
        join(const T_STRING_CONTAINER& container,
             const typename T_STRING_CONTAINER::value_type& sep)
        {
            typename T_STRING_CONTAINER::value_type result;
            typename T_STRING_CONTAINER::const_iterator it, end;
            it = container.begin();
            end = container.end();
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

        namespace algorithm {
            using unboost::is_alnum;
            using unboost::is_alpha;
            using unboost::is_any_of;
            using unboost::is_classified;
            using unboost::is_cntrl;
            using unboost::is_digit;
            using unboost::is_from_range;
            using unboost::is_lower;
            using unboost::is_punct;
            using unboost::is_space;
            using unboost::is_upper;
            using unboost::is_xdigit;
            using unboost::join;
            using unboost::replace_all;
            using unboost::replace_all_copy;
            using unboost::split;
            using unboost::to_lower;
            using unboost::to_lower_copy;
            using unboost::to_upper;
            using unboost::to_upper_copy;
            using unboost::trim;
            using unboost::trim_copy;
            using unboost::trim_copy_if;
            using unboost::trim_if;
            using unboost::trim_left;
            using unboost::trim_left_copy;
            using unboost::trim_left_copy_if;
            using unboost::trim_left_if;
            using unboost::trim_right;
            using unboost::trim_right_copy;
            using unboost::trim_right_copy_if;
            using unboost::trim_right_if;
        } // namespace algorithm
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_STRING_ALGORITHM_HPP_
