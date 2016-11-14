// system_error.hpp --- Unboost system error
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_SYSTEM_ERROR_HPP_
#define UNBOOST_SYSTEM_ERROR_HPP_

#include "unboost.hpp"

// If not choosed, choose one
#if (defined(UNBOOST_USE_CXX11_SYSTEM) + defined(UNBOOST_USE_BOOST_SYSTEM) + defined(UNBOOST_USE_UNBOOST_SYSTEM) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_SYSTEM
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_SYSTEM
    #else
        #ifdef UNBOOST_CXX11
            #define UNBOOST_USE_CXX11_SYSTEM
        #else
            #define UNBOOST_USE_UNBOOST_SYSTEM
        #endif
    #endif
#endif

#ifdef UNBOOST_USE_CXX11_SYSTEM
    #include <system_error>
    namespace unboost {
        namespace system {
            using std::error_category;
            using std::generic_category;
            using std::system_category;
            using std::error_condition;
            using std::error_code;
            using std::system_error;
            using std::is_error_code_enum;
            using std::is_error_condition_enum;
            using std::make_error_code;
            using std::make_error_condition;
        }
        using std::error_category;
        using std::generic_category;
        using std::system_category;
        using std::error_condition;
        using std::error_code;
        using std::system_error;
        using std::is_error_code_enum;
        using std::is_error_condition_enum;
        using std::make_error_code;
        using std::make_error_condition;
    } // namespace unboost;
#elif defined(UNBOOST_USE_BOOST_SYSTEM)
    #include <boost/system/system_error.hpp>    // for boost::system::system_error
    namespace unboost {
        namespace system {
            using boost::system::error_category;
            using boost::system::generic_category;
            using boost::system::system_category;
            using boost::system::error_condition;
            using boost::system::error_code;
            using boost::system::system_error;
            using boost::system::is_error_code_enum;
            using boost::system::is_error_condition_enum;
            using boost::system::make_error_code;
            using boost::system::make_error_condition;
        }
        using boost::system::error_category;
        using boost::system::generic_category;
        using boost::system::system_category;
        using boost::system::error_condition;
        using boost::system::error_code;
        using boost::system::system_error;
        using boost::system::is_error_code_enum;
        using boost::system::is_error_condition_enum;
        using boost::system::make_error_code;
        using boost::system::make_error_condition;
    } // namespace unboost;
