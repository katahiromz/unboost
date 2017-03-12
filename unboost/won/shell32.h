/* Won shell32 */
/****************************************************************************/

#ifndef WON_SHELL32_H_
#define WON_SHELL32_H_

#include "won.h"

#ifndef _WON32
    #error Windows only
#endif

#include <shlobj.h>
#include <shlwapi.h>
#include <objidl.h>         /* for IStream_... */

/****************************************************************************/

#ifndef WONSHELLAPI_2K
    #if defined(WON_OLD_COMPILER) || (_WIN32_IE >= 0x0500) && (_WON32_IE < 0x0500)
        #define WONSHELLAPI_2K      /* 2K runtime */
    #endif
#endif

#ifndef WONSHELLAPI_XP
    #if defined(WON_OLD_COMPILER) || (_WIN32_IE >= 0x0501) && (_WON32_IE < 0x0501)
        #define WONSHELLAPI_XP      /* XP runtime */
    #endif
#endif

#ifndef WON_TYPED_ITEMIDS
    #ifdef WON_OLD_COMPILER
        #define WON_TYPED_ITEMIDS   /* Vista+ compiler */
    #endif
#endif

/****************************************************************************/

#ifdef WON_TYPED_ITEMIDS
    #if defined(STRICT_TYPED_ITEMIDS) && defined(__cplusplus)
        #include <pshpack1.h>
        typedef struct _ITEMIDLIST_RELATIVE : ITEMIDLIST { } ITEMIDLIST_RELATIVE;
        typedef struct _ITEMIDLIST_ABSOLUTE : ITEMIDLIST_RELATIVE { } ITEMIDLIST_ABSOLUTE;
        typedef struct _ITEMID_CHILD : ITEMIDLIST_RELATIVE { } ITEMID_CHILD;
        #include <poppack.h>
    #else
        typedef ITEMIDLIST ITEMIDLIST_RELATIVE;
        typedef ITEMIDLIST ITEMIDLIST_ABSOLUTE;
        typedef ITEMIDLIST ITEMID_CHILD;
    #endif
    #if defined(STRICT_TYPED_ITEMIDS) && defined(__cplusplus)
        typedef       ITEMIDLIST_ABSOLUTE * PIDLIST_ABSOLUTE;
        typedef const ITEMIDLIST_ABSOLUTE * PCIDLIST_ABSOLUTE;
        typedef const ITEMIDLIST_ABSOLUTE * PCUIDLIST_ABSOLUTE;
        typedef       ITEMIDLIST_RELATIVE * PIDLIST_RELATIVE;
        typedef const ITEMIDLIST_RELATIVE * PCIDLIST_RELATIVE;
        typedef       ITEMIDLIST_RELATIVE * PUIDLIST_RELATIVE;
        typedef const ITEMIDLIST_RELATIVE * PCUIDLIST_RELATIVE;
        typedef       ITEMID_CHILD *        PITEMID_CHILD;
        typedef const ITEMID_CHILD *        PCITEMID_CHILD;
        typedef       ITEMID_CHILD *        PUITEMID_CHILD;
        typedef const ITEMID_CHILD *        PCUITEMID_CHILD;
        typedef const PCUITEMID_CHILD *     PCUITEMID_CHILD_ARRAY;
        typedef const PCUIDLIST_RELATIVE *  PCUIDLIST_RELATIVE_ARRAY;
        typedef const PCIDLIST_ABSOLUTE *   PCIDLIST_ABSOLUTE_ARRAY;
        typedef const PCUIDLIST_ABSOLUTE *  PCUIDLIST_ABSOLUTE_ARRAY;
    #else
        #define PIDLIST_ABSOLUTE            LPITEMIDLIST
        #define PCIDLIST_ABSOLUTE           LPCITEMIDLIST
        #define PCUIDLIST_ABSOLUTE          LPCITEMIDLIST
        #define PIDLIST_RELATIVE            LPITEMIDLIST
        #define PCIDLIST_RELATIVE           LPCITEMIDLIST
        #define PUIDLIST_RELATIVE           LPITEMIDLIST
        #define PCUIDLIST_RELATIVE          LPCITEMIDLIST
        #define PITEMID_CHILD               LPITEMIDLIST
        #define PCITEMID_CHILD              LPCITEMIDLIST
        #define PUITEMID_CHILD              LPITEMIDLIST
        #define PCUITEMID_CHILD             LPCITEMIDLIST
        #define PCUITEMID_CHILD_ARRAY       LPCITEMIDLIST *
        #define PCUIDLIST_RELATIVE_ARRAY    LPCITEMIDLIST *
        #define PCIDLIST_ABSOLUTE_ARRAY     LPCITEMIDLIST *
        #define PCUIDLIST_ABSOLUTE_ARRAY    LPCITEMIDLIST *
    #endif
