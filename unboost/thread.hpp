// thread.hpp --- Unboost thread
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_THREAD_HPP
#define UNBOOST_THREAD_HPP

#include "unboost.hpp"
#include "chrono.hpp"
#include "exception.hpp"

// If not choosed, choose one
#if (defined(UNBOOST_USE_CXX11_THREAD) + defined(UNBOOST_USE_BOOST_THREAD) + defined(UNBOOST_USE_WIN32_THREAD) + defined(UNBOOST_USE_POSIX_THREAD) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_THREAD
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_THREAD
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_THREAD
        #elif defined(_WIN32)
            #if (_MSC_VER >= 1800)
                // Visual C++ 2013 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_THREAD
                #else
                    #define UNBOOST_USE_WIN32_THREAD
                #endif
            #else
                #define UNBOOST_USE_WIN32_THREAD
            #endif
        #else
            #define UNBOOST_USE_POSIX_THREAD
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_THREAD
    #include <thread>
    #include <mutex>
    namespace unboost {
        using std::thread;
        namespace this_thread {
            using std::this_thread::get_id;
            using std::this_thread::sleep_for;
            using std::this_thread::sleep_until;
            using std::this_thread::yield;
        }
        using std::mutex;
        using std::timed_mutex;
        using std::recursive_mutex;
        using std::recursive_timed_mutex;
        using std::unique_lock;
        using std::lock_guard;
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_THREAD)
    #include <boost/thread.hpp>
    namespace unboost {
        using boost::thread;
        namespace this_thread {
            using boost::this_thread::get_id;
            using boost::this_thread::sleep_for;
            using boost::this_thread::sleep_until;
            using boost::this_thread::yield;
        }
        using boost::mutex;
        using boost::timed_mutex;
        using boost::recursive_mutex;
        using boost::recursive_timed_mutex;
        using boost::unique_lock;
        using boost::lock_guard;
    } // namespace unboost
