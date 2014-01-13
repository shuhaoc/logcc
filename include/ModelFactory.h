#pragma once

#include <mrl/common/SingletonSupport.h>
#include "ModelDeclare.h"

class ILogQuery;

class MODEL_INTERFACE ModelFactory : public mrl::common::SingletonSupport<ModelFactory> {
public:
	ILogQuery* CreateLogQuery() const;

private:
	SHLIB_COMMON_SINGLETON_SUPPORT_DECLARE(ModelFactory)
};