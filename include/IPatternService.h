#pragma once

#include <vector>
#include <mrl/common/ObserverContainer.h>
#include "IPatternServiceObserver.h"

struct Pattern;

/**
 * 高亮样式管理接口
 * @author CaoShuhao
 * @date 2014-2-8
 */
class IPatternService : public mrl::common::ObserverContainer<IPatternServiceObserver> {
public:
	virtual ~IPatternService() {
	}

	virtual std::vector<Pattern*> all() = 0;

	virtual void save(Pattern* pattern) = 0;

	virtual void remove(Pattern* pattern) = 0;

protected:

};