#elif defined(UNBOOST_USE_WIN32_THREAD)
    #include <stdexcept>
    #include <process.h>
    #ifndef _INC_WINDOWS
        #include <windows.h>
    #endif
    #define UNBOOST_DEFINE_LOCK_EXTRA

    namespace unboost {
        class thread {
        public:
            typedef DWORD id;
            typedef HANDLE native_handle_type;

        protected:
            template <typename FUNC>
            struct THREAD_DATA_ARG0 {
                FUNC        m_func;
                THREAD_DATA_ARG0(FUNC func) : m_func(func) { }
            };
            template <typename FUNC>
            static unsigned __stdcall thread_function_arg0(void *ptr) {
                THREAD_DATA_ARG0<FUNC> *data;
                data = (THREAD_DATA_ARG0<FUNC> *)ptr;
                data->m_func();
                delete data;
                return 0;
            }
            template <typename FUNC, typename ARG1>
            struct THREAD_DATA_ARG1 {
                FUNC        m_func;
                ARG1        m_arg1;
                THREAD_DATA_ARG1(FUNC func, ARG1 arg1) :
                    m_func(func), m_arg1(arg1) { }
            };
            template <typename FUNC, typename ARG1>
            static unsigned __stdcall thread_function_arg1(void *ptr) {
                THREAD_DATA_ARG1<FUNC, ARG1> *data;
                data = (THREAD_DATA_ARG1<FUNC, ARG1> *)ptr;
                data->m_func(data->m_arg1);
                delete data;
                return 0;
            }
            template <typename FUNC, typename ARG1, typename ARG2>
            struct THREAD_DATA_ARG2 {
                FUNC        m_func;
                ARG1        m_arg1;
                ARG2        m_arg2;
                THREAD_DATA_ARG2(FUNC func, ARG1 arg1, ARG2 arg2) :
                    m_func(func), m_arg1(arg1), m_arg2(arg2) { }
            };
            template <typename FUNC, typename ARG1, typename ARG2>
            static unsigned __stdcall thread_function_arg2(void *ptr) {
                THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *data;
                data = (THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *)ptr;
                data->m_func(data->m_arg1, data->m_arg2);
                delete data;
                return 0;
            }
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3>
            struct THREAD_DATA_ARG3 {
                FUNC        m_func;
                ARG1        m_arg1;
                ARG2        m_arg2;
                ARG3        m_arg3;
                THREAD_DATA_ARG3(FUNC func, ARG1 arg1, ARG2 arg2, ARG2 arg3) :
                    m_func(func), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }
            };
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3>
            static unsigned __stdcall thread_function_arg3(void *ptr) {
                THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3> *data;
                data = (THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3> *)ptr;
                data->m_func(data->m_arg1, data->m_arg2, data->m_arg3);
                delete data;
                return 0;
            }

        public:
            thread() : m_hThread(NULL), m_id() { }
            ~thread() {
                if (m_hThread) {
                    ::CloseHandle(m_hThread);
                    std::terminate();
                }
            }

            template <typename FUNC>
            thread(FUNC func) : m_hThread(NULL), m_id() {
                THREAD_DATA_ARG0<FUNC> *data;
                data = new THREAD_DATA_ARG0<FUNC>(func);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg0<FUNC>,
                                   data, 0, (unsigned *)&m_id));
                if (m_hThread == NULL) {
                    delete data;
                    throw unboost::system_error(::GetLastError());
                }
            }
            template <typename FUNC, typename ARG1>
            thread(FUNC func, ARG1 arg1) : m_hThread(NULL), m_id() {
                THREAD_DATA_ARG1<FUNC, ARG1> *data;
                data = new THREAD_DATA_ARG1<FUNC, ARG1>(func, arg1);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg1<FUNC, ARG1>,
                                   data, 0, (unsigned *)&m_id));
                if (m_hThread == NULL) {
                    delete data;
                    throw unboost::system_error(::GetLastError());
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2>
            thread(FUNC func, ARG1 arg1, ARG2 arg2) : m_hThread(NULL), m_id() {
                THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *data;
                data = new THREAD_DATA_ARG2<FUNC, ARG1, ARG2>(func, arg1, arg2);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg2<FUNC, ARG1, ARG2>,
                                   data, 0, (unsigned *)&m_id));
                if (m_hThread == NULL) {
                    delete data;
                    throw unboost::system_error(::GetLastError());
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3>
            thread(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3) :
                m_hThread(NULL), m_id()
            {
                THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3> *data;
                data = new THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3>(func, arg1, arg2, arg3);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg3<FUNC, ARG1, ARG2, ARG3>,
                                   data, 0, (unsigned *)&m_id));
                if (m_hThread == NULL) {
                    delete data;
                    throw unboost::system_error(::GetLastError());
                }
            }

            id get_id() const { return m_id; }
            native_handle_type native_handle() { return m_hThread; }
            bool joinable() { return m_id != id(); }

            void join() {
                if (joinable()) {
                    ::WaitForSingleObject(m_hThread, INFINITE);
                    ::CloseHandle(m_hThread);
                    m_hThread = NULL;
                    m_id = id();
                }
            }
            void detach() {
                if (m_hThread) {
                    ::CloseHandle(m_hThread);
                    m_hThread = NULL;
                    m_id = id();
                }
            }

            void swap(thread& other) {
                unboost::swap(m_hThread, other.m_hThread);
                unboost::swap(m_id, other.m_id);
            }
            friend void swap(thread& x, thread& y) {
                x.swap(y);
            }

            static unsigned hardware_concurrency() {
                SYSTEM_INFO info;
                ::GetSystemInfo(&info);
                return info.dwNumberOfProcessors;
            }
        protected:
            HANDLE  m_hThread;
            id      m_id;
        private:
            thread(const thread&);
            thread& operator=(const thread&);
        }; // class thread

        namespace this_thread {
            inline unboost::thread::id get_id() {
                unboost::thread::id i(::GetCurrentThreadId());
                return i;
            }
            template <class Rep, class Period>
            inline void sleep_for(const unboost::chrono::duration<Rep,Period>& sleep_duration) {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(sleep_duration);
                ::Sleep(DWORD(ms.count()));
            }
            //template <class Clock, class Duration>
            //inline void sleep_until(const chrono::time_point<Clock, Duration>&
            //                        sleep_time)
            //{
            //    ;
            //}
            inline void yield() {
                ::Sleep(0);
            }
        } // namespace this_thread

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

    } // namespace unboost
