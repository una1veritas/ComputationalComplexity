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

char Tape::SPECIAL_BLANK = 'B';
char Tape::SPECIAL_DONTCARE = '*';
char Tape::SPECIAL_THESAME = '*';

const bool Tuple::matchesLeft(const std::string & state, const std::string & reads, const char doncare) const {
	if ( this->read.size() != reads.size() )
		return false;
	if ( current != state)
		return false;
	for (unsigned int tno = 0; tno < this->read.size(); tno++) {
		if ( this->read[tno] == doncare ) {
			continue;
		}
		if ( this->read[tno] != reads[tno] ) {
			return false;
		}
	}
	return true;
}
//
void TuringMachine::program(std::istream & file, const bool inputIsReadOnly) {

	std::istringstream strin;
	std::string buff;

	// inspecting the number of tapes
	std::string dummy;
	unsigned int cnt = 0;
	std::set<std::string> states;

	// inspect a line to determin the number of tapes.

	while (!file.eof()) {
		getline(file, buff, '\n');
		strin.str(buff);
		strin.clear();
		for (cnt = 0; !strin.eof(); cnt++) {
			strin >> dummy;
			if ( dummy.compare(0,2,"//") == 0 )
				break;
		}
		if ( cnt != 0 )
			break;
	}
	std::cerr << "program consists of " << cnt << " columns, ";
	if ( inputIsReadOnly ) {
		std::cerr << "the input-tape is read only, ";
		noOfTapes = (cnt - 4) / 3 + 1;
	} else {
		std::cerr << "the input tape is writable, ";
		noOfTapes = (cnt - 2) / 3;
	}
	std::cerr << " totally "<< noOfTapes << " tapes." << std::endl;

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
		if ( buff.compare(0,2, "//") == 0 )
			continue;

		table.push_back(Tuple(noOfTapes));
		// the 1st element
		strin >> table.back().current;
		for (cnt = 0; cnt < noOfTapes; cnt++) {
			// the readout of (c+1)th tape
			strin >> table.back().read[cnt];
		}
		std::cerr << "table row: " << table.back() << std::endl;
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
		for (cnt = 0; cnt < noOfTapes; cnt++) {
			if ( cnt == 0 && inputIsReadOnly ) {
				table.back().write[cnt] = table.back().read[cnt];
			} else {
				strin >> table.back().write[cnt];
			}
			strin >> table.back().headding[cnt];
		}
		std::cerr << "table row: " << table.back() << std::endl;

		if (file.eof())
			break;
#ifdef FALSE
#error ???
		if (states.count(table.back().current) == 0)
			std::cerr << "Error!!" << std::endl << std::flush;
#endif
		//
		for (cnt = 0; cnt < noOfTapes; cnt++) {
			if (!(isgraph(table.back().read[cnt])
					&& isgraph(table.back().write[cnt]))) {
				std::cout << "table-" << table.size() << ":Improper format." << std::endl;
				skipremaining = true;
				break; //exit(1);
			}
			if (!(table.back().headding[cnt] == 'R'
					|| table.back().headding[cnt] == 'L'
					|| table.back().headding[cnt] == 'N')) {
				std::cout << "table-" << table.size()
						<< ":Improper head motion specification: " << table.back().headding[cnt] << std::endl;
				skipremaining = true;
				break; //exit(1);
			}
		}
		//
//		table.size()++;
	}

	return;
}

void TuringMachine::initialize(const std::string inputTape, const char blank) {
	blankSymbol = blank;
	tapes = new Tape[noOfTapes];
	tapes[0].set(inputTape, 0, blankSymbol);
	if ( inputTape.length() == 0 )
		tapes[0].content += blankSymbol;
	//cerr << head[0] << "," << input.begin()<< endl;
	for(unsigned int i = 1; i < noOfTapes; i++) {
		tapes[i].set(tapes[i].content + blankSymbol, tapes[i].headpos, blankSymbol);
	}
	state = table[0].current; //the initial state

	std::srand(std::time(0)); // seed for nondeterministic transitions
}

