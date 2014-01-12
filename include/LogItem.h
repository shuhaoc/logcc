#pragma once

#include <tstring.h>

/**
 * 日志行
 * @author CaoShuhao
 * @date 2014-1-12
 */
struct LogItem {
	/* 行号 */
	unsigned line;

	/* 原文 */
	tstring text;

	/* 是否选中 */
	bool selected;
};