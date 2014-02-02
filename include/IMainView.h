#pragma once

class LogQueryResult;

struct IMainView {
	LogQueryResult* queryResult;
	tstring curCriteria;
	unsigned selectedLine;

	IMainView() : queryResult(nullptr) { }
};