#pragma once

template <typename IViewT> class IViewAware {
public:
	IViewAware() : view(nullptr) { }

	virtual ~IViewAware() { }

	void setView(IViewT* view) { this->view = view; }

	IViewT* getView() const { return view; }

private:
	IViewT* view;
};