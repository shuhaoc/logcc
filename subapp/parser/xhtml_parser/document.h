#pragma once
#include "lexer.h"
#include "element.h"

namespace mylib {
namespace xhtml_parser {


/**
 * filter -> expr remain OR - filter
 * remain -> op expr remain OR ¦Å
 * expr -> WORD OR ( filter )
 * op -> & OR | OR -
 *
 * @author CaoShuhao
 * @date 2014-2-7
 */
class GrammarTree {
public:
	GrammarTree() : _lexer(_file) { }

	~GrammarTree();

	void load(const char* file);

	const Node* rootNode() const { return _rootNode; }

private:
	struct Remain {
		std::string op;
		Node* expr;
		Remain* remain;
		
		Remain() : expr(nullptr), remain(nullptr) {
		}

		~Remain() {
			delete expr;
			delete remain;
		}
	};

	std::ifstream _file;
	Lexer _lexer;
	Node* _rootNode;

	void reportError(const std::string& wanted);
	void match(const std::string& t);
	void build();
	Node* filter();
	Remain* remain();
	Node* expr();
	std::string op();
	OpNode* trans(Node* left, Remain* remain);
};

} // namespace xhtml_parser
} // namespace mylib