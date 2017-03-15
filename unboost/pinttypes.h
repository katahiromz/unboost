/* pinttypes.h by katahiromz */
/* This file is public domain software (PDS). */
#ifndef UNBOOST_PINTTYPES_H_
#define UNBOOST_PINTTYPES_H_    1   /* Version 1 */

#include "unboost.h"

#ifdef __cplusplus
#include <cctype>
namespace unboost {
#else
#include <ctype.h>
#endif

    typedef _int64_t intmax_t;
    typedef _uint64_t uintmax_t;
    typedef struct imaxdiv_t {
        intmax_t quot;
        intmax_t rem;
    } imaxdiv_t;

#ifdef __cplusplus
} // namespace unboost
#endif

#if defined(__STDC_FORMAT_MACROS)
#define PRId8 "d"
#define PRId16 "d"
#define PRId32 "d"
#define PRId64 "I64d"

#define PRIdLEAST8 "d"
#define PRIdLEAST16 "d"
#define PRIdLEAST32 "d"
#define PRIdLEAST64 "I64d"

#define PRIdFAST8 "d"
#define PRIdFAST16 "d"
#define PRIdFAST32 "d"
#define PRIdFAST64 "I64d"

#define PRIdMAX "I64d"

#define PRIi8 "i"
#define PRIi16 "i"
#define PRIi32 "i"
#define PRIi64 "I64i"

#define PRIiLEAST8 "i"
#define PRIiLEAST16 "i"
#define PRIiLEAST32 "i"
#define PRIiLEAST64 "I64i"

#define PRIiFAST8 "i"
#define PRIiFAST16 "i"
#define PRIiFAST32 "i"
#define PRIiFAST64 "I64i"

#define PRIiMAX "I64i"

#define PRIo8 "o"
#define PRIo16 "o"
#define PRIo32 "o"
#define PRIo64 "I64o"

#define PRIoLEAST8 "o"
#define PRIoLEAST16 "o"
#define PRIoLEAST32 "o"
#define PRIoLEAST64 "I64o"

#define PRIoFAST8 "o"
#define PRIoFAST16 "o"
#define PRIoFAST32 "o"
#define PRIoFAST64 "I64o"

#define PRIoMAX "I64o"

#define PRIu8 "u"
#define PRIu16 "u"
#define PRIu32 "u"
#define PRIu64 "I64u"

#define PRIuLEAST8 "u"
#define PRIuLEAST16 "u"
#define PRIuLEAST32 "u"
#define PRIuLEAST64 "I64u"

#define PRIuFAST8 "u"
#define PRIuFAST16 "u"
#define PRIuFAST32 "u"
#define PRIuFAST64 "I64u"

#define PRIuMAX "I64u"

#define PRIx8 "x"
#define PRIx16 "x"
#define PRIx32 "x"
#define PRIx64 "I64x"

#define PRIxLEAST8 "x"
#define PRIxLEAST16 "x"
#define PRIxLEAST32 "x"
#define PRIxLEAST64 "I64x"

#define PRIxFAST8 "x"
#define PRIxFAST16 "x"
#define PRIxFAST32 "x"
#define PRIxFAST64 "I64x"

#define PRIxMAX "I64x"

#define PRIX8 "X"
#define PRIX16 "X"
#define PRIX32 "X"
#define PRIX64 "I64X"

#define PRIXLEAST8 "X"
#define PRIXLEAST16 "X"
#define PRIXLEAST32 "X"
#define PRIXLEAST64 "I64X"

#define PRIXFAST8 "X"
#define PRIXFAST16 "X"
#define PRIXFAST32 "X"
#define PRIXFAST64 "I64X"

#define PRIXMAX "I64X"

#define SCNd16 "hd"
#define SCNd32 "d"
#define SCNd64 "I64d"

#define SCNdLEAST16 "hd"
#define SCNdLEAST32 "d"
#define SCNdLEAST64 "I64d"

#define SCNdFAST16 "hd"
#define SCNdFAST32 "d"
#define SCNdFAST64 "I64d"

#define SCNdMAX "I64d"

#define SCNi16 "hi"
#define SCNi32 "i"
#define SCNi64 "I64i"

#define SCNiLEAST16 "hi"
#define SCNiLEAST32 "i"
#define SCNiLEAST64 "I64i"

#define SCNiFAST16 "hi"
#define SCNiFAST32 "i"
#define SCNiFAST64 "I64i"

#define SCNiMAX "I64i"

#define SCNo16 "ho"
#define SCNo32 "o"
#define SCNo64 "I64o"

#define SCNoLEAST16 "ho"
#define SCNoLEAST32 "o"
#define SCNoLEAST64 "I64o"

#define SCNoFAST16 "ho"
#define SCNoFAST32 "o"
#define SCNoFAST64 "I64o"

#define SCNoMAX "I64o"

#define SCNx16 "hx"
#define SCNx32 "x"
#define SCNx64 "I64x"

