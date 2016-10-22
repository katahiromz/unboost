// filesystem.hpp --- Unboost filesystem
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_FILESYSTEM_HPP_
#define UNBOOST_FILESYSTEM_HPP_

#include "unboost_core.hpp"

// include directory interface
#ifdef _WIN32
    #ifndef _INC_WINDOWS
        #include <windows.h>    // for Windows API
    #endif
    #ifndef UNBOOST_UINT64
        #define UNBOOST_UINT64  DWORDLONG
    #endif
#else
    #include <direct.h>     // for DIR, opendir, readdir, closedir
    #include <sys/stat.h>   // for stat
    #ifndef UNBOOST_UINT64
        #define UNBOOST_UINT64  unsigned long long
    #endif
#endif

// If not choosed, choose one
#if ((defined(UNBOOST_USE_BOOST_FILESYSTEM) + defined(UNBOOST_USE_UNBOOST_FILESYSTEM)) == 0)
    #if defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_FILESYSTEM
    #else
        #define UNBOOST_USE_UNBOOST_FILESYSTEM
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_BOOST_FILESYSTEM
    #include <boost/filesystem/path.hpp>
    #include <boost/filesystem/operations.hpp>
    namespace unboost {
        namespace filesystem {
            using boost::filesystem::path;
            using boost::filesystem::exists;
            using boost::filesystem::is_directory;
            using boost::filesystem::is_regular_file;
            using boost::filesystem::copy_file;
            using boost::filesystem::copy_directory;
            using boost::filesystem::create_directory;
            using boost::filesystem::create_directories;
            using boost::filesystem::current_path;
            using boost::filesystem::system_complete;
            using boost::filesystem::file_size;
            using boost::filesystem::remove;
            using boost::filesystem::remove_all;
            using boost::filesystem::rename;
            using boost::filesystem::directory_iterator;
            inline void copy_directory_tree(const path& from, const path& to) {
                create_directory(to);
                path p = system_complete(to);
                path cur_dir = current_path();
                current_path(from);
                #ifdef _WIN32
                    WIN32_FIND_DATAW find;
                    HANDLE hFind = ::FindFirstFileW(L"*", &find);
                    const WCHAR *name;
                    do {
                        name = find.cFileName;
                        if (!wcscmp(name, L".") || !wcscmp(name, L"..")) {
                            continue;
                        }
                        path new_p(p);
                        new_p /= name;
                        if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                            copy_directory_tree(name, new_p);
                        } else {
                            copy_file(name, new_p);
                        }
                    } while (::FindNextFileW(hFind, &find));
                    ::FindClose(hFind);
                #else
                    DIR *pdir = opendir(cur_dir.c_str());
                    const char *name;
                    if (pdir) {
                        struct dirent *ent;
                        while ((ent = readdir(pdir)) != NULL) {
                            name = ent->d_name;
                            if (!strcmp(name, ".") || !strcmp(name, "..")) {
                                continue;
                            }
                            path new_p(p);
                            new_p /= name;
                            if (is_directory(name)) {
                                copy_directory_tree(name, new_p);
                            } else {
                                copy_file(name, new_p);
                            }
                        }
                        closedir(pdir);
                    }
                #endif
                current_path(cur_dir);
            } // copy_directory
        } // namespace filesystem
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_FILESYSTEM)
    // NOTE: Unboost Filesystem is a subset of Boost Filesystem.
    // NOTE: Unboost Filesystem doesn't support conversion.
    #include <string>           // for std::string and std::wstring
    #include <algorithm>        // for std::replace
    namespace unboost {
        namespace filesystem {
            class path;
            namespace detail {
                const path& dot_path();
                const path& dot_dot_path();
            } // namespace detail
            #ifdef _WIN32
                typedef wchar_t value_type;
                static const value_type preferred_separator = L'\\';
                typedef std::basic_string<value_type> string_type;
                static const wchar_t separator = L'/';
                inline const wchar_t *separators() { return L"/\\"; }
                static const wchar_t colon = L':';
                static const wchar_t dot = L'.';
                static const wchar_t questionmark = L'?';
                inline bool is_letter(wchar_t c) {
                    return (c >= L'a' && c <= L'z') ||
                           (c >= L'A' && c <= L'Z');
                }
            #else
                typedef char value_type;
                static const value_type preferred_separator = '/';
                typedef std::basic_string<value_type> string_type;
                static const char separator = '/';
                inline const char *separators() { return "/"; }
                static const char dot = '.';
            #endif
            typedef string_type::size_type size_type;
            bool is_separator(value_type c) {
                return c == separator
#ifdef _WIN32
                || c == preferred_separator
#endif
                ;
            }
            bool is_root_separator(const string_type & str, size_type pos) {
                while (pos > 0 && is_separator(str[pos - 1])) --pos;
                if (pos == 0) return true;
#ifdef _WIN32
                if (pos == 2 && is_letter(str[0]) && str[1] == colon)  
                    return true;
#endif
                if (pos < 3 || !is_separator(str[0]) || !is_separator(str[1]))
                    return false;

                return str.find_first_of(separators(), 2) == pos;
            }
            class path {
            public:
                path() {}
                path(const path& p) : m_pathname(p.m_pathname) {}
                path(const value_type* s) : m_pathname(s) {}
                path(value_type* s) : m_pathname(s) {}
                path(const string_type& s) : m_pathname(s) {}
                path(string_type& s) : m_pathname(s) {}
                template <class InputIterator>
                path(InputIterator begin, InputIterator end) : m_pathname(begin, end) {}
                template <class InputIterator>
                path& assign(InputIterator begin, InputIterator end) {
                    m_pathname.assign(begin, end);
                    return *this;
                }
                path& operator=(const path& p) { m_pathname = p.m_pathname; return *this; }
                path& operator=(const value_type* ptr) { m_pathname = ptr; return *this; }
                path& operator=(value_type* ptr) { m_pathname = ptr; return *this; }
                path& operator=(const string_type& s) { m_pathname = s; return *this; }
                path& operator=(string_type& s) { m_pathname = s; return *this; }
                path& operator+=(const path& p) { m_pathname += p.m_pathname; return *this; }
                path& operator+=(const value_type* ptr) { m_pathname += ptr; return *this; }
                path& operator+=(value_type* ptr) { m_pathname += ptr; return *this; }
                path& operator+=(const string_type& s) { m_pathname += s; return *this; }
                path& operator+=(string_type& s) { m_pathname += s; return *this; }
                path& operator+=(value_type c) { m_pathname += c; return *this; }
                path& operator/=(const path& p) {
                    if (p.empty()) return *this;
                    if (this == &p) {
                        path rhs(p);
                        if (!is_separator(rhs.m_pathname[0]))
                            m_append_separator_if_needed();
                        m_pathname += rhs.m_pathname;
                    } else {
                        if (!is_separator(*p.m_pathname.begin()))
                            m_append_separator_if_needed();
                        m_pathname += p.m_pathname;
                    }
                    return *this;
                }
                path& operator/=(const value_type* ptr) { return this->operator/=(path(ptr)); }
                path& operator/=(const string_type& s) { return this->operator/=(path(s)); }
                path& append(const path& p) { return this->operator/=(p); }
                path& append(const value_type* ptr) { return this->operator/=(ptr); }
                path& append(const string_type& s) { return this->operator/=(s); }
                template <class InputIterator>
                path& append(InputIterator begin, InputIterator end) {
                    path p(begin, end);
                    return this->operator/=(p);
                }
                void swap(path& rhs) { m_pathname.swap(rhs.m_pathname); }
                const string_type& native() const { return m_pathname; }
                const value_type* c_str() const   { return m_pathname.c_str(); }
                size_type size() const            { return m_pathname.size(); }
                bool empty() const                { return m_pathname.size() == 0; }
                bool has_filename() const         { return !m_pathname.empty(); }
                bool has_stem() const             { return !stem().empty(); }
                bool has_extension() const        { return !extension().empty(); }
                int compare(const path& p) const  { return m_pathname.compare(p.m_pathname); }
#ifdef _WIN32
                int compare(const std::wstring& s) const { return compare(path(s)); }
                std::wstring wstring() const { return m_pathname; }
#else
                int compare(const std::string& s) const { return compare(path(s)); }
                std::string string() const { return m_pathname; }
#endif
                int compare(const value_type* s) const  { return compare(path(s)); }
                void clear() { m_pathname.clear(); }
                path& make_preferred() {
#ifdef _WIN32
                    std::replace(m_pathname.begin(), m_pathname.end(), L'/', L'\\');
#endif
                    return *this;
                }
                path filename() const {
                    size_type pos(filename_pos(m_pathname, m_pathname.size()));
                    return (m_pathname.size()
                              && pos
                              && is_separator(m_pathname[pos])
                              && !is_root_separator(m_pathname, pos))
                      ? detail::dot_path()
                      : path(m_pathname.c_str() + pos);
                }
                path stem() const {
                    path name(filename());
                    if (name == detail::dot_path() ||
                        name == detail::dot_dot_path()) return name;
                    size_type pos(name.m_pathname.rfind(dot));
                    return pos == string_type::npos ? name
                      : path(name.m_pathname.c_str(), name.m_pathname.c_str() + pos);
                }
                path extension() const {
                    path name(filename());
                    if (name == detail::dot_path() ||
                        name == detail::dot_dot_path()) return path();
                    size_type pos = name.m_pathname.rfind(dot);
                    return pos == string_type::npos ? path()
                      : path(name.m_pathname.c_str() + pos);
                }
                path& remove_trailing_separator() {
                    if (!m_pathname.empty() &&
                        is_separator(m_pathname[m_pathname.size() - 1]))
                            m_pathname.erase(m_pathname.size() - 1);
                    return *this;
                }
                path& replace_extension(const path& new_extension = path()) {
                    m_pathname.erase(m_pathname.size() - extension().m_pathname.size());
                    if (!new_extension.empty()) {
                        if (new_extension.m_pathname[0] != dot)
                            m_pathname.push_back(dot);
                        m_pathname.append(new_extension.m_pathname);
                    }
                    return *this;
                }
                bool operator==(const path& p) const {
                    return m_pathname == p.m_pathname;
                }
                bool operator!=(const path& p) const {
                    return m_pathname != p.m_pathname;
                }
                bool operator>=(const path& p) const {
                    return m_pathname >= p.m_pathname;
                }
                bool operator<=(const path& p) const {
                    return m_pathname <= p.m_pathname;
                }
                bool operator>(const path& p) const {
                    return m_pathname > p.m_pathname;
                }
                bool operator<(const path& p) const {
                    return m_pathname < p.m_pathname;
                }
                // TODO: implement more methods
            private:
                string_type m_pathname;
                size_type filename_pos(const string_type & str, size_type end_pos) const {
                    if (end_pos == 2 && is_separator(str[0]) &&
                                        is_separator(str[1])) return 0;
                    if (end_pos && is_separator(str[end_pos - 1])) return end_pos - 1;

                    size_type pos(str.find_last_of(separators(), end_pos - 1));
#ifdef _WIN32
                    if (pos == string_type::npos && end_pos > 1)
                        pos = str.find_last_of(colon, end_pos - 2);
#endif
                    return (pos == string_type::npos
                      || (pos == 1 && is_separator(str[0]))) ? 0 : pos + 1;
                }
                size_type m_append_separator_if_needed() {
                    if (!m_pathname.empty() &&
#ifdef _WIN32
                        *(m_pathname.end() - 1) != colon && 
#endif
                        !is_separator(*(m_pathname.end() - 1)))
                    {
                        size_type tmp(m_pathname.size());
                        m_pathname += preferred_separator;
                        return tmp;
                    }
                    return 0;
                }
            }; // class path
            inline path operator/(const path& p1, const path& p2) {
                path p(p1);
                p /= p2;
                return p;
            }
            namespace detail {
                inline const path& dot_path() {
                    #ifdef _WIN32
                        static const path dot_pth(L".");
                    #else
                        static const path dot_pth(".");
                    #endif
                    return dot_pth;
                }
                inline const path& dot_dot_path() {
                    #ifdef _WIN32
                        static const path dot_dot(L"..");
                    #else
                        static const path dot_dot("..");
                    #endif
                    return dot_dot;
                }
            } // namespace detail
            inline bool exists(const path& p) {
                #ifdef _WIN32
                    return ::GetFileAttributesW(p.c_str()) != 0xFFFFFFFF;
                #else
                    struct stat st;
                    st.st_size = 0;
                    return stat(p.c_str(), &st) == 0;
                #endif
            }
            inline bool is_directory(const path& p) {
                #ifdef _WIN32
                    DWORD dw = ::GetFileAttributesW(p.c_str());
                    return (dw != 0xFFFFFFFF) && (dw & FILE_ATTRIBUTE_DIRECTORY);
                #else
                    struct stat st;
                    if (stat(p.c_str(), &st) != 0) return false;
                    return (st.st_mode & S_IFMT) == S_IFDIR;
                #endif
            }
            inline bool is_regular_file(const path& p) {
                #ifdef _WIN32
                    DWORD dw = ::GetFileAttributesW(p.c_str());
                    return (dw != 0xFFFFFFFF) && !(dw & FILE_ATTRIBUTE_DIRECTORY);
                #else
                    struct stat st;
                    if (stat(p.c_str(), &st) != 0) return false;
                    return (st.st_mode & S_IFMT) == S_IFREG;
                #endif
            }
            inline void copy_file(const path& from, const path& to) {
                #ifdef _WIN32
                    if (!::CopyFileW(from.c_str(), to.c_str(), FALSE)) {
                        throw std::runtime_error("unboost::filesystem::copy_file");
                    }
                #else
                    bool ok = false;
                    FILE *inf = fopen(from.c_str(), "rb");
                    if (inf) {
                        FILE *outf = fopen(to.c_str(), "wb");
                        if (outf) {
                            const int c_buf_size = 1024;
                            static char buf[c_buf_size];
                            ok = true;
                            for (;;) {
                                int count = fread(buf, 1, c_buf_size, inf);
                                if (count == 0) break;
                                if (!fwrite(buf, count, 1, outf)) {
                                    ok = false;
                                    break;
                                }
                            }
                            fclose(outf);
                        }
                        fclose(inf);
                    }
                    if (!ok) {
                        unlink(to.c_str());
                        throw std::runtime_error("unboost::filesystem::copy_file");
                    }
                #endif
            } // copy_file
            inline bool create_directory(const path& p) {
                #ifdef _WIN32
                    return !!::CreateDirectoryW(p.c_str(), NULL);
                #else
                    return mkdir(p.c_str()) == 0;
                #endif
            }
            inline bool create_directories(const path& p) {
                if (is_directory(p)) return true;
                #ifdef _WIN32
                    string_type str = p.wstring();
                    size_t index = str.find_last_of(separators());
                #else
                    string_type str = p.string();
                    size_t index = str.find_last_of(separator);
                #endif
                if (index != string_type::npos) {
                    if (!create_directories(str.substr(0, index)))
                        return false;
                }
                return create_directory(str);
            }
            inline path current_path() {
                #ifdef _WIN32
                    std::wstring str;
                    DWORD cch = ::GetCurrentDirectoryW(0, NULL);
                    str.resize(cch);
                    cch = ::GetCurrentDirectoryW(cch, &str[0]);
                    str.resize(cch);
                    return path(str);
                #else
                    char *ptr = getcwd(NULL, 512);
                    path p(ptr);
                    free(ptr);
                    return p;
                #endif
            }
            inline void current_path(const path& p) {
                #ifdef _WIN32
                    if (!::SetCurrentDirectoryW(p.c_str())) {
                        throw std::runtime_error("unboost::filesystem::current_path");
                    }
                #else
                    if (chdir(p.c_str()) != 0) {
                        throw std::runtime_error("unboost::filesystem::current_path");
                    }
                #endif
            }
            inline size_type root_directory_start(const string_type & path, size_t size) {
#ifdef _WIN32
                // case "c:/"
                if (size > 2 && path[1] == colon && is_separator(path[2])) return 2;
#endif
                // case "//"
                if (size == 2 && is_separator(path[0]) && is_separator(path[1]))
                    return string_type::npos;
#ifdef _WIN32
                // case "\\?\"
                if (size > 4 && is_separator(path[0]) && is_separator(path[1])
                    && path[2] == questionmark && is_separator(path[3]))
                {
                    string_type::size_type pos(path.find_first_of(separators(), 4));
                    return pos < size ? pos : string_type::npos;
                }
#endif
                // case "//net {/}"
                if (size > 3 && is_separator(path[0])
                    && is_separator(path[1]) && !is_separator(path[2]))
                {
                    string_type::size_type pos(path.find_first_of(separators(), 2));
                    return pos < size ? pos : string_type::npos;
                }
                // case "/"
                if (size > 0 && is_separator(path[0])) return 0;

                return string_type::npos;
            } // root_directory_start
            inline path system_complete(const path& p) {
#ifdef _WIN32
                if (p.empty()) return p;
                WCHAR *pch;
                std::wstring str;
                DWORD cch = ::GetFullPathNameW(p.c_str(), 0, NULL, &pch);
                str.resize(cch);
                cch = ::GetFullPathNameW(p.c_str(), cch, &str[0], &pch);
                str.resize(cch);
                return path(str);
#else
                if (p.empty()) return p;
                size_type pos(root_directory_start(m_pathname, m_pathname.size()));
                if (pos == string_type::npos) {
                    path p2(m_pathname.c_str() + pos, m_pathname.c_str() + pos + 1);
                    if (p2.empty()) return p;
                }
                return current_path() / p;
#endif
            } // system_complete
            inline void copy_directory(const path& from, const path& to) {
                #ifdef _WIN32
                    if (!::CreateDirectoryExW(from.c_str(), to.c_str(), NULL)) {
                        throw std::runtime_error("unboost::filesystem::copy_directory");
                    }
                #else
                    struct stat st;
                    if (stat(from.c_str(), &st) != 0 ||
                        mkdir(to.c_str(), st.st_mode) != 0)
                    {
                        throw std::runtime_error("unboost::filesystem::copy_directory");
                    }
                #endif
            } // copy_directory
            // TODO: use directory_iterator
            // TODO: do not change current directory
            inline void copy_directory_tree(const path& from, const path& to) {
                create_directory(to);
                path p = system_complete(to);
                path cur_dir = current_path();
                current_path(from);
                #ifdef _WIN32
                    WIN32_FIND_DATAW find;
                    HANDLE hFind = ::FindFirstFileW(L"*", &find);
                    const WCHAR *name;
                    do {
                        name = find.cFileName;
                        if (detail::dot_path() == name ||
                            detail::dot_dot_path() == name) continue;
                        path new_p(p);
                        new_p /= name;
                        if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                            copy_directory_tree(name, new_p);
                        } else {
                            copy_file(name, new_p);
                        }
                    } while (::FindNextFileW(hFind, &find));
                    ::FindClose(hFind);
                #else
                    DIR *pdir = opendir(cur_dir.c_str());
                    const char *name;
                    if (pdir) {
                        struct dirent *ent;
                        while ((ent = readdir(pdir)) != NULL) {
                            name = ent->d_name;
                            if (!strcmp(name, ".") || !strcmp(name, "..")) {
                                continue;
                            }
                            path new_p(p);
                            new_p /= name;
                            if (is_directory(name)) {
                                copy_directory_tree(name, new_p);
                            } else {
                                copy_file(name, new_p);
                            }
                        }
                        closedir(pdir);
                    }
                #endif
                current_path(cur_dir);
            } // copy_directory_tree
            inline UNBOOST_UINT64 file_size(const path& p) {
                #ifdef _WIN32
                    WIN32_FIND_DATAW find;
                    HANDLE hFind = ::FindFirstFileW(p.c_str(), &find);
                    if (hFind == INVALID_HANDLE_VALUE) return (ULONGLONG)-1;
                    ::FindClose(hFind);
                    ULONGLONG ull = find.nFileSizeHigh;
                    ull <<= 32;
                    return ull | find.nFileSizeLow;
                #else
                    struct stat st;
                    st.st_size = 0;
                    if (stat(p.c_str(), &st) == 0) return st.st_size;
                    return (UNBOOST_UINT64)-1;
                #endif
            }
            inline bool remove(const path& p) {
                #ifdef _WIN32
                    return ::RemoveDirectoryW(p.c_str()) || ::DeleteFileW(p.c_str());
                #else
                    return rmdir(p.c_str()) == 0 || unlink(p.c_str()) == 0;
                #endif
            }
            inline bool delete_directory(const path& p) {
                path full = system_complete(p);
                path cur_dir = current_path();
                current_path(p);
                #ifdef _WIN32
                    WIN32_FIND_DATAW find;
                    HANDLE hFind = ::FindFirstFileW(L"*", &find);
                    const WCHAR *name;
                    do {
                        name = find.cFileName;
                        if (detail::dot_path() == name ||
                            detail::dot_dot_path() == name) continue;
                        path new_p(full);
                        new_p /= name;
                        if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                            delete_directory(new_p);
                        } else {
                            remove(new_p);
                        }
                    } while (::FindNextFileW(hFind, &find));
                    ::FindClose(hFind);
                #else
                    DIR *pdir = opendir(cur_dir.c_str());
                    const char *name;
                    if (pdir) {
                        struct dirent *ent;
                        while ((ent = readdir(pdir)) != NULL) {
                            name = ent->d_name;
                            if (!strcmp(name, ".") || !strcmp(name, "..")) {
                                continue;
                            }
                            path new_p(full);
                            new_p /= name;
                            if (is_directory(new_p)) {
                                delete_directory(new_p);
                            } else {
                                remove(new_p);
                            }
                        }
                        closedir(pdir);
                    }
                #endif
                current_path(cur_dir);
                return remove(full);
            }
            inline bool remove_all(const path& p) {
                return delete_directory(p) || remove(p);
            }
            inline void rename(const path& old_p, const path& new_p) {
                #ifdef _WIN32
                    if (!::MoveFileExW(old_p.c_str(), new_p.c_str(),
                                       MOVEFILE_REPLACE_EXISTING)) {
                        throw std::runtime_error("unboost::filesystem::rename");
                    }
                #else
                    if (rename(old_p.c_str(), new_p.c_str()) != 0) {
                        throw std::runtime_error("unboost::filesystem::rename");
                    }
                #endif
            }
            // TODO: support directory_iterator
        } // namespace filesystem
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_FILESYSTEM_HPP_
