// filesystem.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef BOOST
    #include <boost/filesystem.hpp>
#else   // Unboost
    #include <unboost/filesystem.hpp>
#endif

#include <cstdio>

int main(void) {
    std::cout << "filesystem" << std::endl;

    std::FILE *fp = std::fopen("test.dat", "w");
    std::fputs("TEST", fp);
    std::fclose(fp);

#ifdef BOOST
    using namespace boost::filesystem;
#else   // Unboost
    using namespace unboost::filesystem;
#endif

    #ifdef _WIN32
        std::wcout << current_path().c_str() << std::endl;
        create_directory(L"dir");
        copy_file(L"test.dat", L"dir/test2.dat");
        assert(exists(L"dir/test2.dat"));
        copy_directory_tree(L"dir", L"dir2");
        assert(exists(L"dir2/test2.dat"));
        assert(file_size(L"test.dat") > 0);
        remove(L"test.dat");
        assert(!exists(L"test.dat"));
        remove(L"dir/test2.dat");
        assert(!exists(L"dir/test2.dat"));
        create_directories(L"mydir1/mydir2/mydir3");
        assert(is_directory(L"mydir1/mydir2/mydir3"));
        remove_all(L"mydir1");
        assert(!is_directory(L"mydir1/mydir2/mydir3"));
        assert(!is_directory(L"mydir1"));
        remove_all(L"dir");
        assert(!is_directory(L"dir"));
        remove_all(L"dir2");
        assert(!is_directory(L"dir2"));
    #else
        std::cout << current_path().c_str() << std::endl;
        create_directory("dir");
        copy_file("test.dat", "dir/test2.dat");
        assert(exists("dir/test2.dat"));
        copy_directory_tree("dir", "dir2");
        assert(exists("dir2/test2.dat"));
        std::cout << file_size("test.dat") << std::endl;
        remove("test.dat");
        assert(!exists("test.dat"));
        remove("dir/test2.dat");
        assert(!exists("dir/test2.dat"));
        create_directories("mydir1/mydir2/mydir3");
        assert(is_directory("mydir1/mydir2/mydir3"));
        remove_all("mydir1");
        assert(!is_directory("mydir1/mydir2/mydir3"));
        assert(!is_directory("mydir1"));
        remove_all("dir");
        assert(!is_directory("dir"));
        remove_all("dir2");
        assert(!is_directory("dir2"));
    #endif

    std::cout << "success" << std::endl;
    return 0;
} // main