#define SCNxLEAST16 "hx"
#define SCNxLEAST32 "x"
#define SCNxLEAST64 "I64x"

#define SCNxFAST16 "hx"
#define SCNxFAST32 "x"
#define SCNxFAST64 "I64x"

#define SCNxMAX "I64x"

#define SCNu16 "hu"
#define SCNu32 "u"
#define SCNu64 "I64u"

#define SCNuLEAST16 "hu"
#define SCNuLEAST32 "u"
#define SCNuLEAST64 "I64u"

#define SCNuFAST16 "hu"
#define SCNuFAST32 "u"
#define SCNuFAST64 "I64u"

#define SCNuMAX "I64u"

#ifdef _WIN64
    #define PRIdPTR "I64d"
    #define PRIiPTR "I64i"
    #define PRIoPTR "I64o"
    #define PRIuPTR "I64u"
    #define PRIxPTR "I64x"
    #define PRIXPTR "I64X"
    #define SCNdPTR "I64d"
    #define SCNiPTR "I64i"
    #define SCNoPTR "I64o"
    #define SCNxPTR "I64x"
    #define SCNuPTR "I64u"
#else
    #define PRIdPTR "d"
    #define PRIiPTR "i"
    #define PRIoPTR "o"
    #define PRIuPTR "u"
    #define PRIxPTR "x"
    #define PRIXPTR "X"
    #define SCNdPTR "d"
    #define SCNiPTR "i"
    #define SCNoPTR "o"
    #define SCNxPTR "x"
    #define SCNuPTR "u"
#endif

#if (defined(__cplusplus) && __cplusplus >= 201103L) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#undef PRId64
#undef PRIdLEAST64
#undef PRIdFAST64
#undef PRIdMAX
#undef PRIi64
#undef PRIiLEAST64
#undef PRIiFAST64
#undef PRIiMAX
#undef PRIo64
#undef PRIoLEAST64
#undef PRIoFAST64
#undef PRIoMAX
#undef PRIu64
#undef PRIuLEAST64
#undef PRIuFAST64
#undef PRIuMAX
#undef PRIx64
#undef PRIxLEAST64
#undef PRIxFAST64
#undef PRIxMAX
#undef PRIX64
#undef PRIXLEAST64
#undef PRIXFAST64
#undef PRIXMAX
#undef SCNd64
#undef SCNdLEAST64
#undef SCNdFAST64
#undef SCNdMAX
#undef SCNi64
#undef SCNiLEAST64
#undef SCNiFAST64
#undef SCNiMAX
#undef SCNo64
#undef SCNoLEAST64
#undef SCNoFAST64
#undef SCNoMAX
#undef SCNx64
#undef SCNxLEAST64
#undef SCNxFAST64
#undef SCNxMAX
#undef SCNu64
#undef SCNuLEAST64
#undef SCNuFAST64
#undef SCNuMAX
#define PRId64 "lld"
#define PRIdLEAST64 "lld"
#define PRIdFAST64 "lld"
#define PRIdMAX "lld"
#define PRIi64 "lli"
#define PRIiLEAST64 "lli"
#define PRIiFAST64 "lli"
#define PRIiMAX "lli"
#define PRIo64 "llo"
#define PRIoLEAST64 "llo"
#define PRIoFAST64 "llo"
#define PRIoMAX "llo"
#define PRIu64 "llu"
#define PRIuLEAST64 "llu"
#define PRIuFAST64 "llu"
#define PRIuMAX "llu"
#define PRIx64 "llx"
#define PRIxLEAST64 "llx"
#define PRIxFAST64 "llx"
#define PRIxMAX "llx"
#define PRIX64 "llX"
#define PRIXLEAST64 "llX"
#define PRIXFAST64 "llX"
#define PRIXMAX "llX"
#define SCNd64 "lld"
#define SCNdLEAST64 "lld"
#define SCNdFAST64 "lld"
#define SCNdMAX "lld"
#define SCNi64 "lli"
#define SCNiLEAST64 "lli"
#define SCNiFAST64 "lli"
#define SCNiMAX "lli"
#define SCNo64 "llo"
#define SCNoLEAST64 "llo"
#define SCNoFAST64 "llo"
#define SCNoMAX "llo"
#define SCNx64 "llx"
#define SCNxLEAST64 "llx"
#define SCNxFAST64 "llx"
#define SCNxMAX "llx"
#define SCNu64 "llu"
#define SCNuLEAST64 "llu"
#define SCNuFAST64 "llu"
#define SCNuMAX "llu"
#ifdef _WIN64
    #undef PRIdPTR
    #undef PRIiPTR
    #undef PRIoPTR
    #undef PRIuPTR
    #undef PRIxPTR
    #undef PRIXPTR
    #undef SCNdPTR
    #undef SCNiPTR
    #undef SCNoPTR
    #undef SCNxPTR
    #undef SCNuPTR
    #define PRIdPTR "lld"
    #define PRIiPTR "lli"
    #define PRIoPTR "llo"
    #define PRIuPTR "llu"
    #define PRIxPTR "llx"
    #define PRIXPTR "llX"
    #define SCNdPTR "lld"
    #define SCNiPTR "lli"
    #define SCNoPTR "llo"
    #define SCNxPTR "llx"
    #define SCNuPTR "llu"
