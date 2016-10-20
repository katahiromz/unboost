// unordered_map.hpp --- Unboost unordered_map and unordered_multimap
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_UNORDERED_MAP_HPP_
#define UNBOOST_UNORDERED_MAP_HPP_

#include <unboost/core.hpp>

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_UNORDERED_MAP) + defined(UNBOOST_USE_TR1_UNORDERED_MAP) + defined(UNBOOST_USE_BOOST_UNORDERED_MAP)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_UNORDERED_MAP
    #elif defined(UNBOOST_USE_TR1)
        #define UNBOOST_USE_TR1_UNORDERED_MAP
    #else
        #if defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #define UNBOOST_USE_CXX11_UNORDERED_MAP
            #elif (_MSC_VER >= 1500)
                // Visual C++ 2008
                #define UNBOOST_USE_TR1_UNORDERED_MAP
            #else
                #define UNBOOST_USE_BOOST_UNORDERED_MAP
            #endif
        #elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
            // GCC 4.3 and later
            #define UNBOOST_USE_TR1_UNORDERED_MAP
        #else
            #define UNBOOST_USE_BOOST_UNORDERED_MAP
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_UNORDERED_MAP
    #include <unordered_map>            // for std::unordered_map, ...
    namespace unboost {
        using std::unordered_map;
        using std::unordered_multimap;
    }
#elif defined(UNBOOST_USE_TR1_UNORDERED_MAP)
    #ifdef _MSC_VER
        #include <unordered_map>        // for std::tr1::unordered_map, ...
    #else
        #include <tr1/unordered_map>    // for std::tr1::unordered_map, ...
    #endif
    namespace unboost {
        using std::tr1::unordered_map;
        using std::tr1::unordered_multimap;
    }
#elif defined(UNBOOST_USE_BOOST_UNORDERED_MAP)
    #include <boost/unordered_map.hpp>  // for boost::unordered_map, ...
    namespace unboost {
        using boost::unordered_map;
        using boost::unordered_multimap;
    }
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_UNORDERED_MAP_HPP_
