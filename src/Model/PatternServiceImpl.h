#pragma once

#include <mrl/common/SingletonSupport.h>
#include <sqlitidy.h>
#include "IPatternService.h"


class PatternServiceImpl : public IPatternService, public mrl::common::SingletonSupport<PatternServiceImpl> {
private:
	SHLIB_COMMON_SINGLETON_SUPPORT_DECLARE(PatternServiceImpl);
	
	PatternServiceImpl();

protected:
	virtual vector<Pattern*> all();

	virtual void save(Pattern* pattern);

	virtual void remove(Pattern* pattern);

private:
	sqlitidy::DbContext _db;
};