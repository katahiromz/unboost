// snprintf.hpp --- Unboost snprintf (hack)
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_SNPRINTF_H_
#define UNBOOST_SNPRINTF_H_

#include "unboost.h"

//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_SNPRINTF_MAX_SIZE
    #define UNBOOST_SNPRINTF_MAX_SIZE   1024
#endif

#if !defined(UNBOOST_SNPRINTF_USE_HEAP) && (UNBOOST_SNPRINTF_MAX_SIZE >= 2048)
    #define UNBOOST_SNPRINTF_USE_HEAP
#endif

#ifdef __cplusplus
namespace unboost {
    using std::vsprintf;
    using std::vswprintf;
#endif

//////////////////////////////////////////////////////////////////////////////

inline int
vsnprintf(char *bufptr, size_t size, const char *fmt, va_list va)
{
    int n;
#ifdef UNBOOST_SNPRINTF_USE_HEAP
    char *buf = malloc(UNBOOST_SNPRINTF_MAX_SIZE);
    if (buf == NULL)
    {
        if (bufptr && size)
            *bufptr = 0;
        return 0;
    }
#else
    char buf[UNBOOST_SNPRINTF_MAX_SIZE];
#endif

    assert(bufptr);
    assert(fmt);
    n = vsprintf(buf, fmt, va);
    if (size > n)
    {
        memcpy(bufptr, buf, n * sizeof(char));
        bufptr[n] = 0;
    }
    else if (size > 0)
    {
        memcpy(bufptr, buf, size * sizeof(char));
        bufptr[size - 1] = 0;
    }

#ifdef UNBOOST_SNPRINTF_USE_HEAP
    free(buf);
#endif
    return n;
}

inline int
vsnwprintf(wchar_t *bufptr, size_t size, const wchar_t *fmt, va_list va)
{
    int n;
#ifdef UNBOOST_SNPRINTF_USE_HEAP
    wchar_t *buf = (wchar_t *)malloc(UNBOOST_SNPRINTF_MAX_SIZE / sizeof(wchar_t));
    if (buf == NULL)
    {
        if (bufptr && size)
            *bufptr = 0;
        return 0;
    }
#else
    wchar_t buf[UNBOOST_SNPRINTF_MAX_SIZE / sizeof(wchar_t)];
#endif

    assert(bufptr);
    assert(fmt);
    n = vswprintf(buf, fmt, va);
    if (size > n)
    {
        memcpy(bufptr, buf, n * sizeof(char));
        bufptr[n] = 0;
    }
    else if (size > 0)
    {
        memcpy(bufptr, buf, size * sizeof(char));
        bufptr[size - 1] = 0;
    }

#ifdef UNBOOST_SNPRINTF_USE_HEAP
    free(buf);
#endif
    return n;
}

inline int
snprintf(char *bufptr, size_t size, const char *fmt, ...)
{
    int n;
    va_list va;
    va_start(va, fmt);
    assert(bufptr);
    assert(fmt);
    n = vsnprintf(bufptr, size, fmt, va);
    va_end(va);
    return n;
}

inline int
snwprintf(wchar_t *bufptr, size_t size, const wchar_t *fmt, ...)
{
    int n;
    va_list va;
    va_start(va, fmt);
    assert(bufptr);
    assert(fmt);
    n = vsnwprintf(bufptr, size, fmt, va);
    va_end(va);
    return n;
}

//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
} // namespace unboost
#endif

//////////////////////////////////////////////////////////////////////////////

#endif  /* ndef UNBOOST_SNPRINTF_H_ */
