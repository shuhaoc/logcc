#include "stdafx.h"
#include "LogPainterFactory.h"
#include "ILogItemPainter.h"
#include "LogItem.h"

class LogSingleLinePainter : public ILogItemPainter {
	virtual void Draw(HDC hdc, const RECT& rect, const LogItem& item) {
		int oldBkMode = ::SetBkMode(hdc, TRANSPARENT);

		if (item.selected) {
			HBRUSH bkgdBrush = ::CreateSolidBrush(0x00FF9933);
			HGDIOBJ oldBrush = ::SelectObject(hdc, bkgdBrush);

			::FillRect(hdc, &rect, bkgdBrush);

			::SelectObject(hdc, oldBrush);
			::DeleteObject(bkgdBrush);
		}

		std::basic_ostringstream<TCHAR> oss;
		oss << item.line << _T(" ") << item.text;
		tstring line = oss.str();

		unsigned height = rect.top - rect.bottom;
		::DrawText(hdc, line.c_str(), line.size(), const_cast<RECT*>(&rect),
			DT_NOCLIP | DT_WORDBREAK | DT_NOPREFIX | DT_EXPANDTABS);

		::SetBkMode(hdc, oldBkMode);
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