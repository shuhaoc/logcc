#pragma once

#include "ModelExport.h"

struct LogItem;

/**
 * 日志查询结果集
 */
class LogQueryResult {
public:
	LogQueryResult() { }

	LogQueryResult(vector<LogItem*> queryResult);

	/**
	 * 查询行数
	 */
	MODEL_EXPORT unsigned getCount() const;

	/**
	 * 获取索引在[begin, end)区间内的日志行
	 * @param begin [in] 起始行
	 * @param end [in] 最后一行的下一行
	 */
	MODEL_EXPORT vector<LogItem*> getRange(unsigned begin, unsigned end) const;

	/**
	 * 根据索引获取日志行
	 * @param i [in] 索引
	 * @return 日志行
	 */
	MODEL_EXPORT LogItem* getIndex(unsigned i) const;

	/**
	 * 根据日志行查找索引，失败返回0xFFFFFFFF
	 * @param item [in] 日志行
	 * @return 索引
	 */
	MODEL_EXPORT unsigned findIndex(LogItem* item) const;

private:
	vector<LogItem*> queryResult;
};