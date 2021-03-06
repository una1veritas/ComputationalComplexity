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

#include <unistd.h>

#include "TuringMachine.h"

using namespace std;

struct CommandParams {
	string programFileName;
	string inputTape;
	bool inputIsReadOnly;
	char blankSymbol;

	CommandParams(void) :
		programFileName(""), inputTape(""), inputIsReadOnly(true), blankSymbol(Tape::SPECIAL_BLANK) {}

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
	cout << " Go next step         -> '[return]'" << endl
			<<  " Continue until halt  -> 'c'" << endl
			<<  " High-speed continue until halt  -> 's'" << endl
		<<  " Exit                 -> 'e'" << endl << endl;

	tm.initialize(params.inputTape, params.blankSymbol);
	char c = 'n';
	do {
		tm.showConfiguration(std::cout);
		std::cout << std::endl;
		if (c != 's' && c != 'c') {
			// make prompt
			std::cout << ">> " ;
			std::cin.get(c);
		}
		if ( c == 'e' ) {
			break;
		} else if ( c == 'c' ) {
			//Sleep(750);
			usleep(250000);
		} else if ( c == 's' ) {
			usleep(25000);
		}
	} while ( tm.step() );
	std::cout << std::endl << "The Machine has stopped at the state '" << tm.stateName() << "' and " << std::endl;
	if ( tm.accepted() ) {
		std::cout << "accepted ";
	} else {
		std::cout << "rejected ";
	}
	std::cout << "input '" << tm.inputTape() << "'." << std::endl << std::endl;

	return 0;
}


int getCommandParams(CommandParams & params, unsigned int argc, char * argv[]) {
	unsigned int i;
	string argstr;
	for(i = 1; i < argc; i++) {
		argstr = argv[i];
		if ( argstr[0] == '-' ) {
			if (argstr == "-rw") {
				params.inputIsReadOnly = false;
				continue;
			} else if  (argstr == "-ro") {
				params.inputIsReadOnly = true;
				continue;
			} else if  (argstr.compare(0, 4, "-sp=") == 0 ) {
				params.blankSymbol = argstr[4];
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
