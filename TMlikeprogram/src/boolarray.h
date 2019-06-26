/*
 * boolarray.h
 *
 *  Created on: 2017/07/22
 *      Author: sin
 */
#ifndef CPROG_BOOLARRAY_H_
#define CPROG_BOOLARRAY_H_

class boolarray {
	bool * array;
	unsigned int length;

public:
	boolarray(unsigned int n = 8) : array(new bool[n]), length(n) {	}

	~boolarray() { delete [] array; }

	unsigned int size() const { return length; }

	const bool & operator[](const unsigned int i) const { return array[i]; }

	bool & operator[](const unsigned int i) { return array[i]; }

	friend std::ostream & operator<<(std::ostream & ostr, const boolarray & b) {
		for(unsigned int i = 0; i < b.size(); i++)
			ostr << b[i];
		return ostr;
	}
};

#endif /* CPROG_BOOLARRAY_H_ */
