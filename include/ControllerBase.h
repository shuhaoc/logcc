#pragma once

typedef CDocument BasicViewData;

class ControllerBase : public CWnd {
public:
	ControllerBase(CWnd* parent) {
		Create(::AfxRegisterWndClass(0), NULL, 0, CRect(), parent, 0);
	}

	virtual void PostNcDestroy() { delete this; }

	BasicViewData* getViewData() const { return viewData; }

	void setViewData(BasicViewData* viewData) { this->viewData = viewData; }

private:
	BasicViewData* viewData;
};