// mutex.hpp --- Unboost mutex
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_MUTEX_HPP_
#define UNBOOST_MUTEX_HPP_

#include "unboost.hpp"
#include "chrono.hpp"
#include "thread.hpp"
#include "exception.hpp"

// If not choosed, choose one
#if (defined(UNBOOST_USE_CXX11_MUTEX) + defined(UNBOOST_USE_BOOST_MUTEX) + defined(UNBOOST_USE_WIN32_MUTEX) + defined(UNBOOST_USE_POSIX_MUTEX) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_MUTEX
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_MUTEX
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_MUTEX
        #elif defined(_WIN32)
            #define UNBOOST_USE_WIN32_MUTEX
        #else
            #define UNBOOST_USE_POSIX_MUTEX
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_MUTEX
    #include <mutex>
    namespace unboost {
        using std::mutex;
        using std::timed_mutex;
        using std::recursive_mutex;
        using std::recursive_timed_mutex;
        using std::unique_lock;
        using std::lock_guard;
    }
#elif defined(UNBOOST_USE_BOOST_MUTEX)
    #include <boost/thread.hpp>
    namespace unboost {
        using boost::mutex;
        using boost::timed_mutex;
        using boost::recursive_mutex;
        using boost::recursive_timed_mutex;
        using boost::unique_lock;
        using boost::lock_guard;
    }
#elif defined(UNBOOST_USE_WIN32_MUTEX)
    #define UNBOOST_DEFINE_LOCK_EXTRA
    #ifdef _WIN32
        #ifndef _INC_WINDOWS
            #include <windows.h>
        #endif
    #endif
    namespace unboost {
        class mutex {
        public:
            typedef HANDLE native_handle_type;
            mutex() : m_hMutex(::CreateMutexA(NULL, FALSE, NULL)) {
                if (m_hMutex == NULL)
                    throw system_error(::GetLastError());
            }
            virtual ~mutex() { ::CloseHandle(m_hMutex); }
            native_handle_type native_handle() { return m_hMutex; }
            void lock() {
                ::WaitForSingleObject(m_hMutex, INFINITE);
            }
            void unlock() {
                ::ReleaseMutex(m_hMutex);
            }
            bool try_lock() {
                return (::WaitForSingleObject(m_hMutex, 0) == WAIT_OBJECT_0);
            }
        protected:
            native_handle_type  m_hMutex;
        private:
            mutex(const mutex&);
            mutex& operator=(const mutex&);
        }; // class mutex
        class timed_mutex : public mutex {
        public:
            timed_mutex() { }
            virtual ~timed_mutex() { }
            template <class Rep, class Period>
            bool try_lock_for(const unboost::chrono::duration<Rep, Period>&
                              timeout_duration)
            {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(timeout_duration);
                return ::WaitForSingleObject(m_hMutex, ms.count()) == WAIT_OBJECT_0;
            }
            //template <class Clock, class Duration>
            //bool try_lock_until(
            //    const unboost::chrono::time_point<Clock, Duration>&
            //    timeout_time)
            //{
            //    // FIXME
            //}
            //bool try_lock_until(
            //    const unboost::chrono::auto_time_point& timeout_time)
            //{
            //    // FIXME
            //}
        private:
            timed_mutex(const timed_mutex&);
            timed_mutex& operator=(const timed_mutex&);
        }; // class timed_mutex
    }; // namespace unboost
