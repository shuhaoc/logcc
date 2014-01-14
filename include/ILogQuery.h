#pragma once

struct LogItem;

/**
 * 日志查询，每个对象对应一个日志文件
 * @author CaoShuhao
 * @date 2014-1-12
 */
class ILogQuery {
public:
	virtual ~ILogQuery() { }

	/**
	 * 同步读取文件并按分行
	 * @param filePath [in] 文件路径
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual bool load(const tstring& filePath) = 0;

	/**
	 * 获取日志路径
	 * @return 文件路径
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual const tstring& getFilePath() const = 0;

	/**
	 * 查询行数
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual unsigned getCount() const = 0;

	/**
	 * 获取索引在[begin, end)区间内的日志行
	 * @param begin [in] 起始行
	 * @param end [in] 最后一行的下一行
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual vector<LogItem*> getRange(unsigned begin, unsigned end) const = 0;

	/**
	 * 根据索引获取日志行
	 * @param i [in] 索引
	 * @return 日志行
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	virtual LogItem* getIndex(unsigned i) const = 0;

	/**
	 * 设置某行为选中，其他所有行为非选中
	 * @param i [in] 索引
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	virtual void select(unsigned i) const = 0;
};
