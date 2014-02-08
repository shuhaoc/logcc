#pragma once

#include <vector>

struct Pattern;

/**
 * ������ʽ����ӿ�
 * @author CaoShuhao
 * @date 2014-2-8
 */
class IPatternService {
public:
	virtual ~IPatternService() {
	}

	std::vector<Pattern*> all();

	void save(Pattern* pattern);

	void remove(Pattern* pattern);
};