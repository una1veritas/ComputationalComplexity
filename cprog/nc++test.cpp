#include <iostream>
#include <cctype>
#include <string>
#include <sstream>

/* NC++ definitions */
#include <random>
std::random_device _randev; 
// may be slow, but no seed is required.
#define ndif if ( _randev() & 1 )
#define ndswitch(x) switch(_randev() % (x))
/* NC++ definitions end */

#define ABS(x) ((x)>=0 ? (x) : -(x))
#define SIGN(x) ((x) < 0 ? -1: 1)

class boolassignment {
	bool * array;
	unsigned int length;

public:
	boolassignment(unsigned int n) {
		length = n;
		array = new bool[length];
	}

	~boolassignment() {
		//delete [] array;
	}

	unsigned int size() const { return length; }

	void set(const unsigned int pos) {
		array[pos] = true;
	}

	void reset(const unsigned int pos) {
		array[pos] = false;
	}

	bool test(const unsigned int pos) const {
		return array[pos];
	}

	const bool & operator[](const unsigned int i) const {
		return array[i];
	}

	bool & operator[](const unsigned int i) {
		return array[i];
	}

	friend std::ostream & operator<<(std::ostream & ostr, const boolassignment & b) {
		for(unsigned int i = 0; i < b.size(); i++)
			ostr << b[i];
		return ostr;
	}
};

bool evalformula(char const * formula, boolassignment x) {
	char fm[strlen(formula)];
	char * bgptr, * edptr = fm;
	long varid;
	bool litval, claval, fmlval;
	enum OPERATOR {
		OR, AND
	} opr = OR;
	strcpy(fm, formula);
	std::cout << "evalformula.." << std::endl;
	claval = false;
	fmlval = true;
	while(1) {
		for( bgptr = edptr; isspace(*bgptr); ++bgptr) ;
		if ( *bgptr == ',' ) {
			std::cout << " OR ";
			opr = OR;
			++bgptr;
		} else if ( *bgptr == ';' ) {
			std::cout << " AND " << std::endl;
			opr = AND;
			++bgptr;
		} else {
			// the first literal
			opr = OR;
		}
		varid = strtol(bgptr, &edptr, 10);
		if ( SIGN(varid) > 0 ) {
			litval = x[varid];
			std::cout << "x" << varid << " = " << litval;
		} else {
			varid = ABS(varid);
			litval = !x[varid];
			std::cout << "~x" << varid << " = " << litval;
		}
		if ( opr == OR ) {
			claval = claval || litval;
		} else if ( opr == AND ) {
			fmlval = fmlval && claval;
			claval = litval;
		}
		if ( bgptr == edptr || *edptr == 0 )
			break;
	}
	std::cout << std::endl;
	std::cout << "fmlval = " << fmlval << std::endl;
	return fmlval;
}

int main(const int argc, const char * argv[]) {
	if ( argc < 2 )
		return -1;

	std::cout << argv[1] << std::endl;

	const int n = 9;
	boolassignment x(n);
  
  for(int i = 0; i < n; i++) {
    ndif {
      x[i] = true;
    } else {
      x[i] = false;
    }
  }
  std::cout << "Boolean assignment: "<< x << std::endl;
  
  if ( evalformula(argv[1], x) )
	  std::cout << "yes." << std::endl;
  else
	  std::cout << "halt." << std::endl;
  
  return 0;
}
