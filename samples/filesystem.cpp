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

#ifdef BOOST
    using namespace boost::filesystem;
#else   // Unboost
    using namespace unboost::filesystem;
#endif

    system::error_code ec;
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
    assert(ec.empty());

    // test #1
    assert(p1 == p1);
    assert(p1 != p2);
    assert(absolute(p1) == p1);
    assert(canonical(p3 / "..", ec) == p2)
    assert(ec.empty());
    assert(equivalent(current_path(ec), ".", ec));
    assert(!equivalent(p1, p2, ec));

    // test #2
    path cur_dir = current_path(ec);
    assert(ec.empty());
    flag = create_directory("sandbox", ec);
    assert(flag);
    assert(ec.empty());
    current_path("sandbox", ec);
    assert(ec.empty());
    current_path("..", ec);
    assert(ec.empty());
    assert(current_path(ec) == cur_dir);
    assert(ec.empty());
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(ec.empty());

    // test #3
    flag = create_directory("sandbox", ec);
    assert(flag);
    assert(ec.empty());
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
    assert(ec.empty());
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
    assert(ec.empty());

    // test #5
    flag = create_directories("sandbox/a/b", ec);
    assert(flag);
    assert(ec.empty());
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
    assert(ec.empty());

    // test #6
    flag = create_directories("sandbox/dir/subdir", ec);
    assert(flag);
    assert(ec.empty());
    std::ofstream("sandbox/file1.txt").put('a');
    copy("sandbox/file1.txt", "sandbox/file2.txt", ec);
    assert(ec.empty());
    copy("sandbox/dir", "sandbox/dir2", ec);
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
    assert(ec.empty());

    // test #7
    flag = create_directories("sandbox/subdir", ec);
    assert(flag);
    assert(ec.empty());
    std::ofstream("sandbox/a").put('a'); // create regular file
    create_hard_link("sandbox/a", "sandbox/b", ec);
    assert(ec.empty());
    flag = remove("sandbox/a", ec);
    assert(flag);
    assert(ec.empty());
    char c = std::ifstream("sandbox/b").get();
    assert(c == 'a');
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(ec.empty());

    // test #8
    flag = create_directories("sandbox/subdir", ec);
    assert(flag);
    assert(ec.empty());
    create_symlink("target", "sandbox/sym1");
    create_directory_symlink("subdir", "sandbox/sym2");
    {
        directory_iterator it("sandbox");
        assert(is_symlink(it->symlink_status()));
        assert(it->path() == "sandbox/sym1");
        assert(read_symlink(*it) == "target");
        ++it;
        assert(is_symlink(it->symlink_status()));
        assert(it->path() == "sandbox/sym2");
        assert(read_symlink(*it) == "subdir");
        ++it;
    }
    flag = remove_all("sandbox", ec);
    assert(flag);
    assert(ec.empty());

    // test #9
    flag = create_directories("sandbox/dir", ec);
    assert(flag);
    assert(ec.empty());
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
    assert(ec.empty());

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
    assert(ec.empty());
    path example_p("sandbox/example.bin");
    std::ofstream(p.c_str()).put('a');
    resize_file(p, 1024, ec);
    assert(file_size(p, ec) == 1024);
    assert(ec.empty());
    rename(example_p, "sandbox/renamed.bin", ec);
    assert(ec.empty());
    flag = remove("sandbox/renamed.bin", ec);
    assert(flag);
    assert(ec.empty());
    flag = remove("sandbox", ec);
    assert(flag);
    assert(ec.empty());

    std::cout << "success" << std::endl;
    return 0;
} // main
