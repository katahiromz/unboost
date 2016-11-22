// thread.hpp --- Unboost thread
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_THREAD_HPP
#define UNBOOST_THREAD_HPP

#if (_MSC_VER > 1000)
    #pragma once
#endif

#include "unboost.h"
#include "chrono.hpp"           // for unboost::chrono
#include "system_error.hpp"     // for unboost::system_error
#include "rv_ref.hpp"           // for UNBOOST_RV_REF, ...

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
            #if defined(_MSC_VER) && (_MSC_VER >= 1700)
                // Visual C++ 2012 and later
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
        using std::defer_lock_t;
        using std::defer_lock;
        using std::try_to_lock_t;
        using std::try_to_lock;
        using std::adopt_lock_t;
        using std::adopt_lock;
        using std::call_once;
        using std::once_flag;
        using std::lock;
        using std::try_lock;
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
        using boost::defer_lock_t;
        using boost::defer_lock;
        using boost::try_to_lock_t;
        using boost::try_to_lock;
        using boost::adopt_lock_t;
        using boost::adopt_lock;
        using boost::call_once;
        using boost::once_flag;
        using boost::lock;
        using boost::try_lock;
    } // namespace unboost
#elif defined(UNBOOST_USE_WIN32_THREAD)
    #include <process.h>
    #ifndef _INC_WINDOWS
        #ifndef NOMINMAX
            #define NOMINMAX
        #endif
        #include <windows.h>
    #endif
    #include "exception.hpp"        // for unboost::system_error
    #include "swap.hpp"             // for unboost::swap
    #include "functional/hash.hpp"  // for unboost::hash
    #define UNBOOST_NEED_LOCK_EXTRA

    namespace unboost {
        struct once_flag {
            once_flag() : m_flag(0) { }
            LONG    m_flag;
        private:
            once_flag(const once_flag&)/* = delete*/;
            once_flag& operator=(const once_flag&)/* = delete*/;
        };

        inline LONG _interlocked_exchange(LONG *ptr, LONG value) {
            return ::InterlockedExchange(ptr, value);
        }

        template <typename Callable>
        inline void call_once(once_flag& flag, Callable fn) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn();
            }
        }
        template <typename Callable, typename ARG1>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2, typename ARG3>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2, ARG3 arg3) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2, arg3);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2, arg3, arg4);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2, arg3, arg4, arg5);
            }
        }

        class thread {
        public:
            struct id {
            public:
                id() UNBOOST_NOEXCEPT : m_value(0) { }
                id(DWORD value) UNBOOST_NOEXCEPT : m_value(value) { }
                DWORD m_value;
            };
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
                THREAD_DATA_ARG3(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3) :
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
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            struct THREAD_DATA_ARG4 {
                FUNC        m_func;
                ARG1        m_arg1;
                ARG2        m_arg2;
                ARG3        m_arg3;
                ARG4        m_arg4;
                THREAD_DATA_ARG4(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) :
                    m_func(func), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4) { }
            };
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            static unsigned __stdcall thread_function_arg4(void *ptr) {
                THREAD_DATA_ARG4<FUNC, ARG1, ARG2, ARG3, ARG4> *data;
                data = (THREAD_DATA_ARG4<FUNC, ARG1, ARG2, ARG3, ARG4> *)ptr;
                data->m_func(data->m_arg1, data->m_arg2, data->m_arg3, data->m_arg4);
                delete data;
                return 0;
            }
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            struct THREAD_DATA_ARG5 {
                FUNC        m_func;
                ARG1        m_arg1;
                ARG2        m_arg2;
                ARG3        m_arg3;
                ARG4        m_arg4;
                ARG4        m_arg5;
                THREAD_DATA_ARG5(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) :
                    m_func(func), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5) { }
            };
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            static unsigned __stdcall thread_function_arg5(void *ptr) {
                THREAD_DATA_ARG5<FUNC, ARG1, ARG2, ARG3, ARG4, ARG5> *data;
                data = (THREAD_DATA_ARG5<FUNC, ARG1, ARG2, ARG3, ARG4, ARG5> *)ptr;
                data->m_func(data->m_arg1, data->m_arg2, data->m_arg3, data->m_arg4, data->m_arg5);
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
                                   data, 0, (unsigned *)&m_id.m_value));
                if (m_hThread == NULL) {
                    delete data;
                    throw system_error(::GetLastError());
                }
            }
            template <typename FUNC, typename ARG1>
            thread(FUNC func, ARG1 arg1) : m_hThread(NULL), m_id() {
                THREAD_DATA_ARG1<FUNC, ARG1> *data;
                data = new THREAD_DATA_ARG1<FUNC, ARG1>(func, arg1);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg1<FUNC, ARG1>,
                                   data, 0, (unsigned *)&m_id.m_value));
                if (m_hThread == NULL) {
                    delete data;
                    throw system_error(::GetLastError());
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2>
            thread(FUNC func, ARG1 arg1, ARG2 arg2) : m_hThread(NULL), m_id() {
                THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *data;
                data = new THREAD_DATA_ARG2<FUNC, ARG1, ARG2>(func, arg1, arg2);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg2<FUNC, ARG1, ARG2>,
                                   data, 0, (unsigned *)&m_id.m_value));
                if (m_hThread == NULL) {
                    delete data;
                    throw system_error(::GetLastError());
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
                                   data, 0, (unsigned *)&m_id.m_value));
                if (m_hThread == NULL) {
                    delete data;
                    throw system_error(::GetLastError());
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            thread(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) :
                m_hThread(NULL), m_id()
            {
                THREAD_DATA_ARG4<FUNC, ARG1, ARG2, ARG3, ARG4> *data;
                data = new THREAD_DATA_ARG4<FUNC, ARG1, ARG2, ARG3, ARG4>(func, arg1, arg2, arg3, arg4);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg4<FUNC, ARG1, ARG2, ARG3, ARG4>,
                                   data, 0, (unsigned *)&m_id.m_value));
                if (m_hThread == NULL) {
                    delete data;
                    throw system_error(::GetLastError());
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            thread(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) :
                m_hThread(NULL), m_id()
            {
                THREAD_DATA_ARG5<FUNC, ARG1, ARG2, ARG3, ARG4, ARG5> *data;
                data = new THREAD_DATA_ARG5<FUNC, ARG1, ARG2, ARG3, ARG4, ARG5>(func, arg1, arg2, arg3, arg4, arg5);
                m_hThread = reinterpret_cast<HANDLE>(
                    _beginthreadex(NULL, 0, thread_function_arg4<FUNC, ARG1, ARG2, ARG3, ARG4, ARG5>,
                                   data, 0, (unsigned *)&m_id.m_value));
                if (m_hThread == NULL) {
                    delete data;
                    throw system_error(::GetLastError());
                }
            }

            id get_id() const { return m_id; }
            native_handle_type native_handle() { return m_hThread; }
            bool joinable() { return m_id.m_value != id().m_value; }

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
                } else {
                    throw system_error(ERROR_INVALID_PARAMETER);
                }
            }

            void swap(thread& other) {
                unboost::swap(m_hThread, other.m_hThread);
                unboost::swap(m_id, other.m_id);
            }

            static unsigned hardware_concurrency() {
                SYSTEM_INFO info;
                ::GetSystemInfo(&info);
                return info.dwNumberOfProcessors;
            }

