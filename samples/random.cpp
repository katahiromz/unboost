#ifdef CXX11
    #include <random>
#elif defined(BOOST)
    #include <boost/random/random_device.hpp>
    #include <boost/random.hpp>
#else   // Unboost
    #include <unboost/random/random_device.hpp>
    #include <unboost/random.hpp>
#endif

int main(void) {
    std::cout << "random" << std::endl;

#ifdef CXX11
    std::mt19937 engine;
    std::uniform_int_distribution<int> distribution(1, 6);
    for (int i = 0; i < 5; ++i) {
        std::cout << distribution(engine) << std::endl;
    }
#elif defined(BOOST)
    boost::random::mt19937 engine;
    boost::random::uniform_int_distribution<int> distribution(1, 6);
    for (int i = 0; i < 5; ++i) {
        std::cout << distribution(engine) << std::endl;
    }
#else   // Unboost
    unboost::random::mt19937 engine;
    unboost::random::uniform_int_distribution<int> distribution(1, 6);
    for (int i = 0; i < 5; ++i) {
        std::cout << distribution(engine) << std::endl;
    }
#endif  // Unboost

    return 0;
}
