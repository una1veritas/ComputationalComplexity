#include <iostream>
#include <cctype>
#include <cstring>

#include "nc++.h"
#include "boolarray.h"

#define ABS(x) ((x)>=0 ? (x) : -(x))
#define SIGN(x) ((x) < 0 ? -1: 1)

//"1, 2, 3;1, -2, 3;1, 2, 3;-1, 2, 3;-1, -2, -3;-3, 5;-4, 5;3,-4,-5"
bool evalcnfformula(const char * formula, const boolarray & x);

int main(const int argc, const char * argv[]) {
	if ( argc < 2 )
		return -1;

	const int n = 5;
	boolarray x(n);

  for(int i = 0; i < n; i++) {
    ndif
      x[i] = true;
    else
      x[i] = false;
  }

  std::cout << "Boolean assignment: "<< x << std::endl;
  if ( evalcnfformula(argv[1], x) )
	  std::cout << "yes." << std::endl;
  else
	  std::cout << "(halt.)" << std::endl;

  return 0;
}

bool evalcnfformula(const char * formula, const boolarray & x) {
	char fm[strlen(formula)];
	char * bgptr, * edptr = fm;
	long varid;
	bool litval, claval, fmlval;
	enum OPERATOR {
		OR, AND
	} opr = OR;
	strcpy(fm, formula);

	claval = false;
	fmlval = true;
	while(1) {
		for( bgptr = edptr; isspace(*bgptr); ++bgptr) ;
		if ( *bgptr == ',' ) {
			std::cout << " v ";
			opr = OR;
			++bgptr;
		} else if ( *bgptr == ';' ) {
			std::cout << " ^ " << std::endl;
			opr = AND;
			++bgptr;
		} else {
			// the first literal
			opr = OR;
		}
		varid = strtol(bgptr, &edptr, 10);
		if ( SIGN(varid) > 0 ) {
			litval = x[varid-1];
			std::cout << "x" << varid << "=" << litval;
		} else {
			varid = ABS(varid);
			litval = !x[varid-1];
			std::cout << "~x" << varid << "=" << litval;
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
	return fmlval;
}
