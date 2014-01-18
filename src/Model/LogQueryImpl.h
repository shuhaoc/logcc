#pragma once

#include "ILogQuery.h"

class LogQueryResult;

class LogQueryImpl : public ILogQuery {
protected:
	virtual ~LogQueryImpl();

	virtual bool load(const tstring& filePath);

	virtual const tstring& getFilePath() const;

	virtual LogQueryResult* query(const tstring& criteria) const;

	virtual void select(unsigned i);

	virtual LogItem* getSelected() const;
private:
	tstring filePath;
	vector<LogItem*> logItems;
};