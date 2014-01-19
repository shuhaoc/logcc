#pragma once

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
	 * @author CaoShuhao
	 * @date 2014-1-19
	 */
	virtual void onQueryResultChanged() { };

	/**
	 * 滚动位置变更
	 * @author CaoShuhao
	 * @date 2014-1-20
	 */
	virtual void onScrollPositionChanged(int yPosition) { };
};