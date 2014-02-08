#pragma once

#include <string>
#include <array>
#include "sqlitidy.h"

struct Pattern {
	int id;
	int textColor;
	int backColor;

	static const std::string tableName;

	static const std::string keyName;

	static const bool pkAutoInc = true;

	static const std::array<std::string, 3> fieldNames;

	SQLITIDY_VALUE_GETTER_BEGIN
		SQLITIDY_VALUE_GETTER(id)
		SQLITIDY_VALUE_GETTER(textColor)
		SQLITIDY_VALUE_GETTER(backColor)
	SQLITIDY_VALUE_GETTER_END

	SQLITIDY_VALUE_SETTER_BEGIN
		SQLITIDY_INT_VALUE_SETTER(id)
		SQLITIDY_INT_VALUE_SETTER(textColor)
		SQLITIDY_INT_VALUE_SETTER(backColor)
	SQLITIDY_VALUE_SETTER_END

	Pattern() : id(-1), textColor(0), backColor(-1) { }
};