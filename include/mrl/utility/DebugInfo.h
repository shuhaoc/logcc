#pragma once

#include <time.h>
#include <string>
#include <iostream>
#include <Windows.h>

namespace mrl {
namespace utility {

template <typename Elem>
class basic_debug_streambuf : public std::basic_streambuf<Elem> {
public:
	static const size_t InitBufferSize = 1024;

	basic_debug_streambuf() : _size(InitBufferSize) {
		setg(NULL, NULL, NULL);

		_buf = new Elem[_size];
		setp(_buf, _buf + _size - 1);
	}

	~basic_debug_streambuf() {
		delete[] _buf;
	}

	virtual int_type underflow() {
		return traits_type::eof();
	}

	virtual int sync() {
		*pptr() = 0;
		output(_buf);
		setp(_buf, _buf + _size - 1);
		return 0;
	}

	virtual int_type overflow(int_type _Meta /*= char_traits<_Elem>::eof*/) {
		increase();
		if (!traits_type::eq_int_type(_Meta, traits_type::eof())) {
			sputc(traits_type::to_char_type(_Meta));
		}
		return traits_type::not_eof(_Meta);
	}

private:
	void output(const Elem* str);

	void increase() {
		size_t new_size = _size * 2;
		Elem* new_buf = new Elem[new_size];
		memcpy(new_buf, _buf, _size * sizeof(Elem));

		setp(new_buf + _size - 1, new_buf + new_size - 1);

		delete[] _buf;
		_buf = new_buf;
		_size = new_size;
	}

	Elem* _buf;
	size_t _size;
};

inline void basic_debug_streambuf<char>::output(const char* str) {
	::OutputDebugStringA(str);
}

inline void basic_debug_streambuf<wchar_t>::output(const wchar_t* str) {
	::OutputDebugStringW(str);
}

template <typename Elem>
class basic_debug_stream : public std::basic_ostream<Elem> {
public:
	basic_debug_stream() : basic_ostream(new basic_debug_streambuf<Elem>()) {
	}

	~basic_debug_stream() {
		delete rdbuf();
	}
};

#define COUNT_ARRAY(a) (sizeof(a) / sizeof(a[0]))

template <typename Elem>
void get_cur_time_str(std::basic_string<Elem>* str);

template <>
inline void get_cur_time_str<char>(std::string* str) {
	time_t now_t;
	time(&now_t);

	char temp[64];
	tm t;
	localtime_s(&t, &now_t);
	strftime(temp, COUNT_ARRAY(temp), "%Y-%m-%d %H:%M:%S", &t);
	*str = temp;
}

template <>
inline void get_cur_time_str<wchar_t>(std::wstring* str) {
	time_t now_t;
	time(&now_t);

	wchar_t temp[64];
	tm t;
	localtime_s(&t, &now_t);
	wcsftime(temp, COUNT_ARRAY(temp), L"%Y-%m-%d %H:%M:%S", &t);
	*str = temp;
}

static basic_debug_stream<char> debug;

static basic_debug_stream<wchar_t> wdebug;

} // namespace utility
} // namespace mrl

#ifdef _DEBUG

#define DEBUG_INFOA(s) {				                                                              \
	using namespace mrl::utility;                                                            \
	std::string t;					                                                                  \
	get_cur_time_str(&t);			                                                                \
	debug << "[" << t << "] (" << __FUNCTION__ << ":" << __LINE__ << ") " << s << std::endl;	\
}

#define DEBUG_INFOW(s) {				                                                                  \
	using namespace mrl::utility;                                                                  \
	std::wstring t;					                                                                        \
	get_cur_time_str(&t);			                                                                      \
	wdebug << L"[" << t << L"] (" << __FUNCTIONW__ << L":" << __LINE__ << L") " << s << std::endl;	\
}

#else

#define DEBUG_INFOA(s)
#define DEBUG_INFOW(s)

#endif

#ifdef _UNICODE

#define DEBUG_INFO DEBUG_INFOW

#else

#define DEBUG_INFO DEBUG_INFOA

#endif