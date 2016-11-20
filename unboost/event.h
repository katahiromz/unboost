// event.hpp --- Unboost event
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_EVENT_H_
#define UNBOOST_EVENT_H_

// class event;
// event_handle create_event(bool manual_reset  = false,
//                           bool initial_state = false);
// bool wait_for_event(event_handle eh, uint32_t milliseconds = -1);
// bool close_event(event_handle eh);
// bool set_event(event_handle eh);
// bool reset_event(event_handle eh);
// bool pulse_event(event_handle eh);

#include "unboost.h"
#include "pstdbool.h"   // for bool, true, false
#include "pstdint.h"    // for unboost::int*_t, uint*_t

// If not choosed, choose one
#if ((defined(UNBOOST_USE_WIN32_EVENT) + defined(UNBOOST_USE_POSIX_EVENT)) == 0)
    #ifdef _WIN32
        #define UNBOOST_USE_WIN32_EVENT
    #else
        #define UNBOOST_USE_POSIX_EVENT
    #endif
#endif

// define unboost_optional_(opt) macro
#ifndef unboost_optional_
    #ifdef __cplusplus
        #define unboost_optional_(opt) = opt
    #else
        #define unboost_optional_(opt)
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_WIN32_EVENT
    #ifndef _INC_WINDOWS
        #ifndef NOMINMAX
            #define NOMINMAX
        #endif
        #include <windows.h>
    #endif
    #ifdef __cplusplus
    namespace unboost {
    #endif
        typedef HANDLE event_handle;

        inline event_handle
        create_event(bool manual_reset unboost_optional_(false),
                     bool initial_state unboost_optional_(false))
        {
            event_handle eh;
            eh = CreateEvent(NULL, manual_reset, initial_state, NULL);
            assert(eh != NULL);
            return eh;
        }

        inline bool
        wait_for_event(event_handle eh,
                       uint32_t milliseconds unboost_optional_(-1))
        {
            assert(eh != NULL);
            return (WaitForSingleObject(eh, milliseconds) == WAIT_TIMEOUT);
        }

        inline bool close_event(event_handle eh) {
            assert(eh != NULL);
            return (bool)CloseHandle(eh);
        }

        inline bool set_event(event_handle eh) {
            assert(eh != NULL);
            return (bool)SetEvent(eh);
        }
        inline bool reset_event(event_handle eh) {
            assert(eh != NULL);
            return (bool)ResetEvent(eh);
        }
        inline bool pulse_event(event_handle eh) {
            assert(eh != NULL);
            return (bool)PulseEvent(eh);
        }
    #ifdef __cplusplus
    } // namespace unboost
    #endif
