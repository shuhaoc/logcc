#pragma once

#include "IModelAware.h"
#include "IViewAware.h"
#include "ViewBase.h"

template <typename ModelT> class InternalControllerBase : public CWnd, public IModelAware<ModelT> {
public:
	InternalControllerBase(CWnd* parent) {
		Create(::AfxRegisterWndClass(0), NULL, 0, CRect(), parent, 0);
	}

	virtual ~InternalControllerBase() {
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

template <typename ModelT, typename IViewT>
	class ControllerBase : public InternalControllerBase<ModelT>, public IViewAware<IViewT> {
public:
	ControllerBase(CWnd* parent) : InternalControllerBase(parent) {
	}

	virtual ~ControllerBase() {
	}
};