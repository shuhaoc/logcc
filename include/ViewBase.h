#pragma once

#include "IModelAware.h"

template <typename ModelT, typename IViewT> class ViewBase
	: public IModelAware<ModelT>, public IViewT {
public:
	virtual ~ViewBase() { }
};