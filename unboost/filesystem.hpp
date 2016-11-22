// filesystem.hpp --- Unboost filesystem
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_FILESYSTEM_HPP_
#define UNBOOST_FILESYSTEM_HPP_

#include "unboost.h"

#include <iterator>     // for std::input_iterator_tag

// If not choosed, choose one
#if (defined(UNBOOST_USE_CXX17_FILESYSTEM) + defined(UNBOOST_USE_BOOST_FILESYSTEM) + defined(UNBOOST_USE_UNBOOST_FILESYSTEM) == 0)
    #ifdef UNBOOST_USE_CXX17
        #define UNBOOST_USE_CXX17_FILESYSTEM
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_FILESYSTEM
    #else
        #ifdef UNBOOST_CXX17
            #define UNBOOST_USE_CXX17_FILESYSTEM
        #else
            #define UNBOOST_USE_UNBOOST_FILESYSTEM
        #endif
    #endif
#endif

#ifdef UNBOOST_USE_CXX17_FILESYSTEM
    #include <experimental/filesystem>
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
            typedef std::filesystem::copy_options copy_option;
            using std::filesystem::directory_options;
            using std::filesystem::file_time_type;
            using std::filesystem::absolute;
            using std::filesystem::system_complete;
            using std::filesystem::canonical;
            using std::filesystem::copy;
            using std::filesystem::copy_directory;
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
            // file_type
            static const file_type status_error = file_type::none;
            static const file_type file_not_found = file_type::not_found;
            static const file_type regular_file = file_type::regular;
            static const file_type directory_file = file_type::directory;
            static const file_type symlink_file = file_type::symlink;
            static const file_type block_file = file_type::block;
            static const file_type character_file = file_type::character;
            static const file_type fifo_file = file_type::fifo;
            static const file_type socket_file = file_type::socket;
            static const file_type type_unknown = file_type::unknown;
            // perms
            static const perms no_perms = perms::none;
            static const perms owner_read = perms::owner_read;
            static const perms owner_write = perms::owner_write;
            static const perms owner_exe = perms::owner_exec;
            static const perms owner_all = perms::owner_all;
            static const perms group_read = perms::group_read;
            static const perms group_write = perms::group_write;
            static const perms group_exe = perms::group_exec;
            static const perms group_all = perms::group_all;
            static const perms others_read = perms::others_read;
            static const perms others_write = perms::others_write;
            static const perms others_exe = perms::others_exec;
            static const perms others_all = perms::others_all;
            static const perms all_all = perms::all;
            static const perms set_uid_on_exe = perms::set_uid;
            static const perms set_gid_on_exe = perms::set_gid;
            static const perms sticky_bit = perms::sticky_bit;
            static const perms perms_mask = perms::mask;
            static const perms perms_not_known = perms::unknown;
            static const perms add_perms = perms::add_perms;
            static const perms remove_perms = perms::remove_perms;
            static const perms symlink_perms = perms::resolve_symlinks;
        } // namespace filesystem
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_FILESYSTEM)
    #include <boost/filesystem.hpp>
    #include <boost/system/system_error.hpp>    // for boost::system::system_error
    #include <boost/system/error_code.hpp>      // for boost::system::error_code
    namespace unboost {
        namespace filesystem {
            using boost::filesystem::path;
            using boost::filesystem::filesystem_error;
            using boost::filesystem::directory_entry;
            using boost::filesystem::directory_iterator;
            using boost::filesystem::recursive_directory_iterator;
            using boost::filesystem::file_status;
            using boost::filesystem::space_info;
            using boost::filesystem::file_type;
            using boost::filesystem::perms;
            using boost::filesystem::copy_option;
            typedef boost::filesystem::copy_option copy_options;
            //using boost::filesystem::directory_options;   // absent
            using boost::filesystem::symlink_option;
            typedef std::time_t file_time_type;
            using boost::filesystem::absolute;
            using boost::filesystem::system_complete;
            using boost::filesystem::canonical;
            using boost::filesystem::copy;
            using boost::filesystem::copy_directory;
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

            inline bool is_block_file(file_status s) {
                return s.type() == boost::filesystem::block_file;
            }
            inline bool is_block_file(const path& p) {
                return is_block_file(status(p));
            }
            inline bool is_block_file(const path& p, boost::system::error_code& ec) {
                return is_block_file(status(p, ec));
            }

            inline bool is_character_file(file_status s) {
                return s.type() == boost::filesystem::character_file;
            }
            inline bool is_character_file(const path& p) {
                return is_character_file(status(p));
            }
            inline bool is_character_file(const path& p, boost::system::error_code& ec) {
                return is_character_file(status(p, ec));
            }

            using boost::filesystem::is_directory;
            using boost::filesystem::is_empty;

            inline bool is_fifo(file_status s) {
                return s.type() == boost::filesystem::fifo_file;
            }
            inline bool is_fifo(const path& p) {
                return is_fifo(status(p));
            }
            inline bool is_fifo(const path& p, boost::system::error_code& ec) {
                return is_fifo(status(p, ec));
            }

            using boost::filesystem::is_other;
            using boost::filesystem::is_regular_file;

            inline bool is_socket(file_status s) {
                return s.type() == boost::filesystem::socket_file;
            }
            inline bool is_socket(const path& p) {
                return is_socket(status(p));
            }
            inline bool is_socket(const path& p, boost::system::error_code& ec) {
                return is_socket(status(p, ec));
            }

            using boost::filesystem::is_symlink;
            using boost::filesystem::status_known;
        } // namespace filesystem
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_FILESYSTEM)
    #include <vector>               // for std::vector
    #include <list>                 // for std::list
    #include "system_error.hpp"     // for unboost::system_error, error_code
    #include "text2text.hpp"        // for unboost::text2text
    namespace unboost {
        namespace filesystem {
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
            static const file_type::inner status_error = file_type::none;
            static const file_type::inner file_not_found = file_type::not_found;
            static const file_type::inner regular_file = file_type::regular;
            static const file_type::inner directory_file = file_type::directory;
            static const file_type::inner symlink_file = file_type::symlink;
            static const file_type::inner block_file = file_type::block;
            static const file_type::inner character_file = file_type::character;
            static const file_type::inner fifo_file = file_type::fifo;
            static const file_type::inner socket_file = file_type::socket;
            static const file_type::inner type_unknown = file_type::unknown;

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
            static const perms::inner no_perms = perms::none;
            static const perms::inner owner_read = perms::owner_read;
            static const perms::inner owner_write = perms::owner_write;
            static const perms::inner owner_exe = perms::owner_exec;
            static const perms::inner owner_all = perms::owner_all;
            static const perms::inner group_read = perms::group_read;
            static const perms::inner group_write = perms::group_write;
            static const perms::inner group_exe = perms::group_exec;
            static const perms::inner group_all = perms::group_all;
            static const perms::inner others_read = perms::others_read;
            static const perms::inner others_write = perms::others_write;
            static const perms::inner others_exe = perms::others_exec;
            static const perms::inner others_all = perms::others_all;
            static const perms::inner all_all = perms::all;
            static const perms::inner set_uid_on_exe = perms::set_uid;
            static const perms::inner set_gid_on_exe = perms::set_gid;
            static const perms::inner sticky_bit = perms::sticky_bit;
            static const perms::inner perms_mask = perms::mask;
            static const perms::inner perms_not_known = perms::unknown;
            static const perms::inner add_perms = perms::add_perms;
            static const perms::inner remove_perms = perms::remove_perms;
            static const perms::inner symlink_perms = perms::resolve_symlinks;

            struct directory_options {
                enum inner {
                    none,
                    follow_directory_symlink,
                    skip_permission_denied
                };
            }; // struct directory_options

            class file_status {
            public:
                explicit file_status(file_type::inner type = file_type::none,
                                     perms::inner permissions = perms::unknown)
                    : m_type(type), m_permissions(permissions) { }

                file_type::inner type() const       { return m_type; }
                void type(file_type::inner type)    { m_type = type; }
                perms::inner permissions() const    { return m_permissions; }
                void permissions(perms::inner perm) { m_permissions = perm; }

                bool operator==(const file_status& other) const {
                    return type() == other.type() &&
                           permissions() == other.permissions();
                }
                bool operator!=(const file_status& other) const {
                    return !(*this == other);
                }

            protected:
                file_type::inner    m_type;
                perms::inner        m_permissions;
            }; // struct file_status

            struct copy_options {
                enum inner {
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
            typedef copy_options copy_option;

            class filesystem_error;
            class path;

            inline bool status_known(file_status s) {
                return s.type() != file_type::none;
            }
            inline bool exists(file_status s) {
                return status_known(s) && s.type() != file_type::not_found;
            }
            inline bool is_block_file(file_status s) {
                return s.type() == file_type::block;
            }
            inline bool is_character_file(file_status s) {
                return s.type() == file_type::character;
            }
            inline bool is_fifo(file_status s) {
                return s.type() == file_type::fifo;
            }
            inline bool is_regular_file(file_status s) {
                return s.type() == file_type::regular;
            }
            inline bool is_symlink(file_status s) {
                return s.type() == file_type::symlink;
            }
            inline bool is_directory(file_status s) {
                return s.type() == file_type::directory;
            }
            inline bool is_other(file_status s) {
                return exists(s) && !is_regular_file(s) && !is_directory(s) &&
                       !is_symlink(s);
            }
            inline bool is_socket(file_status s) {
                return s.type() == file_type::socket;
            }

            namespace detail {
                inline text2text& get_pathansi2pathwide(void) {
                    static text2text pathansi2pathwide;
                    if (!pathansi2pathwide.is_open())
                        pathansi2pathwide.open(ENC_PATHANSI, ENC_PATHWIDE);
                    return pathansi2pathwide;
                }
                inline text2text& get_pathwide2pathansi(void) {
                    static text2text pathwide2pathansi;
                    if (!pathwide2pathansi.is_open())
                        pathwide2pathansi.open(ENC_PATHWIDE, ENC_PATHANSI);
                    return pathwide2pathansi;
                }
                #ifdef _WIN32
                    static const wchar_t dot = L'.';
                    static const wchar_t colon = L':';
                    static const wchar_t *dot_str = L".";
                    static const wchar_t *dot_dot_str = L"..";
                    static const wchar_t sep = L'/';
                    static const wchar_t *sep_str = L"/";
                    static const wchar_t preferred_sep = L'\\';
                    static const wchar_t *preferred_sep_str = L"\\";
                    static const wchar_t question_mark = L'?';
                    static const wchar_t *seps = L"\\/";
                    typedef std::wstring string_type;
                    typedef string_type::size_type size_type;
                    inline bool _is_sep(wchar_t ch) {
                        return ch == L'\\' || ch == L'/';
                    }
                    inline bool _is_dot(const std::wstring& str) {
                        return str == L"." || str == L"..";
                    }
                    inline bool _is_letter(wchar_t c) {
                        return (L'a' <= c && c <= L'z') || (L'A' <= c && c <= L'Z');
                    }
                #else
                    static const char dot = '.';
                    static const char colon = ':';
                    static const char *dot_str = ".";
                    static const char *dot_dot_str = "..";
                    static const char sep = '/';
                    static const char *sep_str = "/";
                    static const char preferred_sep = '/';
                    static const char *preferred_sep_str = "/";
                    static const char *seps = "\\/";
                    typedef std::string string_type;
                    typedef string_type::size_type size_type;
                    inline bool _is_sep(char ch) {
                        return ch == '/';
                    }
                    inline bool _is_dot(const std::string& str) {
                        return str == "." || str == "..";
                    }
                #endif

                inline size_t
                _root_dir_start(const string_type& path, size_type size) {
#ifdef _WIN32
                    // case "c:/"
                    if (size > 2 && path[1] == detail::colon && _is_sep(path[2]))
                        return 2;
#endif
                    // case "//"
                    if (size == 2 && _is_sep(path[0]) && _is_sep(path[1])) {
                        return string_type::npos;
                    }
#ifdef _WIN32
                    // case "\\?\"
                    if (size > 4 && _is_sep(path[0]) && _is_sep(path[1]) &&
                        path[2] == detail::question_mark && _is_sep(path[3]))
                    {
                        size_type pos = path.find_first_of(detail::seps, 4);
                        if (pos < size)
                            return pos;
                        return string_type::npos;
                    }
#endif
                    // case "//net {/}"
                    if (size > 3 && _is_sep(path[0]) && _is_sep(path[1]) && !_is_sep(path[2]))
                    {
                        size_type pos = path.find_first_of(detail::seps, 2);
                        if (pos < size)
                            return pos;
                        return string_type::npos;
                    }
                    // case "/"
                    if (size > 0 && _is_sep(path[0]))
                        return 0;

                    return string_type::npos;
                } // _root_dir_start

                inline bool
                _is_root_sep(const string_type & str, size_type pos) {
                    assert(!str.empty() && _is_sep(str[pos]));

                    while (pos > 0 && _is_sep(str[pos - 1]))
                        --pos;

                    if (pos == 0)
                        return true;

#ifdef _WIN32
                    if (pos == 2 && _is_letter(str[0]) && str[1] == colon) {
                        return true;
                    }
#endif
                    if (pos < 3 || !_is_sep(str[0]) || !_is_sep(str[1]))
                        return false;

                    return str.find_first_of(seps, 2) == pos;
                } // _is_root_sep

                inline size_type
                _filename_pos(const string_type& str, size_type end_pos)
                {
                    // case: "//"
                    if (end_pos == 2  && _is_sep(str[0]) && _is_sep(str[1]))
                        return 0;

                    // case: ends in "/"
                    if (end_pos && _is_sep(str[end_pos - 1]))
                        return end_pos-1;
    
                    size_type pos = str.find_last_of(detail::seps, end_pos - 1);

#ifdef _WIN32
                    if (pos == string_type::npos)
                        pos = str.find_last_of(detail::colon, end_pos - 2);
#endif
                    if (pos == string_type::npos ||
                        (pos == 1 && _is_sep(str[0])))
                    {
                        return 0;
                    }
                    return pos + 1; 
                } // _filename_pos
            } // namespace detail

            struct directory_entry;

            namespace path_traits {
                // empty
                //
                template <typename Container>
                inline bool
                empty(const Container & c) {
                    return std::begin(c) == end(c);
                }

                template <typename T>
                inline bool
                empty(T * const & c_str) {
                    assert(c_str);
                    return !*c_str;
                }

                // pathable
                //
                template <typename T>
                struct is_pathable { enum { value = 0 }; };
                template <>
                struct is_pathable<char*>                  { enum { value = 1 }; };
                template <>
                struct is_pathable<const char*>            { enum { value = 1 }; };
                template <>
                struct is_pathable<wchar_t*>               { enum { value = 1 }; };
                template <>
                struct is_pathable<const wchar_t*>         { enum { value = 1 }; };
                template <>
                struct is_pathable<std::string>            { enum { value = 1 }; };
                template <>
                struct is_pathable<std::wstring>           { enum { value = 1 }; };
                template <>
                struct is_pathable<std::vector<char> >     { enum { value = 1 }; };
                template <>
                struct is_pathable<std::vector<wchar_t> >  { enum { value = 1 }; };
                template <>
                struct is_pathable<std::list<char> >       { enum { value = 1 }; };
                template <>
                struct is_pathable<std::list<wchar_t> >    { enum { value = 1 }; };
                template <>
                struct is_pathable<directory_entry>        { enum { value = 1 }; };

                // convert
                //
                inline void
                convert(const char* from, const char* from_end,
                        std::wstring& to)
                {
                    assert(from);
                    if (from_end)
                        to = detail::get_pathansi2pathwide().from_bytes(from, from_end);
                    else
                        to = detail::get_pathansi2pathwide().from_bytes(from);
                }
                inline void
                convert(const wchar_t* from, const wchar_t* from_end,
                        std::string& to)
                {
                    assert(from);
                    if (from_end)
                        to = detail::get_pathwide2pathansi().to_bytes(from, from_end);
                    else
                        to = detail::get_pathwide2pathansi().to_bytes(from);
                }
                inline 
                void convert(const char* from, std::wstring& to) {
                    assert(from);
                    to = detail::get_pathansi2pathwide().from_bytes(from);
                }
                inline void
                convert(const wchar_t* from, std::string& to) {
                    assert(from);
                    to = detail::get_pathwide2pathansi().to_bytes(from);
                }

                inline void
                convert(const char* from, const char* from_end,
                        std::string& to)
                {
                    assert(from);
                    assert(from_end);
                    to.append(from, from_end);
                }
                inline void
                convert(const char* from, std::string& to) {
                    assert(from);
                    to += from;
                }
                inline void
                convert(const wchar_t* from, const wchar_t* from_end,
                       std::wstring& to)
                {
                    assert(from);
                    assert(from_end);
                    to.append(from, from_end);
                }
                inline void
                convert(const wchar_t* from, std::wstring & to) {
                    assert(from);
                    to += from;
                }

                // dispatch
                //
                template <typename U>
                inline void
                dispatch(const std::string& c, U& to) {
                    if (c.size())
                        convert(&*c.begin(), &*c.begin() + c.size(), to);
                }
                template <typename U>
                inline void
                dispatch(const std::wstring& c, U& to) {
                    if (c.size())
                        convert(&*c.begin(), &*c.begin() + c.size(), to);
                }
                template <typename U>
                inline void
                dispatch(const std::vector<char>& c, U& to) {
                    if (c.size())
                        convert(&*c.begin(), &*c.begin() + c.size(), to);
                }
                template <typename U>
                inline void
                dispatch(const std::vector<wchar_t>& c, U& to) {
                    if (c.size())
                        convert(&*c.begin(), &*c.begin() + c.size(), to);
                }

                template <typename Container, typename U>
                inline void
                dispatch(const Container & c, U& to) {
                    if (c.size()) {
                        std::basic_string<typename Container::value_type>
                            s(c.begin(), c.end());
                        convert(s.c_str(), s.c_str() + s.size(), to);
                    }
                }
                template <typename T, typename U>
                inline void
                dispatch(T * const & c_str, U& to) {
                    assert(c_str);
                    convert(c_str, to);
                }
                inline void
                dispatch(const directory_entry& de,
#ifdef _WIN32
                    std::wstring& to
#else
                    std::string& to
#endif
                );
            } // namespace path_traits

            class path {
            public:
                #ifdef _WIN32
                    typedef wchar_t                     value_type;
                #else
                    typedef char                        value_type;
                #endif
                typedef std::basic_string<value_type>   string_type;

                static const value_type     preferred_separator;

                // constructors
                //
                path() { }
                path(const path& p) : m_pathname(p.m_pathname) { }

                template <typename Source>
                path(const Source& source) {
                    assert(path_traits::is_pathable<Source>::value);
                    path_traits::dispatch(source, m_pathname);
                }
                path(const value_type *str) : m_pathname(str) { }
                path(const std::basic_string<value_type>& str)
                    : m_pathname(str) {}

                template <typename InputIt>
                path(InputIt first, InputIt last) {
                    if (first != last) {
                        path_traits::convert(first, last, m_pathname);
                    }
                }

                // assignments
                //
                path& operator=(const path& p) {
                    m_pathname = p.m_pathname;
                    return *this;
                }
                path& operator=(const value_type *str) {
                    m_pathname = str;
                    return *this;
                }
                template <typename Source>
                path& operator=(const Source& source) {
                    m_pathname.clear();
                    path_traits::dispatch(source, m_pathname);
                    return *this;
                }
                template <typename Source>
                path& assign(const Source& source) {
                    m_pathname.clear();
                    path_traits::dispatch(source, m_pathname);
                    return *this;
                }
                template <typename InputIt>
                path& assign(InputIt first, InputIt last) {
                    m_pathname.clear();
                    if (first != last) {
                        path_traits::convert(first, last, m_pathname);
                    }
                    return *this;
                }

                // concatenation
                //
                path& operator+=(const path& p) {
                    m_pathname += p.m_pathname;
                    return *this;
                }
                path& operator+=(const string_type& str) {
                    m_pathname += str;
                    return *this;
                }
                path& operator+=(const value_type *ptr) {
                    m_pathname += ptr;
                    return *this;
                }
                path& operator+=(value_type x) {
                    m_pathname += x;
                    return *this;
                }
                template <typename Source>
                path& operator+=(const Source& source) {
                    assert(path_traits::is_pathable<Source>::value);
                    return concat(source);
                }
                template <typename CharT>
                path& operator+=(CharT x) {
                    CharT tmp[2];
                    tmp[0] = x;
                    tmp[1] = 0;
                    return concat(tmp);
                }
                template <typename Source>
                path& concat(const Source& source) {
                    assert(path_traits::is_pathable<Source>::value);
                    path_traits::dispatch(source, m_pathname);
                    return *this;
                }
                template <typename InputIt>
                path& concat(InputIt first, InputIt last) {
                    if (first != last) {
                        path_traits::convert(first, last, m_pathname);
                    }
                    return *this;
                }

                // appends
                //
                path& operator/=(const path& p) {
                    if (empty())
                        return *this;
                    if (this == &p) {
                        path rhs(p);
                        if (!_is_sep(rhs.m_pathname[0]))
                            _append_sep_if_needed();
                        m_pathname += rhs.m_pathname;
                    } else {
                        if (!_is_sep(p.m_pathname[0]))
                            _append_sep_if_needed();
                        m_pathname += p.m_pathname;
                    }
                    return *this;
                }
                path& operator/=(const value_type *ptr) {
                    if (*ptr == 0)
                        return *this;
                    if (m_pathname.data() <= ptr &&
                        ptr < m_pathname.data() + m_pathname.size())
                    {
                        path rhs(ptr);
                        if (!_is_sep(rhs.m_pathname[0]))
                            _append_sep_if_needed();
                        m_pathname += rhs.m_pathname;
                    } else {
                        if (!_is_sep(*ptr))
                            _append_sep_if_needed();
                        m_pathname += ptr;
                    }
                    return *this;
                }
                template <typename Source>
                path& operator/=(const Source& source) {
                    return append(source);
                }
                template <typename Source>
                path& append(const Source& source) {
                    assert(path_traits::is_pathable<Source>::value);
                    if (path_traits::empty(source))
                        return *this;
                    size_type sep_pos = _append_sep_if_needed();
                    path_traits::dispatch(source, m_pathname);
                    if (sep_pos)
                        _erase_redundant_sep(sep_pos);
                    return *this;
                }
                template <typename InputIt>
                path& append(InputIt first, InputIt last) {
                    if (first == last)
                        return *this;
                    size_type sep_pos = _append_sep_if_needed();
                    path_traits::convert(first, last, m_pathname);
                    if (sep_pos)
                        _erase_redundant_sep(sep_pos);
                    return *this;
                }

                // modifiers
                //
                void clear() { m_pathname.clear(); }

                path& make_preferred() {
                    #ifdef _WIN32
                        std::replace(m_pathname.begin(), m_pathname.end(), L'/', L'\\');
                    #endif
                    return *this;
                }

                path& remove_filename() {
                    assert(has_filename());
                    m_pathname.erase(_parent_path_end());
                    return *this;
                }
                path& replace_filename(const path& replacement) {
                    assert(has_filename());
                    remove_filename();
                    *this /= replacement;
                    return *this;
                }
                path& replace_extension(const path& replacement = path()) {
                    m_pathname.erase(m_pathname.size() - extension().m_pathname.size());
                    if (!replacement.empty()) {
                        if (replacement.m_pathname[0] != detail::dot)
                            m_pathname.push_back(detail::dot);
                        m_pathname.append(replacement.m_pathname);
                    }
                    return *this;
                }
                void swap(path& other) {
                    std::swap(m_pathname, other.m_pathname);
                }

                // observers
                //
                const string_type& native() const { return m_pathname; }
                const value_type *c_str() const   { return m_pathname.c_str(); }

                std::string string() const {
                    #ifdef _WIN32
                        return detail::get_pathwide2pathansi().to_bytes(m_pathname);
                    #else
                        return m_pathname;
                    #endif
                }
                std::wstring wstring() const {
                    #ifdef _WIN32
                        return m_pathname;
                    #else
                        return detail::get_pathansi2pathwide().from_bytes(m_pathname);
                    #endif
                }
                template <typename CharT, typename Traits>
                std::basic_string<CharT, Traits>
                string() const {
                    if (sizeof(CharT) == 1)
                        return string();
                    if (sizeof(CharT) == 2)
                        return wstring();
                    assert(0);
                    return std::basic_string<CharT, Traits>();
                }

                // generic format observers
                //
                std::string generic_string() const {
                    path tmp(*this);
                    std::replace(tmp.m_pathname.begin(), tmp.m_pathname.end(), L'\\', L'/');
                    return tmp.string();
                }
                std::wstring generic_wstring() const {
                    path tmp(*this);
                    std::replace(tmp.m_pathname.begin(), tmp.m_pathname.end(), L'\\', L'/');
                    return tmp.wstring();
                }

                operator string_type() const {
                    return m_pathname;
                }

                // compare
                //
                int compare(const path& p) const {
                    //...
                    return 0;
                }
                int compare(const string_type& str) const {
                    return compare(path(str));
                }
                int compare(const value_type *ptr) const {
                    return compare(path(ptr));
                }

                // decomposition
                //
                path root_path() const {
                    path tmp(root_name());
                    if (!root_directory().empty())
                        tmp.m_pathname += root_directory().c_str();
                    return tmp;
                }
                path root_name() const;
                path root_directory() const {
                    size_type pos = detail::_root_dir_start(m_pathname, m_pathname.size());
                    if (pos == string_type::npos)
                        return path();
                    return path(m_pathname.c_str() + pos, m_pathname.c_str() + pos + 1);
                }
                path relative_path() const;
                path parent_path() const {
                    size_type end_pos = _parent_path_end();
                    if (end_pos == string_type::npos)
                        return path();
                    return path(m_pathname.c_str(), m_pathname.c_str() + end_pos);
                }
                path filename() const {
                    size_type pos = detail::_filename_pos(m_pathname, m_pathname.size());
                    if (m_pathname.size() && pos &&
                        _is_sep(m_pathname[pos]) && !
                        detail::_is_root_sep(m_pathname, pos))
                    {
                        return path(detail::dot_str);
                    }
                    return path(m_pathname.c_str() + pos);
                }
                path stem() const {
                    path name(filename());
                    if (name._is_dot())
                        return name;
                    size_type pos = name.m_pathname.rfind(detail::dot);
                    if (pos == string_type::npos)
                        return name;
                    return path(name.m_pathname.c_str(), name.m_pathname.c_str() + pos);
                }
                path extension() const {
                    path name(filename());
                    if (name._is_dot())
                        return path();
                    size_type pos = name.m_pathname.rfind(detail::dot);
                    if (pos == string_type::npos)
                        return path();
                    return path(name.m_pathname.c_str() + pos);
                }

                // query
                //
                bool empty() const { return m_pathname.empty(); }
                bool has_root_path() const      { return !root_path().empty(); }
                bool has_root_name() const      { return !root_name().empty(); }
                bool has_root_directory() const { return !root_directory().empty(); }
                bool has_relative_path() const  { return !relative_path().empty(); }
                bool has_parent_path() const    { return !parent_path().empty(); }
                bool has_filename() const       { return !filename().empty(); }
                bool has_stem() const           { return !stem().empty(); }
                bool has_extension() const      { return !extension().empty(); }
                bool is_absolute() const {
                    #ifdef _WIN32
                        return has_root_name() && has_root_directory();
                    #else
                        return has_root_directory();
                    #endif
                }
                bool is_relative() const        { return !is_absolute(); }

                // iterators
                //
                struct iterator;
                typedef iterator const_iterator;

                iterator begin() const;
                iterator end() const;

                path(path&& p);
                path& operator=(path&& p);

            protected:
                typedef string_type::size_type          size_type;
                typedef string_type::value_type         char_type;
                string_type                 m_pathname;

                bool _is_sep(char_type ch) const {
                    return detail::_is_sep(ch);
                }
                bool _is_dot() const {
                    return detail::_is_dot(m_pathname);
                }
                size_type _append_sep_if_needed() {
                    if (!m_pathname.empty() &&
#ifdef _WIN32
                        m_pathname.back() != detail::colon &&
#endif
                        !_is_sep(m_pathname.back())
                    )
                    {
                        size_type tmp = m_pathname.size();
                        m_pathname += detail::preferred_sep;
                        return tmp;
                    }
                    return 0;
                } // _append_sep_if_needed

                void _erase_redundant_sep(size_type sep_pos) {
                    if (sep_pos && sep_pos < m_pathname.size() &&
                        _is_sep(m_pathname[sep_pos + 1]))
                    {
                        m_pathname.erase(sep_pos, 1);
                    }
                } // _erase_redundant_sep

                size_type _parent_path_end() const {
                    size_type end_pos =
                        detail::_filename_pos(m_pathname, m_pathname.size());

                    bool filename_was_separator =
                        m_pathname.size() && _is_sep(m_pathname[end_pos]);

                    size_type root_dir_pos =
                        detail::_root_dir_start(m_pathname, end_pos);

                    for (; end_pos > 0 && (end_pos - 1) != root_dir_pos &&
                         _is_sep(m_pathname[end_pos - 1]);
                         --end_pos)
                    {
                    }

                    if (end_pos == 1 && root_dir_pos == 0 && filename_was_separator)
                        return string_type::npos;
                    return end_pos;
                } // _parent_path_end
            }; // class path

            struct path::iterator {
                typedef iterator                        self_type;
                typedef path                            value_type;
                typedef const path&                     reference;
                typedef const path *                    pointer;
                typedef ptrdiff_t                       difference_type;
                typedef std::bidirectional_iterator_tag iterator_category;

                reference operator*() const { return m_element; }
                pointer operator->() const  { return &m_element; }

                void increment();
                void decrement();

                self_type& operator++() {
                    increment();
                    return *this;
                }
                self_type operator++(int) {
                    self_type temp(*this);
                    increment();
                    return temp;
                }
                self_type& operator-() {
                    decrement();
                    return *this;
                }
                self_type operator--(int) {
                    self_type temp(*this);
                    decrement();
                    return temp;
                }

                path                m_element;
                const path*         m_path_ptr;
                size_type           m_pos;
            protected:
                bool _is_sep(char_type ch) const {
                    return detail::_is_sep(ch);
                }
            }; // path::iterator

            inline path path::root_name() const {
                iterator it = begin();
                if (it.m_pos != m_pathname.size() &&
                    ((it.m_element.m_pathname.size() > 1 &&
                     _is_sep(it.m_element.m_pathname[0]) &&
                     _is_sep(it.m_element.m_pathname[1]))
#ifdef _WIN32
                     || it.m_element.m_pathname.back() == detail::colon
#endif
                    ))
                {
                    return it.m_element;
                }
                return path();
            } // path path::root_name
            inline path path::relative_path() const {
                iterator it = begin();
                for (; it.m_pos != m_pathname.size() && (
                    _is_sep(it.m_element.m_pathname[0])
#ifdef _WIN32
                    || it.m_element.m_pathname.back() == detail::colon
#endif
                    ); ++it)
                {
                }
                return path(m_pathname.c_str() + it.m_pos);
            } // path::relative_path

            inline void path::iterator::increment() {
                assert(m_pos < m_path_ptr->m_pathname.size());

                m_pos += m_element.m_pathname.size();

                if (m_pos == m_path_ptr->m_pathname.size()) {
                    m_element.clear();
                    return;
                }

                bool was_net = m_element.m_pathname.size() > 2 &&
                  _is_sep(m_element.m_pathname[0]) &&
                  _is_sep(m_element.m_pathname[1]) &&
                  !_is_sep(m_element.m_pathname[2]);

                if (_is_sep(m_path_ptr->m_pathname[m_pos])) {
                    if (was_net
#ifdef _WIN32
                        || m_element.m_pathname.back() == detail::colon
#endif
                    )
                    {
                        m_element.m_pathname = detail::sep;
                        return;
                    }

                    while (m_pos != m_path_ptr->m_pathname.size() &&
                           _is_sep(m_path_ptr->m_pathname[m_pos]))
                    {
                        ++m_pos;
                    }

                    if (m_pos == m_path_ptr->m_pathname.size() &&
                        detail::_is_root_sep(m_path_ptr->m_pathname, m_pos - 1))
                    {
                        --m_pos;
                        m_element = detail::dot_str;
                    }
                }

                size_type end_pos =
                    m_path_ptr->m_pathname.find_first_of(detail::seps, m_pos);
                if (end_pos == string_type::npos)
                    end_pos = m_path_ptr->m_pathname.size();
                m_element = m_path_ptr->m_pathname.substr(m_pos, end_pos - m_pos);
            } // path::iterator::increment

            inline void path::iterator::decrement() {
                assert(m_pos > 0);

                size_type end_pos(m_pos);
                if (m_pos == m_path_ptr->m_pathname.size() &&
                    m_path_ptr->m_pathname.size() > 1 &&
                    _is_sep(m_path_ptr->m_pathname.back()) && 
                    !detail::_is_root_sep(m_path_ptr->m_pathname, m_pos - 1))
                {
                    --m_pos;
                    m_element = detail::dot_str;
                    return;
                }

                size_type root_dir_pos =
                    detail::_root_dir_start(m_path_ptr->m_pathname, end_pos);
                for (; end_pos > 0 && (end_pos - 1) != root_dir_pos &&
                     _is_sep(m_path_ptr->m_pathname[end_pos - 1]);
                     --end_pos)
                {
                    ;
                }

                m_pos = detail::_filename_pos(m_path_ptr->m_pathname, end_pos);
                m_element = m_path_ptr->m_pathname.substr(m_pos, end_pos - m_pos);
                if (m_element.m_pathname == detail::preferred_sep_str)
                    m_element.m_pathname = detail::sep_str;
            } // path::iterator::decrement

            class filesystem_error {
            public:
                filesystem_error(const std::string& what_arg, error_code ec) {
                    m_what = what_arg;
                    m_code = ec;
                }
                filesystem_error(const std::string& what_arg,
                                 const path& p1, error_code ec)
                {
                    m_what = what_arg;
                    m_p1 = p1;
                    m_code = ec;
                }
                filesystem_error(const std::string& what_arg, const path& p1,
                                 const path& p2, error_code ec)
                {
                    m_what = what_arg;
                    m_p1 = p1;
                    m_p2 = p2;
                    m_code = ec;
                }
                const path& path1() const { return m_p1; }
                const path& path2() const { return m_p2; }
                const char *what() const {
                    using namespace std;
                    static char buf[512];
                    if (m_p1.empty() && m_p2.empty()) {
                        sprintf(buf,
                            "%s: error_code: %d", m_what.c_str(), m_code);
                    } else if (m_p2.empty()) {
                        sprintf(buf, "%s: error_code: %d",
                            (m_what + ": " + m_p1.string()).c_str(),
                            m_code);
                    } else {
                        sprintf(buf, "%s: error_code: %d",
                            (m_what + ": " + m_p1.string() + ", " +
                                m_p2.string()).c_str(), m_code);
                    }
                    return buf;
                } // what
            protected:
                path m_p1;
                path m_p2;
                std::string m_what;
                error_code m_code;
            }; // class filesystem_error

            namespace detail {
                #ifdef _WIN32
                    struct handle_wrapper {
                        HANDLE m_h;
                        handle_wrapper(HANDLE h) : m_h(h) { }
                        ~handle_wrapper() {
                            if (m_h != INVALID_HANDLE_VALUE)
                                ::CloseHandle(m_h);
                        }
                    };

                    inline bool not_found_error(int ev) {
                        switch (ev) {
                        case ERROR_FILE_NOT_FOUND:
                        case ERROR_PATH_NOT_FOUND:
                        case ERROR_INVALID_NAME:
                        case ERROR_INVALID_DRIVE:
                        case ERROR_NOT_READY:
                        case ERROR_INVALID_PARAMETER:
                        case ERROR_BAD_PATHNAME:
                        case ERROR_BAD_NETPATH:
                            return true;
                        default:
                            return false;
                        }
                    }

                    file_status process_status_failure(const path& p, error_code *ec);
                    perms::inner make_permissions(const path& p, DWORD attr);
                    bool is_reparse_point_a_symlink(const path& p);
                #else   // ndef _WIN32
                    inline bool not_found_error(int errval) {
                        return errno == ENOENT || errno == ENOTDIR;
                    }
                #endif  // ndef _WIN32
            } // namespace detail

            file_status status(const path& p);
            file_status status(const path& p, error_code& ec);
            file_status symlink_status(const path& p);
            file_status symlink_status(const path& p, error_code& ec);

            inline bool exists(const path& p, error_code& ec) {
                return exists(status(p, ec));
            }
            inline bool exists(const path& p) {
                error_code ec;
                if (exists(p, ec)) {
                    return true;
                }
                throw system_error(ec);
            }

            inline bool is_block_file(const path& p) {
                return is_block_file(status(p));
            }
            inline bool is_block_file(const path& p, error_code& ec) {
                return is_block_file(status(p, ec));
            }

            inline bool is_character_file(const path& p) {
                return is_character_file(status(p));
            }
            inline bool is_character_file(const path& p, error_code& ec) {
                return is_character_file(status(p, ec));
            }

            inline bool is_fifo(const path& p) {
                return is_fifo(status(p));
            }
            inline bool is_fifo(const path& p, error_code& ec) {
                return is_fifo(status(p, ec));
            }

            inline bool is_regular_file(const path& p) {
                return is_regular_file(status(p));
            }
            inline bool is_regular_file(const path& p, error_code& ec) {
                return is_regular_file(status(p, ec));
            }

            inline bool is_symlink(const path& p) {
                return is_symlink(status(p));
            }
            inline bool is_symlink(const path& p, error_code& ec) {
                return is_symlink(status(p, ec));
            }

            inline bool is_directory(const path& p) {
                return is_directory(status(p));
            }
            inline bool is_directory(const path& p, error_code& ec) {
                return is_directory(status(p, ec));
            }

            inline bool is_other(const path& p) {
                return is_other(status(p));
            }
            inline bool is_other(const path& p, error_code& ec) {
                return is_other(status(p, ec));
            }

            inline bool is_socket(const path& p) {
                return is_socket(status(p));
            }
            inline bool is_socket(const path& p, error_code& ec) {
                return is_socket(status(p, ec));
            }

            #ifdef _WIN32
                /*static*/ const wchar_t path::preferred_separator = L'\\';
            #else
                /*static*/ const char    path::preferred_separator = '/';
            #endif

            template <typename CharT, typename Traits>
            inline std::basic_istream<CharT, Traits>&
            operator>>(std::basic_istream<CharT, Traits>& is, path& p) {
                std::basic_string<CharT, Traits> t;
                is >> t;
                p = t;
                return is;
            }

            template <typename CharT, typename Traits>
            inline std::basic_ostream<CharT, Traits>&
            operator<<(std::basic_ostream<CharT, Traits>& os, const path& p) {
                os << p.string<CharT, Traits>();
                return os;
            }

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
                return !(lhs < rhs);
            }

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
                file_status status() const {
                    return unboost::filesystem::status(m_path);
                }
                file_status status(error_code& ec) const {
                    return unboost::filesystem::status(m_path, ec);
                }
                file_status symlink_status() const {
                    return unboost::filesystem::symlink_status(m_path);
                }
                file_status symlink_status(error_code& ec) const {
                    return unboost::filesystem::symlink_status(m_path, ec);
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
                unboost::filesystem::path   m_path;
                file_status                 m_status1;
                file_status                 m_status2;
            }; // struct directory_entry

            namespace detail {
                inline void
                dispatch(const directory_entry& de,
#ifdef _WIN32
                    std::wstring& to
#else
                    std::string& to
#endif
                )
                {
                    to = de.path().native();
                }
            } // namespace detail

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
                if (current_path(p, &ec)) {
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
                path new_p = system_complete(p, &ec);
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

            inline file_time_type last_write_time(const path& p, error_code& ec) {
                ...
            }
            inline void
            last_write_time(const path& p, file_time_type new_time, error_code& ec) {
                ...
            }
            inline file_time_type last_write_time(const path& p) {
                error_code ec;
                file_time_type ret = last_write_time(p, &ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::last_write_time", p, ec);
                }
                return ret;
            }
            inline void
            last_write_time(const path& p, file_time_type new_time) {
                error_code ec;
                file_time_type ret = last_write_time(p, new_time, ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::last_write_time", p, ec);
                }
                return ret;
            }

            inline path read_symlink(const path& p, error_code& ec) {
                ...
            }
            inline path read_symlink(const path& p) {
                error_code ec;
                path ret = read_symlink(p, &ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::read_symlink", p, ec);
                }
                return ret;
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
                if (create_directory(p, &ec)) {
                    return true;
                }
                throw filesystem_error("unboost::filesystem::create_directory", p, ec);
            }

            inline bool create_directories(const path& p, error_code& ec) {
                ...
            }
            inline bool create_directories(const path& p) {
                error_code ec;
                if (create_directories(p, &ec)) {
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
                uintmax_t siz = file_size(p, &ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::file_size", p, ec);
                }
                return siz;
            }

            uintmax_t hard_link_count(const path& p, error_code& ec) {
                ...
            }
            uintmax_t hard_link_count(const path& p) {
                error_code ec;
                uintmax_t ret = hard_link_count(p, &ec);
                if (ec) {
                    throw filesystem_error("unboost::filesystem::hard_link_count", p, ec);
                }
                return ret;
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
                if (!remove(p, &ec)) {
                    throw filesystem_error("unboost::filesystem::remove", p, ec);
                }
                return true;
            }

            uintmax_t remove_all(const path& p, error_code& ec) {
                ...
            }
            uintmax_t remove_all(const path& p) {
                error_code ec;
                uintmax_t count = remove_all(p, &ec);
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
                space_info info = space(p, &ec);
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

            namespace detail {
                inline file_status
                process_status_failure(const path& p, error_code *ec) {
                    int ev = ::GetLastError();
                    if (ec)
                        *ec = ev;
                    if (not_found_error(ev)) {
                        return file_status(file_not_found, no_perms);
                    } else if (ev == ERROR_SHARING_VIOLATION) {
                        return file_status(type_unknown);
                    }
                    if (ec == NULL)
                        throw filesystem_erorr("unboost::filesystem::status", p, ev);
                    return file_status(status_error);
                }

                inline perms::inner
                make_permissions(const path& p, DWORD attr)
                {
                    unsigned int prms = owner_read | group_read | others_read;
                    if  ((attr & FILE_ATTRIBUTE_READONLY) == 0)
                        prms |= int(owner_write | group_write | others_write);
                    if (::lstrcmpiA(p.extension().string().c_str(), ".exe") == 0 ||
                        ::lstrcmpiA(p.extension().string().c_str(), ".com") == 0 ||
                        ::lstrcmpiA(p.extension().string().c_str(), ".bat") == 0 ||
                        ::lstrcmpiA(p.extension().string().c_str(), ".cmd") == 0)
                    {
                        prms |= int(owner_exe | group_exe | others_exe);
                    }
                    return static_cast<perms::inner>(prms);
                }

                inline bool
                is_reparse_point_a_symlink(const path& p) {
                    HANDLE hFile = ::CreateFileW(p.c_str(), GENERIC_READ,
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                        NULL, OPEN_EXISTING,
                        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, NULL);
                    handle_wrapper h(hFile);
                    if (hFile == INVALID_HANDLE_VALUE)
                        return false;

                    std::vector<BYTE> buf(MAXIMUM_REPARSE_DATA_BUFFER_SIZE);

                    DWORD dwRetLen;
                    BOOL result = ::DeviceIoControl(h.m_h, FSCTL_GET_REPARSE_POINT,
                        NULL, 0, buf.data(), MAXIMUM_REPARSE_DATA_BUFFER_SIZE, &dwRetLen, NULL);
                    if (!result)
                        return false;

                    REPARSE_DATA_BUFFER *pData;
                    pData = reinterpret_cast<REPARSE_DATA_BUFFER *>(buf.data());
                    return pData->ReparseTag == IO_REPARSE_TAG_SYMLINK;
                }
            } // namespace detail

            inline file_status status(const path& p, error_code& ec) {
                #ifdef _WIN32
                    DWORD attrs = ::GetFileAttributesW(p.c_str());
                    if (attrs == 0xFFFFFFFF) {
                        return process_status_failure(p, &ec);
                    }
                    if (attrs & FILE_ATTRIBUTE_REPARSE_POINT) {
                        HANDLE hFile = ::CreateFileW(p.c_str(), 0,
                            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                            NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
                        handle_wrapper h(hFile);
                        if (hFile == INVALID_HANDLE_VALUE) {
                            return process_status_failure(p, &ec);
                        }
                        if (!is_reparse_point_a_symlink(p))
                            return file_status(reparse_file, make_permissions(p, attrs));
                    }
                    if (ec)
                        ec.clear();
                    if (attrs & FILE_ATTRIBUTE_DIRECTORY)
                        return file_status(directory_file, make_permissions(p, attrs));
                    else
                        return file_status(regular_file, make_permissions(p, attrs));
                #else   // ndef _WIN32
                    using namespace std;
                    struct stat st;
                    if (stat(p.c_str(), &st)) {
                        if (ec)
                            *ec = errno;
                        if (not_found_error(errno)) {
                            return file_status(file_not_found, no_perms);
                        }
                        if (ec == NULL)
                            throw filesystem_error("unboost::filesystem::status",
                                                   p, errno);
                        return file_status(status_error);
                    }
                    if (ec)
                        ec->clear();
                    perms masked = static_cast<perms>(st.st_mode) & perms_mask;
                    if (S_ISDIR(st.st_mode))
                        return file_status(directory_file, masked);
                    if (S_ISREG(st.st_mode))
                        return file_status(regular_file, masked);
                    if (S_ISBLK(st.st_mode))
                        return file_status(block_file, masked);
                    if (S_ISCHR(st.st_mode))
                        return file_status(character_file, masked);
                    if (S_ISFIFO(st.st_mode))
                        return file_status(fifo_file, masked);
                    if (S_ISSOCK(st.st_mode))
                        return file_status(socket_file, masked);
                    return file_status(type_unknown);
                #endif  // ndef _WIN32
            } // status
            inline file_status status(const path& p) {
                error_code ec;
                file_status ret = status(p, ec);
                if (ec)
                    throw system_error(ec);
                return ret;
            }

            inline file_status
            symlink_status(const path& p, error_code& ec) {
                #ifdef _WIN32
                    DWORD attrs = ::GetFileAttributesW(p.c_str());
                    if (attrs == 0xFFFFFFFF)
                        return process_status_failure(p, ec);
                    if (ec)
                        ec->clear();
                    if (attrs & FILE_ATTRIBUTE_REPARSE_POINT) {
                        if (is_reparse_point_a_symlink(p))
                            return file_status(symlink_file, make_permissions(p, attrs));
                        else
                            return file_status(reparse_file, make_permissions(p, attrs));
                    }
                    if (attr & FILE_ATTRIBUTE_DIRECTORY)
                        return file_status(directory_file, make_permissions(p, attrs));
                    else
                        return file_status(regular_file, make_permissions(p, attrs));
                #else
                    using namespace std;
                    struct stat st;
                    if (stat(p.c_str(), &st)) {
                        if (ec)
                            *ec = errno;
                        if (not_found_error(errno)) {
                            return file_status(file_not_found, no_perms);
                        }
                        if (ec == NULL)
                            throw filesystem_error("unboost::filesystem::status",
                                                   p, errno);
                        return file_status(status_error);
                    }
                    if (ec)
                        ec->clear();
                    perms masked = static_cast<perms>(st.st_mode) & perms_mask;
                    if (S_ISREG(st.st_mode))
                        return file_status(regular_file, masked);
                    if (S_ISDIR(st.st_mode))
                        return file_status(directory_file, masked);
                    if (S_ISLNK(st.st_mode))
                        return file_status(symlink_file, masked);
                    if (S_ISBLK(st.st_mode))
                        return file_status(block_file, masked);
                    if (S_ISCHR(st.st_mode))
                        return file_status(character_file, masked);
                    if (S_ISFIFO(st.st_mode))
                        return file_status(fifo_file, masked);
                    if (S_ISSOCK(st.st_mode))
                        return file_status(socket_file, masked);
                    return file_status(type_unknown);
                #endif
            }
            inline file_status symlink_status(const path& p) {
                error_code ec;
                file_status ret = symlink_status(p, ec);
                if (ec)
                    throw system_error(ec);
                return ret;
            }

            inline bool is_empty(const path& p, error_code& ec) {
                WIN32_FILE_ATTRIBUTE_DATA fad;
                GetFileAttributesExW(p.c_str(), ::GetFileExInfoStandard, &fad);
                ...
            }
            inline bool is_empty(const path& p) {
                error_code ec;
                if (is_empty(p, &ec)) {
                    return true;
                }
                throw system_error(ec);
            }
        } // namespace filesystem
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_FILESYSTEM_HPP_
