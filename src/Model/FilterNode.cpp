#include "stdafx.h"
#include "FilterNode.h"

using namespace std;


FilterNode::FilterNode() {
	static int Id = 0;
	id = ++Id;
}

void FilterNode::print() const {
	cout << id << "\t";
}

void OpNode::print() const {
	if (left) left->print();
	else cout << "<null>" << endl;
	if (right) right->print();
	else cout << "<null>" << endl;
	FilterNode::print();
	cout << op << endl;
}

void TextNode::print() const {
	FilterNode::print();
	cout << word << endl;
}

bool doMatch(const FilterNode* node, const string& data) {
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