//
bool TuringMachine::step(const unsigned int n) {
	std::string acc;
	std::map<std::string, int>::iterator sitr;
	std::map<char, int>::iterator hitr;
	std::vector<Tuple *> possibleTuples;

	//std::cerr << "table search ... ";
	std::string readout(noOfTapes, Tape::SPECIAL_BLANK);
	possibleTuples.clear();
	for (unsigned int index = 0; index < table.size(); index++) {
		for(unsigned int tapeno = 0; tapeno < noOfTapes; tapeno++) {
			readout[tapeno] = tapes[tapeno].head();
		}
		if ( table[index].matchesLeft(state, readout) ) {
			possibleTuples.push_back( &table[index]);
		}
	}
	// extracted tuples for possible transitions
	if ( possibleTuples.empty() )
		return false;  // halt
	unsigned int selected = 0;
	if ( possibleTuples.size() > 1 ) {
		selected = rand() % possibleTuples.size();
	}
	Tuple & ctuple = *possibleTuples[selected];
	// head actions for tapes
	for (unsigned int k = 0; k < noOfTapes; k++) {
		if (ctuple.write[k] == Tape::SPECIAL_DONTCARE) {
			tapes[k].head() = readout[k];
			//*head[k] = *head[k];
			// implements this by don't touch
		} else {
			tapes[k].head() = ctuple.write[k] ;
		}
		switch (ctuple.headding[k]) {
		case HEADMOTION_RIGHT:
			tapes[k].move(+1);
			break;
		case HEADMOTION_LEFT:
			tapes[k].move(-1);
			break;
		default: // HEADMOTION_NOMOVE 'N' or 'n'
//		tapes[k].move(0);
			break;
		}
	}
	state = ctuple.next;

	return true;
}


const bool TuringMachine::accepted(void) const {
	return 	tapes[0].headAtTheEnd() &&  (acceptingStates.find(state) != acceptingStates.end());
}

//
void TuringMachine::print(void) const { //string state){

	//
	if ( acceptingStates.find(state) != acceptingStates.end() )
		std::cout << "Accepting ";
	std::cout << std::endl;
	std::cout << "State: " << state << std::endl;

	//
	std::cout << "Input tape: " << std::endl;
	std::cout << tapes[0] << std::endl;

	//
	std::cout << "Working tape:";
	for (unsigned int tn = 1; tn < noOfTapes; tn++) {
		std::cout << std::endl << tapes[tn];
	}
	std::cout << std::endl;

}

// 計算状況（時点表示）のみの表示
std::ostream & TuringMachine::showConfiguration(std::ostream & stream) {

	// 状態
	stream << "( ";
	stream << state;
	if ( acceptingStates.find(state) != acceptingStates.end() )
		stream << "!";
	stream << ", " ;

	// 入力テープ
	stream << tapes[0] << ", ";

	// 作業用テープ
	for (unsigned int tn = 1; tn < noOfTapes; tn++) {
		stream << std::endl << "\t";
		stream<< tapes[tn];
		if ( tn + 1 == noOfTapes )
			continue;
		stream << ", ";
	}
	stream << " )" << std::endl;
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
	for (unsigned int i = 0; i < table.size(); i++) {
		stream << table[i].current << ' ';
		for(unsigned int tno = 0; tno < noOfTapes; tno++)
			stream << table[i].read[tno] << ' ';
		stream << " -> " << table[i].next;
		for(unsigned int tno = 0; tno < noOfTapes; tno++) {
			stream << " (" << table[i].write[tno] << ", " << table[i].headding[tno]
				<< "), ";
		}
		stream << std::endl;
	}
	stream << "---Table end---" << std::endl;
	stream << "Accepting states: ";
	for (std::set<std::string>::iterator ep = acceptingStates.begin();
			ep != acceptingStates.end(); ep++) {
		stream << *ep << ", ";
	}
	stream << std::endl;
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
