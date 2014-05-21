#pragma once

#include <common/singleton_support.h>
#include "IModelFactory.h"

class ModelFactory : public logcc::model::IModelFactory, public common::singleton_support<ModelFactory> {
public:
	virtual ILogQuery* CreateLogQuery() const;

	virtual IPatternService* CreatePatternService() const;

private:
	COMMON_SINGLETON_SUPPORT_DECLARE(ModelFactory)
};
