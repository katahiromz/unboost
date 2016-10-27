// hash.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <functional>
#elif defined(BOOST)
    #include <boost/functional/hash.hpp>
#else
    #include <unboost/functional/hash.hpp>
#endif

int main(void) {
    std::cout << "hash" << std::endl;

#ifdef CXX11
    std::hash<char> char_hash;
    std::hash<unsigned char> uchar_hash;
    std::hash<short> short_hash;
    std::hash<unsigned short> ushort_hash;
    std::hash<long> long_hash;
    std::hash<unsigned long> ulong_hash;
    std::hash<int> int_hash;
    std::hash<unsigned int> uint_hash;
    std::hash<std::string> str_hash;
    std::hash<std::wstring> wstr_hash;
#elif defined(BOOST)
    boost::hash<char> char_hash;
    boost::hash<unsigned char> uchar_hash;
    boost::hash<short> short_hash;
    boost::hash<unsigned short> ushort_hash;
    boost::hash<long> long_hash;
    boost::hash<unsigned long> ulong_hash;
    boost::hash<int> int_hash;
    boost::hash<unsigned int> uint_hash;
    boost::hash<std::string> str_hash;
    boost::hash<std::wstring> wstr_hash;
#else
    unboost::hash<char> char_hash;
    unboost::hash<unsigned char> uchar_hash;
    unboost::hash<short> short_hash;
    unboost::hash<unsigned short> ushort_hash;
    unboost::hash<long> long_hash;
    unboost::hash<unsigned long> ulong_hash;
    unboost::hash<int> int_hash;
    unboost::hash<unsigned int> uint_hash;
    unboost::hash<std::string> str_hash;
    unboost::hash<std::wstring> wstr_hash;
#endif

    std::cout << char_hash(-1) << std::endl;
    std::cout << uchar_hash(-1) << std::endl;
    std::cout << short_hash(-1) << std::endl;
    std::cout << ushort_hash(-1) << std::endl;
    std::cout << long_hash(-1) << std::endl;
    std::cout << ulong_hash(-1) << std::endl;
    std::cout << int_hash(-1) << std::endl;
    std::cout << uint_hash(-1) << std::endl;
    std::cout << str_hash("TEST STRING") << std::endl;
    std::cout << wstr_hash(L"TEST STRING") << std::endl;

    return 0;
} // main
