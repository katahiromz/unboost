// swap.hpp --- Unboost swap
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_SWAP_HPP_
#define UNBOOST_SWAP_HPP_

#include "unboost.hpp"

#include <algorithm>
#if (__cplusplus >= 201103L)
    #include <utility>
#endif

namespace unboost {
    using std::swap;
} // namespace unboost

#endif  // ndef UNBOOST_SWAP_HPP_
