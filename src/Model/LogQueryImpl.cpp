#include "stdafx.h"
#include <mrl/utility/CodeConv.h>
#include "LogQueryImpl.h"
#include "LogItem.h"

#define MULTI_THREAD_GET_LINE

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

	if (lines1.size() && lines1.rbegin()->size() && *lines1.rbegin()->rbegin() != '\n') {
		lines1.rbegin()->append(*lines2.begin());
		lines1.insert(lines1.end(), lines2.begin() + 1, lines2.end());
	} else {
		lines1.insert(lines1.end(), lines2.begin(), lines2.end());
	}

	for (unsigned i = 0; i < lines1.size(); i++) {
		string& line = lines1[i];

		LogItem* item = new LogItem();
		item->line = i + 1;
		#ifdef _UNICODE
		item->text = mrl::utility::codeconv::asciiToUnicode(line);
		#else
		item->text = line;
		#endif
		item->selected = false;
		logItems.push_back(item);
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
		LogItem* item = new LogItem();
		item->line = ++lineNum;
#ifdef _UNICODE
		item->text = mrl::utility::codeconv::asciiToUnicode(line);
#else
		item->text = line;
#endif
		item->selected = false;
		logItems.push_back(item);
	}
#endif
	this->filePath = filePath;
	return true;
}

unsigned LogQueryImpl::getCount() const {
	return logItems.size();
}

const tstring& LogQueryImpl::getFilePath() const {
	return filePath;
}

vector<LogItem*> LogQueryImpl::getRange(unsigned begin, unsigned end) const {
	assert(begin <= end && end <= logItems.size());

	vector<LogItem*> subset;
	for (unsigned i = begin; i < end; i++) {
		subset.push_back(logItems[i]);
	}
	return subset;
}

LogItem* LogQueryImpl::getIndex(unsigned i) const {
	assert(i < logItems.size());
	return logItems[i];
}

void LogQueryImpl::select(unsigned i) const {
	assert(i < logItems.size());

	for (unsigned j = 0; j < logItems.size(); j++) {
		LogItem* item = logItems[j];
		item->selected = (i == j);
	}
}