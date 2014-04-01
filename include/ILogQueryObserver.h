#pragma once

class LogQueryResult;

/**
 * 日志查询功能观察者
 */
class ILogQueryObserver {
public:
	/**
	 * 普通的数据变更
	 */
	virtual void onGeneralDataChanged() { };

	/**
	 * 查询结果变更
	 * @param criteria 查询条件
	 * @param queryResult 查询结果
	 */
	virtual void onQueryResultChanged(const tstring& /*criteria*/, LogQueryResult* /*queryResult*/) { };

	/**
	 * 文件发生变更
	 */
	virtual void onFileChanged() { }
};