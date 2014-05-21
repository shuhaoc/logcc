#pragma once

#include <common/singleton_support.h>

class ILogItemPainter;

/**
 * 日志描画器工厂
 */
class LogPainterFactory : public common::singleton_support<LogPainterFactory> {
public:
	LogPainterFactory();

	~LogPainterFactory();

	/**
	 * 主视图中单行描画器
	 * @return 描画器
	 */
	ILogItemPainter* GetSingleLinePainter() const;

private:
	ILogItemPainter* singleLinePainter;
};