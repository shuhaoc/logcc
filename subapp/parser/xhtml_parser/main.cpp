#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include "GrammarTree.h"

using namespace std;
using namespace logcc::filter_parser;

void main() {
	try {
		ifstream stmtFile("stmt.txt");
		ifstream logFile("log.txt");
		string stmt;
		getline(stmtFile, stmt);

		list<string> logLines;
		string line;
		while (logFile.good()) {
			getline(logFile, line);
			logLines.push_back(line);
		}

		GrammarTree tree;
		tree.compile(stmt);
		tree.rootNode()->print();

		for (auto i = logLines.begin(); i != logLines.end(); i++) {
			if (tree.rootNode()->match(*i)) {
				cout << *i << endl;
			}
		}

	} catch (exception& ex) {
		cout << ex.what() << endl;
	}
}