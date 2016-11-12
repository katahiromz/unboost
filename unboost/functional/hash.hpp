// hash.hpp --- Unboost hash
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_HASH_HPP_
#define UNBOOST_HASH_HPP_

#include "../unboost.hpp"

// If not choosed, choose one
#if (defined(UNBOOST_USE_CXX11_HASH) + defined(UNBOOST_USE_BOOST_HASH) + defined(UNBOOST_USE_UNBOOST_HASH) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_HASH
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_HASH
    #else
        #define UNBOOST_USE_UNBOOST_HASH
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_HASH
    #include <functional>
    namespace unboost {
        using std::hash;
    }
#elif defined(UNBOOST_USE_BOOST_HASH)
    #include <boost/functional/hash.hpp>
    namespace unboost {
        using boost::hash;
    }
#elif defined(UNBOOST_USE_UNBOOST_HASH)
    #include <string>   // for std::string, std::wstring, ...
    namespace unboost {
        template <typename Key>
        struct hash {
            typedef Key argument_type;
            typedef size_t result_type;
            hash() { }
        };

        inline size_t _hash_value(bool b) {
            return b;
        }
        inline size_t _hash_value(char ch) {
            return static_cast<unsigned char>(ch);
        }
        inline size_t _hash_value(signed char ch) {
            return static_cast<unsigned char>(ch);
        }
        inline size_t _hash_value(unsigned char ch) {
            return ch;
        }
        inline size_t _hash_value(short s) {
            return static_cast<unsigned short>(s);
        }
        inline size_t _hash_value(unsigned short s) {
            return s;
        }
        inline size_t _hash_value(long n) {
            return static_cast<unsigned long>(n);
        }
        inline size_t _hash_value(unsigned long n) {
            return n;
        }
        inline size_t _hash_value(int n) {
            return static_cast<unsigned int>(n);
        }
        inline size_t _hash_value(unsigned int n) {
            return n;
        }
        inline size_t _hash_value(_int64_t n) {
            return size_t(n ^ (n >> 32));
        }
        inline size_t _hash_value(_uint64_t n) {
            return size_t(n ^ (n >> 32));
        }
        inline size_t _hash_value(float e) {
            return _hash_value(*reinterpret_cast<const int *>(&e));
        }
        inline size_t _hash_value(double e) {
            return _hash_value(*reinterpret_cast<const _uint64_t *>(&e));
        }
        inline size_t _hash_value(long double e) {
            size_t ret = 0;
            const unsigned char *pch = reinterpret_cast<const unsigned char *>(&e);
            for (size_t i = 0; i < sizeof(e); ++i) {
                ret ^= pch[i];
            }
            return ret;
        }
        inline size_t _hash_value(const void *p) {
            return *reinterpret_cast<const size_t *>(&p);
        }

        inline size_t _hash_value(const std::string& str) {
            size_t ret = 0;
            const size_t count = str.size();
            unsigned char shift = 0;
            for (size_t i = 0; i < count; ++i) {
                ret ^= size_t(str[i]);
                ret <<= shift;
                ++shift;
                if (shift >= 8)
                    shift = 0;
            }
            return ret;
        }
        inline size_t _hash_value(const std::wstring& str) {
            size_t ret = 0;
            const size_t count = str.size();
            unsigned char shift = 0;
            for (size_t i = 0; i < count; ++i) {
                ret ^= size_t(str[i]);
                ret <<= shift;
                ++shift;
                if (shift >= 8)
                    shift = 1;
            }
            return ret;
        }

        #define UNBOOST_HASH_SPECIALIZE(type) \
            template <> \
            struct hash<type> { \
                typedef type argument_type; \
                typedef size_t result_type; \
                hash() { } \
                result_type operator()(type key) const { \
                    return _hash_value(key); \
                } \
            }

        #define UNBOOST_HASH_SPECIALIZE_REF(type) \
            template <> \
            struct hash<type> { \
                typedef type argument_type; \
                typedef size_t result_type; \
                hash() { } \
                result_type operator()(const type& key) const { \
                    return _hash_value(key); \
                } \
            }

        UNBOOST_HASH_SPECIALIZE(bool);
        UNBOOST_HASH_SPECIALIZE(char);
        UNBOOST_HASH_SPECIALIZE(signed char);
        UNBOOST_HASH_SPECIALIZE(unsigned char);
        UNBOOST_HASH_SPECIALIZE(short);
        UNBOOST_HASH_SPECIALIZE(unsigned short);
        UNBOOST_HASH_SPECIALIZE(long);
        UNBOOST_HASH_SPECIALIZE(unsigned long);
        UNBOOST_HASH_SPECIALIZE(int);
        UNBOOST_HASH_SPECIALIZE(unsigned int);
        UNBOOST_HASH_SPECIALIZE(_int64_t);
        UNBOOST_HASH_SPECIALIZE(_uint64_t);
        UNBOOST_HASH_SPECIALIZE(float);
        UNBOOST_HASH_SPECIALIZE(double);
        UNBOOST_HASH_SPECIALIZE(long double);
        UNBOOST_HASH_SPECIALIZE(const void *);

        UNBOOST_HASH_SPECIALIZE_REF(std::string);
        UNBOOST_HASH_SPECIALIZE_REF(std::wstring);
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_HASH_HPP_
