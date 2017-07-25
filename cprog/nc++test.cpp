#include <iostream>
#include <cctype>
#include <cstring>

#include "nc++.h"
#include "boolarray.h"

#define ABS(x) ((x)>=0 ? (x) : -(x))
#define SIGN(x) ((x) < 0 ? -1: 1)

// encode a CNF (x_1 v x_3)^(~x_2 v x_3)^(~x_1 v x_2 v ~x_3)
// "1,3; -2,3; -1, 2, -3;"
bool evalCNFformula(const char * formula, const boolarray & x);

int main(const int argc, const char * argv[]) {
	if ( argc < 2 )
		return -1;

	const int n = 3;
	boolarray x(n);

  for(int i = 0; i < n; i++) {
    ndif
      x[i] = true;
    else
      x[i] = false;
  }

  std::cout << "Boolean assignment: "<< x << std::endl;
  if ( evalCNFformula(argv[1], x) )
	  std::cout << "yes." << std::endl;
  else
	  std::cout << "(halt.)" << std::endl;

  return 0;
}

bool evalCNFformula(const char * formula, const boolarray & x) {
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
		varid = strtol(bgptr, &edptr, 10);
		if ( bgptr != edptr ) {
			if ( SIGN(varid) > 0 ) {
				litval = x[varid-1];
				std::cout << "x" << varid << "=" << litval;
			} else {
				varid = ABS(varid);
				litval = !x[varid-1];
				std::cout << "~x" << varid << "=" << litval;
			}
			claval = claval || litval;
		} else {
			std::cout << "error. " << std::endl;
			break;
		}
		for( ; isspace(*edptr); ++edptr) ;
		if ( *edptr == 0 ) {
			opr = AND;
			std::cout << " ^ " << std::endl;
		} else if ( *edptr == ';' || *edptr == ')' ) {
			opr = AND;
			std::cout << " ^ " << std::endl;
			edptr++;
		} else if ( *edptr == ',' ) {
			opr = OR;
			std::cout << " v ";
			edptr++;
		}

		if ( opr == AND ) {
			fmlval = fmlval && claval;
			claval = false;
		}
		if ( *edptr == 0 )
			break;
	}
	std::cout << std::endl;
	return fmlval;
}
