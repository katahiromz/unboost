// tuple.hpp --- Unboost tuple
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_TUPLE_HPP_
#define UNBOOST_TUPLE_HPP_

#include <unboost/core.hpp>

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_TUPLE) + defined(UNBOOST_USE_BOOST_TUPLE)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_TUPLE
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_TUPLE
    #else
        #ifdef UNBOOST_CXX11
            #define UNBOOST_USE_CXX11_TUPLE
        #else
            #define UNBOOST_USE_BOOST_TUPLE
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_TUPLE
    #include <tuple>
    #include <functional>   // for std::ref, std::cref
    namespace unboost {
        using std::tuple;
        using std::make_tuple;
        using std::tie;
        using std::get;
        using std::tuple_size;
        using std::ref;
        using std::cref;
        using std::ignore;
        namespace tuples {
            using std::ignore;
            template <typename T>
            struct length {
                static constexpr size_t value = std::tuple_size<T>::value;
            };
        } // namespace tuples
        using std::tuple_cat;
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_TUPLE)
    #include <boost/tuple/tuple.hpp>
    #include <boost/tuple/tuple_comparison.hpp>
    #include <boost/tuple/tuple_io.hpp>
    namespace unboost {
        using boost::tuple;
        using boost::make_tuple;
        using boost::tie;
        using boost::get;
        template <typename T>
        struct tuple_size {
            static const size_t value = boost::tuples::length<T>::value;
        };
        using boost::ref;
        using boost::cref;
        using boost::tuples::ignore;
        namespace tuples {
            using boost::tuples::ignore;
            using boost::tuples::length;
        } // namespace tuples
        // NOTE: There is no boost::tuple_cat.
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_TUPLE_HPP_
