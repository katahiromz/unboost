// array.hpp --- Unboost array
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_ARRAY_HPP_
#define UNBOOST_ARRAY_HPP_

#include "unboost.hpp"
#include "rv_ref.hpp"
#undef max
#undef min

// If not choosed, choose one
#if (defined(UNBOOST_USE_CXX11_ARRAY) + defined(UNBOOST_USE_TR1_ARRAY) + defined(UNBOOST_USE_BOOST_ARRAY) + defined(UNBOOST_USE_UNBOOST_ARRAY) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_ARRAY
    #elif defined(UNBOOST_USE_TR1)
        #define UNBOOST_USE_TR1_ARRAY
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_ARRAY
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_ARRAY
        #elif defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_ARRAY
                #else
                    #define UNBOOST_USE_UNBOOST_ARRAY
                #endif
            #elif (1500 <= _MSC_VER) && (_MSC_VER < 1600)
                // Visual C++ 2008
                #ifndef UNBOOST_NO_TR1
                    #define UNBOOST_USE_TR1_ARRAY
                #else
                    #define UNBOOST_USE_UNBOOST_ARRAY
                #endif
            #else
                #define UNBOOST_USE_UNBOOST_ARRAY
            #endif
        #elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
            // GCC 4.3 and later
            #ifndef UNBOOST_NO_TR1
                #define UNBOOST_USE_TR1_ARRAY
            #else
                #define UNBOOST_USE_UNBOOST_ARRAY
            #endif
        #else
            #define UNBOOST_USE_UNBOOST_ARRAY
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_ARRAY
    #include <array>            // for std::array
    namespace unboost {
        using std::array;
    }
#elif defined(UNBOOST_USE_TR1_ARRAY)
    #ifdef _MSC_VER
        #include <array>        // for std::tr1::array
    #else
        #include <tr1/array>    // for std::tr1::array
    #endif
    namespace unboost {
        using std::tr1::array;
    }
#elif defined(UNBOOST_USE_BOOST_ARRAY)
    #include <boost/array.hpp>  // for boost::array
    namespace unboost {
        using boost::array;
    }
#elif defined(UNBOOST_USE_UNBOOST_ARRAY)
    #include <stdexcept>
    #include <iterator>         // for std::reverse_iterator
    #include "exception.hpp"    // for unboost::out_of_range
    #include "swap.hpp"         // for unboost::swap
    namespace unboost {
        template <typename T, size_t N>
        struct array {
            typedef T value_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type *iterator;
            typedef const value_type *const_iterator;
            typedef std::reverse_iterator<iterator>         reverse_iterator;
            typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;
            typedef value_type *pointer;
            typedef const value_type *const_pointer;

            value_type m_data[N];

            reference at(size_type pos) {
                if (!(pos < size()))
                    std::out_of_range("unboost::array");
                return m_data[pos];
            }
            const_reference at(size_type pos) const {
                if (!(pos < size()))
                    std::out_of_range("unboost::array");
                return m_data[pos];
            }
            reference operator[](size_type pos) {
                return m_data[pos];
            }
            const_reference operator[](size_type pos) const {
                return m_data[pos];
            }
                  reference front()         { return m_data[0]; }
            const_reference front() const   { return m_data[0]; }
                  reference back()          { return m_data[size() - 1]; }
            const_reference back() const    { return m_data[size() - 1]; }
                  T* data()       { return m_data; }
            const T* data() const { return m_data; }

            bool empty() const { return N == 0; }
            size_type size() const { return N; }
            size_t max_size() const { return size_type(-1) / sizeof(T); }

                  iterator begin()          { return &m_data[0]; }
            const_iterator begin() const    { return &m_data[0]; }
            const_iterator cbegin() const   { return &m_data[0]; }
                  iterator end()            { return &m_data[N]; }
            const_iterator end() const      { return &m_data[N]; }
            const_iterator cend() const     { return &m_data[N]; }

                  reverse_iterator rbegin()         { return reverse_iterator(end()); }
            const_reverse_iterator rbegin() const   { return const_reverse_iterator(end()); }
            const_reverse_iterator crbegin() const  { return const_reverse_iterator(end()); }
                  reverse_iterator rend()           { return reverse_iterator(begin()); }
            const_reverse_iterator rend() const     { return const_reverse_iterator(begin()); }
            const_reverse_iterator crend() const    { return const_reverse_iterator(begin()); }

            void fill(const T& value) {
                if (sizeof(T) == 1) {
                    memset(m_data, value, N * sizeof(T));
                    return;
                }
                for (size_type i = 0; i < N; ++i) {
                    m_data[i] = value;
                }
            }
            void swap(array<T, N>& other) {
                array<T, N> tmp = other;
                other = *this;
                *this = tmp;
            }
            friend void swap(array<T, N>& a1, array<T, N>& a2) {
                a1.swap(a2);
            }
        }; // array<T, N>

        template <typename T, size_t N>
        inline void swap(array<T, N>& a1, array<T, N>& a2) {
            a1.swap(a2);
        }

        template <typename T, size_t N>
        inline int _compare_array(array<T, N>& a1, array<T, N>& a2) {
            for (typename array<T, N>::size_type i = 0; i < N; ++i) {
                if (a1.data()[i] < a2.data()[i])
                    return -1;
                if (a1.data()[i] > a2.data()[i])
                    return 1;
            }
            return 0;
        }

        template <typename T, size_t N>
        inline bool operator==(array<T, N>& a1, array<T, N>& a2) {
            return _compare_array(a1, a2) == 0;
        }
        template <typename T, size_t N>
        inline bool operator!=(array<T, N>& a1, array<T, N>& a2) {
            return _compare_array(a1, a2) != 0;
        }
        template <typename T, size_t N>
        inline bool operator<(array<T, N>& a1, array<T, N>& a2) {
            return _compare_array(a1, a2) < 0;
        }
        template <typename T, size_t N>
        inline bool operator<=(array<T, N>& a1, array<T, N>& a2) {
            return _compare_array(a1, a2) <= 0;
        }
        template <typename T, size_t N>
        inline bool operator>(array<T, N>& a1, array<T, N>& a2) {
            return _compare_array(a1, a2) > 0;
        }
        template <typename T, size_t N>
        inline bool operator>=(array<T, N>& a1, array<T, N>& a2) {
            return _compare_array(a1, a2) >= 0;
        }

        template <size_t I, typename T, size_t N>
        inline T& get(array<T, N>& a) {
            return a.data()[I];
        }
        template <size_t I, typename T, size_t N>
        inline const T& get(const array<T, N>& a) {
            return a.data()[I];
        }
        #ifdef UNBOOST_RV_REF
            #ifdef UNBOOST_OLD_COMPILER
                template <size_t I, typename T, size_t N>
                inline UNBOOST_RV_REF(T)
                get(rv<array<T, N> > a) {
                    return move(UNBOOST_RV(a).data()[I]);
                }
            #else
                template <size_t I, typename T, size_t N>
                inline UNBOOST_RV_REF(T)
                get(UNBOOST_RV_REF(array<T, N>) a) {
                    return move(UNBOOST_RV(a).data()[I]);
                }
            #endif
        #endif
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_ARRAY_HPP_
