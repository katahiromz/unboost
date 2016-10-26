#ifndef UNBOOST_EXCEPTION_HPP_
#define UNBOOST_EXCEPTION_HPP_

#include "unboost.hpp"
#include <cstdio>

namespace unboost {
    class exception {
    public:
        exception() { }
        exception(const exception& other) { }
        virtual ~exception() { }
        exception& operator=(const exception& other) {
            return *this;
        }
        virtual const char *what() const { return "exception"; }
    };

    class bad_lexical_cast : public exception {
    public:
        bad_lexical_cast() { }
        virtual const char *what() const { return "lexical_cast"; }
    };

    class invalid_argument : public exception {
    public:
        explicit invalid_argument(const std::string& str) : m_str(str) { }
        explicit invalid_argument(const char *str) : m_str(str) { }
        virtual const char *what() const { return m_str.c_str(); }
    protected:
        std::string m_str;
    };

    class out_of_range : public exception {
    public:
        explicit out_of_range(const std::string& str) : m_str(str) { }
        explicit out_of_range(const char *str) : m_str(str) { }
        virtual const char *what() const { return m_str.c_str(); }
    protected:
        std::string m_str;
    };

    class system_error : public exception {
    public:
        typedef long error_code;
        system_error(error_code ec) : m_code(ec) { }
        const error_code code() const { return m_code; }
        virtual const char *what() const {
            static char buf[32];
            std::sprintf(buf, "%d", code());
            return buf;
        }
    protected:
        int m_code;
    };

    class bad_weak_ptr : public exception {
    public:
        bad_weak_ptr() { }
        virtual ~bad_weak_ptr() { }
        virtual const char *what() const { return "unboost::bad_weak_ptr"; }
    };
} // namespace unboost

#endif  // ndef UNBOOST_EXCEPTION_HPP_
