// emplace.hpp --- Unboost emplace
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_EMPLACE_HPP_
#define UNBOOST_EMPLACE_HPP_

#include "unboost.hpp"

#ifndef UNBOOST_EMPLACE
    #ifdef UNBOOST_CXX11
        #define UNBOOST_EMPLACE(type, obj, ...) \
            (obj).emplace(__VA_ARGS__)
        #define UNBOOST_EMPLACE_FRONT(type, obj, ...) \
            (obj).emplace_front(__VA_ARGS__)
        #define UNBOOST_EMPLACE_BACK(type, obj, ...) \
            (obj).emplace_back(__VA_ARGS__)
    #else
        #if defined(__BORLANDC__) && (__BORLANDC__ <= 0x0551)
            // __VA_ARGS__ is not available
        #else
            #define UNBOOST_EMPLACE(type, obj, ...) \
                (obj).insert(type(__VA_ARGS__))
            #define UNBOOST_EMPLACE_FRONT(type, obj, ...) \
                (obj).push_front(type(__VA_ARGS__))
            #define UNBOOST_EMPLACE_BACK(type, obj, ...) \
                (obj).push_back(type(__VA_ARGS__))
        #endif
    #endif
#endif

#endif  // ndef UNBOOST_EMPLACE_HPP_
