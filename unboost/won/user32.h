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
        typedef struct tagPOINT {
            int x, y;
        } POINT, *PPOINT, *LPPOINT;
        typedef struct tagSIZE {
            int cx, cy;
        } SIZE, *PSIZE, *LPSIZE;
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

    inline WONUSERAPI BOOL WONAPI WON(IntersectRect)(LPRECT dest, const RECT *src1, const RECT *src2)
    {
#ifndef WON_SPEED
        assert(dest);
        assert(src1);
        assert(src2);
        if (dest == NULL || src1 == NULL || src2 == NULL)
            return FALSE;
#endif

        if (WON(IsRectEmpty)(src1) || WON(IsRectEmpty)(src2) ||
            src1->left >= src2->right || src2->left >= src1->right ||
            src1->top >= src2->bottom || src2->top >= src1->bottom)
        {
            WON(SetRectEmpty)(dest);
            return FALSE;
        }

        dest->left = max(src1->left, src2->left);
        dest->right = min(src1->right, src2->right);
        dest->top = max(src1->top, src2->top);
        dest->bottom = min(src1->bottom, src2->bottom);
        return TRUE;
    }

    inline WONUSERAPI BOOL WONAPI WON(SubtractRect)(LPRECT dest, const RECT *src1, const RECT *src2)
    {
        RECT TempRect;

#ifndef WON_SPEED
        assert(dest);
        assert(src1);
        assert(src2);
        if (dest == NULL || src1 == NULL || src2 == NULL)
            return FALSE;
#endif

        if (!WON(IntersectRect)(&TempRect, src1, src2))
        {
            *dest = *src1;
            return TRUE;
        }

        if (WON(EqualRect)(&TempRect, src1))
        {
            WON(SetRectEmpty)(dest);
            return FALSE;
        }

        *dest = *src1;

        if (dest->top == TempRect.top && dest->bottom == TempRect.bottom)
        {
            if (dest->left == TempRect.left)
                dest->left = TempRect.right;
            else if (dest->right == TempRect.right)
                dest->right = TempRect.left;
        }
        else if (dest->left == TempRect.left && dest->right == TempRect.right)
        {
            if (dest->top == TempRect.top)
                dest->top = TempRect.bottom;
            else if (dest->bottom == TempRect.bottom)
                dest->bottom = TempRect.top;
        }

        return TRUE;
    }

    inline WONUSERAPI BOOL WONAPI WON(UnionRect)(LPRECT dest, const RECT *src1, const RECT *src2)
    {
#ifndef WON_SPEED
        assert(dest);
        assert(src1);
        assert(src2);
        if (dest == NULL || src1 == NULL || src2 == NULL)
            return FALSE;
#endif

        if (WON(IsRectEmpty)(src1))
        {
            if (WON(IsRectEmpty)(src2))
            {
                WON(SetRectEmpty)(dest);
                return FALSE;
            }
            else
            {
                *dest = *src2;
            }
        }
        else
        {
            if (WON(IsRectEmpty)(src2))
            {
                *dest = *src1;
            }
            else
            {
                dest->left = min(src1->left, src2->left);
                dest->top = min(src1->top, src2->top);
                dest->right = max(src1->right, src2->right);
                dest->bottom = max(src1->bottom, src2->bottom);
            }
        }

        return TRUE;
    }

#endif  /* def WONUSERAPI */

/****************************************************************************/

#ifdef __cplusplus
} // namespace won
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
            #define UnionRect       won::WON(UnionRect)
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
            #define UnionRect       WON(UnionRect)
        #endif
    #endif
#endif  /* ndef WON_NO_WRAP_FN */

/****************************************************************************/

#endif  /* ndef WON_USER32_H_ */
