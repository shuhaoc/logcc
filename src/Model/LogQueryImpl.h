#pragma once

#include "ILogQuery.h"

class LogQueryResult;

class LogQueryImpl : public ILogQuery {
public:
	LogQueryImpl();

protected:
	virtual ~LogQueryImpl();

	virtual bool load(const tstring& filePath);

	virtual const tstring& getFilePath() const;

	virtual LogQueryResult* query(const tstring& criteria);

	virtual void setSelected(const LogItem* item);

	virtual LogItem* getSelected() const;

	virtual LogQueryResult* getCurQueryResult() const;

private:
	void setCurQueryResult(LogQueryResult* curQueryResult);

	tstring filePath;
	vector<LogItem*> logItems;
	LogQueryResult* curQueryResult;
};