#endif  /* def WON_TYPED_ITEMIDS */

#ifdef __cplusplus
namespace won {
#endif

/****************************************************************************/

#ifdef WONSHELLAPI_2K
    inline WONSHELLAPI_2K void * WONAPI WON(SHAlloc)(SIZE_T cb)
    {
        return CoTaskMemAlloc(cb);
    }

    inline WONSHELLAPI_2K void WONAPI WON(SHFree)(void *pv)
    {
        CoTaskMemFree(pv);
    }
#endif

#ifdef WONSHELLAPI_XP
    inline WONSHELLAPI_XP void WONAPI WON(ILFree)(LPITEMIDLIST pidl)
    {
        CoTaskMemFree(pidl);
    }

    inline WONSHELLAPI_XP UINT WONAPI WON(ILGetSize)(LPCITEMIDLIST pidl)
    {
        LPCSHITEMID si;
        UINT len = 0;

        if (pidl)
        {
            si = &(pidl->mkid);

            while (si->cb)
            {
                len += si->cb;
                si  = (LPCSHITEMID)(((const BYTE*)si)+si->cb);
            }
            len += 2;
        }
        return len;
    }

    inline WONSHELLAPI_XP LPITEMIDLIST WONAPI WON(ILGetNext)(LPCITEMIDLIST pidl)
    {
        WORD len;

        if (pidl)
        {
            len =  pidl->mkid.cb;
            if (len)
            {
                pidl = (LPCITEMIDLIST)(((const BYTE *)pidl) + len);
                return (LPITEMIDLIST)pidl;
            }
        }
        return NULL;
    }

    inline WONSHELLAPI_XP LPITEMIDLIST WONAPI WON(ILClone)(LPCITEMIDLIST pidl)
    {
        LPITEMIDLIST    pidlNew;
        DWORD           len;

        if (pidl == NULL)
            return NULL;

        len = WON(ILGetSize)(pidl);
        pidlNew = (LPITEMIDLIST)CoTaskMemAlloc(len);
        if (pidlNew)
            CopyMemory(pidlNew, pidl, len);

        return pidlNew;
    }

    inline WONSHELLAPI_XP LPITEMIDLIST WONAPI WON(ILCloneFirst)(LPCITEMIDLIST pidl)
    {
        DWORD len;
        LPITEMIDLIST pidlNew = NULL;

        if (pidl)
        {
            len = pidl->mkid.cb;
            pidlNew = (LPITEMIDLIST)CoTaskMemAlloc(len + 2);
            if (pidlNew)
            {
                CopyMemory(pidlNew, pidl, len + 2);

                if (len)
                    WON(ILGetNext)(pidlNew)->mkid.cb = 0x00;
            }
        }

        return pidlNew;
    }

