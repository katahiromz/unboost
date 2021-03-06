// text2text.hpp --- Unboost text-to-text conversion
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_TEXT2TEXT_HPP_
#define UNBOOST_TEXT2TEXT_HPP_

#include "unboost.h"
#include "exception.hpp"    // for unboost::range_error

// If not choosed, choose one
#if (defined(UNBOOST_USE_WIN32_TEXT2TEXT) + defined(UNBOOST_USE_ICONV_TEXT2TEXT) == 0)
    #ifdef _WIN32
        #define UNBOOST_USE_WIN32_TEXT2TEXT
    #else
        #define UNBOOST_USE_ICONV_TEXT2TEXT
    #endif
#endif

namespace unboost {
    enum encoding {
        ENC_ANSI,
        ENC_SJIS,
        ENC_UTF7,
        ENC_UTF8,
        ENC_WIDE,
        ENC_PATHANSI,
        ENC_PATHWIDE
    };
} // namespace unboost

// Adapt choosed one
#ifdef UNBOOST_USE_WIN32_TEXT2TEXT
    #ifndef _INC_WINDOWS
        #ifndef NOMINMAX
            #define NOMINMAX
        #endif
        #include <windows.h>
    #endif
    #include <cstring>  // for std::strlen and std::wcslen
    namespace unboost {
        class text2text {
        public:
            typedef std::basic_string<char>         byte_string;
            typedef std::basic_string<wchar_t>      wide_string;

            text2text() { }

            text2text(encoding from, encoding to,
                      bool throw_if_error_ = false)
            {
                open(from, to, throw_if_error_);
            }

            bool open(encoding from, encoding to,
                      bool throw_if_error_ = false)
            {
                close();

                assert(_is_encoding_wide(from) != _is_encoding_wide(to));
                m_from = from;
                m_to = to;
                m_converted = 0;
                m_throw_if_error = throw_if_error_;
                return true;
            }
            void close() { }

            bool is_open() const {
                return true;
            }

            ~text2text() {
                close();
            }

            // wide string from multi-byte
            wide_string from_bytes(const char *ptr) {
                return from_bytes(ptr, ptr + std::strlen(ptr));
            }
            wide_string from_bytes(const byte_string& str) {
                return from_bytes(&str[0], &str[str.size()]);
            }
            wide_string from_bytes(const char *first, const char *last) {
                assert(m_to == ENC_WIDE || m_to == ENC_PATHWIDE);
                wide_string ret;
                m_converted = 0;

                DWORD dwFlags = 0;
                if (m_throw_if_error)
                    dwFlags |= MB_ERR_INVALID_CHARS;
                if (m_from == ENC_PATHANSI)
                    dwFlags |= MB_PRECOMPOSED;

                UINT nCP = _cp_from_encoding(m_from);
                UINT nCount = ::MultiByteToWideChar(nCP, dwFlags,
                    first, last - first, NULL, 0);
                if (nCount == 0 && ::GetLastError() == ERROR_NO_UNICODE_TRANSLATION) {
                    if (m_throw_if_error) {
                        ret.clear();
                        throw range_error("text2text::from_bytes");
                    }
                }

                ret.resize(nCount);
                m_converted = ::MultiByteToWideChar(nCP, 0, first, last - first,
                                                    &ret[0], nCount);
                return ret;
            } // from_bytes

            // wide string to multi-byte
            byte_string to_bytes(const wchar_t *ptr) {
                using namespace std;
                return to_bytes(ptr, ptr + wcslen(ptr));
            }
            byte_string to_bytes(const wide_string& wstr) {
                return to_bytes(&wstr[0], &wstr[wstr.size()]);
            }
            byte_string to_bytes(const wchar_t *first, const wchar_t *last) {
                assert(m_from == ENC_WIDE || m_from == ENC_PATHWIDE);
                byte_string ret;

                m_converted = 0;

                DWORD dwFlags = WC_COMPOSITECHECK | WC_DEFAULTCHAR;
                if (m_to == ENC_PATHANSI)
                    dwFlags |= WC_NO_BEST_FIT_CHARS;

                UINT nCP = _cp_from_encoding(m_to);
                BOOL UsedDefChar = FALSE;
                UINT nCount = ::WideCharToMultiByte(nCP, dwFlags,
                    first, last - first, NULL, 0, NULL, &UsedDefChar);
                if (UsedDefChar) {
                    if (m_throw_if_error) {
                        ret.clear();
                        throw range_error("text2text::to_bytes");
                    }
                }

                ret.resize(nCount);
                m_converted = ::WideCharToMultiByte(nCP, dwFlags,
                    first, last - first, &ret[0], nCount, NULL, NULL);
                return ret;
            } // to_bytes

            // number of converted characters
            size_t converted() const {
                return m_converted;
            }

            bool throw_if_error() const {
                return m_throw_if_error;
            }
            void throw_if_error(bool flag) {
                m_throw_if_error = flag;
            }

        protected:
            encoding    m_from;
            encoding    m_to;
            size_t      m_converted;
            bool        m_throw_if_error;

            UINT _cp_from_encoding(encoding e) const {
                switch (e) {
                case ENC_ANSI:      return CP_ACP;
                case ENC_SJIS:      return 932;
                case ENC_UTF7:      return CP_UTF7;
                case ENC_UTF8:      return CP_UTF8;
                case ENC_WIDE:      return CP_ACP;
                case ENC_PATHWIDE: case ENC_PATHANSI:
                    if (::AreFileApisANSI())
                        return CP_ACP;
                    else
                        return CP_OEMCP;
                default:
                    assert(0);
                    return CP_ACP;
                }
            }
            bool _is_encoding_wide(encoding e) const {
                switch (e) {
                case ENC_WIDE:
                case ENC_PATHWIDE:
                    return true;
                default:
                    return false;
                }
            }
        }; // text2text
    } // namespace unboost
