// filesystem.hpp --- Unboost filesystem
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_FILESYSTEM_HPP_
#define UNBOOST_FILESYSTEM_HPP_

#include "unboost.hpp"

#include <iterator>     // for std::input_iterator_tag

// If not choosed, choose one
#if (defined(UNBOOST_USE_CXX17_FILESYSTEM) + defined(UNBOOST_USE_BOOST_FILESYSTEM) + defined(UNBOOST_USE_WIN32_FILESYSTEM) + defined(UNBOOST_USE_POSIX_FILESYSTEM) == 0)
    #ifdef UNBOOST_USE_CXX17
        #define UNBOOST_USE_CXX17_FILESYSTEM
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_FILESYSTEM
    #else
        #ifdef UNBOOST_CXX17
            #define UNBOOST_USE_CXX17_FILESYSTEM
        #else
            #ifdef _WIN32
                #define UNBOOST_USE_WIN32_FILESYSTEM
            #else
                #define UNBOOST_USE_POSIX_FILESYSTEM
            #endif
        #endif
    #endif
#endif

#ifdef UNBOOST_USE_CXX17_SYSTEM
    #include <filesystem>
    namespace unboost {
        namespace filesystem {
            using std::filesystem::path;
            using std::filesystem::filesystem_eror;
            using std::filesystem::directory_entry;
            using std::filesystem::directory_iterator;
            using std::filesystem::recursive_directory_iterator;
            using std::filesystem::file_status;
            using std::filesystem::space_info;
            using std::filesystem::file_type;
            using std::filesystem::perms;
            using std::filesystem::copy_options;
            using std::filesystem::directory_options;
            using std::filesystem::file_time_type;
            using std::filesystem::absolute;
            using std::filesystem::system_complete;
            using std::filesystem::canonical;
            using std::filesystem::copy;
            using std::filesystem::copy_file;
            using std::filesystem::copy_symlink;
            using std::filesystem::create_directory;
            using std::filesystem::create_directories;
            using std::filesystem::create_hard_link;
            using std::filesystem::create_symlink;
            using std::filesystem::create_directory_symlink;
            using std::filesystem::current_path;
            using std::filesystem::exists;
            using std::filesystem::equivalent;
            using std::filesystem::file_size;
            using std::filesystem::hard_link_count;
            using std::filesystem::last_write_time;
            using std::filesystem::permissions;
            using std::filesystem::read_symlink;
            using std::filesystem::remove;
            using std::filesystem::remove_all;
            using std::filesystem::rename;
            using std::filesystem::resize_file;
            using std::filesystem::space;
            using std::filesystem::status;
            using std::filesystem::symlink_status;
            using std::filesystem::temp_directory_path;
            using std::filesystem::is_block_file;
            using std::filesystem::is_character_file;
            using std::filesystem::is_directory;
            using std::filesystem::is_empty;
            using std::filesystem::is_fifo;
            using std::filesystem::is_other;
            using std::filesystem::is_regular_file;
            using std::filesystem::is_socket;
            using std::filesystem::is_symlink;
            using std::filesystem::status_known;
        } // namespace filesystem
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_FILESYSTEM)
    #include <boost/filesystem.hpp>
    namespace unboost {
        namespace filesystem {
            using boost::filesystem::path;
            using boost::filesystem::filesystem_eror;
            using boost::filesystem::directory_entry;
            using boost::filesystem::directory_iterator;
            using boost::filesystem::recursive_directory_iterator;
            using boost::filesystem::file_status;
            using boost::filesystem::space_info;
            using boost::filesystem::file_type;
            using boost::filesystem::perms;
            using boost::filesystem::copy_options;
            using boost::filesystem::directory_options;
            using boost::filesystem::file_time_type;
            using boost::filesystem::absolute;
            using boost::filesystem::system_complete;
            using boost::filesystem::canonical;
            using boost::filesystem::copy;
            using boost::filesystem::copy_file;
            using boost::filesystem::copy_symlink;
            using boost::filesystem::create_directory;
            using boost::filesystem::create_directories;
            using boost::filesystem::create_hard_link;
            using boost::filesystem::create_symlink;
            using boost::filesystem::create_directory_symlink;
            using boost::filesystem::current_path;
            using boost::filesystem::exists;
            using boost::filesystem::equivalent;
            using boost::filesystem::file_size;
            using boost::filesystem::hard_link_count;
            using boost::filesystem::last_write_time;
            using boost::filesystem::permissions;
            using boost::filesystem::read_symlink;
            using boost::filesystem::remove;
            using boost::filesystem::remove_all;
            using boost::filesystem::rename;
            using boost::filesystem::resize_file;
            using boost::filesystem::space;
            using boost::filesystem::status;
            using boost::filesystem::symlink_status;
            using boost::filesystem::temp_directory_path;
            using boost::filesystem::is_block_file;
            using boost::filesystem::is_character_file;
            using boost::filesystem::is_directory;
            using boost::filesystem::is_empty;
            using boost::filesystem::is_fifo;
            using boost::filesystem::is_other;
            using boost::filesystem::is_regular_file;
            using boost::filesystem::is_socket;
            using boost::filesystem::is_symlink;
            using boost::filesystem::status_known;
        } // namespace filesystem
    } // namespace unboost
