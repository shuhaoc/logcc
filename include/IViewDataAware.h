#pragma once

template <typename ViewDataT> class IViewDataAware {
public:
	IViewDataAware() : viewData(nullptr) { }

	virtual ~IViewDataAware() { }

	void setViewData(ViewDataT* viewData) { this->viewData = viewData; }

	ViewDataT* getViewData() const { return viewData; }

private:
	ViewDataT* viewData;
};