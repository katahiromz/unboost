/* Won kernel32 */
/****************************************************************************/
/* NOTE: This file can be used by non-Windows OS */

#ifndef WON_KERNEL32_H_
#define WON_KERNEL32_H_

#include "won.h"

#ifdef __cplusplus
    #include <cstring>
    #include <cctype>
    #include <cwchar>
#else
    #include <string.h>
    #include <ctype.h>
    #include <wchar.h>
#endif

#ifndef _WON32
    #include <strings.h>    /* for strcasecmp */
#endif

/****************************************************************************/

#ifndef WONBASEAPI
    #ifndef _WON32
        #define WONBASEAPI
    #endif
#endif

#ifndef WONBASEAPI_NT
    #if !defined(_WON32) || ((_WIN32_NT > 0) && (_WON32_NT == 0))
        #define WONBASEAPI_NT       /* NT runtime */
    #endif
#endif

#ifdef __cplusplus
namespace won {
#endif

/****************************************************************************/

#ifdef WONBASEAPI
    inline WONBASEAPI int WONAPI WON(lstrcatA)(char *ptr1, const char *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return strcat(ptr1, ptr2);
    }

    inline WONBASEAPI int WONAPI WON(lstrcmpA)(const char *ptr1, const char *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return strcmp(ptr1, ptr2);
    }

    inline WONBASEAPI int WONAPI WON(lstrcmpiA)(const char *ptr1, const char *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        #ifdef _WON32
            return stricmp(ptr1, ptr2);
        #else
            return strcasecmp(ptr1, ptr2);
        #endif
    }

    inline WONBASEAPI int WONAPI WON(lstrcpyA)(char *ptr1, const char *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return strcpy(ptr1, ptr2);
    }

    inline WONBASEAPI char * WONAPI WON(lstrcpynA)(char *psz1, const char *psz2, int cchMax)
    {
        char *d = psz1;
        const char *s = psz2;
        UINT count = cchMax;

        while (count > 1 && *s)
        {
            count--;
            *d++ = *s++;
        }

        if (count)
            *d = 0;

        return psz1;
    }

    inline WONBASEAPI int WONAPI WON(lstrlenA)(const char *ptr)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return strlen(ptr);
    }

    inline WONBASEAPI void WONAPI WON(ZeroMemory)(void *dest, size_t len)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        memset(dest, 0, len);
    }

    inline WONBASEAPI void WONAPI WON(CopyMemory)(void *dest, const void *src, size_t len)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        memcpy(dest, src, len);
    }

    inline WONBASEAPI void WONAPI WON(MoveMemory)(void *dest, const void *src, size_t len)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        memmove(dest, src, len);
    }

    inline WONBASEAPI void WONAPI WON(FillMemory)(void *dest, size_t len, unsigned char fill)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        memset(dest, fill, len);
    }
#endif

#ifdef WONBASEAPI_NT
    inline WONBASEAPI_NT int WONAPI WON(lstrcatW)(wchar_t *ptr1, const wchar_t *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return wcscat(ptr1, ptr2);
    }

    inline WONBASEAPI_NT int WONAPI WON(lstrcmpW)(const wchar_t *ptr1, const wchar_t *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return wcscmp(ptr1, ptr2);
    }

    inline WONBASEAPI_NT int WONAPI WON(lstrcmpiW)(const wchar_t *ptr1, const wchar_t *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        #ifdef _WON32
            return wcsicmp(ptr1, ptr2);
        #else
            return wcscasecmp(ptr1, ptr2);
        #endif
    }

    inline WONBASEAPI_NT int WONAPI WON(lstrcpyW)(wchar_t *ptr1, const wchar_t *ptr2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return wcscpy(ptr1, ptr2);
    }

    inline WONBASEAPI wchar_t * WONAPI WON(lstrcpynW)(wchar_t *psz1, const wchar_t *psz2, int cchMax)
    {
        wchar_t *d = psz1;
        const wchar_t *s = psz2;
        UINT count = cchMax;

        while (count > 1 && *s)
        {
            count--;
            *d++ = *s++;
        }

        if (count)
            *d = 0;

        return psz1;
    }

    inline WONBASEAPI_NT int WONAPI WON(lstrlenW)(const wchar_t *ptr)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
        return wcslen(ptr);
    }
