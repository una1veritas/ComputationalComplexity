/*
 * TuringMachine.cpp
 *
 *  Created on: 2015/05/18
 *      Author: sin
 */

#include <unistd.h>
#include <cstdlib>
#include <ctime>

#include "TuringMachine.h"

//
void TuringMachine::program(std::istream & file, const char blank, const bool inputIsReadOnly) {

	std::istringstream strin;
	std::string buff;

	// inspecting the number of tapes
	std::string dummy;
	unsigned int c = 0;
	std::set<std::string> states;

	// inspect a line to determin the number of tapes.

	while (!file.eof()) {
		getline(file, buff, '\n');
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
	std::cerr << noOfTapes << " tapes." << std::endl;

	// Now re-read to define the transition table.

	file.clear();
	file.seekg(0, std::ios::beg);
	bool skipremaining = false;
	while (!file.eof()) {
		if ( skipremaining ) break;
		getline(file, buff, '\n');
		strin.str(buff);
		strin.clear();

		if (std::string(buff).empty())
			continue;
		if (buff[0] == '#')
			continue;

		table.push_back(Tuple(noOfTapes));
		// the 1st element
		strin >> table.back().current;
		for (c = 0; c < noOfTapes; c++) {
			// the readout of (c+1)th tape
			strin >> table.back().read[c];
		}
		// the next state
		std::string elem;
		strin >> elem;
		if ( elem[0] == '!') {
			// with the final state marking
			table.back().next = elem.substr(1, elem.length() - 1);
			acceptingStates.insert(table.back().next);
		} else {
			table.back().next = elem;
		}
		for (c = 0; c < noOfTapes; c++) {
			if ( c == 0 && inputIsReadOnly ) {
				table.back().write[c] = table.back().read[c];
			} else {
				strin >> table.back().write[c];
			}
			strin >> table.back().headding[c];
		}
		if (file.eof())
			break;
#ifdef FALSE
#error ???
		if (states.count(table.back().current) == 0)
			std::cerr << "Error!!" << std::endl << std::flush;
#endif
		//
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
		//
//		table.size()++;
	}

	return;
}

void TuringMachine::initialize(const std::string inputTape) {

	tapes = new Tape[noOfTapes];
	tapes[0].set(inputTape, blankSymbol);
	if ( inputTape.length() == 0 )
		tapes[0].content += SPECIAL_BLANK;
	//cerr << head[0] << "," << input.begin()<< endl;
	for(unsigned int i = 1; i < noOfTapes; i++) {
		tapes[i].content += SPECIAL_BLANK;
		tapes[i].headpos = 0;
	}
	state = table[0].current; //the initial state

	std::srand(std::time(0)); // seed for nondeterministic transitions
}

#ifdef SIMULATE
// tape繧定ｪｭ縺ｿ迥ｶ諷矩�ｷ遘ｻ繧貞ｮ溯｡後☆繧矩未謨ｰ
void TuringMachine::simulate(void) {
	// adrs:繝�繝ｼ繝励�ｮ繝倥ャ繝�縺ｮ菴咲ｽｮ縲《:迴ｾ迥ｶ諷九�《tep:繧ｹ繝�繝�繝玲焚
	unsigned int i;
	int searchOffset, /* adrs[2],*//* s=0, */step = 0; //,undo;
	char c = 'n';
	std::string acc;
//	time_t t1,t2;
	std::map<std::string, int>::iterator sitr;
	std::map<char, int>::iterator hitr;

	int headd;

	// 蛻晄悄迥ｶ諷九�ｮ蜊ｰ蟄�
	std::cout << std::endl << "Step: " << step << " ";
	print();

	// 迥ｶ諷矩�ｷ遘ｻ繧定｡後≧
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
						expectstr += tapes[tn].head();
					} else {
						expectstr += currentTuple.read[tn];
					}
					headstr += tapes[tn].head();
				}
				//cerr << expectstr << " - " << headstr << endl;
				if ( headstr == expectstr)
					break;
			}
		}
		if ( (unsigned ) i == table.size())
			break;  // halt
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

		// 繝�繝ｼ繧ｿ縺ｮ譖ｸ縺肴鋤縺�
		for (unsigned int k = 0; k < noOfTapes; k++) {
			if (table[i].write[k] == SPECIAL_THESAME) {
				//*head[k] = *head[k];
				// implements this by don't touch
			} else {
				tapes[k].head() = table[i].write[k] ;
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
			tapes[k].move(headd);
			state = table[i].next;
		}
		step++;
		std::cout << std::endl << "Step: " << step << " ";
		print();
		// undo,redo
	}
	std::cout << std::endl << "The Machine has halted at the state '" << state << "' and " << std::endl;
	if (acceptingStates.find(state) != acceptingStates.end()) {
		std::cout << "accepted ";
	} else {
		std::cout << "rejected ";
	}
	std::cout << "input '" << inputTape() << "'." << std::endl << std::endl;

	if (step == 0)
		exit(0);
}
#endif

