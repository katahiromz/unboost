// string_algorithm.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_STRING_ALGORITHM
#include <unboost.hpp>

int main(void) {
    std::cout << "string algorithms" << std::endl;

    // ansi
    std::string str = "  TEST1-TEST2_TEST3  ";
    str = unboost::trim_copy(str);
    std::cout << str << std::endl;
    std::vector<std::string> vec;
    unboost::split(vec, str, unboost::is_any_of("-_"));
    std::cout << vec.size() << std::endl;
    str = unboost::join(vec, "<>");
    std::cout << str << std::endl;
    str = unboost::replace_all_copy(str, "<>", "===");
    std::cout << str << std::endl;

    // wide
    std::wstring wstr = L"  TEST1-TEST2_TEST3\u3000";
    wstr = unboost::trim_copy(wstr);
    std::wcout << wstr << std::endl;
    std::vector<std::wstring> vec2;
    unboost::split(vec2, wstr, unboost::is_any_of(L"-_"));
    std::wcout << vec2.size() << std::endl;
    wstr = unboost::join(vec2, L"<>");
    std::wcout << wstr << std::endl;
    wstr = unboost::replace_all_copy(wstr, L"<>", L"===");
    std::wcout << wstr << std::endl;

    return 0;
}
