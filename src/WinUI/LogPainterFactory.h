#pragma once

#include <mrl/common/SingletonSupport.h>

class ILogItemPainter;

/**
 * 日志描画器工厂
 * @author CaoShuhao
 * @date 2014-1-15
 */
class LogPainterFactory : public mrl::common::SingletonSupport<LogPainterFactory> {
public:
	LogPainterFactory();

	~LogPainterFactory();

	/**
	 * 主视图中单行描画器
	 * @return 描画器
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	ILogItemPainter* GetSingleLinePainter() const;

	/**
	 * 详细视图中文本描画
	 * @return 描画器
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	ILogItemPainter* GetLineDetailPainter() const;

private:
	ILogItemPainter* singleLinePainter;
	ILogItemPainter* lineDetailPainter;
};