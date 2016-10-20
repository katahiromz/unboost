// unboost.hpp --- Unboost by katahiromz <katayama.hirofumi.mz@gmail.com>
// This file is public domain software (PDS).
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_HPP_
#define UNBOOST_HPP_    19 // Version 19

#ifndef __cplusplus
    #error Unboost needs C++ compiler. You lose.
#endif

//////////////////////////////////////////////////////////////////////////////
// Unboost core

#include <unboost/core.hpp>

//////////////////////////////////////////////////////////////////////////////

#ifdef UNBOOST_USE_STATIC_ASSERT
    #include <unboost/static_assert.hpp>
#endif

#ifdef UNBOOST_USE_TYPE_TRAITS
    #include <unboost/type_traits.hpp>
#endif

#ifdef UNBOOST_USE_SMART_PTR
    #include <unboost/smart_ptr.hpp>
#endif

#ifdef UNBOOST_USE_ARRAY
    #include <unboost/array.hpp>
#endif

#ifdef UNBOOST_USE_REGEX
    #include <unboost/regex.hpp>
#endif

#ifdef UNBOOST_USE_CONVERSION
    #include <unboost/conversion.hpp>
#endif

#ifdef UNBOOST_USE_COMPLEX_FUNCTIONS
    #include <unboost/complex_functions.hpp>
#endif

#ifdef UNBOOST_USE_RANDOM
    #include <unboost/random.hpp>
#endif

#ifdef UNBOOST_USE_RATIO
    #include <unboost/ratio.hpp>
#endif

#ifdef UNBOOST_USE_CHRONO
    #include <unboost/chrono.hpp>
#endif

#ifdef UNBOOST_USE_THREAD
    #include <unboost/thread.hpp>
#endif

#ifdef UNBOOST_USE_MUTEX
    #include <unboost/mutex.hpp>
#endif

#ifdef UNBOOST_USE_UNORDERED_SET
    #include <unboost/unordered_set.hpp>
#endif

#ifdef UNBOOST_USE_UNORDERED_MAP
    #include <unboost/unordered_map.hpp>
#endif

#ifdef UNBOOST_USE_FOREACH
    #include <unboost/for_each.hpp>
#endif

#ifdef UNBOOST_USE_TUPLE
    #include <unboost/tuple.hpp>
#endif

#ifdef UNBOOST_USE_STRING_ALGORITHM
    #include <unboost/string_algorithm.hpp>
#endif

#ifdef UNBOOST_USE_ASSERT
    #include <unboost/assert.hpp>
#endif

#ifdef UNBOOST_USE_FILESYSTEM
    #include <unboost/filesystem.hpp>
#endif

#ifdef UNBOOST_USE_EMPLACE
    #include <unboost/emplace.hpp>
#endif

#ifdef UNBOOST_USE_SAFE_DELETE
    #include <unboost/safe_delete.hpp>
#endif

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef UNBOOST_HPP_

//////////////////////////////////////////////////////////////////////////////
