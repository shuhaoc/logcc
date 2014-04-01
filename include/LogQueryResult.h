#pragma once

struct LogItem;

/**
 * 日志查询结果集
 */
class LogQueryResult {
public:
	LogQueryResult() { }

	LogQueryResult(vector<LogItem*> queryResult) : queryResult(queryResult) {
	}

	/**
	 * 查询行数
	 */
	unsigned getCount() const {
		return queryResult.size();
	}

	/**
	 * 获取索引在[begin, end)区间内的日志行
	 * @param begin [in] 起始行
	 * @param end [in] 最后一行的下一行
	 */
	vector<LogItem*> getRange(unsigned begin, unsigned end) const {
		assert(begin <= end && end <= queryResult.size());

		vector<LogItem*> subset;
		for (unsigned i = begin; i < end; i++) {
			subset.push_back(queryResult[i]);
		}
		return subset;
	}

	/**
	 * 根据索引获取日志行
	 * @param i [in] 索引
	 * @return 日志行
	 */
	LogItem* getIndex(unsigned i) const {
		assert(i < queryResult.size());
		return queryResult[i];
	}

	/**
	 * 根据日志行查找索引，失败返回0xFFFFFFFF
	 * @param item [in] 日志行
	 * @return 索引
	 */
	unsigned findIndex(LogItem* item) const {
		assert(item);
		unsigned i = 0;
		for (; i < queryResult.size(); i++) {
			if (queryResult[i] == item) break;
		}
		if (i == queryResult.size()) i = 0xFFFFFFFF;
		return i;
	}

private:
	vector<LogItem*> queryResult;
};