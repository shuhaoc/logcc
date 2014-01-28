#pragma once

class LogQueryResult;

struct MainViewData {
	LogQueryResult* queryResult;
	tstring curCriteria;
	unsigned selectedLine;

	MainViewData() : queryResult(nullptr) { }
};