#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "document.h"

using namespace std;
using namespace mylib::xhtml_parser;

void main() {
	GrammarTree doc;
	try {
		doc.load("1.txt");
		if (doc.rootNode()) {
			doc.rootNode()->print();
		} else {
			cout << "<null>" << endl;
		}
	} catch (exception& ex) {
		cout << ex.what() << endl;
	}
}