/*
 * TuringMachine.cpp
 *
 *  Created on: 2015/05/18
 *      Author: sin
 */

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "TuringMachine.h"

// 状態遷移表のチェックと行数の確認
void TuringMachine::maketable(const std::string & filename, const bool inputIsReadOnly) {

	std::ifstream fin(filename);
//	int i;
	std::istringstream strin;
	std::string buff;
	int v;
	//int k = 0;

	// inspecting the number of tapes
	std::string dummy;
//	char tapealphabet;
	unsigned int c = 0;
	std::set<std::string> states;

	// inspect a line to determin the number of tapes.

	while (!fin.eof()) {
		getline(fin, buff, '\n');
		strin.str(buff);
		strin.clear();
		strin >> dummy;
		if (dummy[0] == '#') {
			continue;
		} else {
			for (c = 1; !strin.eof(); c++) {
				strin >> dummy;
			}
			break;
		}
	}
	std::cerr << "columns " << c << std::endl;
	if ( inputIsReadOnly ) {
		noOfTapes = (c - 4) / 3 + 1;
	} else {
		noOfTapes = (c - 2) / 3;
	}
	std::cerr << noOfTapes << "tapes." << std::endl;

	/*
	std::set<char> * tapeAlphabets = new std::set<char>[noOfTapes]; // = new set<char>[k];
	fin.clear();
	fin.seekg(0, std::ios::beg);
	while (!fin.eof()) {
		if (getline(fin, buff, '\n') == 0)
			continue;
		//	cout << "'" << buff << "'" << buff.empty() << endl;
		strin.str(buff);
		strin.clear();
		strin >> dummy;
		if (dummy.empty() or dummy[0] == '#') {
			if ( dummy[0] == '#' )
				std::cout << buff << std::endl;
			continue;
		}
		states.insert(dummy);  // collect from_state.
		// collect tape alphabet
		for (c = 0; c < noOfTapes; c++) {
			strin >> tapealphabet;  // for each tape if read
			if ( tapealphabet == TuringMachine::SPECIAL_DONTCARE || tapealphabet == TuringMachine::SPECIAL_THESAME )
				continue;
			tapeAlphabets[c].insert(tapealphabet);
		}
		strin >> dummy;
		states.insert(dummy);  // collect to_state
		//	cout << dummy << endl;
		for (c = 0; c < noOfTapes; c++) {
			if ( inputIsReadOnly ) {
				// write-symbol should be omitted.
				tapealphabet = TuringMachine::SPECIAL_THESAME;
				// but there remains a motion symbol.
			} else {
				// read a write symbol
				strin >> tapealphabet;
			}
			strin >> dummy; // head motion
			if ( tapealphabet == TuringMachine::SPECIAL_DONTCARE || tapealphabet == TuringMachine::SPECIAL_THESAME )
				continue;
			tapeAlphabets[c].insert(tapealphabet);  // collect a write-symbol
		}
	}

	// Here the set of the states and the alphabet for each tape is defined.

	std::cout << "This is " << noOfTapes << " tape machine w/ states ";
	for (std::set<std::string>::iterator p = states.begin(); p != states.end(); p++) {
		std::cout << *p << ", ";
	}
	std::cout << std::endl;
	std::cout << "and, for each tape, alphabet is as follows: " << std::endl;
	for (unsigned int c = 0; c < noOfTapes; c++) {
		std::cout << "Tape " << c + 1 << " alphabet =";
		std::cout << " {";
		for (std::set<char>::iterator p = tapeAlphabets[c].begin();
				p != tapeAlphabets[c].end(); p++) {
			std::cout << *p << ", ";
		}
		std::cout << "}, ";
	}
	std::cout << std::endl;

	delete[] tapeAlphabets;

	 */
	// Now re-read to define the transition table.

	fin.clear();
	fin.seekg(0, std::ios::beg);
	v = 0;
	bool skipremaining = false;
	while (!fin.eof()) {
		if ( skipremaining ) break;
		getline(fin, buff, '\n');
		strin.str(buff);
		strin.clear();

		if (std::string(buff).empty())
			continue;
		if (buff[0] == '#')
			continue;

		table.push_back(Tuple(noOfTapes));
		strin >> table.back().current;
		for (c = 0; c < noOfTapes; c++)
			strin >> table.back().read[c];
		strin >> table.back().next;
		if (table.back().next[0] == '!') {
			table.back().next = (std::string) table.back().next.substr(1,
					table.back().next.size());
			acceptingStates.insert(table.back().next);
		}
		for (c = 0; c < noOfTapes; c++) {
			if ( c == 0 && inputIsReadOnly ) {
				table.back().write[c] = table.back().read[c];
			} else {
				strin >> table.back().write[c];
			}
			strin >> table.back().headding[c];
		}
		//cerr << table[table.size()].read[0] << ", " << table[table.size()].read[1] << endl;
		if (fin.eof())
			break;
		if (states.count(table.back().current) == 0)
			std::cerr << "Error!!" << std::endl << std::flush;
		// テープ記号がアルファベットもしくは数字かをチェック。
		for (c = 0; c < noOfTapes; c++) {
			if (!(isgraph(table.back().read[c])
					&& isgraph(table.back().write[c]))) {
				std::cout << "table-" << table.size() << ":Improper format." << std::endl;
				skipremaining = true;
				break; //exit(1);
			}
			if (!(table.back().headding[c] == 'R'
					|| table.back().headding[c] == 'L'
					|| table.back().headding[c] == 'N')) {
				std::cout << "table-" << table.size()
						<< ":Improper head motion specification." << std::endl;
				exit(1);
			}
		}
		// 遷移がR,L,Nのいずれかになっているかをチェック。
//		table.size()++;
	}
	fin.close();

	return;

}

