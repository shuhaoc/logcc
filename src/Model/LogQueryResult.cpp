#include "stdafx.h"
#include "LogQueryResult.h"
#include "LogItem.h"

LogQueryResult::LogQueryResult(vector<LogItem*> queryResult)
	: queryResult(queryResult) {
}

unsigned LogQueryResult::getCount() const {
	return queryResult.size();
}

vector<LogItem*> LogQueryResult::getRange(unsigned begin, unsigned end) const {
	assert(begin <= end && end <= queryResult.size());

	vector<LogItem*> subset;
	for (unsigned i = begin; i < end; i++) {
		subset.push_back(queryResult[i]);
	}
	return subset;
}

LogItem* LogQueryResult::getIndex(unsigned i) const {
	assert(i < queryResult.size());
	return queryResult[i];
}

unsigned LogQueryResult::findIndex(LogItem* item) const {
	assert(item);
	unsigned i = 0;
	for (; i < queryResult.size(); i++) {
		if (queryResult[i] == item) break;
	}
	if (i == queryResult.size()) i = 0xFFFFFFFF;
	return i;
}