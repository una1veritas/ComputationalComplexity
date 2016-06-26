CC	= gcc 
CXX	= g++ -std=c++11
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g -O

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<


TMOBJS = TuringMachine.o tm.o

all: tm

tm: $(TMOBJS)
	$(CXX) $(CXXFLAGS) $(TMOBJS) -o tm

TuringMachine.o: TuringMachine.h TuringMachine.cpp

clean   :
	rm -f tm core *.o *~
	rm -f *.dSym
	rm -r RemoteSystemsTempFiles

distclean: clean 
