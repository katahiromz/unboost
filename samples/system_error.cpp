// system_error.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
#include <vector>
#include <string>

#ifdef CXX11
    #include <system_error>
    #include <thread>
#elif defined(BOOST)
    #include <boost/system/system_error.hpp>
    #include <boost/thread.hpp>
#else   // Unboost
    #include <unboost/system_error.hpp>
    #include <unboost/thread.hpp>
#endif  // Unboost

int main(void) {
    bool flag = false;

#ifdef CXX11
    try {
        std::thread().detach();
    } catch (const std::system_error& e) {
        flag = true;
    }
#elif defined(BOOST)
    // Boost doesn't throw
    flag = true;
#else   // Unboost
    #ifdef UNBOOST_USE_BOOST_SYSTEM
        flag = true;
    #else
        try {
            unboost::thread().detach();
        } catch (const unboost::system_error& e) {
            flag = true;
        }
    #endif
#endif  // Unboost
    assert(flag);

#ifdef CXX11
    try {
        throw std::system_error(EDOM, std::generic_category());
    } catch (const std::system_error& error) {
        std::cout << "Error: " << error.code()
                  << " - " << error.code().message() << std::endl;
    }
#elif defined(BOOST)
    try {
        throw boost::system::system_error(EDOM, boost::system::generic_category());
    } catch (const boost::system::system_error& error) {
        std::cout << "Error: " << error.code()
                  << " - " << error.code().message() << std::endl;
    }
#else   // Unboost
    try {
        throw unboost::system_error(EDOM, unboost::system::generic_category());
    } catch (const unboost::system::system_error& error) {
        std::cout << "Error: " << error.code()
                  << " - " << error.code().message() << std::endl;
    }
#endif  // Unboost

#ifdef _WIN32
#ifdef CXX11
    try {
        throw std::system_error(ERROR_INVALID_PARAMETER, std::system_category());
    } catch (const std::system_error& error) {
        std::cout << "Error: " << error.code()
                  << " - " << error.code().message() << std::endl;
    }
#elif defined(BOOST)
    try {
        throw boost::system::system_error(ERROR_INVALID_PARAMETER, boost::system::system_category());
    } catch (const boost::system::system_error& error) {
        std::cout << "Error: " << error.code()
                  << " - " << error.code().message() << std::endl;
    }
#else   // Unboost
    try {
        throw unboost::system_error(ERROR_INVALID_PARAMETER, unboost::system::system_category());
    } catch (const unboost::system::system_error& error) {
        std::cout << "Error: " << error.code()
                  << " - " << error.code().message() << std::endl;
    }
#endif  // Unboost
#endif  // def _WIN32

    std::cout << "success" << std::endl;

    return 0;
} // main
