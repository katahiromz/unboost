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
#ifndef WON_SPEED
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
#ifndef WON_SPEED
        assert(prc1);
        assert(prc2);
        if (prc1 == NULL || prc2 == NULL)
            return FALSE;
#endif
        return memcmp(prc1, prc2, sizeof(RECT)) == 0;
    }

    inline WONUSERAPI BOOL WONAPI WON(CopyRect)(LPRECT dest, const RECT *src)
    {
#ifndef WON_SPEED
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
#ifndef WON_SPEED
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
#ifndef WON_SPEED
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
#ifndef WON_SPEED
        assert(prc);
        if (prc == NULL)
            return FALSE;
#endif
        return (pt.x >= prc->left && pt.x < prc->right &&
                pt.y >= prc->top && pt.y < prc->bottom);
    }

    inline WONUSERAPI BOOL WONAPI WON(SetRect)(LPRECT prc, int left, int top, int right, int bottom)
    {
#ifndef WON_SPEED
        assert(prc);
        if (prc == NULL)
            return FALSE;
#endif
        prc->left = left;
        prc->top = top;
        prc->right = right;
        prc->bottom = bottom;
        return TRUE;
    }

    inline WONUSERAPI BOOL WONAPI WON(SetRectEmpty)(LPRECT prc)
    {
#ifndef WON_SPEED
        assert(prc);
        if (prc == NULL)
            return FALSE;
#endif
        prc->left = prc->right = prc->top = prc->bottom = 0;
        return TRUE;
    }

    inline WONUSERAPI BOOL WONAPI WON(IntersectRect)(LPRECT prcDst, const RECT *prcSrc1, const RECT *prcSrc2)
    {
#ifndef WON_SPEED
        assert(prcDst);
        assert(prcSrc1);
        assert(prcSrc2);
        if (prcDst == NULL || prcSrc1 == NULL || prcSrc2 == NULL)
            return FALSE;
#endif

        if (WON(IsRectEmpty)(prcSrc1) || WON(IsRectEmpty)(prcSrc2) ||
            prcSrc1->left >= prcSrc2->right ||
            prcSrc2->left >= prcSrc1->right ||
            prcSrc1->top >= prcSrc2->bottom ||
            prcSrc2->top >= prcSrc1->bottom)
        {
            WON(SetRectEmpty)(prcDst);
            return FALSE;
        }

        prcDst->left = max(prcSrc1->left, prcSrc2->left);
        prcDst->right = min(prcSrc1->right, prcSrc2->right);
        prcDst->top = max(prcSrc1->top, prcSrc2->top);
        prcDst->bottom = min(prcSrc1->bottom, prcSrc2->bottom);
        return TRUE;
    }

    inline WONUSERAPI BOOL WONAPI WON(SubtractRect)(LPRECT prcDst, const RECT *prcSrc1, const RECT *prcSrc2)
    {
        RECT TempRect;

        if (prcDst == NULL || prcSrc1 == NULL || prcSrc2 == NULL)
            return FALSE;

        if (!IntersectRect(&TempRect, prcSrc1, prcSrc2))
        {
            *prcDst = *prcSrc1;
            return TRUE;
        }

        if (EqualRect(&TempRect, prcSrc1))
        {
            SetRectEmpty(prcDst);
            return FALSE;
        }

        *prcDst = *prcSrc1;

        if (prcDst->top == TempRect.top && prcDst->bottom == TempRect.bottom)
        {
            if (prcDst->left == TempRect.left)
                prcDst->left = TempRect.right;
            else if (prcDst->right == TempRect.right)
                prcDst->right = TempRect.left;
        }
        else if (prcDst->left == TempRect.left && prcDst->right == TempRect.right)
        {
            if (prcDst->top == TempRect.top)
                prcDst->top = TempRect.bottom;
            else if (prcDst->bottom == TempRect.bottom)
                prcDst->bottom = TempRect.top;
        }

        return TRUE;
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
            #define IntersectRect   won::WON(IntersectRect)
            #define IsRectEmpty     won::WON(IsRectEmpty)
            #define OffsetRect      won::WON(OffsetRect)
            #define PtInRect        won::WON(PtInRect)
            #define SetRect         won::WON(SetRect)
            #define SetRectEmpty    won::WON(SetRectEmpty)
            #define SubtractRect    won::WON(SubtractRect)
        #else
            #define CopyRect        WON(CopyRect)
            #define EqualRect       WON(EqualRect)
            #define InflateRect     WON(InflateRect)
            #define IntersectRect   WON(IntersectRect)
            #define IsRectEmpty     WON(IsRectEmpty)
            #define OffsetRect      WON(OffsetRect)
            #define PtInRect        WON(PtInRect)
            #define SetRect         WON(SetRect)
            #define SetRectEmpty    WON(SetRectEmpty)
            #define SubtractRect    WON(SubtractRect)
        #endif
    #endif
#endif  /* ndef WON_NO_WRAP_FN */

/****************************************************************************/

#endif  /* ndef WON_USER32_H_ */
