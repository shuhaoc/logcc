#pragma once

#include <string>
#include <mrl/MrlExport.h>
#include <mrl/common/tstring.h>


namespace mrl {
namespace utility {
namespace codeconv {

/**
 * ANSI编码（GB2312）字符串转化为Unicode编码（UTF-16）。
 * @param src	源字符串
 * @return		目标字符串
 */
MRL_EXPORT std::wstring asciiToUnicode(const std::string& src);

/**
 * Unicode编码（UTF-16）字符串转化为ANSI编码（GB2312）。
 * @param src	源字符串
 * @return		目标字符串
 */
MRL_EXPORT std::string unicodeToAscii(const std::wstring& src);

/**
 * Unicode编码（UTF-16）字符串转化为UTF8编码
 * @param src	源字符串
 * @return		目标字符串
 */
MRL_EXPORT std::string unicodeToUtf8(const std::wstring& src);

} // namespace codeconv
} // namespace utility
} // namespace mrl