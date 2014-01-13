#include "stdafx.h"
#include <mrl/utility/CodeConv.h>
#include "LogQueryImpl.h"
#include "LogItem.h"


LogQueryImpl::~LogQueryImpl() {
	for_each(logItems.begin(), logItems.end(), [] (LogItem* item) { delete item; });
}

bool LogQueryImpl::load(const tstring& filePath) {	
	ifstream file(filePath, ios_base::in | ios_base::binary);
	if (!file.good()) {
		return false;
	}

	file.seekg(0, ios_base::end);
	size_t length = static_cast<size_t>(file.tellg());
	file.seekg(0, ios_base::beg);

#ifdef MULTI_THREAD_GET_LINE

	size_t length1 = length / 2;
	size_t length2 = length - length1;

	char* buffer1 = new char[length1 + 1];
	char* buffer2 = new char[length2];

	streamsize read = 0;
	while (file.good() && length1 - read) {
		file.read(buffer1 + read, length1 - read);
		read += file.gcount();
	}
	buffer1[read] = 0;
	assert(read == length1);

	read = 0;
	while (file.good() && length2 - read) {
		file.read(buffer2 + read, length2 - read);
		read += file.gcount();
	}
	buffer2[read] = 0;
	assert(read == length2);

	vector<string> lines1, lines2;

	boost::thread_group workers;

	auto f = [] (char* buffer, vector<string>* logItems) {
		istringstream iss(buffer);

		string line;
		while (iss.good()) {
			std::getline(iss, line);
			logItems->push_back(line);
		}
	};

	workers.create_thread([f, buffer1, &lines1] () { f(buffer1, &lines1); });
	workers.create_thread([f, buffer2, &lines2] () { f(buffer2, &lines2); });
	workers.join_all();

	logItems.insert(logItems.end(), lines1.begin(), lines1.end());
	if (lines1.size() && lines1.rbegin()->size() && *logItems.rbegin()->rbegin() != '\n') {
		logItems.rbegin()->append(*lines2.begin());
		logItems.insert(logItems.end(), lines2.begin() + 1, lines2.end());
	} else {
		logItems.insert(logItems.end(), lines2.begin(), lines2.end());
	}
#else
	char* buffer = new char[length];
	streamsize read = 0;
	while (file.good() && length - read) {
		file.read(buffer + read, length - read);
		read += file.gcount();
	}
	buffer[read] = 0;
	assert(read == length);

	istringstream iss(buffer);

	string line;
	unsigned lineNum = 0;
	while (iss.good())
	{
		std::getline(iss, line);
#ifdef _UNICODE
		LogItem* item = new LogItem();
		item->line = ++lineNum;
		item->text = mrl::utility::codeconv::asciiToUnicode(line);
		item->selected = false;
		logItems.push_back(item);
#else
#error 多字节字符集情况下尚未实现
#endif
	}
#endif
	this->filePath = filePath;
	return true;
}

unsigned LogQueryImpl::getLineCount() const {
	return logItems.size();
}

const tstring& LogQueryImpl::getFilePath() const {
	return filePath;
}

vector<LogItem*> LogQueryImpl::getRange(unsigned begin, unsigned end) const {
	vector<LogItem*> subset;
	for (unsigned i = begin; i < end; i++) {
		if (i < logItems.size()) {
			subset.push_back(logItems[i]);
		} else {
			break;
		}
	}
	return subset;
}