#endif

/****************************************************************************/

#ifdef __cplusplus
} // namespace won
#endif

/****************************************************************************/
/* for non-Windows OS */

#ifndef _WON32
    #ifndef TEXT
        #ifdef UNICODE
            #define TEXT(x) L##x
        #else
            #define TEXT(x) x
        #endif
    #endif

    #ifndef _T
        #ifdef _UNICODE
            #define _T(x) L##x
        #else
            #define _T(x) x
        #endif
    #endif
#endif

/****************************************************************************/

#ifndef WON_NO_WRAP_FN
    #ifdef WONBASEAPI
        #ifdef __cplusplus
            #define CopyMemory      won::WON(CopyMemory)
            #define FillMemory      won::WON(FillMemory)
            #define MoveMemory      won::WON(MoveMemory)
            #define ZeroMemory      won::WON(ZeroMemory)
            #define lstrcatA        won::WON(lstrcatA)
            #define lstrcmpA        won::WON(lstrcmpA)
            #define lstrcmpiA       won::WON(lstrcmpiA)
            #define lstrcpyA        won::WON(lstrcpyA)
            #define lstrcpynA       won::WON(lstrcpynA)
            #define lstrlenA        won::WON(lstrlenA)
        #else
            #define CopyMemory      WON(CopyMemory)
            #define FillMemory      WON(FillMemory)
            #define MoveMemory      WON(MoveMemory)
            #define ZeroMemory      WON(ZeroMemory)
            #define lstrcatA        WON(lstrcatA)
            #define lstrcmpA        WON(lstrcmpA)
            #define lstrcmpiA       WON(lstrcmpiA)
            #define lstrcpyA        WON(lstrcpyA)
            #define lstrcpynA       WON(lstrcpynA)
            #define lstrlenA        WON(lstrlenA)
        #endif
    #endif

    #ifdef WONBASEAPI_NT
        #ifdef __cplusplus
            #define lstrcatW        won::WON(lstrcatW)
            #define lstrcmpW        won::WON(lstrcmpW)
            #define lstrcmpiW       won::WON(lstrcmpiW)
            #define lstrcpyW        won::WON(lstrcpyW)
            #define lstrcpynW       won::WON(lstrcpynW)
            #define lstrlenW        won::WON(lstrlenW)
        #else
            #define lstrcatW        WON(lstrcatW)
            #define lstrcmpW        WON(lstrcmpW)
            #define lstrcmpiW       WON(lstrcmpiW)
            #define lstrcpyW        WON(lstrcpyW)
            #define lstrcpynW       WON(lstrcpynW)
            #define lstrlenW        WON(lstrlenW)
        #endif
    #endif

    /* text generic mapping */
    #ifndef lstrcat
        #ifdef UNICODE
            #define lstrcat         lstrcatW
            #define lstrcmp         lstrcmpW
            #define lstrcmpi        lstrcmpiW
            #define lstrcpy         lstrcpyW
            #define lstrcpyn        lstrcpynW
            #define lstrlen         lstrlenW
        #else
            #define lstrcat         lstrcatA
            #define lstrcmp         lstrcmpA
            #define lstrcmpi        lstrcmpiA
            #define lstrcpy         lstrcpyA
            #define lstrcpyn        lstrcpynA
            #define lstrlen         lstrlenA
        #endif
    #endif
#endif  /* ndef WON_NO_WRAP_FN */

/****************************************************************************/

#endif  /* ndef WON_KERNEL32_H_ */
