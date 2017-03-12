/* Won user32 */
/****************************************************************************/
/* NOTE: This file can be used by non-Windows OS */

#ifndef WON_USER32_H_
#define WON_USER32_H_

#include "won.h"

/****************************************************************************/

#ifndef WONUSERAPI
    #ifndef _WON32
        #define WONUSERAPI
    #endif
#endif

#ifdef __cplusplus
namespace won {
#endif

/****************************************************************************/

#ifdef WONUSERAPI
    #ifndef _WON32
        /* NOTE: In Linux, a long can be 64-bit value */
        typedef struct tagRECT {
            int left, top, right, bottom;
        } RECT, *PRECT, *LPRECT;
        typedef const RECT *LPCRECT;
    #endif

    inline WONUSERAPI BOOL WONAPI WON(IsRectEmpty)(LPCRECT prc)
    {
#ifdef WON_SPEED
        assert(prc);
        if (prc == NULL)
            return FALSE;
#endif
        return (prc->left >= prc->right || prc->top >= prc->bottom);
    }

    inline WONUSERAPI BOOL WONAPI WON(EqualRect)(const RECT *prc1, const RECT *prc2)
    {
    #ifdef __cplusplus
        using namespace std;
    #endif
#ifdef WON_SPEED
        assert(prc1);
        assert(prc2);
        if (prc1 == NULL || prc2 == NULL)
            return FALSE;
#endif
        return memcmp(prc1, prc2, sizeof(RECT)) == 0;
    }

    inline WONUSERAPI BOOL WONAPI WON(CopyRect)(LPRECT dest, const RECT *src)
    {
#ifdef WON_SPEED
        assert(dest);
        assert(src);
        if (dest == NULL || src == NULL)
            return FALSE;
#endif
        *dest = *src;
        return TRUE;
    }

    inline WONUSERAPI BOOL WONAPI WON(OffsetRect)(LPRECT prc, int dx, int dy)
    {
#ifdef WON_SPEED
        assert(prc);
        if (prc == NULL)
            return FALSE;
#endif
        prc->left += dx;
        prc->right += dx;
        prc->top += dy;
        prc->bottom += dy;
        return prc != NULL;
    }

    inline WONUSERAPI BOOL WONAPI WON(InflateRect)(LPRECT prc, int dx, int dy)
    {
#ifdef WON_SPEED
        assert(prc);
        if (prc == NULL)
            return FALSE;
#endif
        prc->left -= dx;
        prc->top -= dy;
        prc->right += dx;
        prc->bottom += dy;
        return TRUE;
    }

    inline WONUSERAPI BOOL WONAPI WON(PtInRect)(const RECT *prc, POINT pt)
    {
#ifdef WON_SPEED
        assert(prc);
        if (prc == NULL)
            return FALSE;
#endif
        return (pt.x >= prc->left && pt.x < prc->right &&
                pt.y >= prc->top && pt.y < prc->bottom);
    }
#endif  /* def WONUSERAPI */

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
    #ifdef WONUSERAPI
        #ifdef __cplusplus
            #define CopyRect        won::WON(CopyRect)
            #define EqualRect       won::WON(EqualRect)
            #define InflateRect     won::WON(InflateRect)
            #define IsRectEmpty     won::WON(IsRectEmpty)
            #define OffsetRect      won::WON(OffsetRect)
            #define PtInRect        won::WON(PtInRect)
        #else
            #define CopyRect        WON(CopyRect)
            #define EqualRect       WON(EqualRect)
            #define InflateRect     WON(InflateRect)
            #define IsRectEmpty     WON(IsRectEmpty)
            #define OffsetRect      WON(OffsetRect)
            #define PtInRect        WON(PtInRect)
        #endif
    #endif
#endif  /* ndef WON_NO_WRAP_FN */

/****************************************************************************/

#endif  /* ndef WON_USER32_H_ */
