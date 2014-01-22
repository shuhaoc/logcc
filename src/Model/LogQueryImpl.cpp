#include "stdafx.h"
#include "LogQueryImpl.h"
#include "LogItem.h"
#include "LogQueryResult.h"

using namespace mrl::utility;

LogQueryImpl::LogQueryImpl()
	: curQueryResult(new LogQueryResult())
	, taskWnd(new SimpleTaskMessageWindow())
	, monitorThread(NULL)
	, monitoring(false)
	, curQueryRegex(new boost::basic_regex<TCHAR>(_T(""))) {
}

LogQueryImpl::~LogQueryImpl() {
	if (monitoring && monitorThread) {
		monitoring = false;
		monitorThread->join();
		delete monitorThread;
	}
	reset();

	delete curQueryResult;
	delete taskWnd;
}

bool LogQueryImpl::load(const tstring& filePath) {
	this->filePath = filePath;
	startMonitor();
	return true;
}

const tstring& LogQueryImpl::getFilePath() const {
	return filePath;
}

void LogQueryImpl::setSelected(const LogItem* item) {
	for (unsigned j = 0; j < logItems.size(); j++) {
		LogItem* p = logItems[j];
		p->selected = (item == p);
	}
	notifyGeneralDataChanged();
}

LogItem* LogQueryImpl::getSelected() const {
	auto i = find_if(logItems.begin(), logItems.end(), [] (LogItem* p) { return p->selected; });
	if (i != logItems.end()) {
		return *i;
	} else {
		return NULL;
	}
}

LogQueryResult* LogQueryImpl::query(const tstring& criteria) {
	curQueryCriteria = criteria;
	try {
		auto newRegex = new boost::basic_regex<TCHAR>(criteria);
		delete this->curQueryRegex;
		this->curQueryRegex = newRegex;

		vector<LogItem*> queryResult;
		for (auto i = logItems.begin(); i != logItems.end(); i++) {
			LogItem* item = *i;
			if (boost::regex_search(item->text, *curQueryRegex)) {
				queryResult.push_back(item);
			}
		}
		setCurQueryResult(new LogQueryResult(queryResult));
	} catch (...) {
	}
	return curQueryResult;
}

void LogQueryImpl::setCurQueryResult(LogQueryResult* curQueryResult) {
	delete this->curQueryResult;
	this->curQueryResult = curQueryResult;
	notifyQueryResultChanged();
}

LogQueryResult* LogQueryImpl::getCurQueryResult() const {
	return curQueryResult;
}

void LogQueryImpl::scrollTo(int y) {
	notifyScrollPositionChanged(y);
}

void LogQueryImpl::startMonitor() {
	monitorThread = new boost::thread(([this] () {
		monitoring = true;
		while (monitoring) {
			::Sleep(500);
			vector<LogItem*> logItems;
			loadFile(logItems);
			// UNDONE: 简单比较
			if (this->logItems.size() != logItems.size()) {
				DEBUG_INFO(_T("监测到文件变化"));
				LogQueryImpl* that = this;
				taskWnd->post(new SimpleTask([that, logItems] () {
					that->reset(logItems);
				}))->wait();
			} else {
				for_each(logItems.begin(), logItems.end(), [] (LogItem* p) { delete p; });
			}
		} // while monitoring
		DEBUG_INFO(_T("监控线程退出！"));
	}));
}

void LogQueryImpl::reset(const vector<LogItem*>& logItems) {
	for_each(this->logItems.begin(), this->logItems.end(), [] (LogItem* p) { delete p; });
	this->logItems = logItems;
	query(curQueryCriteria);
}

void LogQueryImpl::reset() {
	reset(vector<LogItem*>());
}

void LogQueryImpl::loadFile(vector<LogItem*>& logItems) {
	HANDLE file = ::CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file != INVALID_HANDLE_VALUE) {
		DWORD fileSize = ::GetFileSize(file, NULL);
		char* buffer = new char[fileSize + 1];
		DWORD readSize = 0;
		// 从头重新读取文件
		::SetFilePointer(file, 0, NULL, FILE_BEGIN);
		if (::ReadFile(file, buffer, fileSize + 1, &readSize, NULL)) {
			buffer[readSize] = 0;
			istringstream iss(buffer);

			string line;
			unsigned lineNum = 0;
			while (iss.good()) {
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
		}
		delete[] buffer;
		::CloseHandle(file);
	}
}