#elif defined(UNBOOST_USE_POSIX_MUTEX)
    #define UNBOOST_DEFINE_LOCK_EXTRA
    #ifdef __cplusplus
        #include <cerrno>
    #else
        #include <errno.h>
    #endif
    #include <pthread.h>    /* for POSIX threads */
    namespace unboost {
        class mutex {
        public:
            typedef pthread_mutex_t native_handle_type;
            mutex()         { m_mutex = PTHREAD_MUTEX_INITIALIZER; }
            ~mutex()        { pthread_mutex_destroy(&m_mutex); }
            native_handle_type native_handle() { return m_mutex; }
            void lock()     { pthread_mutex_lock(&m_mutex); }
            void unlock()   { pthread_mutex_unlock(&m_mutex); }
            bool try_lock() {
                return pthread_mutex_trylock(&m_mutex) != EBUSY;
            }
        protected:
            native_handle_type m_mutex;
        private:
            mutex(const mutex&);
            mutex& operator=(const mutex&);
        }; // class mutex
        class timed_mutex : public mutex {
        public:
            timed_mutex() { }
            virtual ~timed_mutex() { }
            //template <class Rep, class Period>
            //bool try_lock_for(const unboost::chrono::duration<Rep, Period>&
            //                  timeout_duration)
            //{
            //    using namespace unboost::chrono;
            //    auto_duration ms = duration_cast<milliseconds>(timeout_duration);
            //    // FIXME
            //}
            //bool try_lock_for(const unboost::chrono::auto_duration&
            //                  timeout_duration)
            //{
            //    using namespace unboost::chrono;
            //    auto_duration ms = duration_cast<milliseconds>(timeout_duration);
            //    // FIXME
            //}
            //template <class Clock, class Duration>
            //bool try_lock_until(
            //    const unboost::chrono::time_point<Clock, Duration>&
            //    timeout_time)
            //{
            //    // FIXME
            //}
            //bool try_lock_until(
            //    const unboost::chrono::auto_time_point& timeout_time)
            //{
            //    // FIXME
            //}
        private:
            timed_mutex(const timed_mutex&);
            timed_mutex& operator=(const timed_mutex&);
        }; // class timed_mutex
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif
#ifdef UNBOOST_DEFINE_LOCK_EXTRA
    namespace unboost {
        struct defer_lock_t { };
        struct try_to_lock_t { };
        struct adopt_lock_t { };

        template <class Mutex>
        class unique_lock {
        public:
            typedef Mutex mutex_type;
            unique_lock() : m_pmutex(NULL), m_locked(false) { }
            explicit unique_lock(mutex_type& m) : m_pmutex(&m), m_locked(true)
            { m_pmutex->lock(); }

            unique_lock(mutex_type& m, defer_lock_t) :
                m_pmutex(&m), m_locked(false) { }
            unique_lock(mutex_type& m, try_to_lock_t) :
                m_pmutex(&m), m_locked(false)
            { m_locked = m_pmutex->try_lock(); }

            unique_lock(mutex_type& m, adopt_lock_t) :
                m_pmutex(&m), m_locked(true) { }
            ~unique_lock() {
                if (m_locked && m_pmutex)
                    m_pmutex->unlock();
            }

            bool owns_lock() const { return m_locked; }
            mutex_type *mutex() const { return m_pmutex; }
            operator bool() const { return owns_lock(); }

            void move_assignment(unique_lock& other) {
                if (m_pmutex && m_locked)
                    m_pmutex->lock();
                m_pmutex = other->m_pmutex;
                m_locked = other->m_locked;
                other->m_pmutex = NULL;
                other->m_locked = false;
            }

            void lock() {
                if (m_pmutex == NULL || m_locked)
                    throw system_error(-1);
                m_pmutex->lock();
                m_locked = true;
            }
            bool try_lock() {
                if (m_pmutex == NULL || m_locked)
                    throw system_error(-1);
                return mutex()->try_lock();
            }
            void unlock() {
                if (m_pmutex == NULL || !m_locked)
                    throw system_error(-1);
                mutex()->unlock();
                m_locked = false;
            }
            mutex_type *release() {
                mutex_type *m = m_pmutex;
                m_pmutex = NULL;
                m_locked = false;
                return m;
            }
            void swap(unique_lock<Mutex>& other) {
                swap(m_pmutex, other.m_pmutex);
                swap(m_locked, other.m_locked);
            }
            template <class Mutex2>
            friend void swap(unique_lock<Mutex2>& ul1,
                             unique_lock<Mutex2>& ul2)
            {
                ul1.swap(ul2);
            }
        protected:
            mutex_type *m_pmutex;
            bool m_locked;
        }; // class unique_lock

        // FIXME:
        //template <class Mutex>
        //class lock_guard {
        //public:
        //    typedef Mutex mutex_type;
        //    explicit lock_guard(mutex_type& m) {
        //    }
        //    lock_guard(mutex_type& m, adopt_lock_t) {
        //    }
        //    ~lock_guard() {
        //    }
        //}; // class lock_guard
    } // namespace unboost
#endif  // def UNBOOST_DEFINE_LOCK_EXTRA

#endif  // ndef UNBOOST_MUTEX_HPP_
