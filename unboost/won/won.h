/* won.h --- Unboost Won */
/****************************************************************************/
/* NOTE: This file can be used by non-Windows OS */

#ifndef WON_H_
#define WON_H_

#if (_MSC_VER > 1000)
    #pragma once
#endif

#ifndef WON
    #ifdef __cplusplus
        #define WON(name)   name
    #else
        #define WON(name)   Won_##name
    #endif
#endif

#define WON_VERSION             0
#define WON_VERSION_STRING      "Unboost Won 0 by Katayama Hirofumi MZ"

/****************************************************************************/

/* NOTE: This Won uses the Unboost library */
#include "../unboost.h"

#if defined(UNBOOST_OLD_COMPILER) && !defined(WON_OLD_COMPILER)
    #define WON_OLD_COMPILER    1
#endif

/****************************************************************************/

#ifndef _WON32
    #ifdef _WIN32
        #define _WON32          1
    #endif
#endif

#ifndef _WON64
    #ifdef _WIN64
        #define _WON64          1
    #endif
#endif

#ifndef WONAPI
    #ifdef WINAPI
        #define WONAPI          WINAPI
    #else
        #define WONAPI          /*empty*/
    #endif
#endif

#ifndef WONAPIV
    #ifdef WINAPIV
        #define WONAPIV         WINAPIV
    #else
        #define WONAPIV         /*empty*/
    #endif
#endif

#ifndef WONVER
    #ifdef WINVER
        #define WONVER          WINVER
    #else
        #define WONVER          0x0410  /* Windows 98 */
    #endif
#endif

#ifndef _WON32_WINDOWS
    #ifdef _WIN32_WINDOWS
        #define _WON32_WINDOWS  _WIN32_WINDOWS
    #else
        #define _WON32_WINDOWS  0x0410  /* Windows 98 */
    #endif
#endif

#ifndef _WON32_WINNT
    #ifdef _WIN32_WINNT
        #define _WON32_WINNT    _WIN32_WINNT
    #else
        #define _WON32_WINNT    0       /* Windows 98 */
    #endif
#endif

#ifndef _WON32_IE
    #ifdef _WIN32_IE
        #define _WON32_IE       _WIN32_IE
    #else
        #define _WON32_IE       0x0410  /* Windows 98 */
    #endif
#endif

/****************************************************************************/

#if defined(_WON32_WINNT) && (WONVER < 0x0400) && (_WON32_WINNT > 0x0400)
    #error WONVER setting conflicts with _WON32_WINNT setting. You lose.
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

#ifndef WON_H_INCLUDED
    #define WON_H_INCLUDED  1
#endif
#endif  /* ndef WON_H_ */
