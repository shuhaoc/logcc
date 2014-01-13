#pragma once

#include "ILogQuery.h"

class LogQueryImpl : public ILogQuery {
public:
	virtual ~LogQueryImpl();

	virtual bool load(const tstring& filePath);

	virtual unsigned getLineCount() const;

	virtual const tstring& getFilePath() const;

	virtual vector<LogItem*> getRange(unsigned begin, unsigned end) const;

private:
	tstring filePath;
	vector<LogItem*> logItems;
};