#elif defined(UNBOOST_USE_UNBOOST_SYSTEM)
    #include "system/error_code.hpp"
    namespace unboost {
        class error_code;
        class error_condition;
        class system_error;

        template<typename _Tp>
        struct is_error_code_enum {
            enum { value = 0 };
        };

        template<typename _Tp>
        struct is_error_condition_enum {
            enum { value = 0 };
        };
        template <>
        struct is_error_condition_enum<errc::errc_t> {
            enum { value = 1 };
        };

        class error_category {
        public:
            error_category() { }
            virtual ~error_category() { }

            virtual const char *name() const UNBOOST_NOEXCEPT = 0;

            virtual error_condition default_error_condition(int code) const {
                return error_condition(code, *this);
            }
            virtual bool
            equivalent(int code, const error_condition& condition) const {
                return default_error_condition(code) == condition;
            }
            virtual bool
            equivalent(const error_code& code, int condition) const {
                return *this == code.category() && code.value() == condition;
            }
            virtual std::string
            message(int condition) const {
                std::string ret = std::strerror(condition);
                return ret;
            }
            inline bool
            operator==(const error_category& rhs) {
                return this == &rhs;
            }
            inline bool
            operator!=(const error_category& rhs) {
                return this != &rhs;
            }
            inline bool
            operator<(const error_category& rhs) {
                return this < &rhs;
            }
        private:
            error_category(const error_category&)/* = delete*/;
            error_category& operator=(const error_category&)/* = delete*/;
        };

        namespace details {
            class _my_generic_category : public error_category {
            public:
                _my_generic_category() { }
                virtual const char *name() const UNBOOST_NOEXCEPT {
                    return "generic_category";
                }
            };
            class _my_system_category : public error_category {
            public:
                _my_system_category() { }
                virtual const char *name() const UNBOOST_NOEXCEPT {
                    return "system_category";
                }
                #ifdef _WIN32
                    virtual std::string message(int condition) const {
                        std::string ret;
                        HLOCAL hLocal = NULL;
                        ::FormatMessageA(
                            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS |
                            FORMAT_MESSAGE_FROM_SYSTEM, NULL, condition, 0,
                            reinterpret_cast<char *>(&hLocal), 1, NULL);
                        if (hLocal)  {
                            ret = reinterpret_cast<char *>(::LocalLock(hLocal));
                            ::LocalUnlock(hLocal);
                            ::LocalFree(hLocal);
                        } else {
                            ret = "internal error";
                        }
                        return ret;
                    } // message
                #endif  // def _WIN32
            }; // class _my_system_category
        } // namespace details

        inline const error_category& generic_category() UNBOOST_NOEXCEPT {
            static const details::_my_generic_category gc;
            return gc;
        }
        inline const error_category& system_category() UNBOOST_NOEXCEPT {
            static const details::_my_system_category sc;
            return sc;
        }

        class error_code {
        public:
            error_code() : m_code(0), m_pecat(&system_category()) {
                ;
            }
            error_code(int ec, const error_category& ecat)
                : m_code(ec), m_pecat(&ecat)
            {
                ;
            }

            template <typename _ErrorCodeEnum>
            error_code(_ErrorCodeEnum e);
            template <typename _ErrorCodeEnum>
            error_code& operator=(_ErrorCodeEnum e);

            void assign(int ec, const error_category& ecat) {
                m_code = ec;
                m_pecat = &ecat;
            }

            void clear() {
                *this = error_code(0, system_category());
            }

            int value() const {
                return m_code;
            }
            const error_category& category() const {
                return *m_pecat;
            }

            error_condition default_error_condition() const {
                return category().default_error_condition(value());
            }

            std::string message() const {
                return category().message(value());
            }

            explicit operator bool() const {
                return value() != 0;
            }

        protected:
            int                     m_code;
            const error_category *  m_pecat;
        }; // class error_code

        class error_condition {
        public:
            error_condition() : m_value(0), m_pecat(&generic_category()) { }

            error_condition(int val, const error_category& ecat)
                : m_value(val), m_pecat(&ecat) { }

            template <typename _ErrorConditionEnum>
            error_condition(_ErrorConditionEnum e) {
                assert(is_error_condition_enum<_ErrorConditionEnum>::value);
                *this = make_error_condition(e);
            }

            template <typename _ErrorConditionEnum>
            error_condition& operator=(_ErrorConditionEnum e) {
                assert(is_error_condition_enum<_ErrorConditionEnum>::value);
                *this = make_error_condition(e);
                return *this;
            }

            error_condition(const error_condition& other) {
                m_value = other.m_value;
                m_pecat = other.m_pecat;
            }
            error_condition& operator=(const error_condition& other) {
                m_value = other.m_value;
                m_pecat = other.m_pecat;
                return *this;
            }

            void assign(int val, const error_category& ecat) {
                m_value = val;
                m_pecat = &ecat;
            }

            void clear() {
                assign(0, generic_category());
            }

            int value() const {
                return m_value;
            }
            const error_category& category() const {
                return *m_pecat;
            }
            std::string message() const {
                return category().message(value());
            }
            explicit operator bool() const {
                return value() != 0;
            }

        protected:
            int m_value;
            const error_category *m_pecat;
        };

        inline bool operator==(const error_code& lhs, const error_code& rhs) {
            return lhs.category() == rhs.category() &&
                   lhs.value() == rhs.value();
        }
        inline bool operator!=(const error_code& lhs, const error_code& rhs) {
            return !(lhs == rhs);
        }
        inline bool operator<(const error_code& lhs, const error_code& rhs) {
            if (lhs.category() < rhs.category())
                return true;
            if (lhs.category() == rhs.category()) {
                if (lhs.value() < rhs.value())
                    return true;
            }
            return false;
        }

        inline bool
        operator==(const error_condition& lhs, const error_condition& rhs) {
            return lhs.category() == rhs.category() &&
                   lhs.value() == rhs.value();
        }
        inline bool
        operator==(const error_code& lhs, const error_condition& rhs) {
            return lhs.category().equivalent(rhs.value(), lhs) ||
                   rhs.category().equivalent(lhs.value(), rhs);
        }
        inline bool
        operator==(const error_condition& lhs, const error_code& rhs) {
            return lhs.category().equivalent(rhs.value(), lhs) ||
                   rhs.category().equivalent(lhs.value(), rhs);
        }
        inline bool
        operator!=(const error_condition& lhs, const error_condition& rhs) {
            return !(lhs == rhs);
        }
        inline bool
        operator!=(const error_code& lhs, const error_condition& rhs) {
            return !(lhs == rhs);
        }
        inline bool
        operator!=(const error_condition& lhs, const error_code& rhs) {
            return !(lhs == rhs);
        }
        inline bool
        operator<(const error_condition& lhs, const error_condition& rhs) {
            if (lhs.category() < rhs.category())
                return true;
            if (lhs.category() == rhs.category()) {
                if (lhs.value() < rhs.value())
                    return true;
            }
            return false;
        }

        template <typename CharT, class Traits>
        inline std::basic_ostream<CharT, Traits>&
        operator<<(std::basic_ostream<CharT, Traits>& os, const error_code& ec) {
            os << ec.category().name() << ':' << ec.value();
            return os;
        }

        template <>
        struct hash<error_code> {
            typedef error_code argument_type;
            typedef size_t result_type;
            result_type operator()(error_code key) const {
                return key.value();
            }
        };

        class system_error : public std::runtime_error {
        public:
            system_error(error_code ec = error_code())
                : runtime_error(ec.message()), m_code(ec) { }

            system_error(error_code ec, const string& what)
                : runtime_error(what + ": " + ec.message()),
                  m_code(ec) { }

            system_error(error_code ec, const char* what)
                : runtime_error(what + (": " + ec.message())),
                  m_code(ec) { }

            system_error(int v, const error_category& ecat, const char* what)
                : system_error(error_code(v, ecat), what) { }

            system_error(int v, const error_category& ecat)
                : runtime_error(error_code(v, ecat).message()),
                  m_code(v, ecat) { }

            system_error(int v, const error_category& ecat,
                         const string& what)
                : runtime_error(what + ": " +
                                error_code(v, ecat).message()),
                  m_code(v, ecat) { }

            virtual ~system_error() UNBOOST_NOEXCEPT { }

            const error_code& code() const UNBOOST_NOEXCEPT {
                return m_code;
            }

        protected:
            error_code  m_code;
        }; // system_error
    } // namespace unboost

    #ifdef _WIN32
        #include "system/windows_error.hpp"

        namespace unboost {
            template <>
            struct is_error_code_enum<windows_error::windows_error_code> {
                enum { value = 1 };
            };

            inline error_code
            make_error_code(windows_error::windows_error_code e) {
                return error_code(e, system_category());
            }
        } // namespace unboost
    #elif defined(__linux__)
        #include "system/linux_error.hpp"

        namespace unboost {
            template <>
            struct is_error_code_enum<linux_error::linux_errno> {
                enum { value = 1 };
            };

            inline error_code
            make_error_code(linux_error::linux_errno e) {
                return error_code(e, system_category());
            }
        } // namespace unboost
    #else
        #error Your compiler is not supported yet. You lose.
    #endif

    namespace unboost {
        template <typename _ErrorCodeEnum>
        inline error_code::error_code(_ErrorCodeEnum e) {
            assert(is_error_code_enum<_ErrorCodeEnum>::value);
            *this = make_error_code(e);
        }

        template <typename _ErrorCodeEnum>
        inline error_code& error_code::operator=(_ErrorCodeEnum e) {
            assert(is_error_code_enum<_ErrorCodeEnum>::value);
            *this = make_error_code(e);
            return *this;
        }

        namespace system {
            using unboost::error_category;
            using unboost::generic_category;
            using unboost::system_category;
            using unboost::error_condition;
            using unboost::error_code;
            using unboost::system_error;
            using unboost::is_error_code_enum;
            using unboost::is_error_condition_enum;
            using unboost::make_error_code;
            using unboost::make_error_condition;
        } // namespace system
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_SYSTEM_ERROR_HPP_
