#pragma once


struct FilterNode {
	int id;

	FilterNode();

	virtual ~FilterNode() { }

	virtual void print() const;

	virtual bool match(const std::string& data) const = 0;
};

struct OpNode : public FilterNode {
	std::string op;
	FilterNode* left;
	FilterNode* right;

	OpNode() : left(nullptr), right(nullptr) {
	}

	virtual ~OpNode() {
		delete left;
		delete right;
	}

	virtual void print() const;

	virtual bool match(const std::string& data) const;
};

struct TextNode : public FilterNode {
	std::string word;

	virtual void print() const;

	virtual bool match(const std::string& data) const;
};