#ifdef UNBOOST_RV_REF
            thread(UNBOOST_RV_REF(thread) other) {
                m_hThread = UNBOOST_RV(other).m_hThread;
                UNBOOST_RV(other).m_hThread = NULL;
                m_id = UNBOOST_RV(other).m_id;
                UNBOOST_RV(other).m_id = id();
            }
            thread& operator=(UNBOOST_RV_REF(thread) other) {
                m_hThread = UNBOOST_RV(other).m_hThread;
                UNBOOST_RV(other).m_hThread = NULL;
                m_id = UNBOOST_RV(other).m_id;
                UNBOOST_RV(other).m_id = id();
                return *this;
            }
#endif

        protected:
            HANDLE  m_hThread;
            id      m_id;
        private:
            thread(const thread&)/* = delete*/;
            thread& operator=(const thread&)/* = delete*/;
        }; // class thread

        inline void swap(thread& x, thread& y) {
            x.swap(y);
        }

        inline bool operator==(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value == y.m_value;
        }
        inline bool operator!=(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value != y.m_value;
        }
        inline bool operator<(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value < y.m_value;
        }
        inline bool operator>=(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value >= y.m_value;
        }
        inline bool operator>(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value > y.m_value;
        }
        inline bool operator<=(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value <= y.m_value;
        }

        template <class charT, class traits>
        inline std::basic_ostream<charT, traits>&
        operator<<(std::basic_ostream<charT, traits>& out, thread::id id) {
            std::ios_base::fmtflags f = out.flags();
            out << "0x" << std::hex << id.m_value;
            out.flags(f);
            return out;
        }

        template <>
        struct hash<thread::id> {
            typedef thread::id argument_type;
            typedef size_t result_type;
            hash() { }
            result_type operator()(thread::id key) const {
                return key.m_value;
            }
        };

        namespace this_thread {
            inline unboost::thread::id get_id() {
                unboost::thread::id i(::GetCurrentThreadId());
                return i;
            }
            template <class Rep, class Period>
            inline void sleep_for(const unboost::chrono::duration<Rep,Period>& sleep_duration) {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(sleep_duration);
                if (ms.count() >= 0) {
                    ::Sleep(DWORD(ms.count()));
                }
            }
            inline void sleep_for(const unboost::chrono::auto_duration& sleep_duration) {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(sleep_duration);
                if (ms.count() >= 0) {
                    ::Sleep(DWORD(ms.count()));
                }
            }
            template <class Clock, class Duration>
            inline void sleep_until(const chrono::time_point<Clock, Duration>&
                                    sleep_time)
            {
                using namespace unboost::chrono;
                auto_duration ad = sleep_time - chrono::time_point<Clock, Duration>::now();
                sleep_for(ad);
            }
            inline void sleep_until(const chrono::auto_time_point& sleep_time) {
                using namespace unboost::chrono;
                auto_duration ad = sleep_time - chrono::system_clock::now();
                sleep_for(ad);
            }
            inline void yield() {
                #if (_WIN32_WINNT >= 0x0400)
                    ::SwitchToThread();
                #else
                    ::Sleep(0);
                #endif
            }
        } // namespace this_thread

        class mutex {
        public:
            typedef HANDLE  native_handle_type;
            mutex() : m_hMutex(::CreateMutex(NULL, FALSE, NULL)) {
                if (m_hMutex == NULL)
                    throw system_error(::GetLastError());
            }
            virtual ~mutex() {
                ::CloseHandle(m_hMutex);
            }
            native_handle_type native_handle() { return m_hMutex; }
            void lock() {
                DWORD dwWait = ::WaitForSingleObject(m_hMutex, INFINITE);
                _check_result(dwWait);
            }
            void unlock() {
                ::ReleaseMutex(m_hMutex);
            }
            bool try_lock() {
                DWORD dwWait = ::WaitForSingleObject(m_hMutex, 0);
                return (dwWait == WAIT_OBJECT_0);
            }
        protected:
            native_handle_type  m_hMutex;
            void _check_result(DWORD dwWait) {
                if (dwWait == WAIT_FAILED) {
                    throw system_error(::GetLastError());
                }
            }
        private:
            mutex(const mutex&)/* = delete*/;
            mutex& operator=(const mutex&)/* = delete*/;
        }; // mutex

        class timed_mutex {
        public:
            typedef HANDLE  native_handle_type;
            timed_mutex() {
                m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
                if (m_hMutex == NULL)
                    throw system_error(::GetLastError());
            }
            virtual ~timed_mutex() {
                ::CloseHandle(m_hMutex);
            }
            native_handle_type native_handle() { return m_hMutex; }
            void lock() {
                DWORD dwWait = ::WaitForSingleObject(m_hMutex, INFINITE);
                _check_result(dwWait);
            }
            void unlock() {
                ::ReleaseMutex(m_hMutex);
            }
            bool try_lock() {
                DWORD dwWait = ::WaitForSingleObject(m_hMutex, 0);
                return (dwWait == WAIT_OBJECT_0);
            }
            template <class Rep, class Period>
            bool try_lock_for(
                const unboost::chrono::duration<Rep, Period>& timeout_duration)
            {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(timeout_duration);
                if (ms.count() > 0) {
                    DWORD dwWait = ::WaitForSingleObject(m_hMutex, ms.count());
                    return (dwWait == WAIT_OBJECT_0);
                } else {
                    return try_lock();
                }
            }
            bool try_lock_for(const unboost::chrono::auto_duration& timeout_duration) {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(timeout_duration);
                if (ms.count() > 0) {
                    DWORD dwWait = ::WaitForSingleObject(m_hMutex, ms.count());
                    return (dwWait == WAIT_OBJECT_0);
                } else {
                    return try_lock();
                }
            }
            template <class Clock, class Duration>
            bool try_lock_until(
                const unboost::chrono::time_point<Clock, Duration>& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
            bool try_lock_until(
                const unboost::chrono::auto_time_point& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
        protected:
            native_handle_type  m_hMutex;
            void _check_result(DWORD dwWait) {
                if (dwWait == WAIT_FAILED) {
                    throw system_error(::GetLastError());
                }
            }
        private:
            timed_mutex(const timed_mutex&)/* = delete*/;
            timed_mutex& operator=(const timed_mutex&)/* = delete*/;
        }; // timed_mutex

        class recursive_mutex {
        public:
            typedef HANDLE      native_handle_type;

            recursive_mutex()   {
                m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
                m_thread_id = DWORD(-1);
                m_lock_count = 0;
            }
            ~recursive_mutex()  {
                ::CloseHandle(m_hMutex);
            }
            native_handle_type native_handle() { return m_hMutex; }
            void lock() {
                if (m_thread_id != ::GetCurrentThreadId()) {
                    DWORD dwWait = ::WaitForSingleObject(m_hMutex, INFINITE);
                    _check_result(dwWait);
                }
                m_thread_id = ::GetCurrentThreadId();
                ::InterlockedIncrement(&m_lock_count);
            }
            void unlock() {
                assert(m_lock_count > 0);
                assert(m_thread_id == ::GetCurrentThreadId());
                if (::InterlockedDecrement(&m_lock_count) == 0) {
                    m_thread_id = DWORD(-1);
                    ::ReleaseMutex(m_hMutex);
                }
            }
            bool try_lock() {
                DWORD dwWait;
                if (m_thread_id != ::GetCurrentThreadId()) {
                    dwWait = ::WaitForSingleObject(m_hMutex, 0);
                } else {
                    dwWait = WAIT_OBJECT_0;
                }
                if (dwWait == WAIT_OBJECT_0) {
                    m_thread_id = ::GetCurrentThreadId();
                    ::InterlockedIncrement(&m_lock_count);
                    return true;
                }
                return false;
            }
        protected:
            native_handle_type  m_hMutex;
            DWORD               m_thread_id;
            LONG                m_lock_count;
            void _check_result(DWORD dwWait) {
                if (dwWait == WAIT_FAILED) {
                    throw system_error(::GetLastError());
                }
            }
        private:
            recursive_mutex(const recursive_mutex&)/* = delete*/;
            recursive_mutex& operator=(const recursive_mutex&)/* = delete*/;
        }; // recursive_mutex

        class recursive_timed_mutex {
        public:
            typedef HANDLE      native_handle_type;

            recursive_timed_mutex()   {
                m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
                m_thread_id = DWORD(-1);
                m_lock_count = 0;
            }
            ~recursive_timed_mutex()  {
                ::CloseHandle(m_hMutex);
            }
            native_handle_type native_handle() { return m_hMutex; }
            void lock() {
                if (m_thread_id != ::GetCurrentThreadId()) {
                    DWORD dwWait = ::WaitForSingleObject(m_hMutex, INFINITE);
                    _check_result(dwWait);
                }
                m_thread_id = ::GetCurrentThreadId();
                ::InterlockedIncrement(&m_lock_count);
            }
            void unlock() {
                assert(m_lock_count > 0);
                assert(m_thread_id == ::GetCurrentThreadId());
                if (::InterlockedDecrement(&m_lock_count) == 0) {
                    m_thread_id = DWORD(-1);
                    ::ReleaseMutex(m_hMutex);
                }
            }
            bool try_lock() {
                DWORD dwWait;
                if (m_thread_id != ::GetCurrentThreadId()) {
                    dwWait = ::WaitForSingleObject(m_hMutex, 0);
                } else {
                    dwWait = WAIT_OBJECT_0;
                }
                if (dwWait == WAIT_OBJECT_0) {
                    m_thread_id = ::GetCurrentThreadId();
                    ::InterlockedIncrement(&m_lock_count);
                    return true;
                }
                return false;
            }
            template <class Rep, class Period>
            bool try_lock_for(
                const unboost::chrono::duration<Rep, Period>& timeout_duration)
            {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(timeout_duration);
                DWORD dwWait = WAIT_TIMEOUT;
                if (ms.count() > 0) {
                    if (m_thread_id != ::GetCurrentThreadId()) {
                        dwWait = ::WaitForSingleObject(m_hMutex, ms.count());
                    }
                } else {
                    if (m_thread_id != ::GetCurrentThreadId()) {
                        dwWait = ::WaitForSingleObject(m_hMutex, 0);
                    } else {
                        dwWait = WAIT_OBJECT_0;
                    }
                }
                if (dwWait == WAIT_OBJECT_0) {
                    m_thread_id = ::GetCurrentThreadId();
                    ::InterlockedIncrement(&m_lock_count);
                    return true;
                }
                return false;
            }
            bool try_lock_for(const unboost::chrono::auto_duration& timeout_duration) {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(timeout_duration);
                DWORD dwWait = WAIT_TIMEOUT;
                if (ms.count() > 0) {
                    if (m_thread_id != ::GetCurrentThreadId()) {
                        dwWait = ::WaitForSingleObject(m_hMutex, ms.count());
                    }
                } else {
                    if (m_thread_id != ::GetCurrentThreadId()) {
                        dwWait = ::WaitForSingleObject(m_hMutex, 0);
                    } else {
                        dwWait = WAIT_OBJECT_0;
                    }
                }
                if (dwWait == WAIT_OBJECT_0) {
                    m_thread_id = ::GetCurrentThreadId();
                    ::InterlockedIncrement(&m_lock_count);
                    return true;
                }
                return false;
            }
            template <class Clock, class Duration>
            bool try_lock_until(
                const unboost::chrono::time_point<Clock, Duration>& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
            bool try_lock_until(
                const unboost::chrono::auto_time_point& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
        protected:
            native_handle_type  m_hMutex;
            DWORD               m_thread_id;
            LONG                m_lock_count;
            void _check_result(DWORD dwWait) {
                if (dwWait == WAIT_FAILED) {
                    throw system_error(::GetLastError());
                }
            }
        private:
            recursive_timed_mutex(const recursive_timed_mutex&)/* = delete*/;
            recursive_timed_mutex& operator=(const recursive_timed_mutex&)/* = delete*/;
        }; // recursive_timed_mutex
    } // namespace unboost
#elif defined(UNBOOST_USE_POSIX_THREAD)
    #include <pthread.h>
    #include <cerrno>
    #ifdef _WIN32
        #ifndef _INC_WINDOWS
            #ifndef NOMINMAX
                #define NOMINMAX
            #endif
            #include <windows.h>    // for Sleep
        #endif
    #else
        #include <time.h>           // for nanosleep
    #endif
    #include "exception.hpp"        // for unboost::system_error
    #include "swap.hpp"             // for unboost::swap
    #include "functional/hash.hpp"  // for unboost::hash
    #define UNBOOST_NEED_LOCK_EXTRA

    namespace unboost {
        #ifdef _WIN32
            struct once_flag {
                once_flag() : m_flag(0) { }
                LONG    m_flag;
            private:
                once_flag(const once_flag&)/* = delete*/;
                once_flag& operator=(const once_flag&)/* = delete*/;
            };
            inline LONG _interlocked_exchange(LONG *ptr, LONG value) {
                return ::InterlockedExchange(ptr, value);
            }
        #else
            struct once_flag {
                once_flag() : m_flag(0) { }
                int     m_flag;
            private:
                once_flag(const once_flag&)/* = delete*/;
                once_flag& operator=(const once_flag&)/* = delete*/;
            };
            inline int _interlocked_exchange(int *ptr, int value) {
                return __sync_lock_test_and_set(ptr, value);
            }
        #endif

        template <typename Callable>
        inline void call_once(once_flag& flag, Callable fn) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn();
            }
        }
        template <typename Callable, typename ARG1>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2, typename ARG3>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2, ARG3 arg3) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2, arg3);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2, arg3, arg4);
            }
        }
        template <typename Callable, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
        inline void call_once(once_flag& flag, Callable fn, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) {
            if (_interlocked_exchange(&flag.m_flag, 1) == 0) {
                fn(arg1, arg2, arg3, arg4, arg5);
            }
        }

        class thread {
        public:
            struct id {
            public:
                id() UNBOOST_NOEXCEPT : m_value(0) { }
                id(pthread_t value) UNBOOST_NOEXCEPT : m_value(value) { }
                pthread_t m_value;
            };
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
                if (m_id.m_value) {
                    detach();
                    std::terminate();
                }
            }

            template <typename FUNC>
            thread(FUNC func) : m_id() {
                THREAD_DATA_ARG0<FUNC> *data;
                data = new THREAD_DATA_ARG0<FUNC>(func);
                pthread_create(&m_id.m_value, NULL,
                               thread_function_arg0<FUNC>, data);
                if (m_id.m_value == 0) {
                    delete data;
                    throw system_error(EAGAIN);
                }
            }
            template <typename FUNC, typename ARG1>
            thread(FUNC func, ARG1 arg1) : m_id() {
                THREAD_DATA_ARG1<FUNC, ARG1> *data;
                data = new THREAD_DATA_ARG1<FUNC, ARG1>(func, arg1);
                pthread_create(&m_id.m_value, NULL,
                               thread_function_arg1<FUNC, ARG1>,
                               data);
                if (m_id.m_value == 0) {
                    delete data;
                    throw system_error(EAGAIN);
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2>
            thread(FUNC func, ARG1 arg1, ARG2 arg2) : m_id() {
                THREAD_DATA_ARG2<FUNC, ARG1, ARG2> *data;
                data = new THREAD_DATA_ARG2<FUNC, ARG1, ARG2>(func, arg1, arg2);
                pthread_create(&m_id.m_value, NULL,
                               thread_function_arg2<FUNC, ARG1, ARG2>,
                               data);
                if (m_id.m_value == 0) {
                    delete data;
                    throw system_error(EAGAIN);
                }
            }
            template <typename FUNC, typename ARG1, typename ARG2, typename ARG3>
            thread(FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3) : m_id()
            {
                THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3> *data;
                data = new THREAD_DATA_ARG3<FUNC, ARG1, ARG2, ARG3>(func, arg1, arg2, arg3);
                pthread_create(&m_id.m_value, NULL,
                               thread_function_arg3<FUNC, ARG1, ARG2, ARG3>,
                               data);
                if (m_id.m_value == 0) {
                    delete data;
                    throw system_error(EAGAIN);
                }
            }

            id get_id() const { return id(m_id); }
            native_handle_type native_handle() { return m_id.m_value; }
            bool joinable() { return m_id.m_value != id().m_value; }

            void join() {
                if (joinable()) {
                    pthread_join(m_id.m_value, NULL);
                    m_id = id();
                }
            }

            void detach() {
                if (m_id.m_value) {
                    pthread_detach(m_id.m_value);
                    m_id = id();
                } else {
                    throw system_error(EINVAL);
                }
            }

            void swap(thread& other) {
                unboost::swap(m_id, other.m_id);
            }

            static unsigned hardware_concurrency() {
                return pthread_num_processors_np();
            }

#ifdef UNBOOST_RV_REF
            thread(UNBOOST_RV_REF(thread) other) {
                m_id = UNBOOST_RV(other).m_id;
                UNBOOST_RV(other).m_id = id();
            }
            thread& operator=(UNBOOST_RV_REF(thread) other) {
                m_id = UNBOOST_RV(other).m_id;
                UNBOOST_RV(other).m_id = id();
                return *this;
            }
#endif

        protected:
            id      m_id;
        private:
            thread(const thread&)/* = delete*/;
            thread& operator=(const thread&)/* = delete*/;
        }; // class thread

        inline void swap(thread& x, thread& y) {
            x.swap(y);
        }

        inline bool operator==(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value == y.m_value;
        }
        inline bool operator!=(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value != y.m_value;
        }
        inline bool operator<(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value < y.m_value;
        }
        inline bool operator>=(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value >= y.m_value;
        }
        inline bool operator>(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value > y.m_value;
        }
        inline bool operator<=(thread::id x, thread::id y) UNBOOST_NOEXCEPT {
            return x.m_value <= y.m_value;
        }

        template <class charT, class traits>
        inline std::basic_ostream<charT, traits>&
        operator<<(std::basic_ostream<charT, traits>& out, thread::id id) {
            std::ios_base::fmtflags f = out.flags();
            out << "0x" << std::hex << id.m_value;
            out.flags(f);
            return out;
        }

        template <>
        struct hash<thread::id> {
            typedef thread::id argument_type;
            typedef size_t result_type;
            hash() { }
            result_type operator()(thread::id key) const {
                return key.m_value;
            }
        };

        namespace this_thread {
            inline unboost::thread::id get_id() {
                return unboost::thread::id(pthread_self());
            }
            template <class Rep, class Period>
            inline void sleep_for(const unboost::chrono::duration<Rep, Period>& sleep_duration) {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(sleep_duration);
                if (ms.count() > 0) {
                    #ifdef _WIN32
                        ::Sleep(DWORD(ms.count()));
                    #else
                        time_spec spec;
                        spec.tv_sec = ms.count() / 1000;
                        spec.tv_nsec = (ms.count() % 1000) * 1000000;
                        nanosleep(&spec, NULL);
                    #endif
                }
            }
            inline void sleep_for(const unboost::chrono::auto_duration& sleep_duration) {
                using namespace unboost::chrono;
                milliseconds ms = duration_cast<milliseconds>(sleep_duration);
                if (ms.count() > 0) {
                    #ifdef _WIN32
                        ::Sleep(DWORD(ms.count()));
                    #else
                        time_spec spec;
                        spec.tv_sec = ms.count() / 1000;
                        spec.tv_nsec = (ms.count() % 1000) * 1000000;
                        nanosleep(&spec, NULL);
                    #endif
                }
            }
            template <class Clock, class Duration>
            inline void sleep_until(const chrono::time_point<Clock, Duration>&
                                    sleep_time)
            {
                using namespace unboost::chrono;
                auto_duration ad = sleep_time - chrono::time_point<Clock, Duration>::now();
                sleep_for(ad);
            }
            inline void sleep_until(const chrono::auto_time_point& sleep_time) {
                using namespace unboost::chrono;
                auto_duration ad = sleep_time - chrono::system_clock::now();
                sleep_for(ad);
            }
            inline void yield() {
                sched_yield();
            }
        } // namespace this_thread

        class mutex {
        public:
            typedef pthread_mutex_t     native_handle_type;

            mutex()         { m_mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER; }
            ~mutex()        { pthread_mutex_destroy(&m_mutex); }
            native_handle_type native_handle() { return m_mutex; }
            void lock()     {
                int result = pthread_mutex_lock(&m_mutex);
                _check_result(result);
            }
            void unlock()   { pthread_mutex_unlock(&m_mutex); }
            bool try_lock() {
                int result = pthread_mutex_trylock(&m_mutex);
                return result != EBUSY;
            }
        protected:
            native_handle_type m_mutex;
            void _check_result(int err) {
                if (err == EDEADLK) {
                    throw system_error(EDEADLK);
                }
            }
        private:
            mutex(const mutex&)/* = delete*/;
            mutex& operator=(const mutex&)/* = delete*/;
        }; // mutex

        class timed_mutex : public mutex {
        public:
            typedef pthread_mutex_t     native_handle_type;

            timed_mutex()   { m_mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER; }
            ~timed_mutex()  { pthread_mutex_destroy(&m_mutex); }
            native_handle_type native_handle() { return m_mutex; }
            void lock()     {
                int result = pthread_mutex_lock(&m_mutex);
                _check_result(result);
            }
            void unlock()   { pthread_mutex_unlock(&m_mutex); }
            bool try_lock() {
                int result = pthread_mutex_trylock(&m_mutex);
                return result != EBUSY;
            }
            template <class Rep, class Period>
            bool try_lock_for(
                const unboost::chrono::duration<Rep, Period>& timeout_duration)
            {
                using namespace unboost::chrono;
                auto_duration ns = duration_cast<nanoseconds>(timeout_duration);
                struct timespec ts;
                ts.tv_sec = _uint64_t(ns.count()) / 1000000000;
                ts.tv_nsec = _uint64_t(ns.count()) % 1000000000;
                return !pthread_mutex_timedlock(&m_mutex, &ts);
            }
            bool try_lock_for(const unboost::chrono::auto_duration& timeout_duration) {
                using namespace unboost::chrono;
                auto_duration ns = duration_cast<nanoseconds>(timeout_duration);
                struct timespec ts;
                ts.tv_sec = _uint64_t(ns.count()) / 1000000000;
                ts.tv_nsec = _uint64_t(ns.count()) % 1000000000;
                return !pthread_mutex_timedlock(&m_mutex, &ts);
            }
            template <class Clock, class Duration>
            bool try_lock_until(
                const unboost::chrono::time_point<Clock, Duration>& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
            bool try_lock_until(
                const unboost::chrono::auto_time_point& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
        protected:
            native_handle_type m_mutex;
            void _check_result(int err) {
                if (err == EDEADLK) {
                    throw system_error(EDEADLK);
                }
            }
        private:
            timed_mutex(const timed_mutex&)/* = delete*/;
            timed_mutex& operator=(const timed_mutex&)/* = delete*/;
        }; // timed_mutex

        class recursive_mutex {
        public:
            typedef pthread_mutex_t     native_handle_type;
            recursive_mutex()   {
                m_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
            }
            ~recursive_mutex()  { pthread_mutex_destroy(&m_mutex); }
            native_handle_type native_handle() { return m_mutex; }
            void lock() {
                int result = pthread_mutex_lock(&m_mutex);
                _check_result(result);
            }
            void unlock()   { pthread_mutex_unlock(&m_mutex); }
            bool try_lock() {
                int result = pthread_mutex_trylock(&m_mutex);
                return result != EBUSY;
            }
        protected:
            native_handle_type m_mutex;
            void _check_result(int err) {
                if (err == EDEADLK) {
                    throw system_error(EDEADLK);
                }
            }
        private:
            recursive_mutex(const recursive_mutex&)/* = delete*/;
            recursive_mutex& operator=(const recursive_mutex&)/* = delete*/;
        }; // recursive_mutex

        class recursive_timed_mutex {
        public:
            typedef pthread_mutex_t     native_handle_type;

            recursive_timed_mutex()   {
                m_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
            }
            ~recursive_timed_mutex()  {
                pthread_mutex_destroy(&m_mutex);
            }
            native_handle_type native_handle() { return m_mutex; }
            void lock() {
                int result = pthread_mutex_lock(&m_mutex);
                _check_result(result);
            }
            void unlock()   { pthread_mutex_unlock(&m_mutex); }
            bool try_lock() {
                int result = pthread_mutex_trylock(&m_mutex);
                return result != EBUSY;
            }
            template <class Rep, class Period>
            bool try_lock_for(
                const unboost::chrono::duration<Rep, Period>& timeout_duration)
            {
                using namespace unboost::chrono;
                auto_duration ns = duration_cast<nanoseconds>(timeout_duration);
                struct timespec ts;
                ts.tv_sec = _uint64_t(ns.count()) / 1000000000;
                ts.tv_nsec = _uint64_t(ns.count()) % 1000000000;
                return !pthread_mutex_timedlock(&m_mutex, &ts);
            }
            bool try_lock_for(const unboost::chrono::auto_duration& timeout_duration) {
                using namespace unboost::chrono;
                auto_duration ns = duration_cast<nanoseconds>(timeout_duration);
                struct timespec ts;
                ts.tv_sec = _uint64_t(ns.count()) / 1000000000;
                ts.tv_nsec = _uint64_t(ns.count()) % 1000000000;
                return !pthread_mutex_timedlock(&m_mutex, &ts);
            }
            template <class Clock, class Duration>
            bool try_lock_until(
                const unboost::chrono::time_point<Clock, Duration>& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
            bool try_lock_until(
                const unboost::chrono::auto_time_point& timeout_time)
            {
                using namespace unboost::chrono;
                return try_lock_for(timeout_time - system_clock::now());
            }
        protected:
            native_handle_type m_mutex;
            void _check_result(int err) {
                if (err == EDEADLK) {
                    throw system_error(EDEADLK);
                }
            }
        private:
            recursive_timed_mutex(const recursive_timed_mutex&)/* = delete*/;
            recursive_timed_mutex& operator=(const recursive_timed_mutex&)/* = delete*/;
        }; // recursive_timed_mutex
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#ifdef UNBOOST_NEED_LOCK_EXTRA
    namespace unboost {
        struct defer_lock_t { };
        struct try_to_lock_t { };
        struct adopt_lock_t { };
        static const defer_lock_t   defer_lock;
        static const try_to_lock_t  try_to_lock;
        static const adopt_lock_t   adopt_lock;

        template <class Mutex>
        class unique_lock {
        public:
            typedef Mutex               mutex_type;
            typedef unique_lock<Mutex>  self_type;

            unique_lock() : m_pmutex(NULL), m_locked(false) { }
            explicit unique_lock(mutex_type& m)
                : m_pmutex(&m), m_locked(true)
            {
                m_pmutex->lock();
            }

            unique_lock(mutex_type& m, defer_lock_t)
                : m_pmutex(&m), m_locked(false) { }
            unique_lock(mutex_type& m, try_to_lock_t)
                : m_pmutex(&m), m_locked(false)
            {
                m_locked = m_pmutex->try_lock();
            }

            unique_lock(mutex_type& m, adopt_lock_t)
                : m_pmutex(&m), m_locked(true) { }

            template <typename Clock, typename Duration>
            unique_lock(mutex_type& m,
                        const chrono::time_point<Clock, Duration>& abs_time) 
                : m_pmutex(&m), m_locked(false)
            {
                m_locked = m_pmutex->try_lock_until(abs_time);
            }

            template <typename Rep, typename Period>
            unique_lock(mutex_type& m,
                        const chrono::duration<Rep, Period>& rel_time)
                : m_pmutex(&m), m_locked(false)
            {
                m_locked = m_pmutex->try_lock_for(rel_time);
            }

            ~unique_lock() {
                if (m_locked && m_pmutex)
                    m_pmutex->unlock();
            }

            bool owns_lock() const { return m_locked; }
            mutex_type *mutex() const { return m_pmutex; }
            operator bool() const { return owns_lock(); }

            void lock() {
                if (m_pmutex == NULL)
                    throw system_error(EPERM);
                if (m_locked)
                    throw system_error(EDEADLK);
                m_pmutex->lock();
                m_locked = true;
            }
            bool try_lock() {
                if (m_pmutex == NULL)
                    throw system_error(EPERM);
                if (m_locked)
                    throw system_error(EDEADLK);
                m_locked = mutex()->try_lock();
                return m_locked;
            }
            void unlock() {
                if (m_pmutex) {
                    if (!m_locked)
                        throw system_error(EPERM);
                    mutex()->unlock();
                    m_locked = false;
                }
            }
            mutex_type *release() {
                mutex_type *m = m_pmutex;
                m_pmutex = NULL;
                m_locked = false;
                return m;
            }
            void swap(unique_lock<Mutex>& other) {
                unboost::swap(m_pmutex, other.m_pmutex);
                unboost::swap(m_locked, other.m_locked);
            }

#ifdef UNBOOST_RV_REF
            unique_lock(UNBOOST_RV_REF(self_type) other) {
                m_pmutex = UNBOOST_RV(other).m_pmutex;
                m_locked = UNBOOST_RV(other).m_locked;
                UNBOOST_RV(other).m_pmutex = NULL;
                UNBOOST_RV(other).m_locked = false;
            }
            unique_lock& operator=(UNBOOST_RV_REF(self_type) other) {
                m_pmutex = UNBOOST_RV(other).m_pmutex;
                m_locked = UNBOOST_RV(other).m_locked;
                UNBOOST_RV(other).m_pmutex = NULL;
                UNBOOST_RV(other).m_locked = false;
                return *this;
            }
#endif
        protected:
            mutex_type *m_pmutex;
            bool m_locked;
        private:
            unique_lock(const self_type&)/* = delete*/;
            unique_lock& operator=(const self_type&)/* = delete*/;
        }; // class unique_lock

        template <class Mutex2>
        inline void
        swap(unique_lock<Mutex2>& ul1, unique_lock<Mutex2>& ul2) {
            ul1.swap(ul2);
        }

        template <class Mutex>
        class lock_guard {
        public:
            typedef Mutex               mutex_type;
            typedef lock_guard<Mutex>   self_type;

            explicit lock_guard(mutex_type& m) : m_mutex(m) {
                m_mutex.lock();
            }
            lock_guard(mutex_type& m, adopt_lock_t) : m_mutex(m) { }

            ~lock_guard() {
                m_mutex.unlock();
            }
        protected:
            Mutex&      m_mutex;
        private:
            lock_guard(const self_type&)/* = delete*/;
            self_type& operator=(const self_type&)/* = delete*/;
        }; // class lock_guard

        template <typename L1, typename L2>
        inline void lock(L1& l1, L2& l2) {
            try {
                unique_lock<L1> lock1(l1);
                if (lock1.owns_lock()) {
                    unique_lock<L2> lock2(l2);
                    if (lock2.owns_lock()) {
                        lock2.release();
                        lock1.release();
                        return;
                    }
                    lock1.unlock();
                }
            } catch (const system_error&) {
                ;
            } catch (...) {
                throw;
            }
        } // lock
        template <typename L1, typename L2, typename L3>
        inline void lock(L1& l1, L2& l2, L3& l3) {
            try {
                unique_lock<L1> lock1(l1);
                if (lock1.owns_lock()) {
                    unique_lock<L2> lock2(l2);
                    if (lock2.owns_lock()) {
                        unique_lock<L3> lock3(l3);
                        if (lock3.owns_lock()) {
                            lock3.release();
                            lock2.release();
                            lock1.release();
                            return;
                        }
                        lock2.unlock();
                    }
                    lock1.unlock();
                }
            } catch (...) {
                throw;
            }
        } // lock
        template <typename L1, typename L2, typename L3, typename L4>
        inline void lock(L1& l1, L2& l2, L3& l3, L4& l4) {
            try {
                unique_lock<L1> lock1(l1);
                if (lock1.owns_lock()) {
                    unique_lock<L2> lock2(l2);
                    if (lock2.owns_lock()) {
                        unique_lock<L3> lock3(l3);
                        if (lock3.owns_lock()) {
                            unique_lock<L4> lock4(l4);
                            if (lock4.owns_lock()) {
                                lock4.release();
                                lock3.release();
                                lock2.release();
                                lock1.release();
                                return;
                            }
                            lock3.unlock();
                        }
                        lock2.unlock();
                    }
                    lock1.unlock();
                }
            } catch (const system_error&) {
                ;
            } catch (...) {
                throw;
            }
        } // lock
        template <typename L1, typename L2, typename L3, typename L4, typename L5>
        inline void lock(L1& l1, L2& l2, L3& l3, L4& l4, L5& l5) {
            try {
                unique_lock<L1> lock1(l1);
                if (lock1.owns_lock()) {
                    unique_lock<L2> lock2(l2);
                    if (lock2.owns_lock()) {
                        unique_lock<L3> lock3(l3);
                        if (lock3.owns_lock()) {
                            unique_lock<L4> lock4(l4);
                            if (lock4.owns_lock()) {
                                unique_lock<L5> lock5(l5);
                                if (lock5.owns_lock()) {
                                    lock5.release();
                                    lock4.release();
                                    lock3.release();
                                    lock2.release();
                                    lock1.release();
                                    return;
                                }
                                lock4.unlock();
                            }
                            lock3.unlock();
                        }
                        lock2.unlock();
                    }
                    lock1.unlock();
                }
            } catch (const system_error&) {
                ;
            } catch (...) {
                throw;
            }
        } // lock
        template <typename L1, typename L2>
        inline int try_lock(L1& l1, L2& l2) {
            volatile int i = 0;
            try {
                unique_lock<L1> lock1(l1, try_to_lock);
                if (lock1.owns_lock()) {
                    ++i;
                    unique_lock<L2> lock2(l2, try_to_lock);
                    if (lock2.owns_lock()) {
                        ++i;
                        lock2.release();
                        lock1.release();
                        return -1;
                    }
                    lock1.unlock();
                }
            } catch (...) {
                throw;
            }
            return i;
        } // try_lock
        template <typename L1, typename L2, typename L3>
        inline int try_lock(L1& l1, L2& l2, L3& l3) {
            int i = 0;
            try {
                unique_lock<L1> lock1(l1, try_to_lock);
                if (lock1.owns_lock()) {
                    ++i;
                    unique_lock<L2> lock2(l2, try_to_lock);
                    if (lock2.owns_lock()) {
                        ++i;
                        unique_lock<L3> lock3(l3, try_to_lock);
                        if (lock3.owns_lock()) {
                            ++i;
                            lock3.release();
                            lock2.release();
                            lock1.release();
                            return -1;
                        }
                        lock2.unlock();
                    }
                    lock1.unlock();
                }
            } catch (...) {
                throw;
            }
            return i;
        } // try_lock
        template <typename L1, typename L2, typename L3, typename L4>
        inline int try_lock(L1& l1, L2& l2, L3& l3, L4& l4) {
            int i = 0;
            try {
                unique_lock<L1> lock1(l1, try_to_lock);
                if (lock1.owns_lock()) {
                    ++i;
                    unique_lock<L2> lock2(l2, try_to_lock);
                    if (lock2.owns_lock()) {
                        ++i;
                        unique_lock<L3> lock3(l3, try_to_lock);
                        if (lock3.owns_lock()) {
                            ++i;
                            unique_lock<L4> lock4(l4, try_to_lock);
                            if (lock4.owns_lock()) {
                                ++i;
                                lock4.release();
                                lock3.release();
                                lock2.release();
                                lock1.release();
                                return -1;
                            }
                            lock3.unlock();
                        }
                        lock2.unlock();
                    }
                    lock1.unlock();
                }
            } catch (...) {
                throw;
            }
            return i;
        } // try_lock
        template <typename L1, typename L2, typename L3, typename L4, typename L5>
        inline int try_lock(L1& l1, L2& l2, L3& l3, L4& l4, L5& l5) {
            int i = 0;
            try {
                unique_lock<L1> lock1(l1, try_to_lock);
                if (lock1.owns_lock()) {
                    ++i;
                    unique_lock<L2> lock2(l2, try_to_lock);
                    if (lock2.owns_lock()) {
                        ++i;
                        unique_lock<L3> lock3(l3, try_to_lock);
                        if (lock3.owns_lock()) {
                            ++i;
                            unique_lock<L4> lock4(l4, try_to_lock);
                            if (lock4.owns_lock()) {
                                ++i;
                                unique_lock<L5> lock5(l5, try_to_lock);
                                if (lock5.owns_lock()) {
                                    ++i;
                                    lock5.release();
                                    lock4.release();
                                    lock3.release();
                                    lock2.release();
                                    lock1.release();
                                    return -1;
                                }
                                lock4.unlock();
                            }
                            lock3.unlock();
                        }
                        lock2.unlock();
                    }
                    lock1.unlock();
                }
            } catch (...) {
                throw;
            }
            return i;
        } // try_lock
    } // namespace unboost
#endif  // def UNBOOST_NEED_LOCK_EXTRA

#endif  // ndef UNBOOST_THREAD_HPP
