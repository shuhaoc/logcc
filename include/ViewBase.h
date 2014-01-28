#pragma once

#include "IModelAware.h"

template <typename ModelT, typename ViewDataT> class ViewBase
	: public IModelAware<ModelT>, public ViewDataT {
public:
	virtual ~ViewBase() { }
	
	virtual void onSubmit() = 0;
};