#elif defined(UNBOOST_USE_ICONV_TEXT2TEXT)
    #include <iconv.h>
    #include <cstring>  // for std::strlen and std::wcslen
    namespace unboost {
        class text2text {
        public:
            typedef std::basic_string<char>         byte_string;
            typedef std::basic_string<wchar_t>      wide_string;

            text2text() : m_iconv(iconv_t(-1)) { }

            text2text(encoding from, encoding to,
                      bool throw_if_error_ = false) : m_iconv(iconv_t(-1))
            {
                open(from, to, throw_if_error_);
            }

            bool open(encoding from, encoding to,
                      bool throw_if_error_ = false)
            {
                close();

                assert(_is_encoding_wide(from) != _is_encoding_wide(to));
                m_from = from;
                m_to = to;
                m_converted = 0;
                m_throw_if_error = throw_if_error_;
                m_iconv = iconv_open(_code_from_encoding(to),
                                     _code_from_encoding(from));
                assert(m_iconv != iconv_t(-1));
                return m_iconv != iconv_t(-1);
            }
            void close() {
                if (m_iconv != iconv_t(-1)) {
                    iconv_close(m_iconv);
                    m_iconv = iconv_t(-1);
                }
            }
            bool is_open() const {
                return m_iconv != iconv_t(-1);
            }

            ~text2text() {
                close();
            }

            // wide string from multi-byte
            wide_string from_bytes(const char *ptr) {
                return from_bytes(ptr, ptr + std::strlen(ptr));
            }
            wide_string from_bytes(const byte_string& str) {
                return from_bytes(&str[0], &str[str.size()]);
            }
            wide_string from_bytes(const char *first, const char *last) {
                assert(m_to == ENC_WIDE || m_to == ENC_PATHWIDE);

                wide_string ret;
                m_converted = 0;

                char *inp = const_cast<char *>(first);
                size_t in_len = last - first;

                size_t out_len = in_len;
                ret.resize(out_len);
                char *out = reinterpret_cast<char *>(&ret[0]);
                char *out_buf = out;

                size_t result;
                for (;;) {
                    result = iconv(m_iconv, &inp, &in_len, &out, &out_len);
                    if (result != size_t(-1))
                        break;
                    if (m_throw_if_error) {
                        ret.clear();
                        throw range_error("text2text::to_bytes");
                    }
                    if (errno == EILSEQ) {
                        if (out_len >= sizeof(wchar_t)) {
                            *(wchar_t *)out = L'?';
                            out += sizeof(wchar_t);
                            out_len -= sizeof(wchar_t);
                        } else {
                            break;
                        }
                        ++inp;
                        --in_len;
                        continue;
                    }
                    ret.clear();
                    return ret;
                }
                result = (out - out_buf) / sizeof(wchar_t);
                m_converted = result;
                ret.resize(result);

                return ret;
            } // from_bytes

            // wide string to multi-byte
            byte_string to_bytes(const wchar_t *ptr) {
                using namespace std;
                return to_bytes(ptr, ptr + wcslen(ptr));
            }
            byte_string to_bytes(const wide_string& wstr) {
                return to_bytes(&wstr[0], &wstr[wstr.size()]);
            }
            byte_string to_bytes(const wchar_t *first, const wchar_t *last) {
                assert(m_from == ENC_WIDE || m_from == ENC_PATHWIDE);

                byte_string ret;
                m_converted = 0;

                char *inp = const_cast<char *>(
                    reinterpret_cast<const char *>(first));
                size_t in_len =
                    reinterpret_cast<const char *>(last)
                        - reinterpret_cast<const char *>(first);

                size_t out_len = in_len * 6;
                ret.resize(out_len);
                char *out = &ret[0];
                char *out_buf = out;

                size_t result;
                for (;;) {
                    result = iconv(m_iconv, &inp, &in_len, &out, &out_len);
                    if (result != size_t(-1))
                        break;
                    if (m_throw_if_error) {
                        ret.clear();
                        throw range_error("text2text::to_bytes");
                    }
                    if (errno == EILSEQ) {
                        *out++ = '?';
                        --out_len;
                        inp += sizeof(wchar_t);
                        in_len -= sizeof(wchar_t);
                        continue;
                    }
                    ret.clear();
                    return ret;
                }

                result = (out - out_buf) * sizeof(char);
                m_converted = result;
                ret.resize(result);

                return ret;
            } // to_bytes

            // number of converted characters
            size_t converted() const {
                return m_converted;
            }

            bool throw_if_error() const {
                return m_throw_if_error;
            }
            void throw_if_error(bool flag) {
                m_throw_if_error = flag;
            }

        protected:
            iconv_t     m_iconv;
            encoding    m_from;
            encoding    m_to;
            size_t      m_converted;
            bool        m_throw_if_error;

            const char *_code_from_encoding(encoding e) const {
                switch (e) {
                case ENC_ANSI:          return "CP1252";
                case ENC_SJIS:          return "CP932";
                case ENC_UTF7:          return "UTF-7";
                case ENC_UTF8:          return "UTF-8";
                case ENC_PATHANSI:      return "UTF-8";
                case ENC_WIDE: case ENC_PATHWIDE:
                    if (sizeof(wchar_t) == 2)
                        return "UTF-16LE";
                    if (sizeof(wchar_t) == 4)
                        return "UTF-32LE";
                    // FALL THROUGH
                default:
                    assert(0);
                    return "CP1252";
                }
            }
            bool _is_encoding_wide(encoding e) const {
                switch (e) {
                case ENC_WIDE:
                case ENC_PATHWIDE:
                    return true;
                default:
                    return false;
                }
            }
        }; // text2text
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_TEXT2TEXT_HPP_
