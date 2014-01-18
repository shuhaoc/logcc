#pragma once

#include <mrl/common/ObserverContainer.h>
#include "ILogQueryObserver.h"

struct LogItem;

/**
 * 日志查询，每个对象对应一个日志文件
 * @author CaoShuhao
 * @date 2014-1-12
 */
class ILogQuery : public mrl::common::ObserverContainer<ILogQueryObserver> {
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
	 * 设置某行为选中，其他所有行为非选中
	 * @param i [in] 索引
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	virtual void select(unsigned i) = 0;

	/**
	 * 返回当前选中行，没有选中时返回NULL
	 * @return 选中行
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	virtual LogItem* getSelected() const = 0;
};
