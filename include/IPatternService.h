#pragma once

#include <vector>
#include <common/observer_list.h>
#include "IPatternServiceObserver.h"

struct Pattern;

/**
 * 高亮样式管理接口
 */
class IPatternService : public common::observer_list<IPatternServiceObserver> {
public:
	virtual ~IPatternService() {
	}

	virtual std::vector<Pattern*> all() = 0;

	virtual void save(Pattern* pattern) = 0;

	virtual void remove(Pattern* pattern) = 0;

protected:

};