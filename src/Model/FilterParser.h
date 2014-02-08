#pragma once

#include "FilterLexer.h"
#include "FilterNode.h"


/**
 * filter -> expr remain OR - filter
 * remain -> op expr remain OR ¦Å
 * expr -> WORD OR ( filter )
 * op -> & OR | OR -
 *
 * @author CaoShuhao
 * @date 2014-2-7
 */
class FilterParser {
public:
	FilterParser() : _lexer(_file) { }

	~FilterParser();

	void compile(const std::string& stmt);

	const FilterNode* rootNode() const { return _rootNode; }

private:
	struct Remain {
		std::string op;
		FilterNode* expr;
		Remain* remain;
		
		Remain() : expr(nullptr), remain(nullptr) {
		}

		~Remain() {
			delete expr;
			delete remain;
		}
	};

	std::istringstream _file;
	FilterLexer _lexer;
	FilterNode* _rootNode;

	void reportError(const std::string& wanted);
	void match(const std::string& t);
	void build();
	FilterNode* filter();
	Remain* remain();
	FilterNode* expr();
	std::string op();
	OpNode* trans(FilterNode* left, Remain* remain);
};

