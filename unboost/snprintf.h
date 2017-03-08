// snprintf.hpp --- Unboost snprintf
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_SNPRINTF_H_
#define UNBOOST_SNPRINTF_H_

#include "unboost.h"

//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_SNPRINTF_MAX_SIZE
    #define UNBOOST_SNPRINTF_MAX_SIZE   1024
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
#if (UNBOOST_SNPRINTF_MAX_SIZE >= 2048)
    char *buf = malloc(UNBOOST_SNPRINTF_MAX_SIZE);
    if (buf == NULL)
        return 0;
#else
    char buf[UNBOOST_SNPRINTF_MAX_SIZE];
#endif

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

#if (UNBOOST_SNPRINTF_MAX_SIZE >= 2048)
    free(buf);
#endif
    return n;
}

inline int
vsnwprintf(wchar_t *bufptr, size_t size, const wchar_t *fmt, va_list va)
{
    int n;
#if (UNBOOST_SNPRINTF_MAX_SIZE >= 2048)
    wchar_t *buf = (wchar_t *)malloc(UNBOOST_SNPRINTF_MAX_SIZE / sizeof(wchar_t));
    if (buf == NULL)
        return 0;
#else
    wchar_t buf[UNBOOST_SNPRINTF_MAX_SIZE / sizeof(wchar_t)];
#endif

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

#if (UNBOOST_SNPRINTF_MAX_SIZE >= 2048)
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
