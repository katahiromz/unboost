// ilist.hpp --- Unboost initializer list
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_TYPE_ILIST_HPP_
#define UNBOOST_TYPE_ILIST_HPP_

#include "unboost.hpp"
#include "rv_ref.hpp"   // for rvalue reference

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_ILIST) + defined(UNBOOST_USE_UNBOOST_ILIST)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_ILIST
    #else
        #define UNBOOST_USE_UNBOOST_ILIST
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_ILIST
    #include <initializer_list>     // for std::initializer
    namespace unboost {
        using std::initializer_list;
        struct initializer {
            template <class T, typename VALUE>
            initializer(T& obj, const std::initializer_list<VALUE>& ilist) {
                obj = ilist;
            }
        };
    } // namespace unboost
    #define UNBOOST_ILIST_DEFINE(type,name)     unboost::initializer_list<type> name
    #define UNBOOST_ILIST_INIT(obj,name)        unboost::initializer initializer_##__LINE__((obj), (name))
    #define UNBOOST_ILIST_ASSIGN(obj,name)      ((obj) = (name))
#elif defined(UNBOOST_USE_UNBOOST_ILIST)
    #include <vector>   // for std::vector
    #include <list>     // for std::list
    namespace unboost {
        template <typename T>
        struct initializer_list {
            typedef T           value_type;
            typedef T&          reference;
            typedef const T&    const_reference;
            typedef size_t      size_type;
            typedef const T*    iterator;
            typedef const T*    const_iterator;

            initializer_list() {
                m_ptr = NULL;
                m_count = 0;
            }

            template <typename VALUE, size_t N>
            initializer_list(const VALUE (&array)[N]) {
                m_ptr = array;
                m_count = N;
            }

            template <typename VALUE>
            initializer_list(const VALUE *ptr, size_type N) {
                m_ptr = ptr;
                m_count = N;
            }

            size_type size() const { return m_count; }
            const T *begin() const {
                return &m_ptr[0];
            }
            const T *end() const {
                return &m_ptr[m_count];
            }

            T& operator[](size_type i) {
                return m_ptr[i];
            }
            const T& operator[](size_type i) const {
                return m_ptr[i];
            }

        public:
            const T *       m_ptr;
            size_t          m_count;
        };

        template <typename E>
        const E* begin(const initializer_list<E>& il) {
            return il.begin();
        }
        template <typename E>
        const E* end(const initializer_list<E>& il) {
            return il.end();
        }

        template <typename T, typename VALUE>
        inline std::vector<T>&
        _ilist_assign(std::vector<T>& obj, const initializer_list<VALUE>& ilist) {
            obj.clear();
            const size_t count = ilist.size();
            obj.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                obj.push_back(ilist[i]);
            }
            return obj;
        }

        template <typename T, typename VALUE, size_t N>
        inline std::vector<T>&
        _ilist_assign(std::vector<T>& obj, const VALUE (&array)[N]) {
            initializer_list<VALUE> ilist(array);
            return _ilist_assign(obj, ilist);
        }

        template <typename T, typename VALUE>
        inline std::list<T>&
        _ilist_assign(std::list<T>& obj, const initializer_list<VALUE>& ilist) {
            obj.clear();
            const size_t count = ilist.size();
            for (size_t i = 0; i < count; ++i) {
                obj.insert(ilist[i]);
            }
            return obj;
        }

        template <typename T, typename VALUE, size_t N>
        inline std::list<T>&
        _ilist_assign(std::list<T>& obj, const VALUE (&array)[N]) {
            initializer_list<VALUE> ilist(array);
            return _ilist_assign(obj, ilist);
        }

        struct initializer {
            template <typename OBJ_T, typename VALUE, size_t N>
            initializer(OBJ_T& obj, const VALUE (&array)[N]) {
                initializer_list<VALUE> ilist(array, N);
                _ilist_assign(obj, ilist);
            }
        };
    } // namespace unboost
    #define UNBOOST_ILIST_DEFINE(type,name)     type name[]
    #define UNBOOST_ILIST_INIT(obj,name)        unboost::initializer initializer_##__LINE__((obj), (name))
    #define UNBOOST_ILIST_ASSIGN(obj,name)      unboost::_ilist_assign((obj), (name))
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_TYPE_ILIST_HPP_
