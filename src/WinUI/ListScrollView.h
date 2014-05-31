#pragma once

// ListScrollView 视图

class ListScrollView : public CScrollView {
	DECLARE_DYNCREATE(ListScrollView)

public:
	void insert(const tstring& text, void* data = nullptr, unsigned before = 0xFFFFFFFF);
	void update() { resetScrollSize(); }

protected:
	struct Item {
		tstring text;
		void* data;

		Item() : data(nullptr) { }
	};

	ListScrollView();           // 动态创建所使用的受保护的构造函数
	virtual ~ListScrollView();

	void resetScrollSize();

	void scrollTo(int yScrollPos);

	void scrollDelta(int delta);

	void scrollLines(int count);

	void scrollPages(int count);

	bool isItemVisible(unsigned index) const;

	void clear();

	unsigned getSelectedIndex() const { return _selectedIndex; }

	void setSelectedIndex(unsigned i);

	virtual void drawItem(HDC hdc, const RECT& rect, const Item* item);

	virtual void onSelectedChanged() { }

private:
	vector<Item*> _itemList;

	unsigned _selectedIndex; // 0xFFFFFFFF means no selection

	CSize _totalSize;

	unsigned _lineHeight;

protected:
	virtual void OnInitialUpdate();     // 构造后的第一次
	virtual void PostNcDestroy();
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图

	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


