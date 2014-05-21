#include "stdafx.h"
#include "LogPainterFactory.h"
#include "ILogItemPainter.h"
#include "LogItem.h"

class LogSingleLinePainter : public ILogItemPainter {
	virtual void Draw(HDC hdc, const RECT& rect, const LogItem& item) {
		int oldBkMode = ::SetBkMode(hdc, TRANSPARENT);
		int oldTextColor = ::GetTextColor(hdc);

		// 背景
		HBRUSH bkgdBrush = NULL;
		if (item.selected) {
			bkgdBrush = ::CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
			::SetTextColor(hdc, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
		} else if (item.text.find(_T("ERROR")) != tstring::npos) {
			bkgdBrush = ::CreateSolidBrush(0x000000FF);
		} else if (item.text.find(_T("WARN")) != tstring::npos) {
			bkgdBrush = ::CreateSolidBrush(0x0000FFFF);
		} else {
			bkgdBrush = ::CreateSolidBrush(0x00FFFFFF);
		}
		HGDIOBJ oldBrush = ::SelectObject(hdc, bkgdBrush);
		::FillRect(hdc, &rect, bkgdBrush);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(bkgdBrush);

		// 文本
		std::basic_ostringstream<TCHAR> oss;
		oss << item.line << _T(" ") << item.text;
		tstring line = oss.str();

		RECT textRect = rect;
		textRect.top += 1;
		textRect.bottom -= 1;
		::DrawText(hdc, line.c_str(), line.size(), &textRect,
		           DT_NOCLIP | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX | DT_EXPANDTABS);

		::SetBkMode(hdc, oldBkMode);
		::SetTextColor(hdc, oldTextColor);
	}
};

COMMON_SINGLETON_SUPPORT_IMPLEMENT(LogPainterFactory)

LogPainterFactory::LogPainterFactory()
	: singleLinePainter(new LogSingleLinePainter()) {
}

LogPainterFactory::~LogPainterFactory() {
	delete singleLinePainter;
}

ILogItemPainter* LogPainterFactory::GetSingleLinePainter() const {
	return singleLinePainter;
}
