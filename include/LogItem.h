#pragma once

#include <tstring.h>

/**
 * ��־��
 * @author CaoShuhao
 * @date 2014-1-12
 */
struct LogItem {
	/* �к� */
	unsigned line;

	/* ԭ�� */
	tstring text;

	/* �Ƿ�ѡ�� */
	bool selected;
};