#pragma once
#include <string>
#include <map>
#include <iostream>

namespace mylib {
namespace xhtml_parser {

/**
 * Óï·¨Ê÷½áµã
 * @author CaoShuhao
 * @date 2014-2-7
 */
struct Node {
	Node() {
		static int Id = 0;
		id = ++Id;
	}

	virtual ~Node() { }

	int id;

	virtual void print() const {
		std::cout << id << "\t";
}
};

struct OpNode : public Node {
	std::string op;
	Node* left;
	Node* right;

	OpNode() : left(nullptr), right(nullptr) {
	}

	virtual ~OpNode() {
		delete left;
		delete right;
	}

	virtual void print() const {
		if (left) left->print();
		else std::cout << "<null>" << std::endl;
		if (right) right->print();
		else std::cout << "<null>" << std::endl;
		Node::print();
		std::cout << op << std::endl;
	}
};

struct TextNode : public Node {
	std::string word;

	virtual void print() const {
		Node::print();
		std::cout << word << std::endl;
	}
};

} // namespace xhtml_parser
} // namespace mylib