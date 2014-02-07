#include <exception>
#include <sstream>
#include <cassert>
#include "GrammarTree.h"

using namespace std;

namespace logcc {
namespace filter_parser {

void GrammarTree::compile(const string& stmt) {
	_file.str(stmt);
	build();
}

void GrammarTree::reportError(const string& wanted) {
	stringstream msg;
	msg << "line " << _lexer.curLineNum() << ": syntax error, should be " + wanted + " here!";
	throw exception(msg.str().c_str());
}

GrammarTree::~GrammarTree() {
}

void GrammarTree::match(const std::string& t) {
	if (_lexer.read() != t) reportError(t);
}

void GrammarTree::build() {
	if (_file.good()) _rootNode = filter();
	else throw exception("open file error!");
}

Node* GrammarTree::filter() {
	Node* ret = nullptr;
	string first = _lexer.peek();
	if (first != "-") {
		Node* e = expr();
		Remain* r = remain();
		if (r) {
			ret = trans(e, r);
			delete r;
		} else {
			ret = e;
		}
	} else {
		OpNode* opNode = new OpNode();
		opNode->op = op();
		opNode->right = filter();
		ret = opNode;
	}
	return ret;
}

GrammarTree::Remain* GrammarTree::remain() {
	Remain* ret = nullptr;
	string first = _lexer.peek();
	if (!first.empty()) {
		// 针对括号内的特殊处理，没有反应在文法里
		if (first != ")") {
			ret = new Remain();
			ret->op = op();
			ret->expr = expr();
			ret->remain = remain();
		}
	}
	return ret;
}

Node* GrammarTree::expr() {
	Node* ret = nullptr;
	string first = _lexer.peek();
	if (first != "(") {
		if (first != ")") {
			TextNode* textNode = new TextNode();
			textNode->word = _lexer.read();
			ret = textNode;
		}
	} else {
		match("(");
		ret = filter();
		match(")");
	}
	return ret;
}

string GrammarTree::op() {
	string ret = _lexer.peek();
	if (ret == "&" || ret == "|" || ret == "-") {
		return _lexer.read();
	} else {
		reportError("OPERATOR");
		// warning C4715
		return "";
	}
}

OpNode* GrammarTree::trans(Node* left, Remain* remain) {
	assert(remain);

	OpNode* ret = new OpNode();
	ret->op = remain->op;
	ret->left = left;
	ret->right = remain->expr;

	if (remain->remain) {
		ret = trans(ret, remain->remain);
	}

	remain->expr = nullptr;

	return ret;
}


} // namespace filter_parser
} // namespace logcc