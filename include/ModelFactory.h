#pragma once

#include <common/singleton_support.h>
#include "ModelExport.h"

class ILogQuery;
class IPatternService;

class MODEL_EXPORT ModelFactory : public common::singleton_support<ModelFactory> {
public:
	ILogQuery* CreateLogQuery() const;

	IPatternService* CreatePatternService() const;

private:
	COMMON_SINGLETON_SUPPORT_DECLARE(ModelFactory)
};
