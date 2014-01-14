#pragma once

#include "ILogQuery.h"

class LogQueryImpl : public ILogQuery {
protected:
	virtual ~LogQueryImpl();

	virtual bool load(const tstring& filePath);

	virtual unsigned getCount() const;

	virtual const tstring& getFilePath() const;

	virtual vector<LogItem*> getRange(unsigned begin, unsigned end) const;

	virtual LogItem* getIndex(unsigned i) const;

	virtual void select(unsigned i) const;
private:
	tstring filePath;
	vector<LogItem*> logItems;
};