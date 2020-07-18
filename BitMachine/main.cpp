#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

int open_def_file(const std::string & fname, const int tapes, const bool read_only,
		std::vector<std::string> & states, std::vector<std::string> & alphabet) {
	std::ifstream file;
	file.open(fname, std::ifstream::in);
	if ( !file.is_open() ) {
		std::cerr << "File open failed." << std::endl;
		return -1;
	}

	std::set<std::string> stateset, alphabetset;

	std::istringstream sstrm;
	std::string buff;
	std::string dummy;
	std::vector<std::string> tokens;
	while (!file.eof()) {
		getline(file, buff);
		if ( buff.length() == 0 )
			continue;
		sstrm.str(buff);
		sstrm.clear();
		tokens.clear();
		while ( !sstrm.eof() ) {
			dummy.clear();
			sstrm >> dummy;
			if ( dummy.empty() )
				continue;
			tokens.push_back(dummy);
		}
		if ( tokens.size() == 2 + tapes*3 - 1 ) {
			stateset.insert(tokens[0]);
			stateset.insert(tokens[tapes+1]);
			// if input is read-only:
			alphabetset.insert(tokens[1]);
			for(int i = 1; i < tapes; ++i) {
				alphabetset.insert(tokens[1+i]);
				alphabetset.insert(tokens[3+tapes+2*(i-1)]);
			}
		}
	}
	alphabet.clear();
	if ( alphabetset.find("_") != alphabetset.end() ) {
		alphabet.push_back("_");
		alphabetset.erase("_");
	}
	std::copy(alphabetset.begin(), alphabetset.end(), alphabet.begin());	std::vector<std::string> alpharray(alphabet.size());
	states.clear();
	std::copy(stateset.begin(), stateset.end(), states.begin());

	file.close();

	return 0;
}

int main(const int argc, const char **argv) {
	std::string fname;
	if ( argc > 1 ) {
		fname = argv[1];
	} else {
		return -1;
	}
	std::vector<std::string> alphabet, states;
	if ( open_def_file(fname, 2, true, states, alphabet) ) {
		return -1;
	}
	for(int i = 0; i < states.size(); ++i) {
		std::cout << i << " " << states[i] << ", ";
	}
	std::cout << std::endl;
	for(int i = 0; i < alphabet.size(); ++i) {
		std::cout << i << " " << alphabet[i] << ", ";
	}
	std::cout << std::endl;

	return 0;
}
