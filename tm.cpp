//============================================================================
// Name        : tm.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#include <stdio.h>
//#include <conio.h>
#include <cctype>
#include <cstdlib>
#include <ctime>
//#include <windows.h>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stack>

#include "TuringMachine.h"

using namespace std;

struct CommandParams {
	string programFileName;
	string inputTape;
	bool inputIsReadOnly;

	CommandParams(void) : programFileName(""), inputTape(""), inputIsReadOnly(true) {}

	friend ostream & operator<<(ostream & stream, const CommandParams & obj) {
		stream << obj.programFileName << ", " << obj.inputTape << ", " << (obj.inputIsReadOnly ? "true" : "false")
				<< endl << endl;
		return stream;
	}
};

int getCommandParams(CommandParams & params, unsigned int argc, char * argv[]);

// メイン関数
int main(int argc, char * argv[]) {

	TuringMachine tm;
	CommandParams params;
	ifstream file;

	cout << "Version 16.0615" << endl << endl;

	if ( getCommandParams(params, argc, argv) != 0 ) {
		cerr << "Parameter error." << endl;
		return 1;
	}

	file.open(params.programFileName, std::ifstream::in);
	if ( !file.is_open() ) {
		cerr << "File cannot be opened." << endl;
		return 1;
	}
	// TMファイルを読み込み、状態遷移表を作成する

	tm.program(file, params.inputIsReadOnly);
	file.close();

	// 遷移関数の表示
	tm.show(cout);
	cout << endl << endl;

	// シミュレート実行
	cout
	//		<< " Redo      -> 'r'" << endl
	<< " Go next step         -> '[return]'" << endl
//		<< " Undo      -> 'u'" << endl
			<< " Continue until halt  -> 'c'" << endl
//		<< " Traverse  -> 't'" << endl
			<< " Exit                 -> 'e'" << endl << endl;

	tm.initialize(params.inputTape);
	tm.simulate();

	return 0;
}


int getCommandParams(CommandParams & params, unsigned int argc, char * argv[]) {
	unsigned int c;
	string argstr;
	for(c = 1; c < argc; c++) {
		argstr = argv[c];
		if ( argstr[0] == '-' ) {
			if (argstr == "-rw") {
				params.inputIsReadOnly = false;
				continue;
			} else if  (argstr == "-ro") {
				params.inputIsReadOnly = true;
				continue;
			}
			// not an option.
		}
		// primarily string is assigned to the file name for the transition relation.
		if ( params.programFileName == "" ) {
			params.programFileName = argstr;
			continue;
		} else if ( params.inputTape == "" ) {
			params.inputTape = argstr;
			continue;
		}
	}

	return 0;
}
