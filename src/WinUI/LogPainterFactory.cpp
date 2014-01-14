#include "stdafx.h"
#include "LogPainterFactory.h"
#include "ILogItemPainter.h"
#include "LogItem.h"

class LogSingleLinePainter : public ILogItemPainter {
	virtual void Draw(HDC hdc, const RECT& rect, const LogItem& item) {
		int oldBkMode = ::SetBkMode(hdc, TRANSPARENT);

		if (item.selected) {
			HBRUSH bkgdBrush = ::CreateSolidBrush(RGB(214, 235, 255));
			HGDIOBJ oldBrush = ::SelectObject(hdc, bkgdBrush);

			::FillRect(hdc, &rect, bkgdBrush);

			::SelectObject(hdc, oldBrush);
			::DeleteObject(bkgdBrush);
		}

		std::basic_ostringstream<TCHAR> oss;
		oss << item.line << _T(" ") << item.text;
		tstring line = oss.str();

		unsigned height = rect.top - rect.bottom;
		::TextOut(hdc, rect.left, rect.top, line.c_str(), line.size());

		::SetBkMode(hdc, oldBkMode);
	}
};

SHLIB_COMMON_SINGLETON_SUPPORT_IMPLEMENT(LogPainterFactory)

LogPainterFactory::LogPainterFactory()
: singleLinePainter(new LogSingleLinePainter()) {
}

LogPainterFactory::~LogPainterFactory() {
	delete singleLinePainter;
}

ILogItemPainter* LogPainterFactory::GetSingleLinePainter() const {
	return singleLinePainter;	
}