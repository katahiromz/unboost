// string_algorithm.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_STRING_ALGORITHM
#include <unboost.hpp>

int main(void) {
    std::cout << "string algorithms" << std::endl;

    // ansi
    std::string str = "  TEST1-TEST2_TEST3  ";
    str = unboost::trim_copy(str);
    assert(str == "TEST1-TEST2_TEST3");

    std::vector<std::string> vec;
    unboost::split(vec, str, unboost::is_any_of("-_"));
    assert(vec[0] == "TEST1");
    assert(vec[1] == "TEST2");
    assert(vec[2] == "TEST3");
    assert(vec.size() == 3);

    str = unboost::join(vec, "<>");
    assert(str == "TEST1<>TEST2<>TEST3");

    str = unboost::replace_all_copy(str, "<>", "===");
    assert(str == "TEST1===TEST2===TEST3");

    // wide
    std::wstring wstr = L"  TEST1-TEST2_TEST3\u3000";
    wstr = unboost::trim_copy(wstr);
    assert(wstr == L"TEST1-TEST2_TEST3");

    std::vector<std::wstring> wvec;
    unboost::split(wvec, wstr, unboost::is_any_of(L"-_"));
    assert(wvec[0] == L"TEST1");
    assert(wvec[1] == L"TEST2");
    assert(wvec[2] == L"TEST3");
    assert(wvec.size() == 3);

    wstr = unboost::join(wvec, L"<>");
    assert(wstr == L"TEST1<>TEST2<>TEST3");

    wstr = unboost::replace_all_copy(wstr, L"<>", L"===");
    assert(wstr == L"TEST1===TEST2===TEST3");

    return 0;
}