#elif defined(UNBOOST_USE_POSIX_EVENT)
    #include <sys/time.h>   // for struct timeval, timespec
    #include <pthread.h>    // for POSIX threads
    #ifdef __cplusplus
        #include <cerrno>   // for ETIMEDOUT
    #else
        #include <errno.h>  // for ETIMEDOUT
    #endif

    #ifdef __cplusplus
    namespace unboost {
    #endif
        typedef struct _event_data {
            char dummy;
        } _event_data;
        typedef _event_data * event_handle;

        typedef struct _event_impl_t {
            pthread_cond_t      m_condition;
            pthread_mutex_t     m_lock;
            bool                m_signaled;
            bool                m_auto_reset;
        } _event_impl_t;

        inline bool set_event(event_handle eh) {
            int result;
            _event_impl_t *e = (_event_impl_t *)eh;

            result = pthread_mutex_lock(&e->m_lock);
            assert(result == 0);
            result = result;

            e->m_signaled = true;

            if (e->m_auto_reset) {
                if (e->m_signaled) {
                    result = pthread_mutex_unlock(&e->m_lock);
                    assert(result == 0);
                    result = result;

                    result = pthread_cond_signal(&e->m_condition);
                    assert(result == 0);
                    result = result;
                }
            } else {
                result = pthread_mutex_unlock(&e->m_lock);
                assert(result == 0);
                result = result;

                result = pthread_cond_broadcast(&e->m_condition);
                assert(result == 0);
                result = result;
            }

            return true;
        } // set_event

        inline event_handle
        create_event(bool manual_reset unboost_optional_(false),
                        bool initial_state unboost_optional_(false))
        {
            int result;
            _event_impl_t *e;
            event_handle eh = NULL;

            e = (_event_impl_t *)malloc(sizeof(_event_impl_t));
            if (e != NULL) {
                result = pthread_cond_init(&e->m_condition, 0);
                assert(result == 0);
                result = result;

                result = pthread_mutex_init(&e->m_lock, 0);
                assert(result == 0);
                result = result;

                e->m_signaled = false;
                e->m_auto_reset = !manual_reset;

                eh = (event_handle)e;
                if (initial_state) {
                    bool ret = set_event(eh);
                    assert(ret);
                    ret = ret;
                }
            }

            return eh;
        } // create_event

        inline bool
        wait_for_event(event_handle eh,
                       uint32_t milliseconds unboost_optional_(-1))
        {
            bool timeout;
            int result;
            struct timespec ts;
            struct timeval tv;
            uint64_t nanoseconds;
            const uint64_t kilo = 1000;
            const uint64_t mega = 1000 * 1000;
            const uint64_t giga = 1000 * 1000 * 1000;
            _event_impl_t *e = (_event_impl_t *)eh;

            if (e->m_signaled) {
                if (e->m_auto_reset) {
                    e->m_signaled = false;
                }
                timeout = false;
            } else {
                if (milliseconds != (uint32_t)(-1)) {
                    gettimeofday(&tv, NULL);

                    nanoseconds =
                        (tv.tv_sec * giga) +
                        (milliseconds * mega) +
                        (tv.tv_usec * kilo);

                    ts.tv_sec = nanoseconds / giga;
                    ts.tv_nsec = nanoseconds % giga;

                    do {
                        result = pthread_cond_timedwait(&e->m_condition,
                                                        &e->m_lock,
                                                        &ts);
                    } while ((result == 0) && !e->m_signaled);
                } else {
                    do {
                        result = pthread_cond_wait(&e->m_condition, &e->m_lock);
                    } while ((result == 0) && !e->m_signaled);
                }

                timeout = (result == ETIMEDOUT);
                if (result == 0) {
                    if (e->m_auto_reset) {
                        e->m_signaled = false;
                    }
                }
            }

            return timeout;
        } // wait_for_event

        inline bool close_event(event_handle eh) {
            int result;
            _event_impl_t *e = (_event_impl_t *)eh;

            result = pthread_cond_destroy(&e->m_condition);
            assert(result == 0);
            result = result;

            result = pthread_mutex_destroy(&e->m_lock);
            assert(result == 0);
            result = result;

            free(e);
            return true;
        } // close_event

        inline bool reset_event(event_handle eh) {
            int result;
            _event_impl_t *e = (_event_impl_t *)eh;

            result = pthread_mutex_lock(&e->m_lock);
            assert(result == 0);
            result = result;

            e->m_signaled = false;

            result = pthread_mutex_unlock(&e->m_lock);
            assert(result == 0);
            result = result;

            return true;
        }

        inline bool pulse_event(event_handle eh) {
            bool ret = set_event(eh);
            assert(ret);
            ret = ret;

            ret = reset_event(eh);
            assert(ret);
            ret = ret;

            return true;
        }
    #ifdef __cplusplus
    } // namespace unboost
    #endif
#else
    #error Your compiler is not supported yet. You lose.
#endif

#ifdef __cplusplus
#include "rv_ref.hpp"   // for UNBOOST_RV_REF, ...
namespace unboost {
    class event {
    public:
        event() : m_handle(NULL) { }
        event(bool manual_reset, bool initial_state)
            : m_handle(unboost::create_event(manual_reset, initial_state)) { }

        #ifdef UNBOOST_RV_REF
            event(UNBOOST_RV_REF(event) e)
                : m_handle(UNBOOST_RV(e).m_handle)
            {
                UNBOOST_RV(e).m_handle = NULL;
            }
            event& operator=(UNBOOST_RV_REF(event) e)
            {
                m_handle = UNBOOST_RV(e).m_handle;
                UNBOOST_RV(e).m_handle = NULL;
                return *this;
            }
        #endif

        virtual ~event() {
            close();
        }

        operator bool() const   { return m_handle != NULL; }
        bool operator!() const  { return m_handle == NULL; }

        bool create(bool manual_reset = false, bool initial_state = false) {
            close();
            m_handle = unboost::create_event(manual_reset, initial_state);
            return (m_handle != NULL);
        }

        // NOTE: wait_for_event() returns true if timeout.
        bool wait_for_event(uint32_t milliseconds = -1) {
            return unboost::wait_for_event(m_handle, milliseconds);
        }

        bool close() {
            if (m_handle != NULL) {
                unboost::close_event(m_handle);
                m_handle = NULL;
                return true;
            }
            return false;
        }

        bool set()      { return unboost::set_event(m_handle); }
        bool reset()    { return unboost::reset_event(m_handle); }
        bool pulse()    { return unboost::pulse_event(m_handle); }

    protected:
        event_handle m_handle;

    private:
        // NOTE: event cannot be copyed.
        event(const event&)/* = delete*/;
        event& operator=(const event&)/* = delete*/;
    };
} // namespace unboost
#endif  // def __cplusplus

#endif  // ndef UNBOOST_EVENT_H_
