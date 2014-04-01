#pragma once

#include <common/singleton_support.h>
#include <sqlitidy.h>
#include "IPatternService.h"


class PatternServiceImpl : public IPatternService, public common::singleton_support<PatternServiceImpl> {
private:
	COMMON_SINGLETON_SUPPORT_DECLARE(PatternServiceImpl);
	
	PatternServiceImpl();

protected:
	virtual vector<Pattern*> all();

	virtual void save(Pattern* pattern);

	virtual void remove(Pattern* pattern);

private:
	sqlitidy::DbContext _db;
};