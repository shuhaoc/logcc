#pragma once

class LogQueryResult;

/**
 * 日志查询功能观察者
 * @author CaoShuhao
 * @date 2014-1-15
 */
class ILogQueryObserver {
public:
	/**
	 * 普通的数据变更
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	virtual void onGeneralDataChanged() { };

	/**
	 * 查询结果变更
	 * @param criteria 查询条件
	 * @param queryResult 查询结果
	 * @author CaoShuhao
	 * @date 2014-1-19
	 */
	virtual void onQueryResultChanged(const tstring& /*criteria*/, LogQueryResult* /*queryResult*/) { };

	/**
	 * 文件发生变更
	 * @author CaoShuhao
	 * @date 2014-1-28
	 */
	virtual void onFileChanged() { }
};