#pragma once

#include <sqlitidy.h>
#include "IPatternService.h"


class PatternServiceImpl : public IPatternService {
public:
	PatternServiceImpl();

protected:
	virtual vector<Pattern*> all();

	virtual void save(Pattern* pattern);

	virtual void remove(Pattern* pattern);

private:
	sqlitidy::DbContext _db;
};