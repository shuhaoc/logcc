#pragma once

#include <SingletonSupport.h>
#include "ModelDeclare.h"

class ILogQuery;

class MODEL_INTERFACE ModelFactory : public shlib::common::SingletonSupport<ModelFactory> {
public:
	ILogQuery* CreateLogQuery() const;

private:
	SHLIB_COMMON_SINGLETON_SUPPORT_DECLARE(ModelFactory)
};