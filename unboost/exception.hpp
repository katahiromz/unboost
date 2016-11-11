// exception.hpp --- Unboost exceptions
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_EXCEPTION_HPP_
#define UNBOOST_EXCEPTION_HPP_

#include "unboost.hpp"
#include <exception>
#include <stdexcept>
#include <cstdio>

#ifdef UNBOOST_USE_CXX11
    #include <system_error>
    #include <memory>
#elif defined(UNBOOST_USE_BOOST)
    #include <boost/system/system_error.hpp>
    #include <boost/smart_ptr/bad_weak_ptr.hpp>
#endif

namespace unboost {
    using std::exception;
    using std::invalid_argument;
    using std::out_of_range;
    using std::runtime_error;

    #ifdef UNBOOST_USE_CXX11
        namespace system {
            using std::system_error;
        }
    #elif defined(UNBOOST_USE_BOOST)
        namespace system {
            using boost::system::system_error;
        }
    #else   // Unboost
        namespace system {
            class system_error : public exception {
            public:
                typedef long error_code;
                system_error(error_code ec) : m_code(ec) { }
                const error_code code() const { return m_code; }
                virtual const char *what() const UNBOOST_NOEXCEPT {
                    static char buf[64];
                    std::sprintf(buf, "Error Code: %d", code());
                    return buf;
                }
            protected:
                int m_code;
            };
        } // namespace system
    #endif  // Unboost
    using unboost::system::system_error;

    #ifdef UNBOOST_USE_BOOST
        using boost::lexical_cast;
    #else
        class bad_lexical_cast : public exception {
        public:
            bad_lexical_cast() { }
            virtual const char *what() const UNBOOST_NOEXCEPT{
                return "lexical_cast";
            }
        };
    #endif

    #ifdef UNBOOST_USE_CXX11
        using std::bad_weak_ptr;
    #elif defined(UNBOOST_USE_BOOST)
        using boost::bad_weak_ptr;
    #else
        class bad_weak_ptr : public exception {
        public:
            bad_weak_ptr() { }
            virtual ~bad_weak_ptr() { }
            virtual const char *what() const UNBOOST_NOEXCEPT {
                return "unboost::bad_weak_ptr";
            }
        };
    #endif
} // namespace unboost

#endif  // ndef UNBOOST_EXCEPTION_HPP_