#elif defined(UNBOOST_USE_POSIX_THREAD)
    #include <stdexcept>
    #include <pthread.h>
    #include <cerrno>
    #ifdef _WIN32
        #ifndef _INC_WINDOWS
            #include <windows.h>    // for Sleep
        #endif
    #else
        #include <time.h>     // for nanosleep
    #endif
    #define UNBOOST_DEFINE_LOCK_EXTRA

    namespace unboost {
        class thread {
        public:
            typedef pthread_t id;
            typedef pthread_t native_handle_type;

        protected:
            template <typename FUNC>
            struct THREAD_DATA_ARG0 {
                FUNC        m_func;
                THREAD_DATA_ARG0(FUNC func) : m_func(func) { }
            };
            template <typename FUNC>
            static void *thread_function_arg0(void *ptr) {
                THREAD_DATA_ARG0<FUNC> *data;
                data = (THREAD_DATA_ARG0<FUNC> *)ptr;
                data->m_func();
                delete data;
                return NULL;
            }

            template <typename FUNC, typename ARG1>
            struct THREAD_DATA_ARG1 {
                FUNC        m_func;
                ARG1        m_arg1;
                THREAD_DATA_ARG1(FUNC func, ARG1 arg1) :
                    m_func(func), m_arg1(arg1) { }
            };
            template <typename FUNC, typename ARG1>
            static void *thread_function_arg1(void *ptr) {
                THREAD_DATA_ARG1<FUNC, ARG1> *data;
                data = (THREAD_DATA_ARG1<FUNC, ARG1> *)ptr;
                data->m_func(data->m_arg1);
                delete data;
                return NULL;
            }

            template <typename FUNC, typename ARG1, typename ARG2>
            struct THREAD_DATA_ARG2 {
                FUNC        m_func;
                ARG1        m_arg1;
                ARG2        m_arg2;
                THREAD_DATA_ARG2(FUNC func, ARG1 arg1, ARG2 arg2) :
                    m_func(func), m_arg1(arg1), m_arg2(arg2) { }
            };
            template <typename FUNC, typename ARG1, typename ARG2>
            static void *thread_function_arg2(void *ptr) {
                THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *data;
                data = (THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *)ptr;
                data->m_func(data->m_arg1, data->m_arg2);
                delete data;
                return NULL;
            }

            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3>
            struct THREAD_DATA_ARG3 {
                FUNC        m_func;
                ARG1        m_arg1;
                ARG2        m_arg2;
                ARG3        m_arg3;
                THREAD_DATA_ARG3(FUNC func, ARG1 arg1, ARG2 arg2, ARG2 arg3) :
                    m_func(func), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }
            };
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3>
            static void *thread_function_arg3(void *ptr) {
                THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3> *data;
                data = (THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3> *)ptr;
                data->m_func(data->m_arg1, data->m_arg2, data->m_arg3);
                delete data;
                return NULL;
            }

        public:
            thread() : m_id(_PTHREAD_NULL_THREAD) { }
            ~thread() {
                if (m_id) {
                    detach();
                    std::terminate();
                }
            }

            template <typename FUNC>
            thread(FUNC func) : m_id() {
                THREAD_DATA_ARG0<FUNC> *data;
                data = new THREAD_DATA_ARG0<FUNC>(func);
                pthread_create(&m_id, NULL,
                               thread_function_arg0<FUNC>, data);
                if (m_id == 0) {
                    delete data;
                    throw unboost::system_error(-1);
                }
            }
            template <typename FUNC, typename ARG1>
            thread(FUNC func, ARG1 arg1) : m_id() {
                THREAD_DATA_ARG1<FUNC, ARG1> *data;
                data = new THREAD_DATA_ARG1<FUNC, ARG1>(func, arg1);
                pthread_create(&m_id, NULL,
                               thread_function_arg1<FUNC, ARG1>,
                               data);
                if (m_id == 0) {
                    delete data;
                    throw unboost::system_error(-1);
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2>
            thread(FUNC func, ARG1 arg1, ARG2 arg2) : m_id() {
                THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *data;
                data = new THREAD_DATA_ARG2<FUNC, ARG1, ARG2>(func, arg1, arg2);
                pthread_create(&m_id, NULL,
                               thread_function_arg2<FUNC, ARG1, ARG2>,
                               data);
                if (m_id == 0) {
                    delete data;
                    throw unboost::system_error(-1);
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3>
            thread(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3) : m_id()
            {
                THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3> *data;
                data = new THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3>(func, arg1, arg2, arg3);
                pthread_create(&m_id, NULL,
                               thread_function_arg3<FUNC, ARG1, ARG2, ARG3>,
                               data);
                if (m_id == 0) {
                    delete data;
                    throw unboost::system_error(-1);
                }
            }

            id get_id() const { return m_id; }
            native_handle_type native_handle() { return m_id; }
            bool joinable() { return m_id != id(); }

            void join() {
                if (joinable()) {
                    pthread_join(m_id, NULL);
                    m_id = id();
                }
            }

            void detach() {
                if (m_id) {
                    pthread_detach(m_id);
                    m_id = id();
                }
            }

            void swap(thread& other) {
                swap(m_id, other.m_id);
            }
            friend void swap(thread& x, thread& y) {
                x.swap(y);
            }

            static unsigned hardware_concurrency() {
                return pthread_num_processors_np();
            }
        protected:
            pthread_t   m_id;
        private:
            thread(const thread&);
            thread& operator=(const thread&);
        }; // class thread

        namespace this_thread {
            inline unboost::thread::id get_id() {
                return pthread_self();
            }
            template <class Rep, class Period>
            inline void sleep_for(const unboost::chrono::duration<Rep, Period>& sleep_duration) {
                using namespace unboost::chrono;
                unboost_auto_duration ms = duration_cast<milliseconds>(sleep_duration);
                #ifdef _WIN32
                    ::Sleep(ms.count());
                #else
                    time_spec spec;
                    spec.tv_sec = ms.count() / 1000;
                    spec.tv_nsec = (ms.count() % 1000) * 1000000;
                    nanosleep(&spec, NULL);
                #endif
            }
            inline void sleep_for(const unboost::chrono::auto_duration& sleep_duration) {
                using namespace unboost::chrono;
                unboost_auto_duration ms = duration_cast<milliseconds>(sleep_duration);
                #ifdef _WIN32
                    ::Sleep(ms.count());
                #else
                    time_spec spec;
                    spec.tv_sec = ms.count() / 1000;
                    spec.tv_nsec = (ms.count() % 1000) * 1000000;
                    nanosleep(&spec, NULL);
                #endif
            }
            //template <class Clock, class Duration>
            //inline void sleep_until(const chrono::time_point<Clock, Duration>&
            //                        sleep_time)
            //{
            //    ;
            //}
            inline void yield() {
                sched_yield();
            }
        } // namespace this_thread

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

#endif  // ndef UNBOOST_THREAD_HPP
