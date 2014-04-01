#include "stdafx.h"
#include "common/utility/code_conv.h"

/**
 * 多字节编码字符串转化为Unicode编码。
 * @param src_code_page		源编码类型，参见MSDN中MultiByteToWideChar中第一个参数
 * @param src				输入参数，源多字节字符串
 * @param dest				输出参数，目标Unicode字符串
 * @see						参见MSDN中MultiByteToWideChar函数
 */
void multiByteToWideChar(UINT src_code_page, const std::string& src, std::wstring& dest) {
	int wide_chars_num = MultiByteToWideChar(src_code_page, 
											 0, 
											 src.c_str(), 
											 src.size(), 
											 NULL, 
											 0);
	dest.resize(wide_chars_num);
	
	MultiByteToWideChar(src_code_page, 
						0, 
						src.c_str(), 
						src.size(), 
						const_cast<wchar_t*>(dest.c_str()),
						dest.size());
}

/**
 * Unicode编码字符串转化为多字节编码。
 * @param src_code_page		目标编码类型，参见MSDN中MultiByteToWideChar中第一个参数
 * @param src				输入参数，源Unicode字符串
 * @param dest				输出参数，目标多字节字符串的指针
 * @see						参见MSDN中MultiByteToWideChar函数
 */
void wideCharToMultiByte(UINT dest_code_page, const std::wstring& src, std::string& dest) {
	int multi_bytes_num = WideCharToMultiByte(dest_code_page,
											  0,
											  src.c_str(),
											  src.size(),
											  NULL,
											  NULL,
											  NULL,
											  NULL);
	dest.resize(multi_bytes_num);
	
	WideCharToMultiByte(dest_code_page,
						0,
						src.c_str(),
						src.size(),
						const_cast<char*>(dest.c_str()),
						dest.size(),
						NULL,
						NULL);
}

// -------------------------------------------------------------------------------------------

namespace common {
namespace utility {
namespace code_conv {

std::wstring ascii_to_utf16(const std::string& src) {
	std::wstring dest;
	multiByteToWideChar(CP_ACP, src, dest);
	return dest;
}

std::wstring utf8ToUnicode(const std::string& src) {
	std::wstring dest;
	multiByteToWideChar(CP_UTF8, src, dest);
	return dest;
}

std::string utf16_to_ascii(const std::wstring& src) {
	std::string dest;
	wideCharToMultiByte(CP_ACP, src, dest);
	return dest;
}

std::string utf16_to_utf8(const std::wstring& src) {
	std::string dest;
	wideCharToMultiByte(CP_UTF8, src, dest);
	return dest;
}

} // namespace code_conv
} // namespace utility
} // namespace common