// tapeを読み状態遷移を実行する関数
void TuringMachine::simulate(std::string input, std::string work[]) {
	// adrs:テープのヘッダの位置、s:現状態、step:ステップ数
	unsigned int i;
	int searchOffset, /* adrs[2],*//* s=0, */step = 0; //,undo;
	char c = 'n';
	std::string acc;
//	time_t t1,t2;
	std::map<std::string, int>::iterator sitr;
	std::map<char, int>::iterator hitr;

	int headd;

	tape = new std::string[noOfTapes];
	head = new std::string::iterator[noOfTapes];

	tape[0] = input;
	head[0] = tape[0].begin();
	//cerr << head[0] << "," << input.begin()<< endl;
	for (i = 1; i < noOfTapes; i++) {
		tape[i] = work[i];
		head[i] = tape[i].begin();
	}
	state = table[0].current; //the initial state

	// 初期状態の印字
	print(step);
	// 乱数の初期化
	srand(time(NULL));
	// 状態遷移を行う
	while (true) {
		searchOffset = rand() % table.size();
		for (i = 0; i < table.size(); i++) {
			Tuple & currentTuple = table[(searchOffset + i) % table.size()];
			if (currentTuple.current == state) {
				unsigned int tn;
				//cerr << currentTuple << endl;
				std::string expectstr(""), headstr("");
				for (tn = 0; tn < noOfTapes; tn++) {
					if ( currentTuple.read[tn] == SPECIAL_DONTCARE ) {
						expectstr += *(head[tn]);
					} else {
						expectstr += currentTuple.read[tn];
					}
					headstr += *(head[tn]);
				}
				//cerr << expectstr << " - " << headstr << endl;
				if ( headstr == expectstr)
					break;
			}
		}
		if ( (unsigned ) i == table.size())
			break;
		// preserve the row-in-table number of the tuple
		i = (searchOffset + i) % table.size();
		if (c == 'r') {
			c = 'n';
		} else if (c != 's' && c != 'c') {
			std::cout << ">>" << std::endl;
			c = (char) getchar();
		}
		switch (c) {
		case 'e':
			exit(0);
		case 'c':
			//Sleep(750);
			usleep(250000);
			break;
		}

		// データの書き換え
		for (unsigned int k = 0; k < noOfTapes; k++) {
			if (table[i].write[k] == SPECIAL_THESAME) {
				//*head[k] = *head[k];
				// implements this by don't touch
			} else {
				*head[k] = table[i].write[k];
			}
			switch (table[i].headding[k]) {
			case 'R':
			case 'r':
				headd = +1;
				break;
			case 'L':
			case 'l':
				headd = -1;
				break;
			default: // 'N' or 'n'
				headd = 0;
				break;
			}
			if (head[k] == tape[k].begin() && headd == -1) {
				tape[k] = std::string("_") + tape[k];
				head[k] = tape[k].begin();
			} else {
				head[k] = head[k] + headd;
			}
			if (head[k] == tape[k].end()) {
				tape[k] += "_";
				head[k] = tape[k].end();
				head[k]--;
			}
			state = table[i].next;
		}
		step++;
		print(step);
		// undo,redo
	}
	std::cout << std::endl << "The Machine has halted at the state '" << state << "' and " << std::endl;
	if (acceptingStates.find(state) != acceptingStates.end()) {
		std::cout << "accepted ";
	} else {
		std::cout << "rejected ";
	}
	std::cout << "input '" << input << "'." << std::endl << std::endl;

	if (step == 0)
		exit(0);
}

// ステップ毎の状態を表示する関数
void TuringMachine::print(int step) { //string state){
	std::string::iterator h;

	std::cout << std::endl << "Step: " << step << " ";
	if (acceptingStates.find(state) != acceptingStates.end())
		std::cout << "Accepting ";
	std::cout << std::endl;
	std::cout << "State: " << state << std::endl;
	// 入力用テープの表示
	std::cout << "Input tape: " << std::endl;
	for (h = tape[0].begin() - 1; h != tape[0].end(); h++) {
		if (h + 1 != tape[0].begin())
			std::cout << *h;
		if (h + 1 == head[0]) {
			std::cout << "[";
		} else if (h == head[0]) {
			std::cout << "]";
		} else {
			std::cout << " ";
		}
	}
	std::cout << std::endl;

	// 作業用テープの表示
	std::cout << "Working tape:";
	for (unsigned int tn = 1; tn < noOfTapes; tn++) {
		std::cout << std::endl;
		for (h = tape[tn].begin() - 1; h != tape[tn].end(); h++) {
			if (h + 1 != tape[tn].begin())
				std::cout << *h;
			if (h + 1 == head[tn]) {
				std::cout << "[";
			} else if (h == head[tn]) {
				std::cout << "]";
			} else {
				std::cout << " ";
			}
		}
	}
	std::cout << std::endl;

}

bool TuringMachine::searchin(std::string s, char in, char wk) {

	for (unsigned int i = 0; i < table.size(); i++)
		if (table[i].current == s && table[i].read[0] == in
				&& table[i].read[1] == wk)
			return true;
	return false;
}

