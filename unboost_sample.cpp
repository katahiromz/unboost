// unboost_sample.cpp --- Unboost sample
// This file is public domain software (PDS).
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_RATIO
#define UNBOOST_USE_THREAD
#define UNBOOST_USE_CHRONO
#include "unboost.hpp"

#include <iostream>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

#ifdef UNBOOST_USE_STATIC_ASSERT
    static_assert(1, "OK");
    //static_assert(0, "NG");
#endif

#ifdef UNBOOST_USE_TUPLE
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
#endif  // def UNBOOST_USE_TUPLE

//////////////////////////////////////////////////////////////////////////////

#ifdef UNBOOST_USE_THREAD
    void thread_proc0(void) {
        std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
    }
    void thread_proc1(int n) {
        std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
        std::cout << "n: " << n << std::endl;
    }
    void thread_proc2(int n, int m) {
        std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
        std::cout << "n: " << n << std::endl;
        std::cout << "m: " << m << std::endl;
    }
#endif

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    #ifdef UNBOOST_USE_SMART_PTR
        std::cout << "smart ptr" << std::endl;
        unboost::shared_ptr<int> spi = unboost::make_shared<int>(2);
        std::cout << *spi << std::endl;
    #endif

    #ifdef UNBOOST_USE_THREAD
        unboost::chrono::milliseconds dura(2000);
        std::cout << "thread" << std::endl;
        unboost::thread t0(thread_proc0);
        t0.join();
        unboost::this_thread::sleep_for(dura);
        unboost::thread t1(thread_proc1, 2);
        t1.join();
        unboost::this_thread::sleep_for(dura);
        unboost::thread t2(thread_proc2, 2, 3);
        t2.join();
    #endif

    #ifdef UNBOOST_USE_ARRAY
        std::cout << "array" << std::endl;
        unboost::array<int,2> a = {2, 3};
        std::cout << a[0] << std::endl;
        std::cout << a[1] << std::endl;
    #endif

    #ifdef UNBOOST_USE_REGEX
        std::cout << "regex" << std::endl;
        std::vector<std::string> fnames;
        fnames.push_back("foo.txt");
        fnames.push_back("bar.txt");
        fnames.push_back("baz.dat");
        fnames.push_back("zoidberg");
        using unboost::regex;
        regex txt_regex("[a-z]+\\.txt");
     
        for (size_t i = 0; i < fnames.size(); ++i) {
            using namespace unboost;
            std::string& fname = fnames[i];
            std::cout << fname << ": " << regex_match(fname, txt_regex) << '\n';
        }
    #endif

    #ifdef UNBOOST_USE_CONVERSION
        std::cout << "conversion" << std::endl;
        std::cout << unboost::to_string(unboost::stoi("2016")) << std::endl;
        std::cout << unboost::stod("999.99999999999999999999999") << std::endl;
        std::cout << unboost::stoull("100000000000000") << std::endl;
    #endif

    #ifdef UNBOOST_USE_COMPLEX_FUNCTIONS
        std::cout << "complex functions" << std::endl;
        std::cout << unboost::math::asin(std::complex<double>(2, 3)).real() << std::endl;
    #endif

    #ifdef UNBOOST_USE_RANDOM
        std::cout << "random" << std::endl;
        {
            using namespace unboost::random;
            mt19937 engine;
            uniform_int_distribution<int> distribution(1, 6);
            for (int i = 0; i < 5; ++i) {
                std::cout << distribution(engine) << std::endl;
            }
        }
    #endif

    #ifdef UNBOOST_USE_RATIO
        std::cout << unboost::ratio<7,-21>::num << std::endl;   // -1;
        std::cout << unboost::ratio<7,-21>::den << std::endl;   // 3;

        typedef unboost::ratio<2, 3> two_third;
        typedef unboost::ratio<1, 6> one_sixth;

        typedef unboost::ratio_add<two_third, one_sixth> sum;
        std::cout << sum::num << "/" << sum::den << std::endl;  // 5/6

        typedef unboost::ratio_subtract<two_third, one_sixth> diff;
        std::cout << diff::num << '/' << diff::den << std::endl;    // 1/2

        typedef unboost::ratio_multiply<two_third, one_sixth> prod;
        std::cout << prod::num << '/' << prod::den << std::endl;    // 1/9

        typedef unboost::ratio_divide<two_third, one_sixth> quot;
        std::cout << quot::num << '/' << quot::den << std::endl;    // 4/1

        typedef unboost::ratio_equal<two_third, two_third> eq;
        typedef unboost::ratio_equal<two_third, one_sixth> neq;
        std::cout << "eq: " << eq() << std::endl;
        std::cout << "neq: " << neq() << std::endl;

        std::cout << "less: " <<
            unboost::ratio_less<unboost::ratio<23,37>,
                                unboost::ratio<57,90> >::value << std::endl;
    #endif

    #ifdef UNBOOST_USE_CHRONO
        std::cout << "chrono" << std::endl;
        {
            using namespace unboost::chrono;
            seconds sec(1);
            std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
            std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
            std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
            std::cout << duration_cast<hours>(sec).count() << " hours" << std::endl;
        }

        //unboost::chrono::time_point<unboost::chrono::steady_clock> t1, t2;
        //for (unsigned __int64 size = 1; size < 10000000; size *= 10) {
        //    t1 = unboost::chrono::steady_clock::now();
        //    std::vector<int> v(size, 42);
        //    t2 = unboost::chrono::steady_clock::now();
        //    std::cout << t1.time_since_epoch().count() << std::endl;
        //    std::cout << t2.time_since_epoch().count() << std::endl;
        //    std::cout << size << ": " << (t1 - t2).count() << std::endl;
        //}
    #endif

    #ifdef UNBOOST_USE_UNORDERED_SET
        std::cout << "unorderd set" << std::endl;
        unboost::unordered_set<int> us;
        us.insert(1);
        us.insert(2);
        {
            unboost::unordered_set<int>::iterator it, end = us.end();
            for (it = us.begin(); it != end; ++it) {
                std::cout << *it << std::endl;
            }
        }
    #endif

    #ifdef UNBOOST_USE_UNORDERED_MAP
        std::cout << "unorderd map" << std::endl;
        unboost::unordered_map<int, int> um;
        um.insert(std::make_pair(2, 3));
        um.insert(std::make_pair(4, 5));
        {
            unboost::unordered_map<int, int>::iterator it, end = um.end();
            for (it = um.begin(); it != end; ++it) {
                std::cout << it->first << ", " << it->second << std::endl;
            }
        }
    #endif

    #ifdef UNBOOST_USE_FOREACH
        std::cout << "foreach" << std::endl;
        {
            std::vector<int> v;
            v.push_back(2);
            v.push_back(3);
            v.push_back(4);
            UNBOOST_FOREACH(int& i, v) {
                i -= 1;
            }
            UNBOOST_FOREACH(int i, v) {
                std::cout << i << std::endl;
            }
        }
    #endif

    #ifdef UNBOOST_USE_TUPLE
        std::cout << "tuple" << std::endl;
        unboost::tuple<int, const char *, std::string> tup;
        tup = unboost::make_tuple<int, const char *, std::string>(2, "This is", "a test");
        print_taple(tup);
        std::cout << std::endl;
    #endif

    #ifdef UNBOOST_USE_STRING_ALGORITHMS
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
    #endif

    #ifdef UNBOOST_USE_FILESYSTEM
        std::cout << "filesystem" << std::endl;
        {
            using namespace unboost::filesystem;
            FILE *fp = fopen("test.dat", "w");
            fputs("TEST", fp);
            fclose(fp);
            #ifdef _WIN32
                std::wcout << current_path().c_str() << std::endl;
                create_directory(L"dir");
                copy_file(L"test.dat", L"dir/test2.dat");
                if (exists(L"dir/test2.dat")) std::cout << "exists" << std::endl;
                copy_directory_tree(L"dir", L"dir2");
                std::cout << file_size(L"test.dat") << std::endl;
                remove(L"test.dat");
                remove(L"dir/test2.dat");
                create_directories(L"mydir1/mydir2/mydir3");
                remove_all(L"mydir1");
            #else
                std::cout << current_path().c_str() << std::endl;
                create_directory("dir");
                copy_file("test.dat", "dir/test2.dat");
                if (exists("test2.dat")) std::cout << "exists" << std::endl;
                copy_directory_tree("dir", "dir2");
                std::cout << file_size("test.dat") << std::endl;
                remove("test.dat");
                remove("dir/test2.dat");
                create_directories("mydir1/mydir2/mydir3");
                remove_all("mydir1");
            #endif
        }
    #endif

    #ifdef UNBOOST_USE_ASSERT
        std::cout << "assert" << std::endl;
        UNBOOST_ASSERT(1);
        UNBOOST_ASSERT_MSG(1, "OK");
    #endif

    return 0;
} // main

//////////////////////////////////////////////////////////////////////////////
