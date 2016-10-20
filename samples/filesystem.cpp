// filesystem.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_FILESYSTEM
#include <unboost.hpp>

int main(void) {
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
    return 0;
}
