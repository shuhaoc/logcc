#pragma once

/**
 * 日志行
 */
struct LogItem {
	/* 行号 */
	unsigned line;

	/* 原文 */
	tstring text;

	/* 是否选中 */
	bool selected;
};