    inline WONSHELLAPI_XP LPITEMIDLIST WONAPI WON(ILCombine)(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
    {
        DWORD           len1, len2;
        LPITEMIDLIST    pidlNew;

        if (!pidl1 && !pidl2)
            return NULL;

        if (!pidl1)
        {
            pidlNew = WON(ILClone)(pidl2);
            return pidlNew;
        }

        if (!pidl2)
        {
            pidlNew = WON(ILClone)(pidl1);
            return pidlNew;
        }

        len1  = WON(ILGetSize)(pidl1) - 2;
        len2  = WON(ILGetSize)(pidl2);
        pidlNew = (LPITEMIDLIST)CoTaskMemAlloc(len1 + len2);
        if (pidlNew)
        {
            CopyMemory(pidlNew, pidl1, len1);
            CopyMemory(((LPBYTE)pidlNew) + len1, pidl2, len2);
        }

        return pidlNew;
    }

    inline WONSHELLAPI_XP LPITEMIDLIST WONAPI WON(ILAppendID)(LPITEMIDLIST pidl, LPCSHITEMID item, BOOL bEnd)
    {
        LPITEMIDLIST idlRet;
        LPCITEMIDLIST itemid = (LPCITEMIDLIST)item;

        if (!pidl || !pidl->mkid.cb)
        {
            idlRet = WON(ILClone)(itemid);
            CoTaskMemFree(pidl);
            return idlRet;
        }

        if (bEnd)
            idlRet = WON(ILCombine)(pidl, itemid);
        else
            idlRet = WON(ILCombine)(itemid, pidl);

        CoTaskMemFree(pidl);
        return idlRet;
    }

    inline WONSHELLAPI_XP LPITEMIDLIST WONAPI WON(ILFindLastID)(LPCITEMIDLIST pidl)
    {
        LPCITEMIDLIST   pidlLast = pidl;

        if (!pidl)
            return NULL;

        while (pidl->mkid.cb)
        {
            pidlLast = pidl;
            pidl = WON(ILGetNext)(pidl);
        }
        return (LPITEMIDLIST)pidlLast;
    }

    inline WONSHELLAPI_XP BOOL WONAPI WON(ILRemoveLastID)(LPITEMIDLIST pidl)
    {
        if (!pidl || !pidl->mkid.cb)
            return FALSE;
        WON(ILFindLastID)(pidl)->mkid.cb = 0;
        return TRUE;
    }

    inline WONSHELLAPI_XP HRESULT WONAPI WON(ILLoadFromStream)(IStream *pStream, LPITEMIDLIST *ppPidl)
    {
        WORD        wLen = 0;
        DWORD       dwBytesRead;
        HRESULT     ret = E_FAIL;

        CoTaskMemFree(*ppPidl);
        *ppPidl = NULL;

        IStream_AddRef(pStream);

        if (SUCCEEDED(IStream_Read(pStream, &wLen, 2, &dwBytesRead)))
        {
            if (wLen != 0)
            {
                *ppPidl = (LPITEMIDLIST)CoTaskMemAlloc(wLen);
                if (SUCCEEDED(IStream_Read(pStream, *ppPidl , wLen, &dwBytesRead)))
                {
                    ret = S_OK;
                }
                else
                {
                    CoTaskMemFree(*ppPidl);
                    *ppPidl = NULL;
                }
            }
            else
            {
                *ppPidl = NULL;
                ret = S_OK;
            }
        }

        if (*ppPidl)
        {
            CoTaskMemFree(*ppPidl);
            *ppPidl = NULL;
        }

        IStream_Release(pStream);
        return ret;
    }

    inline WONSHELLAPI_XP HRESULT WONAPI WON(ILSaveToStream)(IStream *pStream, LPCITEMIDLIST pPidl)
    {
        WORD        wLen = 0;
        HRESULT     ret = E_FAIL;

        IStream_AddRef(pStream);

        wLen = WON(ILGetSize)(pPidl);
        if (SUCCEEDED(IStream_Write(pStream, &wLen, 2, NULL)))
        {
            if (SUCCEEDED(IStream_Write(pStream, pPidl, wLen, NULL)))
                ret = S_OK;
        }
        IStream_Release(pStream);

        return ret;
    }

#endif

/****************************************************************************/

#ifdef __cplusplus
} // namespace won
#endif

#ifndef WON_NO_WRAP_FN
    #ifdef WONSHELLAPI_2K
        #ifdef __cplusplus
            #define SHAlloc             won::WON(SHAlloc)
            #define SHFree              won::WON(SHFree)
        #else
            #define SHAlloc             WON(SHAlloc)
            #define SHFree              WON(SHFree)
        #endif
    #endif
    #ifdef WONSHELLAPI_XP
        #ifdef __cplusplus
            #define ILAppendID          won::WON(ILAppendID)
            #define ILClone             won::WON(ILClone)
            #define ILCloneFirst        won::WON(ILCloneFirst)
            #define ILCombine           won::WON(ILCombine)
            #define ILFindLastID        won::WON(ILFindLastID)
            #define ILFree              won::WON(ILFree)
            #define ILGetNext           won::WON(ILGetNext)
            #define ILGetSize           won::WON(ILGetSize)
            #define ILLoadFromStream    won::WON(ILLoadFromStream)
            #define ILRemoveLastID      won::WON(ILRemoveLastID)
            #define ILSaveToStream      won::WON(ILSaveToStream)
        #else
            #define ILAppendID          WON(ILAppendID)
            #define ILClone             WON(ILClone)
            #define ILCloneFirst        WON(ILCloneFirst)
            #define ILCombine           WON(ILCombine)
            #define ILFindLastID        WON(ILFindLastID)
            #define ILFree              WON(ILFree)
            #define ILGetNext           WON(ILGetNext)
            #define ILGetSize           WON(ILGetSize)
            #define ILLoadFromStream    WON(ILLoadFromStream)
            #define ILRemoveLastID      WON(ILRemoveLastID)
            #define ILSaveToStream      WON(ILSaveToStream)
        #endif
    #endif
    #ifndef IID_PPV_ARGS
        #define IID_PPV_ARGS    ERROR_You_should_rewrite_IID_PPV_ARGS
        /* e.g. Rewrite "IID_PPV_ARGS(pShellFolder)"
                 as "IID_IShellFolder, (void **)&pShellFolder". */
    #endif
#endif  /* ndef WON_NO_WRAP_FN */

/****************************************************************************/

#endif  /* ndef WON_SHELL32_H_ */
