#pragma once

class FilterLexer {
public:
	FilterLexer(std::istream& is) : _is(is), _line(1) {
	}

	std::string read();

	std::string peek();

	int curLineNum() const { return _line; }

private:
	std::istream& _is;
	std::string _peek;
	int _line;

	void skipSpaceChar();

private:
	// warning C4512
	FilterLexer& operator = (const FilterLexer&);
};

