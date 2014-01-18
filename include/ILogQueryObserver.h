﻿#pragma once

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
	virtual void NotifyGeneralDataChanged() { };

	/**
	 * 查询结果变更
	 * @author CaoShuhao
	 * @date 2014-1-19
	 */
	virtual void NotifyQueryResultChanged() { };
};