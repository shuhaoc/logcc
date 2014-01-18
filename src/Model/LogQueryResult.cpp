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