#elif defined(UNBOOST_USE_WIN32_FILESYSTEM) || defined(UNBOOST_USE_POSIX_FILESYSTEM)
    #include "system_error.hpp"     // for unboost::system_error
    namespace unboost {
        namespace filesystem {
            class path;
            path operator/(const path& lhs, const path& rhs);

            struct file_type {
                enum inner {
                    none = 0,
                    not_found = -1,
                    regular = 1,
                    directory = 2,
                    symlink = 3,
                    block = 4,
                    character = 5,
                    fifo = 6,
                    socket = 7,
                    unknown = 8
                };
            }; // struct file_type

            struct perms {
                enum inner {
                    none = 0,
                    owner_read = 0400,
                    owner_write = 0200,
                    owner_exec = 0100,
                    owner_all = 0700,
                    group_read = 040,
                    group_write = 020,
                    group_exec = 010,
                    group_all = 070,
                    others_read = 04,
                    others_write = 02,
                    others_exec = 01,
                    others_all = 07,
                    all = 0777,
                    set_uid = 04000,
                    set_gid = 02000,
                    sticky_bit = 01000,
                    mask = 07777,
                    unknown = 0xFFFF,
                    add_perms = 0x10000,
                    remove_perms = 0x20000,
                    resolve_symlinks = 0x40000
                };
            }; // struct perms

            struct directory_options {
                enum inner {
                    none,
                    follow_directory_symlink,
                    skip_permission_denied
                };
            }; // struct directory_options

            struct file_status {
                file_type::inner    m_type;
                perms::inner        m_permissions;

                explicit file_status(file_type::inner type = file_type::none,
                                     perms::inner permissions = perms::unknown)
                {
                    m_type = type;
                    m_permissions = permissions;
                }
                file_type::inner type() const {
                    return m_type;
                }
                void type(file_type::inner type) {
                    m_type = type;
                }
                perms::inner permissions() const {
                    return m_permissions;
                }
                void permissions(perms::inner perm) {
                    m_permissions = perm;
                }
            }; // struct file_status

            inline bool status_known(file_status s) {
                return s.type() != file_type::none;
            }

            inline bool exists(file_status s) {
                return status_known(s) && s.type() != file_type::not_found;
            }
            inline bool exists(const path& p, error_code& ec) {
                return exists(status(p, ec));
            }
            inline bool exists(const path& p) {
                error_code ec;
                if (exists(p, ec)) {
                    return true;
                }
                throw ec;
            }

            inline bool is_block_file(file_status s) {
                return s.type() == file_type::block;
            }
            inline bool is_block_file(const path& p) {
                return is_block_file(status(p));
            }
            inline bool is_block_file(const path& p, error_code& ec) {
                return is_block_file(status(p, ec));
            }

            inline bool is_character_file(file_status s) {
                return s.type() == file_type::character;
            }
            inline bool is_character_file(const path& p) {
                return is_character_file(status(p));
            }
            inline bool is_character_file(const path& p, error_code& ec) {
                return is_character_file(status(p, ec));
            }

            inline bool is_empty(const path& p) {
            }
            inline bool is_empty(const path& p, error_code& ec) {
            }

            inline bool is_fifo(file_status s) {
                return s.type() == file_type::fifo;
            }
            inline bool is_fifo(const path& p) {
                return is_fifo(status(p));
            }
            inline bool is_fifo(const path& p, error_code& ec) {
                return is_fifo(status(p, ec));
            }

            inline bool is_regular_file(file_status s) {
                return s.type() == file_type::regular;
            }
            inline bool is_regular_file(const path& p) {
                return is_regular_file(status(p));
            }
            inline bool is_regular_file(const path& p, error_code& ec) {
                return is_regular_file(status(p, ec));
            }

            inline bool is_symlink(file_status s) {
                return s.type() = file_type::symlink;
            }
            inline bool is_symlink(const path& p) {
                return is_symlink(status(p));
            }
            inline bool is_symlink(const path& p, error_code& ec) {
                return is_symlink(status(p, ec));
            }

            inline bool is_directory(file_status s) {
                return s.type() == file_type::directory;
            }
            inline bool is_directory(const path& p) {
                return is_directory(status(p));
            }
            inline bool is_directory(const path& p, error_code& ec) {
                return is_directory(status(p, ec));
            }

            inline bool is_other(file_status s) {
                return exists(s) && !is_regular_file(s) && !is_directory(s) &&
                       !is_symlink(s);
            }
            inline bool is_other(const path& p) {
                return is_other(status(p));
            }
            inline bool is_other(const path& p, error_code& ec) {
                return is_other(status(p, ec));
            }

            inline bool is_socket(file_status s) {
                return s.type() == file_type::socket;
            }
            inline bool is_socket(const path& p) {
                return is_socket(status(p));
            }
            inline bool is_socket(const path& p, error_code& ec) {
                return is_socket(status(p, ec));
            }

            inline file_status status(const path& p, error_code& ec) {
                #ifdef _WIN32
                    DWORD attrs = ::GetFileAttributesW(p.c_str());
                    file_type::inner type;
                    if (attrs == DWORD(-1))
                        type = file_type::not_found;
                    else if (attrs & FILE_ATTRIBUTE_DIRECTORY)
                        type = file_type::directory;
                    else if (attrs & FILE_ATTRIBUTE_DEVICE)
                        type = file_type::character;
                    else
                        type = file_type::regular;
                    perms::inner permissions;
                    ...
                #else
                    ...
                #endif
                file_status fs(type, permissions);
                return fs;
            }
            inline file_status status(const path& p) {
                error_code ec;
                file_status ret = status(p, ec);
                if (ec)
                    throw ec;
                return ret;
            }

            inline file_status symlink_status(const path& p, error_code& ec) {
                #ifdef _WIN32
                    return status(p, ec);
                #else
                    ...
                    file_status fs(type, permissions);
                    return fs;
                #endif
            }
            inline file_status symlink_status(const path& p) {
                error_code ec;
                file_status ret = symlink_status(p, ec);
                if (ec)
                    throw ec;
                return ret;
            }

            class path {
            public:
                #ifdef _WIN32
                    typedef wchar_t value_type;
                #else
                    typedef char value_type;
                #endif
                typedef std::basic_string<value_type>               string_type;
                struct const_iterator {
                    string_type m_root_name;
                    string_type m_root_directory;
                    std::vector<string_type> m_entries;
                    ...
                };
                typedef const_iterator                              iterator;

                static const value_type preferred_separator;

                path() { }
                path(const path& p) : m_str(p.m_str), m_comps(p.m_comps) { }
                path(path&& p)
                    : m_str(std::move(p.m_str)), m_comps(std::move(p.m_comps))
                { }
                template <class Source>
                path(const Source& source) {
                    ...
                }
                template <typename InputIt>
                path(InputIt first, InputIt last) {
                    ...
                }
                template <class Source>
                path(const Source& source, const std::locale& loc) {
                    ...
                    switch (sizeof(Source::value_type)) {
                    case 1:
                        m_str = source.m_str;
                        ...
                        break;
                    case 2:
                        ...
                        break;
                    case 4:
                        ...
                        break;
                    default:
                        assert(0);
                    }
                }
                template <typename InputIt>
                path(InputIt first, InputIt last, const std::locale& loc) {
                    ...
                }
                ~path() {
                    ...
                }

                path& operator=(const path& p) {
                    m_str = p.m_str;
                    return *this;
                }
                path& operator=(path&& p) {
                    m_str = std::move(p.m_str);
                    return *this;
                }
                template <class Source>
                path& operator=(const Source& source) {
                    *this = path(source);
                    return *this;
                }

                template <class Source>
                path& assign(const Source& source) {
                    *this = path(source);
                    return *this;
                }
                template <typename InputIt>
                path& assign(InputIt first, InputIt last) {
                    *this = path(first, last);
                    return *this;
                }

                path& operator/=(const path& p) {
                    if (empty() || p.empty() ||
                        _is_separator(native().back()) ||
                        _is_separator(p.native().front())
                    {
                        m_str += p.native();
                        m_comps.push_back(p.native());
                    } else {
                        m_str += preferred_separator;
                        m_str += p.native();
                        m_comps.push_back(p.native());
                    }
                    return *this;
                }
                template <class Source>
                path& append(const Source& source) {
                    *this /= path(source);
                    return *this;
                }
                template <typename InputIt>
                path& append(InputIt first, InputIt last) {
                    *this /= path(first, last);
                    return *this;
                }
                template <class Source>
                path& operator/=(const Source& source) {
                    *this /= path(source);
                    return *this;
                }

                iterator begin() const {
                    ...
                }
                iterator end() const {
                    ...
                }

                path& operator+=(const path& p) {
                    m_str += p.native();
                    m_comps.insert(m_comps.end(), p.m_comps.begin(), p.m_comps.end());
                    return *this;
                }
                path& operator+=(const string_type& str) {
                    m_str += str;
                    m_comps.back() += str;
                    return *this;
                }
                path& operator+=(const value_type *ptr) {
                    m_str += ptr;
                    m_comps.back() += ptr;
                    return *this;
                }
                path& operator+=(value_type x) {
                    m_str += x;
                    m_comps.back() += x;
                    return *this;
                }
                template <class Source>
                path& operator+=(const Source& source) {
                    *this += path(source);
                    return *this;
                }
                template <class CharT>
                path& operator+=(CharT x) {
                    std::basic_string<CharT> str;
                    str += x;
                    *this += path(str);
                    return *this;
                }
                template <class Source>
                path& concat(const Source& source) {
                    *this += path(source);
                    return *this;
                }
                template <typename InputIt>
                path& concat(InputIt first, InputIt last) {
                    *this += path(first, last);
                    return *this;
                }

                void clear() {
                    m_str.clear();
                    m_comps.clear();
                }
                path& make_preferred() {
                    #ifdef _WIN32
                        unboost::replace_all(m_str, L'/', L'\\');
                    #endif
                    return *this;
                }

                path& remove_filename() {
                    assert(has_filename());
                    #ifdef _WIN32
                        size_t m, n;
                        m = m_str.rfind(L'/');
                        n = m_str.rfind(L'\\');
                        if (m != string_type::npos && n != string_type::npos) {
                            if (m < n) {
                                m_str = m_str.substr(0, n);
                            } else {
                                m_str = m_str.substr(0, m);
                            }
                        } else if (m != string_type::npos) {
                            m_str = m_str.substr(0, m);
                        } else if (n != string_type::npos) {
                            m_str = m_str.substr(0, n);
                        }
                    #else
                        size_t m = m_str.rfind(L'/');
                        if (m != string_type::npos) {
                            m_str = m_str.substr(0, m);
                        }
                    #endif
                    m_comps.pop_back();
                    return *this;
                }

                path& replace_filename(const path& replacement) {
                    assert(has_filename());
                    remove_filename();
                    *this /= replacement;
                    return *this;
                }

                path& replace_extension(const path& replacement = path()) {
                    if (!extension().empty()) {
                        _remove_extension();
                    }
                    if (!replacement.empty() && replacement.native().front() != _dot()) {
                        *this += _dot();
                    }
                    *this += replacement;
                    return *this;
                }

                void swap(path& other) {
                    std::swap(m_str, other.m_str);
                    std::swap(m_comps, other.m_comps);
                }

                const value_type *c_str() const {
                    return native().c_str();
                }
                const string_type& native() const {
                    return m_str;
                }
                operator string_type() const {
                    return m_str;
                }

                template <typename CharT, class Traits = std::char_traits<CharT> >
                std::basic_string<CharT, Traits> string() const {
                    std::basic_string<CharT, Traits> ret;
                    switch (sizeof(CharT)) {
                    case 1:
                        ret = ...;
                    case 2:
                        ret = ...;
                    case 4:
                        ret = ...;
                    default:
                        assert(0);
                    }
                    return ret;
                }
                std::string string() const {
                    return m_str;
                }
                std::wstring wstring() const {
                    if (sizeof(wchar_t) == 2)
                        return u16string();
                    if (sizeof(wchar_t) == 4)
                        return u32string();
                    assert(0);
                    return L"";
                }
                std::string u8string() const {
                    ...
                }
                std::u16string u16string() const {
                    ...
                }
                std::u32string u32string() const {
                    ...
                }

                template <typename CharT, class Traits = std::char_traits<CharT> >
                std::basic_string<CharT, Traits> generic_string() const {
                    std::basic_string<CharT, Traits> ret;
                    switch (sizeof(CharT)) {
                    case 1:
                        ret = m_str;
                        break;
                    case 2:
                        ret = m_str;
                        break;
                    case 4:
                        ret = m_str;
                        break;
                    default:
                        assert(0);
                    }
                    return ret;
                }
                std::string generic_string() const {
                    ...
                }
                std::wstring generic_wstring() const {
                    ...
                }
                std::string generic_u8string() const {
                    ...
                }
                std::u16string generic_u16string() const {
                    ...
                }
                std::u32string generic_u32string() const {
                    ...
                }

                int compare(const path& p) const {
                    string_type::const_iterator it1, end1, it2, end2;
                    it1 = native().begin();
                    end1 = native().end();
                    it2 = p.native().begin();
                    end2 = p.native().end();
                    for (;;) {
                        if (it1 == end1 || it2 == end2)
                            break;
                        if (*it1 < *it2)
                            return -1;
                        if (*it1 > *it2)
                            return 1;
                        ++it1;
                        ++it2;
                    }
                    if (it1 == end1 && it2 == end2)
                        return 0;
                    if (it1 == end1)
                        return -1;
                    return 1;
                }
                int compare(const string_type& str) const {
                    return compare(path(str));
                }
                int compare(const value_type *s) const {
                    return compare(path(s));
                }

                path root_name() const {
                    if (empty()) {
                        path p;
                        return p;
                    }
                    #ifdef _WIN32
                        // C:
                        if (m_str[1] == L':' &&
                            std::isalpha(m_str[0]))
                        {
                            path p(m_str.substr(0, 2));
                            return p;
                        }
                        // \\server
                        if (m_str.substr(0, 2) == L"\\\\") {
                            size_t i = 2;
                            while (std::is_alnum(m_str[i])) {
                                ++i;
                            }
                            path p(m_str.substr(0, i));
                            return p;
                        }
                    #else
                        if (m_str[0] == '/') {
                            return path("/");
                        }
                    #endif
                }
                path root_directory() const {
                    ...
                }
                path root_path() const {
                    return root_name() / root_directory();
                }

                path relative_path() const {
                    path p(++begin(), end());
                    return p;
                }

                path parent_path() const {
                    if (empty() || begin() == --end())
                        return path();
                    path p(begin(), --end());
                    return p;
                }

                path filename() const {
                    return empty() ? path() : *--end();
                }

                path stem() const {
                    path p = filename();
                    p._remove_extension();
                    return p;
                }

                path extension() const {
                    string_type fname = filename().native();
                    size_t i = fname.rfind('.');
                    if (i == string_type::npos ||
                        fname == "." || fname == "..")
                    {
                        path p;
                        return p;
                    } else {
                        path p(&fname[i]);
                        return p;
                    }
                }

                bool empty() const {
                    return m_str.empty();
                }

                bool has_root_path() const {
                    return !root_path().empty();
                }
                bool has_root_name() const {
                    return !root_name().empty();
                }
                bool has_root_directory() const {
                    return !root_directory().empty();
                }
                bool has_relative_path() const {
                    return !relative_path().empty();
                }
                bool has_parent_path() const {
                    return !parent_path().empty();
                }
                bool has_filename() const {
                    return !filename().empty();
                }
                bool has_stem() const {
                    return !stem().empty();
                }
                bool has_extension() const {
                    return !extension().empty();
                }

                bool is_absolute() const {
                    error_code ec;
                    return exists(root_path(), ec);
                }

                bool is_relative() const {
                    return !is_absolute();
                }
            protected:
                string_type                 m_str;
                std::vector<string_type>    m_comps;
                bool _is_separator(value_type ch) const {
                    #ifdef _WIN32
                        return ch == L'\\' || ch == L'/';
                    #else
                        return ch == '/';
                    #endif
                }
                value_type _dot() const {
                    #ifdef _WIN32
                        return L'.';
                    #else
                        return '.';
                    #endif
                }
                void _remove_extension() {
                    if (extension().empty())
                        return;
                    size_t i = p.m_str.rfind(_dot());
                    if (i != string_type::npos) {
                        p.m_str = p.m_str.substr(0, i);
                        i = m_comps.back().rfind(_dot());
                        assert(i != string_type::npos);
                        m_comps.back() = m_comps.back().substr(0, i);
                    }
                }
            }; // class path

            #ifdef _WIN32
                /*static*/ const value_type path::preferred_separator = L'\\';
            #else
                /*static*/ const value_type path::preferred_separator = '/';
            #endif

            template <class CharT, class Traits>
            inline std::basic_istream<CharT, Traits>&
            operator>>(std::basic_istream<CharT, Traits>& is, path& p) {
                std::basic_string<CharT, Traits> t;
                is >> std::quoted(t);
                p = t;
                return is;
            }

            template <class CharT, class Traits>
            inline std::basic_ostream<CharT, Traits>&
            operator<<(std::basic_ostream<CharT, Traits>& os, const path& p)
            {
                os << std::quoted(p.string<CharT, Traits>());
                return os;
            }

            template <class Source>
            inline path u8path(const Source& source) {
                ...
            }
            template <typename InputIt>
            inline path u8path(InputIt first, InputIt last) {
                ...
            }

            template <>
            inline void swap(path& lhs, path& rhs) {
                lhs.swap(rhs);
            }

            inline path operator/(const path& lhs, const path& rhs) {
                return path(lhs) /= rhs;
            }

            inline bool operator<(const path& lhs, const path& rhs) {
                return lhs.compare(rhs) < 0;
            }

            inline bool operator==(const path& lhs, const path& rhs) {
                return !(lhs < rhs) && !(rhs < lhs);
            }

            inline bool operator!=(const path& lhs, const path& rhs) {
                return !(lhs == rhs);
            }

            inline bool operator<=(const path& lhs, const path& rhs) {
                return !(rhs < lhs);
            }

            inline bool operator>(const path& lhs, const path& rhs) {
                return rhs < lhs;
            }

            inline bool operator>=(const path& lhs, const path& rhs) {
                return !(lhs < rhs)
            }

            class filesystem_error {
            public:
                filesystem_error(const string& what_arg, error_code ec) {
                    m_what = what_arg;
                    m_code = ec;
                }
                filesystem_error(const string& what_arg, const path& p1, error_code ec) {
                    m_what = what_arg;
                    m_p1 = p1;
                    m_code = ec;
                }
                filesystem_error(
                    const string& what_arg, const path& p1, const path& p2, error_code ec)
                {
                    m_what = what_arg;
                    m_p1 = p1;
                    m_p2 = p2;
                    m_code = ec;
                }
                const path& path1() const {
                    return m_p1;
                }
                const path& path2() const {
                    return m_p2;
                }
                const char *what() const {
                    using namespace std;
                    #ifdef _WIN32
                        wchar_t buf[512];
                        swprintf(buf,
                            L"%s: error_code: %d",
                            (m_what + L": " + m_p1.native() + L", " + m_p2.native()).c_str(),
                            m_code
                        );
                    #else
                        char buf[512];
                        sprintf(buf,
                            "%s: error_code: %d",
                            (m_what + ": " + m_p1.native() + ", " + m_p2.native()).c_str(),
                            m_code
                        );
                    #endif
                    return buf;
                }
            protected:
                path m_p1;
                path m_p2;
                std::string m_what;
                error_code m_code;
            }; // class filesystem_error

            struct directory_entry {
                explicit directory_entry(const path& p) : m_path(p) { }
                ~directory_entry() { }
                void assign(const path& p) {
                    m_path = p;
                }
                void replace_filename(const path& p) {
                    m_path = path().parent_path() / p;
                }
                const path& path() const {
                    return m_path;
                }
                operator const path&() const {
                    return m_path;
                }
                file_status status() const {
                    return status(m_path);
                }
                file_status status(error_code& ec) const {
                    return status(m_path, ec);
                }
                file_status symlink_status() const {
                    return symlink_status(m_path);
                }
                file_status symlink_status(error_code& ec) const {
                    return symlink_status(m_path, ec);
                }
                bool operator==(const directory_entry& rhs) {
                    return path() == rhs.path();
                }
                bool operator!=(const directory_entry& rhs) {
                    return path() != rhs.path();
                }
                bool operator<(const directory_entry& rhs) {
                    return path() < rhs.path();
                }
                bool operator<=(const directory_entry& rhs) {
                    return path() <= rhs.path();
                }
                bool operator>(const directory_entry& rhs) {
                    return path() > rhs.path();
                }
                bool operator>=(const directory_entry& rhs) {
                    return path() >= rhs.path();
                }
            protected:
                path            m_path;
                file_status     m_status1;
                file_status     m_status2;
            }; // struct directory_entry

            struct directory_iterator {
                typedef directory_entry             value_type;
                typedef ptrdiff_t                   difference_type;
                typedef directory_entry *           pointer;
                typedef directory_entry&            reference;
                typedef std::input_iterator_tag     iterator_category;

                directory_iterator() : m_index(0) { }
                explicit directory_iterator(const path& p) : m_index(0) {
                    error_code ec;
                    if (is_directory(p, ec)) {
                        ...
                    }
                }
                directory_iterator(const path& p, error_code& ec) {
                    if (is_directory(p, ec)) {
                        ...
                    }
                }
                const directory_entry& operator*() const {
                    return m_entries[m_index];
                }
                const directory_entry *operator->() const {
                    return &m_entries[m_index];
                }
                directory_iterator& operator++() {
                    ++m_index;
                    if (m_entries.size() <= m_index)
                        m_index = 0;
                    return *this;
                }
                directory_iterator operator++(int) {
                    directory_iterator it = *this;
                    ++m_index;
                    if (m_entries.size() <= m_index)
                        m_index = 0;
                    return it;
                }
                directory_iterator& increment(error_code& ec) {
                    ec.clear();
                    ++m_index;
                    if (m_entries.size() <= m_index)
                        m_index = 0;
                    return *this;
                }
            protected:
                size_t                      m_index;
                std::vector<value_type>     m_entries;
            }; // class directory_iterator

            inline directory_iterator begin(directory_iterator it) {
                return it;
            }
            inline directory_iterator end(const directory_iterator&) {
                directory_iterator it;
                return it;
            }

            struct recursive_directory_iterator {
                typedef directory_entry             value_type;
                typedef ptrdiff_t                   difference_type;
                typedef const directory_entry *     pointer;
                typedef const directory_entry&      reference;
                typedef std::input_iterator_tag     iterator_category;

                recursive_directory_iterator() {
                    ...
                }
                explicit recursive_directory_iterator(const path& p,
                    directory_options::inner options = directory_options::none)
                {
                    ...
                }
                recursive_directory_iterator(const path& p,
                    directory_options::inner options, error_code& ec)
                {
                    ...
                }
                recursive_directory_iterator(const path& p, error_code& ec) {
                    ...
                }

                ~recursive_directory_iterator() {
                }

                const directory_entry& operator*() const {
                    return ...;
                }
                const directory_entry *operator->() const {
                    return ...;
                }
                options
                int depth() const {
                    return m_depth;
                }

                bool recursion_pending() const {
                    ...
                }

                recursive_directory_iterator& increment(error_code& ec) {
                    ...
                    return *this;
                }

                recursive_directory_iterator& operator++() {
                    ...;
                    return *this;
                }

                void pop() {
                    ...
                }

                void disable_recursion_pending() {
                    ...
                }
            protected:
                int m_depth;
            }; // class recursive_directory_iterator

            inline recursive_directory_iterator
            begin(recursive_directory_iterator it) {
                return it;
            }
            inline recursive_directory_iterator
            end(const recursive_directory_iterator&) {
                recursive_directory_iterator it;
                return it;
            }

            struct space_info {
                uintmax_t capacity;
                uintmax_t free;
                uintmax_t available;
            }; // struct space_info

            struct copy_options {
                enum {
                    none = 0,
                    skip_existing = 1,
                    overwrite_existing = 2,
                    update_existing = 4,
                    recursive = 8,
                    copy_symlinks = 16,
                    skip_symlinks = 32,
                    directories_only = 64,
                    create_symlinks = 128,
                    create_hard_links = 256
                };
            }; // class copy_options

            typedef chrono::time_point<
                chrono::system_clock,
                chrono::system_clock::duration> file_time_type;

            inline void current_path(const path& p, error_code& ec) {
                if (::SetCurrentDirectoryW(p.c_str())) {
                    ec.clear();
                } else {
                    ec = ::GetLastError();
                }
            }
            inline path current_path(error_code& ec) {
                WCHAR sz[MAX_PATH * 2];
                if (::GetCurrentDirectoryW(MAX_PATH * 2, sz)) {
                    path = sz;
                    ec.clear();
                } else {
                    ec = ::GetLastError();
                }
            }
            inline path current_path() {
                error_code ec;
                if (current_path(ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::current_path", ec);
            }
            inline void current_path(const path& p) {
                error_code ec;
                if (current_path(p, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::current_path", p, ec);
            }

            inline path
            absolute(const path& p, const path& base = current_path()) {
                if (p.has_root_name()) {
                    if (p.has_root_directory())
                        return p;
                    return p.root_name() / absolute(base).root_directory() /
                           absolute(base).relative_path() / p.relative_path();
                } else {
                    if (p.has_root_directory())
                        return absolute(base).root_name() / p;
                    return absolute(base) / p;
                }
            }

            inline path system_complete(const path& p, error_code& ec) {
                WCHAR sz[MAX_PATH * 2];
                WCHAR *pch;
                if (::GetFullPathNameW(p.c_str(), MAX_PATH * 2, sz, &pch)) {
                    ec.clear();
                    return path(sz);
                } else {
                    ec = ::GetLastError();
                    return path();
                }
            }
            inline path system_complete(const path& p) {
                error_code ec;
                path new_p = system_complete(p, ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::system_complete", p, ec);
                }
                return new_p;
            }

            inline path
            canonical(const path& p, const path& base, error_code& ec) {
                ...
            }
            inline path
            canonical(const path& p, const path& base = current_path()) {
                assert(exists(p));
                return absolute(p, base);
            }
            inline path
            canonical(const path& p, error_code& ec) {
                ...
                return absolute(p);
            }

            inline bool
            equivalent(const path& p1, const path& p2, error_code& ec) {
                struct stat st1, st2;
                if (stat(p1.c_str(), &st1) == 0 && stat(p2.c_str(), &st2) == 0) {
                    ec.clear();
                    return st1.st_ino == st2.st_ino;
                }
                ec = ENOENT;
                return false;
            }
            inline bool equivalent(const path& p1, const path& p2) {
                error_code ec;
                if (equivalent(p1, p2, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::equivalent", p1, p2, ec);
            }

            create_symlink
            create_directory_symlink

            inline void
            create_hard_link(const path& target, const path& link, error_code& ec) {
                ...
            }
            inline void
            create_hard_link(const path& target, const path& link) {
                error_code ec;
                if (create_hard_link(target, link, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::create_hard_link", target, link, ec);
            }

            inline void
            copy_symlink(const path& from, const path& to, error_code& ec) {
                if (is_directory(from)) {
                    create_directory_symlink(read_symlink(from), to);
                } else {
                    create_symlink(read_symlink(from), to);
                }
            }
            inline void copy_symlink(const path& from, const path& to) {
                error_code ec;
                if (copy_symlink(from, to, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::copy_symlink", from, to, ec);
            }

            inline bool
            copy_file(const path& from, const path& to, copy_options options,
                      error_code& ec)
            {
                if (to.exists()) {
                    if (equivalent(to, from, ec)) {
                        ec = ...;
                        return false;
                    }
                    switch (options) {
                    case copy_options::none:
                        ec = ...;
                        break;
                    case copy_options::skip_existing:
                        ec.clear();
                        return true;
                    case copy_options::update_existing:
                        if (last_write_time(from) >= last_write_time(to)) {
                            ec.clear();
                            return true;
                        }
                        // FALL THROUGH
                    case copy_options::overwrite_existing:
                        if (::CopyFileW(from.c_str(), to.c_str(), FALSE)) {
                            ec.clear();
                            return true;
                        } else {
                            ec = ...;
                        }
                        break;
                    }
                    return false;
                } else {
                    return ::CopyFileW(from.c_str(), to.c_str(), FALSE);
                }
            }
            inline bool
            copy_file(const path& from, const path& to, copy_options options) {
                error_code ec;
                if (copy_file(from, to, options, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::copy_file", from, to, ec);
            }
            inline bool copy_file(const path& from, const path& to) {
                return copy_file(from, to, copy_options::none);
            }
            inline bool copy_file(const path& from, const path& to, error_code& ec) {
                return copy_file(from, to, copy_options::none, ec);
            }

            inline void
            copy(const path& from, const path& to, copy_options options,
                 error_code& ec)
            {
                file_status s1 = status(from, ec);
                file_status s2 = status(to, ec);
                if (!exists(s1, ec))
                    throw filesystem_error("unboost::filesystem::copy", from, to, ec);
                if (equivalent(from, to, ec)) {
                    ec = ...;
                    throw filesystem_error("unboost::filesystem::copy", from, to, ec);
                }
                if (is_directory(s1, ec) && is_regular_file(s2, ec)) {
                    ec = ...;
                    throw filesystem_error("unboost::filesystem::copy", from, to, ec);
                }
                if (is_symlink(s1, ec)) {
                    if (options & copy_options::skip_symlinks) {
                        ec.clear();
                        return;
                    }
                    if (exists(s2) && (options & copy_options::copy_symlinks)) {
                        copy_symlink(from, to, ec);
                        return;
                    }
                    ec = ...
                    throw filesystem_error("unboost::filesystem::copy", from, to, ec);
                }
                if (is_regular_file(s1)) {
                    if (options & copy_options::directories_only) {
                        ec.clear();
                        return;
                    }
                    if (options & copy_options::create_symlinks) {
                        create_symlink(...);
                        return;
                    }
                    if (options & copy_options::create_hard_links) {
                        create_hard_link(to, from, ec);
                        return;
                    }
                    if (is_directory(s2)) {
                        copy_file(from, to / from.filename(), options, ec);
                        return;
                    }
                    copy_file(from, to, options, ec);
                    return;
                }
                if (is_directory(s1)) {
                    if ((options & copy_options::recursive) ||
                        options == copy_options::none)
                    {
                        if (!exists(s2)) {
                            create_directory(to, from, ec);
                            ...
                            return;
                        }
                    }
                }
                ec.clear();
            }
            inline void
            copy(const path& from, const path& to, copy_options options) {
                error_code ec;
                if (copy(from, to, options, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::copy", from, to, ec);
                return false;
            }
            inline void copy(const path& from, const path& to) {
                copy(from, to, copy_options::none);
            }
            inline void copy(const path& from, const path& to, error_code& ec) {
                copy(from, to, copy_options::none, ec);
            }

            inline file_time_type last_write_time(const path& p) {
            }
            inline file_time_type last_write_time(const path& p, error_code& ec) {
            }
            inline void
            last_write_time(const path& p, file_time_type new_time) {
            }
            inline void
            last_write_time(const path& p, file_time_type new_time, error_code& ec) {
            }

            inline path read_symlink(const path& p, error_code& ec) {
            }
            inline path read_symlink(const path& p) {
            }

            inline bool
            create_directory(const path& p, const path& existing_p, error_code& ec) {
                #ifdef _WIN32
                    if (::CreateDirectoryExW(existing_p.c_str(), p.c_str(), NULL)) {
                        ec.clear();
                        return true;
                    }
                    ec = ::GetLastError();
                    return false;
                #else
                    struct stat st;
                    stat(existing_p.c_str(), &st);
                    ec = mkdir(p.c_str(), st.st_mode);
                    return (ec == 0);
                #endif
            }
            inline bool
            create_directory(const path& p, const path& existing_p) {
                error_code ec;
                if (create_directory(p, existing_p, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::create_directory", p, ec);
            }
            inline bool create_directory(const path& p, error_code& ec) {
                #ifdef _WIN32
                    if (::CreateDirectoryW(p.c_str(), NULL)) {
                        ec.clear();
                        return true;
                    }
                    ec = ::GetLastError();
                    return false;
                #else
                    ec = mkdir(p.c_str());
                    return (ec == 0);
                #endif
            }
            inline bool create_directory(const path& p) {
                error_code ec;
                if (create_directory(p, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::create_directory", p, ec);
            }

            inline bool create_directories(const path& p, error_code& ec) {
                ...
            }
            inline bool create_directories(const path& p) {
                error_code ec;
                if (create_directories(p, ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::create_directories", p, ec);
            }

            inline uintmax_t file_size(const path& p, error_code& ec) {
                HANDLE hFile = ::CreateFileW(p.c_str(), GENERIC_READ,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    NULL,
                    OPEN_EXISTING,
                    FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN,
                    NULL);
                if (hFile != INVALID_HANDLE_VALUE) {
                    ULARGE_INTEGER siz;
                    siz.LowPart = GetFileSize(hFile, &siz.HighPart);
                    if (siz.LowPart != 0xFFFFFFFF || GetLastError() == NO_ERROR) {
                        ec.clear();
                        return siz.QuadPart;
                    }
                }
                ec = GetLastError();
                return 0;
            }
            inline uintmax_t file_size(const path& p) {
                error_code ec;
                uintmax_t siz = file_size(p, ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::file_size", p, ec);
                }
                return siz;
            }

            uintmax_t hard_link_count(const path& p) {
                
            }
            uintmax_t hard_link_count(const path& p, error_code& ec) {
                
            }

            inline void permissions(const path& p, perms::inner prms, error_code& ec) {
                path p0 = p;
                if (prms & perms::resolve_symlinks)
                    p0 = ...
                if ((prms & perms::add_perms) && (prms & perms::remove_perms)) {
                    ec = ...;
                    ...
                } else if (prms & perms::add_perms) {
                    ...
                } else if (prms & perms::remove_perms) {
                    ...
                } else {
                    ...
                }
                //fchmodat ...
            }
            inline void permissions(const path& p, perms::inner prms) {
                error_code ec;
                permissions(p, prms, ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::permissions", p, ec);
                }
            }

            inline bool remove(const path& p, error_code& ec) {
                BOOL result;
                if (is_directory(p)) {
                    result = ::RemoveDirectoryW(p.c_str());
                } else {
                    result = ::DeleteFileW(p.c_str());
                }
                if (result) {
                    ec.clear();
                    return true;
                } else {
                    ec = ::GetLastError();
                    return false;
                }
            }
            inline bool remove(const path& p) {
                error_code ec;
                if (!remove(p, ec)) {
                    throw filesystem_error("unboost::filesystem::remove", p, ec);
                }
                return true;
            }

            uintmax_t remove_all(const path& p, error_code& ec) {
                ...
            }
            uintmax_t remove_all(const path& p) {
                error_code ec;
                uintmax_t count = remove_all(p, ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::remove_all", p, ec);
                }
                return count;
            }

            inline void
            rename(const path& old_p, const path& new_p, error_code& ec) {
                if (!is_directory(old_p)) {
                    if (equivalent(old_p, new_p, ec))
                        return;
                    if (exists(new_p) && !is_directory(new_p)) {
                        delete(new_p);
                        ...
                    }
                    if (!exists(new_p)) {
                        rename(...);
                    }
                } else {
                    ...
                }
            }
            inline void
            rename(const path& old_p, const path& new_p) {
                error_code ec;
                rename(old_p, new_p, ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::rename", old_p, new_p, ec);
                }
            }

            inline void
            resize_file(const path& p, uintmax_t new_size, error_code& ec) {
                ec = truncate(p.c_str(), new_size);
            }
            inline void
            resize_file(const path& p, uintmax_t new_size) {
                error_code ec;
                resize_file(p, new_size, ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::resize_file", p, ec);
                }
            }

            inline space_info space(const path& p, error_code& ec) {
                space_info info;
                ULARGE_INTEGER avail, capacity, free;
                if (::GetDiskFreeSpaceExW(p.c_str(), &avail, &capacity, &free)) {
                    ec.clear();
                    info.available = avail.QuadPart;
                    info.capacity = capacity.QuadPart;
                    info.free = free.QuadPart;
                } else {
                    ec = ::GetLastError();
                    info.available = static_cast<uintmax_t>(-1);
                    info.capacity = static_cast<uintmax_t>(-1);
                    info.free = static_cast<uintmax_t>(-1);
                }
                return info;
            }
            inline space_info space(const path& p) {
                error_code ec;
                space_info info = space(p, ec);
                if (info.capacity == static_cast<uintmax_t>(-1)) {
                    throw filesystem_error("unboost::filesystem::space", p, ec);
                }
                return info;
            }

            inline path temp_directory_path(error_code& ec) {
                WCHAR sz[MAX_PATH * 2];
                if (::GetTempPathW(MAX_PATH * 2, sz)) {
                    ec.clear();
                } else {
                    ec = ::GetLastError();
                }
            }
            inline path temp_directory_path() {
                error_code ec;
                path p = temp_directory_path(ec);
                if (p.empty()) {
                    throw filesystem_error("unboost::filesystem::temp_directory_path", ec);
                }
                return p;
            }
        } // namespace filesystem
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_FILESYSTEM_HPP_
