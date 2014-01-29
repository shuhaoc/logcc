#pragma once

#include "IModelAware.h"
#include "IViewDataAware.h"
#include "ViewBase.h"

template <typename ModelT>
class InternalControllerBase : public CWnd, public IModelAware<ModelT> {
public:
	InternalControllerBase(CWnd* parent) {
		Create(::AfxRegisterWndClass(0), NULL, 0, CRect(), parent, 0);
	}

	virtual void PostNcDestroy() { delete this; }

	void accept(UINT msg, WPARAM wparam, LPARAM lparam) {
		const AFX_MSGMAP_ENTRY* entry = GetMessageMap()->lpEntries;
		while (entry->nMessage != 0) {
			if (entry->nMessage == msg) {
				this->WindowProc(msg, wparam, lparam);
			}
			entry++;
		}
	}
};


template <typename ModelT, typename ViewDataT>
class ControllerBase : public InternalControllerBase<ModelT>, public IViewDataAware<ViewDataT> {
public:
	ControllerBase(CWnd* parent) : InternalControllerBase(parent) {
	}

	void updateViewData() {
		static_cast<ViewBase<ModelT, ViewDataT>*>(getViewData())->onSubmit();
	}
};
