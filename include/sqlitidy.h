#pragma once

#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <cassert>
#include <sqlite3.h>

namespace sqlitidy {

#pragma warning(push)
#pragma warning(disable: 4127)

struct DbValue {
	int type;
	union {
		void* nullValue;
		int intValue;
		double doubleValue;
		char* stringValue;
	};

	DbValue(const DbValue& value) { assign(value); }

	DbValue& operator = (const DbValue& value) { assign(value); return *this; }

	~DbValue() { if (type == SQLITE_TEXT) delete[] stringValue; }

	DbValue() : type(SQLITE_NULL), nullValue(nullptr) { }

	DbValue(int intValue) : type(SQLITE_INTEGER), intValue(intValue) { }

	DbValue(double doubleValue) : type(SQLITE_FLOAT), doubleValue(doubleValue) { }

	DbValue(const std::string& stringValue);

private:
	void assign(const DbValue& value);
};

class DbContext {
public:
	DbContext(const std::string& filePath);

	~DbContext();

	template <typename ObjectT> void createTable();

	template <typename ObjectT> bool isTableExist();

	template <typename ObjectT> bool isExist(ObjectT& object);

	template <typename ObjectT> void save(ObjectT& object);

	template <typename ObjectT> bool load(const DbValue& id, ObjectT& object);

	template <typename ObjectT> void remove(ObjectT& object);

	template <typename ObjectT> void all(std::vector<ObjectT*>& list);

	template <typename ObjectT, unsigned ParamCount> void where(
		const std::string& clause, const std::array<DbValue, ParamCount>& parameters, std::vector<ObjectT*>& list);

	template <typename ObjectT> void where(const std::string& clause, std::vector<ObjectT*>& list);

private:
	sqlite3_stmt* compile(const std::string& sql);

	int step(sqlite3_stmt* stmt);

	void bind(sqlite3_stmt* stmt, int i, const DbValue& value);

	DbValue extract(sqlite3_stmt* stmt, int i);

	template <typename ObjectT> void extractList(sqlite3_stmt* stmt, std::vector<ObjectT*>& list);

	sqlite3* db;
};

#define SQLITIDY_VALUE_GETTER_BEGIN sqlitidy::DbValue getValue(const std::string& name) const {
#define SQLITIDY_VALUE_GETTER(field) if (name == #field) { return this->field; }
#define SQLITIDY_VALUE_GETTER_END return sqlitidy::DbValue(); }

#define SQLITIDY_VALUE_SETTER_BEGIN void setValue(const std::string& name, const sqlitidy::DbValue& value) {
#define SQLITIDY_INT_VALUE_SETTER(field) if (name == #field) { \
	assert(value.type == SQLITE_INTEGER); \
	this->field = value.intValue; \
	return; \
}
#define SQLITIDY_DOUBLE_VALUE_SETTER(field) if (name == #field) { \
	assert(value.type == SQLITE_FLOAT); \
	this->field = value.doubleValue; \
	return; \
}
#define SQLITIDY_STRING_VALUE_SETTER(field) if (name == #field) { \
	assert(value.type == SQLITE_TEXT); \
	this->field = value.stringValue; \
	return; \
}
#define SQLITIDY_VALUE_SETTER_END assert(false && "Invalid name"); \
}

template <typename ObjectT> bool DbContext::isExist(ObjectT& object) {
	assert(db);

	std::ostringstream sql;
	sql << "select count(" << ObjectT::keyName << ") from " << ObjectT::tableName
	    << " where " << ObjectT::keyName << " = ?;";

	sqlite3_stmt* stmt = compile(sql.str());
	bind(stmt, 1, object.getValue(ObjectT::keyName));
	assert(step(stmt) == SQLITE_ROW);

	int count = ::sqlite3_column_int(stmt, 0);
	::sqlite3_finalize(stmt);
	return count > 0;
}

template <typename ObjectT> void DbContext::save(ObjectT& object) {
	assert(db);

	bool isUpdating = isExist(object);

	std::ostringstream sql;
	sql << "replace into " << ObjectT::tableName << " (";
	for (unsigned i = 0; i < ObjectT::fieldNames.size(); i++) {
		if (isUpdating || ObjectT::fieldNames[i] != ObjectT::keyName || !ObjectT::pkAutoInc) {
			sql << ObjectT::fieldNames[i];
			if (i != ObjectT::fieldNames.size() - 1) {
				sql << ", ";
			}
		}
	}
	sql << ") values (";
	for (unsigned i = 0; i < ObjectT::fieldNames.size(); i++) {
		if (isUpdating || ObjectT::fieldNames[i] != ObjectT::keyName || !ObjectT::pkAutoInc) {
			sql << "?";
			if (i != ObjectT::fieldNames.size() - 1) {
				sql << ", ";
			}
		}
	}
	sql << ");";

	sqlite3_stmt* stmt = compile(sql.str());
	assert(stmt);

	int j = 1;
	for (unsigned i = 0; i < ObjectT::fieldNames.size(); i++) {
		if (isUpdating || ObjectT::fieldNames[i] != ObjectT::keyName || !ObjectT::pkAutoInc) {
			bind(stmt, j, object.getValue(ObjectT::fieldNames[i]));
			j++;
		}
	}

	assert(step(stmt) == SQLITE_DONE);
	::sqlite3_finalize(stmt);

	DbValue key = object.getValue(ObjectT::keyName);
	if (!isUpdating && key.type == SQLITE_INTEGER && ObjectT::pkAutoInc) {
		object.setValue(ObjectT::keyName, DbValue(static_cast<int>(::sqlite3_last_insert_rowid(db))));
	}
}

