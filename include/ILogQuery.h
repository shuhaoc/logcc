#pragma once

#include <common/observer_list.h>
#include "ILogQueryObserver.h"

struct LogItem;
class LogQueryResult;
class IPatternService;

/**
 * 日志查询，每个对象对应一个日志文件
 */
class ILogQuery : public common::observer_list<ILogQueryObserver> {
public:
	virtual ~ILogQuery() { }

	/**
	 * 同步读取文件并按分行
	 * @param filePath [in] 文件路径
	 */
	virtual bool load(const tstring& filePath) = 0;

	/**
	 * 获取日志路径
	 * @return 文件路径
	 */
	virtual const tstring& getFilePath() const = 0;

	/**
	 * 设置某行为选中，其他所有行为非选中
	 * @param item [in] 日志项
	 */
	virtual void setSelected(const LogItem* item) = 0;

	/**
	 * 返回当前选中行，没有选中时返回NULL
	 * @return 选中行
	 */
	virtual LogItem* getSelected() const = 0;

	/**
	 * 条件查询
	 * @param criteria [in] 条件
	 * @return 查询结果集
	 */
	virtual LogQueryResult* query(const tstring& criteria, bool quiet = false) = 0;

protected:
	void notifyGeneralDataChanged() const {
		each_observer([] (ILogQueryObserver* p) {
			p->onGeneralDataChanged();
		});
	}

	void notifyQueryResultChanged(const tstring& criteria, LogQueryResult* queryResult) const {
		each_observer([=] (ILogQueryObserver* p) {
			p->onQueryResultChanged(criteria, queryResult);
		});
	}

	void notifyFileChanged() const {
		each_observer([] (ILogQueryObserver* p) {
			p->onFileChanged();
		});
	}
};
