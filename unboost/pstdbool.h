/* pstdbool.h --- portable stdbool.h */
/* Written by katahiromz <katayama.hirofumi.mz@gmail.com>. */
/* You can use this as replacement of <stdbool.h> and <cstdbool>. */
/* This file is public domain software (PDS). */

#ifndef KATAHIROMZ_PSTDBOOL
#define KATAHIROMZ_PSTDBOOL     0   /* Version 0 */

#ifndef __bool_true_false_are_defined
    #ifdef __cplusplus
        /* already defined */
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
        #include <stdbool.h>
    #else
        #define true        1
        #define false       0
        typedef char        bool;
    #endif
    #define __bool_true_false_are_defined 1
#endif  /* ndef __bool_true_false_are_defined */

#endif  /* ndef KATAHIROMZ_PSTDBOOL */
