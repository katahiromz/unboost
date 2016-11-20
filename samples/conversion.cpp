// conversion.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <string>
#elif defined(BOOST)
    #include <boost/exception/to_string.hpp>
#else
    #include <unboost/exception/to_string.hpp>
#endif

int main(void) {
    std::cout << "conversion" << std::endl;

#ifdef CXX11
    assert(std::to_string(2016) == "2016");
    assert(std::to_string(0x7FFFFFFFFFFFFFFF) == "9223372036854775807");
    assert(std::to_string((float)1) == "1.000000");
    assert(std::to_string((double)1) == "1.000000");
    assert(std::to_string((long double)1) == "1.000000");

    assert(std::to_wstring(2016) == L"2016");
    assert(std::to_wstring(0x7FFFFFFFFFFFFFFF) == L"9223372036854775807");
    assert(std::to_wstring((float)1) == L"1.000000");
    assert(std::to_wstring((double)1) == L"1.000000");
    assert(std::to_wstring((long double)1) == L"1.000000");
#elif defined(BOOST)
    assert(boost::to_string(2016) == "2016");
    assert(boost::to_string(0x7FFFFFFFFFFFFFFF) == "9223372036854775807");
    assert(boost::to_string((float)1) == "1");
    assert(boost::to_string((double)1) == "1");
    assert(boost::to_string((long double)1) == "1");

    // NOTE: to_wstring is not supported in Boost
    //assert(boost::to_wstring(2016) == L"2016");
    //assert(boost::to_wstring(0x7FFFFFFFFFFFFFFF) == L"9223372036854775807");
    //assert(boost::to_wstring((float)1) == L"1.000000");
    //assert(boost::to_wstring((double)1) == L"1.000000");
    //assert(boost::to_wstring((long double)1) == L"1.000000");
#else
    assert(unboost::to_string(2016) == "2016");
    assert(unboost::to_string(0x7FFFFFFFFFFFFFFF) == "9223372036854775807");
    assert(unboost::to_string((float)1) == "1.000000");
    assert(unboost::to_string((double)1) == "1.000000");
    assert(unboost::to_string((long double)1) == "1.000000");

    assert(unboost::to_wstring(2016) == L"2016");
    assert(unboost::to_wstring(0x7FFFFFFFFFFFFFFF) == L"9223372036854775807");
    assert(unboost::to_wstring((float)1) == L"1.000000");
    assert(unboost::to_wstring((double)1) == L"1.000000");
    assert(unboost::to_wstring((long double)1) == L"1.000000");
#endif

    std::cout << "success" << std::endl;
    return 0;
}
