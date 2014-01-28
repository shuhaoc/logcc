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
			bkgdBrush = ::CreateSolidBrush(0x00C36832);
			::SetTextColor(hdc, 0x00FFFFFF);
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

class LogLineDetailPainter : public ILogItemPainter {
	virtual void Draw(HDC hdc, const RECT& rect, const LogItem& item) {
		RECT drawRect = rect;
		::DrawText(hdc, item.text.c_str(), item.text.size(), &drawRect, DT_NOCLIP | DT_WORDBREAK | DT_NOPREFIX);
	}
};

SHLIB_COMMON_SINGLETON_SUPPORT_IMPLEMENT(LogPainterFactory)

LogPainterFactory::LogPainterFactory()
	: singleLinePainter(new LogSingleLinePainter())
	, lineDetailPainter(new LogLineDetailPainter()) {
}

LogPainterFactory::~LogPainterFactory() {
	delete singleLinePainter;
	delete lineDetailPainter;
}

ILogItemPainter* LogPainterFactory::GetSingleLinePainter() const {
	return singleLinePainter;
}

ILogItemPainter* LogPainterFactory::GetLineDetailPainter() const {
	return lineDetailPainter;
}