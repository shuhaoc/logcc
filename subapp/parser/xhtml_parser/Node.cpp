#include <cassert>
#include "Node.h"

using namespace std;

namespace logcc {
namespace filter_parser {

Node::Node() {
	static int Id = 0;
	id = ++Id;
}

void Node::print() const {
	cout << id << "\t";
}

void OpNode::print() const {
	if (left) left->print();
	else cout << "<null>" << endl;
	if (right) right->print();
	else cout << "<null>" << endl;
	Node::print();
	cout << op << endl;
}

void TextNode::print() const {
	Node::print();
	cout << word << endl;
}

bool doMatch(const Node* node, const string& data) {
	return !node || node->match(data);
}

bool OpNode::match(const string& data) const {
	if (op == "&") {
		return doMatch(left, data) && doMatch(right, data);
	} else if (op == "|") {
		return doMatch(left, data) || doMatch(right, data);
	} else if (op == "-") {
		return doMatch(left, data) && !doMatch(right, data);
	} else {
		assert(false && "operator not support");
		return false;
	}
}

bool TextNode::match(const string& data) const {
	return data.find(word) != string::npos;
}

} // namespace filter_parser
} // namespace logcc