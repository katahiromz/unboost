// text2text.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

// Unboost only
#include <unboost/text2text.hpp>

#include <iostream>
#include <cassert>
#include <string>
#include <clocale>

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_CTYPE, "japanese");

    std::string str;
    std::wstring wstr;

    unboost::text2text sjis2wide(unboost::ENC_SJIS, unboost::ENC_WIDE);
    unboost::text2text wide2sjis(unboost::ENC_WIDE, unboost::ENC_SJIS);

    // "Japanese" in Shift_JIS Japanese
    static const char *data1 = "\x93\xFA\x96\x7B\x8C\xEA";
    std::cout << "data1: \"" << data1 << "\"" << std::endl;

    wstr = sjis2wide.from_bytes(data1);
    std::wcout << "wstr: \"" << wstr << "\"" << std::endl;
    std::wcout << sjis2wide.converted() << std::endl;

    str = wide2sjis.to_bytes(wstr);
    std::cout << "str: \"" << str << "\"" << std::endl;
    std::cout << wide2sjis.converted() << std::endl;
    assert(str == data1);

    std::cout << "success" << std::endl;

    return 0;
} // main
