#ifndef _TURINGMACHINE_H_
#define _TURINGMACHINE_H_

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stack>


static const char SPECIAL_BLANK = '_';
static const char SPECIAL_DONTCARE = '*';
static const char SPECIAL_THESAME = '*';

static const char HEADMOTION_NOMOVE = 'N';
static const char HEADMOTION_RIGHT = 'R';
static const char HEADMOTION_LEFT = 'L';

struct Tuple {
	std::string current;
	std::string read;
	std::string next;
	std::string write, headding; // hder[0]:入力用テープのヘッドの動き、hder[1]:作業用テープの

	Tuple(int tapes) {
		current = "";
		read = std::string(tapes, SPECIAL_BLANK);
		next = "";
		write = std::string(tapes, SPECIAL_BLANK);
		headding = std::string(tapes, HEADMOTION_NOMOVE);
	}

	// input & output ;
	friend std::ostream & operator <<(std::ostream & stream, const Tuple & obj) {
		stream << obj.current << ", " << obj.read << ", " << obj.next << ", " << obj.write << ", " << obj.headding;
		return stream;
	}

};

struct Tape {
	unsigned int headpos;
	std::string content;

	void set(std::string str) {
		headpos = 0;
		content = str;
	}

	char & head(void) {
		return content[headpos];
	}

	const char move(int headdir) {
		char tmp = head();
		if ( headdir == 0 )
			return tmp;
		headdir = (headdir < 0 ? -1 : 1 );

		if ( headpos == 0 && headdir == -1) {
			content = std::string("_") + content;
			headpos = 0;
		} else {
			headpos += headdir;
			if ( headpos == length() )
				content += "_";
		}
		return tmp;
	}

	const char & head(void) const {
		return content[headpos];
	}

	unsigned int length(void) const {
		return content.length();
	}

	friend std::ostream & operator<<(std::ostream & stream, const Tape & tape) {
		for (unsigned int h = 0; h <= tape.length() ; h++) {
			if ( h == tape.headpos ) {
				stream << "[" << tape.content[h];
			} else if ( h == tape.headpos+1 ) {
				stream << "]" << tape.content[h];
			} else {
				stream << " " << tape.content[h];
			}
		}
	return stream;
	}
};

struct TuringMachine {

private:
	std::string state;
	Tape * tapes;

public:
	std::vector<Tuple> table;
	unsigned int noOfTapes;
	std::set<std::string> acceptingStates;

	TuringMachine(void) { }
	~TuringMachine(void) { delete [] tapes; }

public:
	void program(std::istream &, const bool inputIsReadOnly = true);
	void initialize(const std::string inputTape);
	void simulate(void);
	const Tuple & transition(const Tuple & currentTuple);
//	bool searchin(std::string state, char oninput, char onwork);

	bool step(const unsigned int n = 1);
	const Tape & inputTape(void) { return tapes[0]; }

	void print(void); //string state);
	void show(std::ostream & stream);

};


#endif
