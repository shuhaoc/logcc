#pragma once

template <typename ViewDataT> class IViewDataSubmitter {
public:
	IViewDataSubmitter() : viewData(new ViewDataT()) { }

	virtual ~IViewDataSubmitter() { delete viewData; }
	
	ViewDataT* getViewData() const { return viewData; }

	virtual void onSubmit(ViewDataT* viewData) = 0;

private:
	ViewDataT* viewData;
};