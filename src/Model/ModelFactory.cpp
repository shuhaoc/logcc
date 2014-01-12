#include "stdafx.h"
#include "ModelFactory.h"
#include "LogQueryImpl.h"

SHLIB_COMMON_SINGLETON_SUPPORT_IMPLEMENT(ModelFactory)


ILogQuery* ModelFactory::CreateLogQuery() const {
	return new LogQueryImpl();
}
