// ListScrollView.cpp : 实现文件
//

#include "stdafx.h"
#include "ListScrollView.h"

// ListScrollView

IMPLEMENT_DYNCREATE(ListScrollView, CScrollView)

ListScrollView::ListScrollView() : _lineHeight(15) {

}

ListScrollView::~ListScrollView() {
}

void ListScrollView::insert(const tstring& text, void* data /*= nullptr*/, unsigned before /*= 0xFFFFFFFF*/) {
	Item* i = new Item();
	i->text = text;
	i->data = data;

	auto pos = before != 0xFFFFFFFF ? _itemList.begin() + before : _itemList.end();
	_itemList.insert(pos, i);
}

void ListScrollView::resetScrollSize() {
	CRect clientRect;
	GetClientRect(clientRect);
	_totalSize.cx = 0;
	// 加1是为了最后一行一定可见
	_totalSize.cy = (_itemList.size() + 1) * _lineHeight;
#define LOGCC_WINUI_CUSTOMIZE_PAGE_SIZE_LINE_SIZE
#ifdef LOGCC_WINUI_CUSTOMIZE_PAGE_SIZE_LINE_SIZE
	CSize pageSize(clientRect.Width(), clientRect.Height() / _lineHeight * _lineHeight);
	CSize lineSize(clientRect.Width(), _lineHeight);
	SetScrollSizes(MM_TEXT, _totalSize, pageSize, lineSize);
#else
	SetScrollSizes(MM_TEXT, _totalSize);
#endif
#define LOGCC_WINUI_SCROLL_TO_END_ON_UPDATE
#ifdef LOGCC_WINUI_SCROLL_TO_END_ON_UPDATE
	int y = _totalSize.cy - clientRect.Height();
	ScrollToPosition(CPoint(0, max(y, 0)));
#endif
}

void ListScrollView::scrollTo(int yScrollPos) {
	CRect clientRect;
	GetClientRect(clientRect);

	// NOTICE:	很奇怪的现象，CScrollView在OnInitUpdate之外函数SetScrollSizes，
	//			如果设置的高度小于ClientRect，虽然没有显示滚动条仍然可以滚动，这里特殊处理一下，禁止滚动
	if (clientRect.Height() >= _totalSize.cy) return;

	ScrollToPosition(CPoint(0, yScrollPos));
}

void ListScrollView::scrollDelta(int delta) {
	int yScrollPos = GetScrollPosition().y;
	yScrollPos += delta;
	scrollTo(max(yScrollPos, 0));
}

void ListScrollView::scrollLines(int count) {
	scrollDelta(_lineHeight * count);
}

void ListScrollView::scrollPages(int count) {
	CRect clientRect;
	GetClientRect(clientRect);

	scrollLines(clientRect.Height() / _lineHeight * count);
}

bool ListScrollView::isItemVisible(unsigned index) const {
	CRect rect;
	GetClientRect(rect);
	return static_cast<int>(index * _lineHeight) >= GetScrollPosition().y
		&& static_cast<int>((index + 1) * _lineHeight) <= GetScrollPosition().y + rect.Height();
}

void ListScrollView::clear() {
	for_each(_itemList.begin(), _itemList.end(), [] (Item* p) { delete p; });
	_itemList.clear();
}

void ListScrollView::setSelectedIndex(unsigned i) {
	_selectedIndex = i;
	Invalidate();
	onSelectedChanged();
}

void ListScrollView::OnInitialUpdate() {
	CScrollView::OnInitialUpdate();

	resetScrollSize();
}

void ListScrollView::PostNcDestroy()
{
	clear();
	CScrollView::PostNcDestroy();
}

// ListScrollView 绘图

