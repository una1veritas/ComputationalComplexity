#include <iostream>

/* NC++ definitions */
#include <random>
std::random_device _randev; 
// may be slow, but no seed is required.
#define ndif if ( _randev() & 1 )
#define ndswitch(x) switch(_randev() % (x))
/* NC++ definitions end */

class bits {
	unsigned char * bytes;
	unsigned int bitnum;
	unsigned int bytenum;

public:
	bits(unsigned int n) {
		bitnum = n;
		bytenum = (bitnum + 7) / 8; // ceiling of bitnum/8
		std::cout << "bytenum = " << bytenum << std::endl;
		bytes = new unsigned char [bytenum];
	}

	~bits() {
		delete [] bytes;
	}

	unsigned int size() const { return bytenum; }

	void set() {
		for(unsigned int i = 0; i < bytenum; i++)
			bytes[i] = 0xff;
	}

	void reset() {
		for(unsigned int i = 0; i < bytenum; i++)
			bytes[i] = 0;
	}

	void set(const unsigned int bitpos) {
		bytes[bitpos>>3] |= (1<<(bitpos&0x07));
	}

	void reset(const unsigned int bitpos) {
		bytes[bitpos>>3] &= ~((unsigned char)(1<<(bitpos&0x07)));
	}

	bool test(const unsigned int bitpos) const {
		return bytes[bitpos>>3] & (1<<(bitpos&0x07));
	}

	bool operator[](const unsigned int i) const {
		return test(i);
	}

	friend std::ostream & operator<<(std::ostream & ostr, const bits & b) {
		for(unsigned int i = 0; i < b.size(); i++)
			ostr << b[i];
		return ostr;
	}
};

bool formula(bits x) {
	return (x[0] || !x[1] || x[4])
			&& (!x[1] || x[2] || !x[5])
			&& (x[1] || !x[3] || x[4])
			&& (!x[2] || !x[4] || x[5]) ;
}

int main(const int argc, const char * argv[]) {
  const int n = 9;
  bits x(n);
  
  for(int i = 0; i < n; i++) {
    ndif {
      x.set(i);
    } else {
      x.reset(i);
    }
  }
  std::cout << "Boolean assignment: "<< x << std::endl;
  
  if ( formula(x) )
	  std::cout << "yes." << std::endl;
  else
	  std::cout << "halt." << std::endl;
  
  return 0;
}
