#pragma once

struct LogItem;

/**
 * 日志行描画器接口
 * @author CaoShuhao
 * @date 2014-1-15
 */
class ILogItemPainter {
public:
	virtual ~ILogItemPainter() { }

	/**
	 * 描画方法
	 * @param hdc [in] DC句柄
	 * @param rect [in] 描画区域
	 * @param item [in] 日志行
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	virtual void Draw(HDC hdc, const RECT& rect, const LogItem& item) = 0;
};