#pragma once

#include "ILogQuery.h"

class LogQueryResult;
namespace mrl {
namespace utility {
class SimpleTaskMessageWindow;
}
}
namespace boost {
class thread;
}

class LogQueryImpl : public ILogQuery {
public:
	LogQueryImpl();

protected:
	virtual ~LogQueryImpl();

	virtual bool load(const tstring& filePath);

	virtual const tstring& getFilePath() const;

	virtual LogQueryResult* query(const tstring& criteria, bool quiet);

	virtual void setSelected(const LogItem* item);

	virtual LogItem* getSelected() const;

	void reset(const vector<LogItem*>& logItems);

	void reset();

private:
	void loadFile(vector<LogItem*>& logItems);

	LogQueryResult* queryImpl(const tstring& criteria);

	tstring filePath;
	vector<LogItem*> logItems;
	hash_map<tstring, LogQueryResult*> queryCache;

	mrl::utility::SimpleTaskMessageWindow* taskWnd;

	// UNDONE: 抽出复用
	void startMonitor();

	bool monitoring;
	boost::thread* monitorThread;
};