// 迥ｶ諷矩�ｷ遘ｻ繧貞ｮ溯｡後☆繧矩未謨ｰ
bool TuringMachine::step(const unsigned int n) {
	std::string acc;
	std::map<std::string, int>::iterator sitr;
	std::map<char, int>::iterator hitr;
	int headd;
	unsigned int index, soffset;

	std::string expect, read;
	soffset = 0; //soffset = std::rand() % table.size();
	for (index = 0; index < table.size(); index++) {
		const Tuple & currentTuple = table[(soffset + index) % table.size()];
		if (currentTuple.current != state)
			continue;
		//cerr << currentTuple << endl;
		expect.clear() ;
		read.clear();
		unsigned int tn;
		for (tn = 0; tn < noOfTapes; tn++) {
			if ( currentTuple.read[tn] == SPECIAL_DONTCARE ) {
				expect += tapes[tn].head();
			} else {
				expect += currentTuple.read[tn];
			}
			read += tapes[tn].head();
		}
		if ( read == expect ) {
			// std::cout << "expect: " << expect << " - read: " << read << std::endl;
			break;
		}
	}
	// std::cout << "index = " << index << " size = " << table.size() << std::endl;
	if ( index == table.size() )
		return false;  // halt
	// preserve the row-in-table number of the tuple
	index = (soffset + index) % table.size();

	// 繝�繝ｼ繧ｿ縺ｮ譖ｸ縺肴鋤縺�
	for (unsigned int k = 0; k < noOfTapes; k++) {
		if (table[index].write[k] == SPECIAL_THESAME) {
			unsigned int tn;
			for(tn = 0; tn < noOfTapes; tn++) {
				if ( table[index].read[tn] == SPECIAL_DONTCARE )
					break;
			}
			if ( tn < noOfTapes )
				tapes[k].head() = read[tn];
			//*head[k] = *head[k];
			// implements this by don't touch
		} else {
			tapes[k].head() = table[index].write[k] ;
		}
		switch (table[index].headding[k]) {
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
		tapes[k].move(headd);
		state = table[index].next;
	}

	return true;
}


const bool TuringMachine::isAccepted(void) {
	return 	tapes[0].headAtTheEnd() &&  (acceptingStates.find(state) != acceptingStates.end());
}

// 繧ｹ繝�繝�繝玲ｯ弱�ｮ迥ｶ諷九ｒ陦ｨ遉ｺ縺吶ｋ髢｢謨ｰ
void TuringMachine::print(void) { //string state){

	// 迥ｶ諷九�ｮ陦ｨ遉ｺ
	if ( acceptingStates.find(state) != acceptingStates.end() )
		std::cout << "Accepting ";
	std::cout << std::endl;
	std::cout << "State: " << state << std::endl;

	// 蜈･蜉帷畑繝�繝ｼ繝励�ｮ陦ｨ遉ｺ
	std::cout << "Input tape: " << std::endl;
	std::cout << tapes[0] << std::endl;

	// 菴懈･ｭ逕ｨ繝�繝ｼ繝励�ｮ陦ｨ遉ｺ
	std::cout << "Working tape:";
	for (unsigned int tn = 1; tn < noOfTapes; tn++) {
		std::cout << std::endl << tapes[tn];
	}
	std::cout << std::endl;

}

// 計算状況（時点表示）のみの表示
std::ostream & TuringMachine::showConfiguration(std::ostream & stream) {

	// 状態
	stream << "(";
	stream << state;
	if ( acceptingStates.find(state) != acceptingStates.end() )
		stream << "!";
	stream << ", ";

	// 入力テープ
	stream << tapes[0] << ", ";

	// 作業用テープ
	for (unsigned int tn = 1; tn < noOfTapes; tn++) {
		stream<< tapes[tn];
		if ( tn + 1 == noOfTapes )
			continue;
		stream << ", ";
	}
	stream << ")";
	return stream;
}

/*
bool TuringMachine::searchin(std::string s, char in, char wk) {

	for (unsigned int i = 0; i < table.size(); i++)
		if (table[i].current == s && table[i].read[0] == in
				&& table[i].read[1] == wk)
			return true;
	return false;
}
*/

void TuringMachine::show(std::ostream & stream) {
	stream << "---Transition table---" << std::endl;
	for (unsigned int i = 0; i < table.size(); i++)
		stream << table[i].current << ' ' << table[i].read[0] << ' '
				<< table[i].read[1] << " -> " << table[i].next << " ("
				<< table[i].write[0] << ", " << table[i].headding[0]
				<< "), (" << table[i].write[1] << ", "
				<< table[i].headding[1] << ") " << std::endl;
	stream << "---Table end---" << std::endl;
	stream << "Accepting states: ";
	for (std::set<std::string>::iterator ep = acceptingStates.begin();
			ep != acceptingStates.end(); ep++) {
		stream << *ep << ", ";
	}
	stream << std::endl;
}
