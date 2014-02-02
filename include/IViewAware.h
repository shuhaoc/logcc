#pragma once

template <typename IView> class IViewAware {
public:
	IViewAware() : viewData(nullptr) { }

	virtual ~IViewAware() { }

	void setViewData(IView* viewData) { this->viewData = viewData; }

	IView* getView() const { return viewData; }

private:
	IView* viewData;
};