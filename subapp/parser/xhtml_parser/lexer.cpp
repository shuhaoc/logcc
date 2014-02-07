#include <cassert>
#include "lexer.h"

using namespace std;
using namespace mylib::xhtml_parser;

inline bool isSpaceChar(char c) {
	static string spaces = " \t\r\n";
	return spaces.find(c) != string::npos;
}

inline bool isOperator(char c) {
	static string operators = "&|-()";
	return operators.find(c) != string::npos;
}

void Lexer::skipSpaceChar() {
	while (_is.good() && isSpaceChar((char)_is.peek())) {
		if (_is.get() == '\n') _line++;
	}
}

string Lexer::read() {
	string ret;
	if (!_peek.empty()) {
		ret = _peek;
		_peek.clear();
		return ret;
	}

	skipSpaceChar();
	istream::traits_type::int_type first;
	while (_is.good() && (first = _is.peek()) != istream::traits_type::eof()) {
		char c = istream::traits_type::to_char_type(first);
		// FIXME: !!!
		if (isSpaceChar(c) || isOperator(c)) {
			if (ret.empty()) {
				_is.get();
				ret += c;
			}
			break;
		} else {
			_is.get();
			if (c != '\\') {
				ret += c;
			} else {
				first = _is.peek();
				if (first != istream::traits_type::eof()) {
					_is.get();
					c = istream::traits_type::to_char_type(first);
					switch (c) {
					case 's': ret += ' '; break;
					case 't': ret += '\t'; break;
					case '&':
					case '|':
					case '-':
						ret += c;
						break;
					}
				}
			}
		}
	}
	return ret;
}

string Lexer::peek() {
	if (_peek.empty()) _peek = read();
	return _peek;
}