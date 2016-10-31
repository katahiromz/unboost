// ref.hpp --- Unboost ref/cref
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_CORE_REF_HPP_
#define UNBOOST_CORE_REF_HPP_

#include "unboost.hpp"

// NOTE: function types are not supported yet

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_REF) + defined(UNBOOST_USE_BOOST_REF) + defined(UNBOOST_USE_UNBOOST_REF)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_REF
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_REF
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_REF
        #else
            #define UNBOOST_USE_UNBOOST_REF
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_REF
    #include <functional>   // for std::ref, std::cref, ...
    #include <memory>       // for std::addressof
    namespace unboost {
        using std::addressof;
        using std::ref;
        using std::cref;
        using std::reference_wrapper;
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_REF)
    #include <boost/core/addressof.hpp> // for boost::addressof
    #include <boost/ref.hpp>            // for boost::ref, boost::cref, ...
    namespace unboost {
        using boost::addressof;
        using boost::ref;
        using boost::cref;
        using boost::reference_wrapper;
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_REF)
    namespace unboost {
        template <typename T>
        inline T* addressof(T& arg) {
            return reinterpret_cast<T*>(
                &const_cast<char&>(
                    reinterpret_cast<const volatile char&>(arg)));
        }

        template <typename T>
        class reference_wrapper {
        public:
            typedef T type;
            typedef reference_wrapper<T>        self_type;

            explicit reference_wrapper(T& t) : m_t(addressof(t)) { }
            reference_wrapper(const self_type& rw) : m_t(rw.m_t) { }

            T& get() const { return *m_t; }
            operator T&() const { return get(); }

            self_type& operator=(const self_type& rw) {
                m_t = rw.get();
                return *this;
            }

        protected:
            T *m_t;

#ifdef UNBOOST_RVALREF
        private:
            reference_wrapper(UNBOOST_RVALREF_TYPE(T))/* = delete*/;
            void ref(UNBOOST_RVALREF_TYPE(T))/* = delete*/;
            void cref(UNBOOST_RVALREF_TYPE(T))/* = delete*/;
#endif  // def UNBOOST_RVALREF
        }; // reference_wrapper<T>

        template <typename T>
        inline reference_wrapper<T> ref(T& t) {
            return reference_wrapper<T>(t);
        }

        template <typename T>
        inline reference_wrapper<const T> cref(const T& t) {
            return reference_wrapper<const T>(t);
        }
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_CORE_REF_HPP_
