#pragma once

#include <string>
#include <common/tstring.h>


namespace common {
namespace utility {
namespace code_conv {

/**
 * ANSI编码（GB2312）字符串转化为Unicode编码（UTF-16）。
 * @param src	源字符串
 * @return		目标字符串
 */
std::wstring ascii_to_utf16(const std::string& src);

/**
 * Unicode编码（UTF-16）字符串转化为ANSI编码（GB2312）。
 * @param src	源字符串
 * @return		目标字符串
 */
std::string utf16_to_ascii(const std::wstring& src);

/**
 * Unicode编码（UTF-16）字符串转化为UTF8编码
 * @param src	源字符串
 * @return		目标字符串
 */
std::string utf16_to_utf8(const std::wstring& src);

} // namespace code_conv
} // namespace utility
} // namespace common