template <typename ObjectT> bool DbContext::load(const DbValue& id, ObjectT& object) {
	assert(db);

	std::ostringstream sql;
	sql << "select * from " << ObjectT::tableName
	    << " where " << ObjectT::keyName << " = ?;";

	sqlite3_stmt* stmt = compile(sql.str());
	bind(stmt, 1, id);

	bool isExist = step(stmt) == SQLITE_ROW;
	if (isExist) {
		for (unsigned i = 0; i < ObjectT::fieldNames.size(); i++) {
			DbValue value = extract(stmt, i);
			object.setValue(ObjectT::fieldNames[i], value);
		}
	}

	::sqlite3_finalize(stmt);
	return isExist;
}

template <typename ObjectT> void DbContext::remove(ObjectT& object) {
	assert(db);

	std::ostringstream sql;
	sql << "delete from " << ObjectT::tableName
	    << " where " << ObjectT::keyName << " = ?;";

	sqlite3_stmt* stmt = compile(sql.str());
	bind(stmt, 1, object.getValue(ObjectT::keyName));

	assert(step(stmt) == SQLITE_DONE);
	::sqlite3_finalize(stmt);
}

template <typename ObjectT> void DbContext::extractList(sqlite3_stmt* stmt, std::vector<ObjectT*>& list) {
	while (step(stmt) == SQLITE_ROW) {
		ObjectT* object = new ObjectT();
		for (unsigned i = 0; i < ObjectT::fieldNames.size(); i++) {
			DbValue value = extract(stmt, i);
			object->setValue(ObjectT::fieldNames[i], value);
		}
		list.push_back(object);
	}
}

template <typename ObjectT, unsigned ParamCount> void DbContext::where(
		const std::string& clause, const std::array<DbValue, ParamCount>& parameters, std::vector<ObjectT*>& list) {
	assert(db);

	std::ostringstream sql;
	sql << "select * from " << ObjectT::tableName
	    << " where " << clause << ";";

	sqlite3_stmt* stmt = compile(sql.str());
	for (unsigned i = 0; i < parameters.size(); i++) {
		bind(stmt, i + 1, parameters[i]);
	}
	extractList(stmt, list);

	::sqlite3_finalize(stmt);
}

template <typename ObjectT> void DbContext::where(const std::string& clause, std::vector<ObjectT*>& list) {
	where(clause, std::array<DbValue, 0>(), list);
}

template <typename ObjectT> void DbContext::all(std::vector<ObjectT*>& list) {
	assert(db);

	std::ostringstream sql;
	sql << "select * from " << ObjectT::tableName << ";";

	sqlite3_stmt* stmt = compile(sql.str());
	extractList(stmt, list);

	::sqlite3_finalize(stmt);
}

template <typename ObjectT> void DbContext::createTable() {
	assert(db);

	std::ostringstream sql;
	sql << "create table " << ObjectT::tableName << " (";

	ObjectT placeholder;
	for (unsigned i = 0; i < ObjectT::fieldNames.size(); i++) {
		sql << ObjectT::fieldNames[i];
		DbValue value = placeholder.getValue(ObjectT::fieldNames[i]);
		switch (value.type) {
		case SQLITE_INTEGER: sql << " integer"; break;
		case SQLITE_FLOAT: sql << " float"; break;
		case SQLITE_TEXT: sql << " text"; break;
		default:
			assert(false && "column type not supported");
		}
		if (ObjectT::fieldNames[i] == ObjectT::keyName) {
			sql << " primary key";
			if (ObjectT::pkAutoInc && value.type == SQLITE_INTEGER) {
				sql << " autoincrement";
			}
		}
		sql << " not null";
		if (i != ObjectT::fieldNames.size() - 1) {
			sql << ", ";
		}
	}

	sql << ");";

	sqlite3_stmt* stmt = compile(sql.str());
	assert(step(stmt) == SQLITE_DONE);

	::sqlite3_finalize(stmt);
}

template <typename ObjectT> bool DbContext::isTableExist() {
	assert(db);

	std::string sql = "select count(*) from sqlite_master where type = 'table' and name = ?;";

	sqlite3_stmt* stmt = compile(sql);
	bind(stmt, 1, ObjectT::tableName);
	assert(step(stmt) == SQLITE_ROW);

	int count = ::sqlite3_column_int(stmt, 0);

	::sqlite3_finalize(stmt);
	return count == 1;
}

#pragma warning(pop)

} // namespace sqlitidy
