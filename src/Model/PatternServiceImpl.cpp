#include "stdafx.h"
#include "PatternServiceImpl.h"
#include "Pattern.h"

COMMON_SINGLETON_SUPPORT_IMPLEMENT(PatternServiceImpl)

PatternServiceImpl::PatternServiceImpl() : _db("config.db") {
	if (!_db.isTableExist<Pattern>()) {
		_db.createTable<Pattern>();
	}
}

vector<Pattern*> PatternServiceImpl::all() {
	vector<Pattern*> ret;
	_db.all(ret);
	return ret;
}

void PatternServiceImpl::save(Pattern* pattern) {
	_db.save(*pattern);
}

void PatternServiceImpl::remove(Pattern* pattern) {
	_db.remove(*pattern);
}