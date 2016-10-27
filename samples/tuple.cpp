// tuple.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <tuple>
#elif defined(BOOST)
    #include <boost/tuple.hpp>
#else   // Unboost
    #include <unboost/tuple.hpp>
#endif

#include <cstring>  // for strcmp

#ifdef CXX11
    template <typename TUP, size_t N>
    struct TuplePrinter {
        static void print(const TUP& tup) {
            TuplePrinter<TUP, N - 1>::print(tup);
            std::cout << ", " << std::get<N - 1>(tup);
        }
    };

    template <typename TUP>
    struct TuplePrinter<TUP,1> {
        static void print(const TUP& tup) {
            std::cout << std::get<0>(tup);
        }
    };

    template <typename TUP>
    void print_taple(const TUP& tup) {
        const size_t count = std::tuple_size<TUP>::value;
        TuplePrinter<TUP, count> printer;
        printer.print(tup);
    }
#elif defined(BOOST)
    template <typename TUP, size_t N>
    struct TuplePrinter {
        static void print(const TUP& tup) {
            TuplePrinter<TUP, N - 1>::print(tup);
            std::cout << ", " << boost::get<N - 1>(tup);
        }
    };

    template <typename TUP>
    struct TuplePrinter<TUP,1> {
        static void print(const TUP& tup) {
            std::cout << boost::get<0>(tup);
        }
    };

    template <typename TUP>
    void print_taple(const TUP& tup) {
        const size_t count = boost::tuple_size<TUP>::value;
        TuplePrinter<TUP, count> printer;
        printer.print(tup);
    }
#else   // Unboost
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
#endif  // Unboost

int main(void) {
    std::cout << "tuple" << std::endl;

#ifdef CXX11
    std::tuple<int, const char *, std::string> tup;
    tup = std::make_tuple<int, const char *, std::string>(2, "This is", "a test");
    print_taple(tup);
    std::cout << std::endl;
    assert(std::get<0>(tup) == 2);
    assert(strcmp(std::get<1>(tup), "This is") == 0);
    assert(std::get<2>(tup) == "a test");
#elif defined(BOOST)
    boost::tuple<int, const char *, std::string> tup;
    tup = boost::make_tuple<int, const char *, std::string>(2, "This is", "a test");
    print_taple(tup);
    std::cout << std::endl;
    assert(boost::get<0>(tup) == 2);
    assert(strcmp(boost::get<1>(tup), "This is") == 0);
    assert(boost::get<2>(tup) == "a test");
#else   // Unboost
    unboost::tuple<int, const char *, std::string> tup;
    tup = unboost::make_tuple<int, const char *, std::string>(2, "This is", "a test");
    print_taple(tup);
    std::cout << std::endl;
    assert(unboost::get<0>(tup) == 2);
    assert(strcmp(unboost::get<1>(tup), "This is") == 0);
    assert(unboost::get<2>(tup) == "a test");
#endif  // Unboost

    std::cout << "success" << std::endl;
    return 0;
} // main
