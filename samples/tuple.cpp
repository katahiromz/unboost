// tuple.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_TUPLE
#include <unboost.hpp>
#include <cstring>  // for strcmp

template <typename TUP, size_t N>
struct TuplePrinter {
    static void print(const TUP& tup) {
        TuplePrinter<TUP, N - 1>::print(tup);
        std::cout << ", " << unboost::get<N - 1>(tup);
    }
};

template <typename TUP>
struct TuplePrinter<TUP,1> {
    static void print(const TUP& tup) {
        std::cout << unboost::get<0>(tup);
    }
};

template <typename TUP>
void print_taple(const TUP& tup) {
    const size_t count = unboost::tuple_size<TUP>::value;
    TuplePrinter<TUP, count> printer;
    printer.print(tup);
}

int main(void) {
    std::cout << "tuple" << std::endl;
    unboost::tuple<int, const char *, std::string> tup;
    tup = unboost::make_tuple<int, const char *, std::string>(2, "This is", "a test");
    print_taple(tup);
    std::cout << std::endl;
    assert(unboost::get<0>(tup) == 2);
    assert(strcmp(unboost::get<1>(tup), "This is") == 0);
    assert(unboost::get<2>(tup) == "a test");
    return 0;
}
