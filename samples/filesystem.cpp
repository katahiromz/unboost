// filesystem.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <cassert>

#ifdef BOOST
    #include <boost/filesystem.hpp>
#else   // Unboost
    #include <unboost/filesystem.hpp>
#endif

#include <cstdio>

int main(void) {
    std::cout << "filesystem" << std::endl;

#ifdef BOOST
    using namespace boost::filesystem;
    using std::swap;
    boost::system::error_code ec;
#else   // Unboost
    using namespace unboost::filesystem;
    using unboost::swap;
    unboost::system::error_code ec;
#endif  // Unboost

    bool flag;

#ifdef _WIN32
    path p1("C:\\"), p2("C:\\Windows"), p3("C:\\Windows\\system32");
    assert(system_complete("notepad.exe") == path("C:\\WINDOWS\\system32\\notepad.exe"));
    space_info devi = space("NUL");
    space_info tmpi = space("C:\\Windows\\Temp");
#else
    path p1("/"), p2("/usr"), p3("/usr/bin");
    assert(system_complete("sh") == path("/bin/sh"));
    space_info devi = space("/dev/null");
    space_info tmpi = space("/tmp");
#endif

    // test #0
    std::cout << temp_directory_path(ec) << std::endl;
    std::cout << p1 << std::endl;
    assert(!ec);

    // test #1
    assert(p1 == p1);
    assert(p1 != p2);
    assert(absolute(p1) == p1);
    assert(canonical(p3 / "..", ec) == p2);
    assert(!ec);
    assert(equivalent(current_path(ec), ".", ec));
    assert(!equivalent(p1, p2, ec));

    // test #2
    path cur_dir = current_path(ec);
    assert(!ec);
    flag = create_directory("sandbox", ec);
    assert(flag);
    assert(!ec);
    current_path("sandbox", ec);
    assert(!ec);
    current_path("..", ec);
    assert(!ec);
    assert(current_path(ec) == cur_dir);
    assert(!ec);
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #3
    flag = create_directory("sandbox", ec);
    assert(flag);
    assert(!ec);
    std::ofstream("sandbox/file1.txt").put('a');
    copy_file("sandbox/file1.txt", "sandbox/file2.txt");
    std::cout << "file1.txt holds : " << std::ifstream("sandbox/file1.txt").rdbuf() << '\n';
    std::cout << "file2.txt holds : " << std::ifstream("sandbox/file2.txt").rdbuf() << '\n';
    create_directory("sandbox/abc");
    try {
        copy_file("sandbox/abc", "sandbox/def");
        assert(0);
    } catch(filesystem_error& e) {
        ;
    }
    remove_all("sandbox");

    // test #4
    flag = create_directories("sandbox/a/b", ec);
    assert(flag);
    assert(!ec);
    std::ofstream("sandbox/file1.txt");
    std::ofstream("sandbox/file2.txt");
    {
        directory_iterator it("sandbox");
        assert(it->path() == "sandbox/a");
        ++it;
        assert(it->path() == "sandbox/file1.txt");
        ++it;
        assert(it->path() == "sandbox/file2.txt");
    }
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #5
    flag = create_directories("sandbox/a/b", ec);
    assert(flag);
    assert(!ec);
    std::ofstream("sandbox/file1.txt");
    create_symlink("a", "sandbox/syma");
    {
        recursive_directory_iterator it("sandbox");
        assert(it->path() == "sandbox/a");
        ++it;
        assert(it->path() == "sandbox/a/b");
        ++it;
        assert(it->path() == "sandbox/file1.txt");
        ++it;
        assert(it->path() == "sandbox/syma");
    }
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #6
    flag = create_directories("sandbox/dir/subdir", ec);
    assert(flag);
    assert(!ec);
    std::ofstream("sandbox/file1.txt").put('a');
    unboost::filesystem::copy("sandbox/file1.txt", "sandbox/file2.txt", ec);
    assert(!ec);
    unboost::filesystem::copy("sandbox/dir", "sandbox/dir2", ec);
    {
        recursive_directory_iterator it("sandbox");
        assert(it->path() == "sandbox/file1.txt");
        ++it;
        assert(it->path() == "sandbox/file2.txt");
        ++it;
        assert(it->path() == "sandbox/dir");
        ++it;
        assert(it->path() == "sandbox/dir/subdir");
        ++it;
        assert(it->path() == "sandbox/dir2");
    }
    copy("sandbox/dir", "sandbox/copy", copy_options::recursive, ec);
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #7
    flag = create_directories("sandbox/subdir", ec);
    assert(flag);
    assert(!ec);
    std::ofstream("sandbox/a").put('a'); // create regular file
    create_hard_link("sandbox/a", "sandbox/b", ec);
    assert(!ec);
    flag = remove("sandbox/a", ec);
    assert(flag);
    assert(!ec);
    char c = std::ifstream("sandbox/b").get();
    assert(c == 'a');
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #8
    flag = create_directories("sandbox/subdir", ec);
    assert(flag);
    assert(!ec);
    create_symlink("target", "sandbox/sym1");
    create_directory_symlink("subdir", "sandbox/sym2");
    {
        directory_iterator it("sandbox");
        assert(is_symlink(it->symlink_status()));
        assert(it->path() == "sandbox/sym1");
        assert(read_symlink(it->path()).string() == "target");
        ++it;
        assert(is_symlink(it->symlink_status()));
        assert(it->path() == "sandbox/sym2");
        assert(read_symlink(it->path()).string() == "subdir");
        ++it;
    }
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #9
    flag = create_directories("sandbox/dir", ec);
    assert(flag);
    assert(!ec);
    std::ofstream("sandbox/file");
    create_symlink("file", "sandbox/symlink");
    assert(is_regular_file("sandbox/file"));
    assert(is_directory("sandbox/dir"));
    assert(is_symlink("sandbox/symlink"));
    {
        directory_iterator it("sandbox");
        assert(is_regular_file(it->symlink_status()));
        ++it;
        assert(is_directory(it->symlink_status()));
        ++it;
        assert(is_symlink(it->symlink_status()));
        ++it;
    }
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #10
    std::cout << ".        Capacity       Free      Available\n"
              << "/dev:   " << devi.capacity << "   "
              << devi.free << "   " << devi.available  << std::endl
              << "/tmp: " << tmpi.capacity << " "
              << tmpi.free << " " << tmpi.available  << std::endl;

    // test #11
    std::cout << "swap" << std::endl;
    unboost::swap(p1, p2);
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;

    // test #12
    flag = create_directory("sandbox", ec);
    assert(flag);
    assert(!ec);
    path example_p("sandbox/example.bin");
    std::ofstream(example_p.string().c_str()).put('a');
    resize_file(example_p, 1024, ec);
    assert(file_size(example_p, ec) == 1024);
    assert(!ec);
    rename(example_p, "sandbox/renamed.bin", ec);
    assert(!ec);
    flag = remove("sandbox/renamed.bin", ec);
    assert(flag);
    assert(!ec);
    flag = remove("sandbox", ec);
    assert(flag);
    assert(!ec);

    // test #13
    assert(hard_link_count(".") >= 2);

    p1.clear();
    assert(p1.empty());
#ifdef _WIN32
    p1 = L"C:";
    p1 /= "Users";
#else
    p1 /= "usr";
#endif
    std::cout << "p1: " << p1 << std::endl;

    {
        path::iterator it = p1.begin(), end = p1.end();
        while (it != end) {
            std::cout << *it << std::endl;
        }
    }

    p1 = "/a/b/";
    p2 = "/a/b/#";
    assert(p1 > p2);
    p2 = p1;
    p2 += "_";
    assert(p1 < p2);

    assert(path("/foo/bar.txt").extension().string() == ".txt");
    assert(path("/foo/bar.").extension().string() == ".");
    assert(path("/foo/bar").extension().string() == "");
    assert(path("/foo/bar.txt/bar.cc").extension().string() == ".cc");
    assert(path("/foo/bar.txt/bar.").extension().string() == ".");
    assert(path("/foo/bar.txt/bar").extension().string() == "");
    assert(path("/foo/.").extension().string() == "");
    assert(path("/foo/..").extension().string() == "");
    assert(path("/foo/.hidden").extension().string() == ".hidden");

    assert(path("/foo/bar.txt").filename().string() == "bar.txt");
    assert(path("/foo/.bar").filename().string() == ".bar");
    assert(path("/foo/bar/").filename().string() == ".");
    assert(path("/foo/.").filename().string() == ".");
    assert(path("/foo/..").filename().string() == "..");
    assert(path(".").filename().string() == ".");
    assert(path("..").filename().string() == "..");
    assert(path("/").filename().string() == "/");

    assert(path("/var/tmp/example.txt").parent_path() == path("/var/tmp"));
    assert(path("/").parent_path() == path(""));
    assert(path("/var/tmp/.").parent_path() == path("/var/tmp"));

    p1 = current_path();
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "root path: " << p1.root_path() << std::endl;
    std::cout << "relative path: " << p1.relative_path() << std::endl;

    assert(path("/foo").remove_filename().string() == "/");
    assert(path("/").remove_filename().string() == "");

    assert(path("/foo").replace_filename("bar").string() == "/bar");
    assert(path("/").replace_filename("bar").string() == "bar");

    assert(path("/foo/bar.jpeg").replace_extension(".jpg").string() == "/foo/bar.jpg");

#ifdef _WIN32
    assert(current_path().root_name().string() == "C:");
    assert(current_path().root_path().string() == "C:\\");
#else
    p1 = "/lib/libc.so.6";
    assert(exists(p) && is_symlink(p));
    assert(read_symlink(p).string() == "libc-2.12.so");
#endif

    assert(path("/foo/bar.txt").stem().string() == "bar");
    assert(path("/foo/.bar").stem().string() == "");
    p1 = "foo.bar.baz.tar";
    assert(p1.extension().string() == ".tar");
    p1 = p1.stem();
    assert(p1.extension().string() == ".baz");
    p1 = p1.stem();
    assert(p1.extension().string() == ".bar");

    p1 = "TEST1";
    p2 = "TEST2";
    p1.swap(p2);
    assert(p1.string() == "TEST2");
    swap(p1, p2);
    assert(p1.string() == "TEST1");

    {
        create_directories("sandbox/a/b/c");
        create_directories("sandbox/a/b/d/e");
        std::ofstream("sandbox/a/b/file1.txt");
        create_symlink("a", "sandbox/syma");
        recursive_directory_iterator it("sandbox");
        assert(it.depth() == 0);
        ++it;
        assert(it.depth() == 1);
        ++it;
        assert(it.depth() == 2);
        ++it;
        assert(it.depth() == 2);
        ++it;
        assert(it.depth() == 3);
        ++it;
        assert(it.depth() == 2);
        ++it;
        remove_all("sandbox");
    }

    {
        create_directories("sandbox/a/b/c");
        create_directories("sandbox/a/b/d/e");
        std::ofstream("sandbox/a/b/file1.txt");
        create_symlink("a", "sandbox/syma");
        recursive_directory_iterator it("sandbox");
        assert(it.recursion_pending());
        assert(it->path().string() == "sandbox/a");
        ++it;
        assert(it->path().string() == "sandbox/a/b");
        it.disable_recursion_pending();
        assert(!it.recursion_pending());
        ++it;
        assert(it->path().string() == "sandbox/syma");
        ++it;
        remove_all("sandbox");
    }

    std::cout << "success" << std::endl;
    return 0;
} // main