void ListScrollView::drawItem(HDC hdc, const RECT& rect, const Item* item) {
	int oldBkMode = ::SetBkMode(hdc, TRANSPARENT);
	int oldTextColor = ::GetTextColor(hdc);

	// 背景
	HBRUSH bkgdBrush = NULL;
	if (find(_itemList.begin(), _itemList.end(), item) - _itemList.begin() == (int)_selectedIndex) {
		bkgdBrush = ::CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		::SetTextColor(hdc, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
	} else if (item->text.find(_T("ERROR")) != tstring::npos) {
		bkgdBrush = ::CreateSolidBrush(0x000000FF);
	} else if (item->text.find(_T("WARN")) != tstring::npos) {
		bkgdBrush = ::CreateSolidBrush(0x0000FFFF);
	} else {
		bkgdBrush = ::CreateSolidBrush(0x00FFFFFF);
	}
	HGDIOBJ oldBrush = ::SelectObject(hdc, bkgdBrush);
	::FillRect(hdc, &rect, bkgdBrush);

	::SelectObject(hdc, oldBrush);
	::DeleteObject(bkgdBrush);

	RECT textRect = rect;
	textRect.top += 1;
	textRect.bottom -= 1;
	::DrawText(hdc, item->text.c_str(), item->text.size(), &textRect,
		DT_NOCLIP | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX | DT_EXPANDTABS);

	::SetBkMode(hdc, oldBkMode);
	::SetTextColor(hdc, oldTextColor);
}

void ListScrollView::OnDraw(CDC* pDC) {
	CRect clientRect;
	GetClientRect(clientRect);

	HDC memDC = ::CreateCompatibleDC(pDC->GetSafeHdc());

	HBITMAP memBmp = ::CreateCompatibleBitmap(pDC->GetSafeHdc(), clientRect.Width(), clientRect.Height());
	HGDIOBJ oldBmp = ::SelectObject(memDC, memBmp);

	HBRUSH bkgdBrush = reinterpret_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	::FillRect(memDC, clientRect, bkgdBrush);

	HFONT font = ::CreateFont(_lineHeight - 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FIXED_PITCH, _T("新宋体"));
	HGDIOBJ oldFont = ::SelectObject(memDC, font);

	CPoint scrollPosition = GetScrollPosition();

	if (!_itemList.empty()) {
		// 顶部可以显示半行
		int yLogLineStart = scrollPosition.y % _lineHeight == 0 ? 0 : (scrollPosition.y % _lineHeight) * -1;
		unsigned beginLine = scrollPosition.y / _lineHeight;
		// +1是为了底部能显示半行
		unsigned endLine = (scrollPosition.y + clientRect.Height()) / _lineHeight + 1;
		endLine = min(endLine, _itemList.size());

		for (unsigned i = 0; i < endLine - beginLine; i++) {
			Item* item = _itemList[beginLine + i];
			CRect rect = clientRect;
			rect.top = yLogLineStart + i * _lineHeight;
			rect.bottom = rect.top + _lineHeight;
			drawItem(memDC, rect, item);
		}
	}

	::BitBlt(pDC->GetSafeHdc(), scrollPosition.x, scrollPosition.y, clientRect.Width(), clientRect.Height(),
		memDC, 0, 0, SRCCOPY);

	::SelectObject(memDC, oldFont);
	::DeleteObject(font);
	::SelectObject(memDC, oldBmp);
	::DeleteObject(memBmp);
	::DeleteDC(memDC);
}

// ListScrollView 消息处理程序

BEGIN_MESSAGE_MAP(ListScrollView, CScrollView)
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BOOL ListScrollView::OnEraseBkgnd(CDC* /*pDC*/) {
#ifdef LOGCC_WINUI_USE_DEFAULT_ERASE_BACKGROUND
	return CScrollView::OnEraseBkgnd(pDC);
#else
	return TRUE;
#endif
}

void ListScrollView::OnVScroll(UINT nSBCode, UINT /*nPos*/, CScrollBar* /*pScrollBar*/) {
	// 以下代码源自：http://blog.csdn.net/xiaji2007/article/details/5744111
	// 并予以修改
	// 解决CScrollView行数过多时滚动条回滚问题
	SCROLLINFO si = { 0 };
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	GetScrollInfo(SB_VERT, &si);
	int lastPos = si.nPos;
	switch (nSBCode) {
	case SB_TOP:		si.nPos = si.nMin;		break;
	case SB_BOTTOM:		si.nPos = si.nMax;		break;
	case SB_LINEUP:		si.nPos -= _lineHeight;	break;
	case SB_LINEDOWN:	si.nPos += _lineHeight;	break;
	case SB_PAGEUP:		si.nPos -= si.nPage;	break;
	case SB_PAGEDOWN:	si.nPos += si.nPage;	break;
	case SB_THUMBTRACK:	si.nPos = si.nTrackPos;	break;
	default:									break;
	}
	si.fMask = SIF_POS;
	SetScrollInfo(SB_VERT, &si);
	if (lastPos!=si.nPos) {
		::ScrollWindow(m_hWnd, 0, lastPos - si.nPos, NULL, NULL);
	}
}

BOOL ListScrollView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	if (zDelta < 0) {
		// 向下3行
		scrollLines(3);
	} else {
		// 向上3行
		scrollLines(-3);
	}
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void ListScrollView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// 以下是切换选中的情况
	if (nChar == VK_UP) {
		// 选中上一行
		if (_selectedIndex > 0 && _selectedIndex != 0xFFFFFFFF) {
			setSelectedIndex(_selectedIndex - 1);

			if (!isItemVisible(_selectedIndex)) {
				scrollLines(-1);
			}
		}
	} else if (nChar == VK_DOWN) {
		// 选中下一行
		if (_selectedIndex != 0xFFFFFFFF && _selectedIndex < _itemList.size() - 1) {
			setSelectedIndex(_selectedIndex + 1);;

			if (!isItemVisible(_selectedIndex)) {
				scrollLines(1);
			}
		}
	} else {
		// 以下是滚动的情况
		if (::GetKeyState(VK_CONTROL) & 0x80000000) {
			if (nChar == VK_HOME) {
				// 跳到第一页
				scrollTo(0);
			} else if (nChar == VK_END) {
				// 跳到最后一页，多出没事
				scrollTo(_itemList.size() * _lineHeight);
			} else if (nChar == VK_UP) {
				// 向上1行
				scrollLines(-1);
			} else if (nChar == VK_DOWN) {
				// 向下1行
				scrollLines(1);
			}
		}
		if (nChar == VK_PRIOR) {
			// 向上1页
			scrollPages(-1);
		} else if (nChar == VK_NEXT) {
			// 向下1页
			scrollPages(1);
		}
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void ListScrollView::OnLButtonUp(UINT nFlags, CPoint point) {
	int yScrollPos = GetScrollPosition().y;
	unsigned index = (yScrollPos + point.y) / _lineHeight;

	if (index < _itemList.size()) {
		setSelectedIndex(index);
	}

	CScrollView::OnLButtonUp(nFlags, point);
}