#endif

#endif  /* defined(__STDC_FORMAT_MACROS) */

#ifdef __cplusplus
namespace unboost {
#endif

inline intmax_t imaxabs(intmax_t i)
{
    return ((i >= 0) ? i : -i);
}

inline imaxdiv_t imaxdiv(intmax_t num, intmax_t den)
{
    imaxdiv_t ret;
    ret.quot = num / den;
    ret.rem = num % den;
    return ret;
}

inline int _ch2num(char ch)
{
    using namespace std;
    if (isdigit(ch))
        return ch - '0';
    if (islower(ch))
        return ch + (10 - 'a');
    if (isupper(ch))
        return ch + (10 - 'A');
    return -1;
}

inline int _wch2num(wchar_t ch)
{
    using namespace std;
    if (iswdigit(ch))
        return ch - '0';
    if (iswlower(ch))
        return ch + (10 - 'a');
    if (iswupper(ch))
        return ch + (10 - 'A');
    return -1;
}

inline intmax_t
strtoimax(const char *nptr, char **endptr, int base)
{
    using namespace std;
    intmax_t ret = 0;
    int num;
    bool sign = false;

    while (isspace(*nptr))
        ++nptr;

    if (*nptr == '-')
    {
        ++nptr;
        sign = true;
    }
    else if (*nptr == '+')
    {
        ++nptr;
    }

    if (*nptr == '0')
    {
        ++nptr;
        if (*nptr == 'x' || *nptr == 'X')
        {
            ++nptr;
            if (base == 0)
                base = 16;
        }
        else
        {
            if (base == 0)
                base = 8;
        }
    }

    while (isdigit(*nptr))
    {
        ret *= base;
        num = _ch2num(*nptr);
        if (num != -1)
            ret += num;
        else
            break;
    }
    if (endptr)
        *endptr = (char *)nptr;
    return (sign ? -ret : ret);
}

inline uintmax_t
strtoumax(const char *nptr, char **endptr, int base)
{
    using namespace std;
    uintmax_t ret = 0;
    int num;
    bool sign = false;

    while (isspace(*nptr))
        ++nptr;

    if (*nptr == '0')
    {
        ++nptr;
        if (*nptr == 'x' || *nptr == 'X')
        {
            ++nptr;
            if (base == 0)
                base = 16;
        }
        else
        {
            if (base == 0)
                base = 8;
        }
    }

    while (isdigit(*nptr))
    {
        ret *= base;
        num = _ch2num(*nptr);
        if (num != -1)
            ret += (unsigned)num;
        else
            break;
    }
    if (endptr)
        *endptr = (char *)nptr;
    return (sign ? -ret : ret);
}

inline intmax_t
wcstoimax(const wchar_t *nptr, wchar_t **endptr, int base)
{
    using namespace std;
    intmax_t ret = 0;
    int num;
    bool sign = false;

    while (iswspace(*nptr))
        ++nptr;

    if (*nptr == L'-')
    {
        ++nptr;
        sign = true;
    }
    else if (*nptr == L'+')
    {
        ++nptr;
    }

    if (*nptr == L'0')
    {
        ++nptr;
        if (*nptr == L'x' || *nptr == L'X')
        {
            ++nptr;
            if (base == 0)
                base = 16;
        }
        else
        {
            if (base == 0)
                base = 8;
        }
    }

    while (iswdigit(*nptr))
    {
        ret *= base;
        num = _wch2num(*nptr);
        if (num != -1)
            ret += num;
        else
            break;
    }
    if (endptr)
        *endptr = (wchar_t *)nptr;
    return (sign ? -ret : ret);
}

inline uintmax_t
wcstoumax(const wchar_t *nptr, wchar_t **endptr, int base)
{
    using namespace std;
    uintmax_t ret = 0;
    int num;
    bool sign = false;

    while (iswspace(*nptr))
        ++nptr;

    if (*nptr == L'0')
    {
        ++nptr;
        if (*nptr == L'x' || *nptr == L'X')
        {
            ++nptr;
            if (base == 0)
                base = 16;
        }
        else
        {
            if (base == 0)
                base = 8;
        }
    }

    while (iswdigit(*nptr))
    {
        ret *= base;
        num = _wch2num(*nptr);
        if (num != -1)
            ret += (unsigned)num;
        else
            break;
    }
    if (endptr)
        *endptr = (wchar_t *)nptr;
    return (sign ? -ret : ret);
}

#ifdef __cplusplus
} // namespace unboost
#endif

#endif  /* ndef UNBOOST_PINTTYPES_H_ */
