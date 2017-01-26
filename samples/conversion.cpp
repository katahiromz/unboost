// conversion.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <string>
#elif defined(BOOST)
    #include <boost/exception/to_string.hpp>
#else
    #include <unboost/exception/to_string.hpp>
#endif

#include <iostream>
#include <cassert>

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

    assert(std::stol("100") == 100);
    assert(std::stoul("100") == 100);
    assert(std::stoi("100") == 100);
    assert(std::stof("100") == 100.0);
    assert(std::stod("100") == 100.0);
#elif defined(BOOST)
    assert(boost::to_string(2016) == "2016");
    assert(boost::to_string(0x7FFFFFFFFFFFFFFF) == "9223372036854775807");
    assert(boost::to_string((float)1) == "1");  // differs from standard
    assert(boost::to_string((double)1) == "1"); // differs
    assert(boost::to_string((long double)1) == "1"); // differs

    // NOTE: to_wstring is not supported in Boost
    //assert(boost::to_wstring(2016) == L"2016");
    //assert(boost::to_wstring(0x7FFFFFFFFFFFFFFF) == L"9223372036854775807");
    //assert(boost::to_wstring((float)1) == L"1.000000");
    //assert(boost::to_wstring((double)1) == L"1.000000");
    //assert(boost::to_wstring((long double)1) == L"1.000000");

    // NOTE: there is no sto* conversion functions in Boost
    //assert(boost::stol("100") == 100);
    //assert(boost::stoul("100") == 100);
    //assert(boost::stoi("100") == 100);
    //assert(boost::stof("100") == 100.0);
    //assert(boost::stod("100") == 100.0);
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

    assert(unboost::stol("100") == 100);
    assert(unboost::stoul("100") == 100);
    assert(unboost::stoi("100") == 100);
    assert(unboost::stof("100") == 100.0);
    assert(unboost::stod("100") == 100.0);
#endif

    std::cout << "success" << std::endl;
    return 0;
} // main
