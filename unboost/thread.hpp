// thread.hpp --- Unboost thread
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_THREAD_HPP
#define UNBOOST_THREAD_HPP

#include <unboost/core.hpp>

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
                #define UNBOOST_USE_CXX11_THREAD
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
    namespace unboost {
        using std::thread;
        namespace this_thread {
            using std::this_thread::get_id;
            using std::this_thread::sleep_for;
            using std::this_thread::sleep_until;
            using std::this_thread::yield;
        }
    }
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
    }
#elif defined(UNBOOST_USE_WIN32_THREAD)
    #include <stdexcept>
    #include <process.h>
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
                    throw std::runtime_error("unboost::thread");
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
                    throw std::runtime_error("unboost::thread");
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
                    throw std::runtime_error("unboost::thread");
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
                    throw std::runtime_error("unboost::thread");
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
                swap(m_hThread, other.m_hThread);
                swap(m_id, other.m_id);
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
                unboost_auto_duration ms = duration_cast<milliseconds>(sleep_duration);
                ::Sleep(ms.count());
            }
            inline void sleep_for(const unboost::chrono::auto_duration& sleep_duration) {
                using namespace unboost::chrono;
                unboost_auto_duration ms = duration_cast<milliseconds>(sleep_duration);
                ::Sleep(ms.count());
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
    } // namespace unboost
#elif defined(UNBOOST_USE_POSIX_THREAD)
    #include <stdexcept>
    #include <pthread.h>
    #ifdef _WIN32
        #ifndef _INC_WINDOWS
            #include <windows.h>    // for Sleep
        #endif
    #else
        #include <time.h>     // for nanosleep
    #endif
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
                    throw std::runtime_error("unboost::thread");
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
                    throw std::runtime_error("unboost::thread");
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
                    throw std::runtime_error("unboost::thread");
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
                    throw std::runtime_error("unboost::thread");
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
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_THREAD_HPP
