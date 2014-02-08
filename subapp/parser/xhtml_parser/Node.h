#pragma once
#include <string>
#include <iostream>

namespace logcc {
namespace filter_parser {

struct Node {
	int id;

	Node();

	virtual ~Node() { }

	virtual void print() const;

	virtual bool match(const std::string& data) const = 0;
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

	virtual void print() const;
	
	virtual bool match(const std::string& data) const;
};

struct TextNode : public Node {
	std::string word;

	virtual void print() const;
	
	virtual bool match(const std::string& data) const;
};

} // namespace filter_parser
} // namespace logcc