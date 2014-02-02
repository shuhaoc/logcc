#pragma once

#include "IModelAware.h"

template <typename ModelT, typename IView> class ViewBase
	: public IModelAware<ModelT>, public IView {
public:
	virtual ~ViewBase() { }
};