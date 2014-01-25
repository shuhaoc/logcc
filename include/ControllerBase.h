#pragma once

#include "IModelAware.h"
#include "IViewDataAware.h"

template <typename ModelT, typename ViewDataT>
class ControllerBase : public CWnd, public IModelAware<ModelT>, public IViewDataAware<ViewDataT> {
public:
	ControllerBase(CWnd* parent) {
		Create(::AfxRegisterWndClass(0), NULL, 0, CRect(), parent, 0);
	}

	virtual void PostNcDestroy() { delete this; }
};