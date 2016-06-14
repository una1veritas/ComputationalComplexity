
CC	= cc
CXX	= g++
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<


TMOBJS = TuringMachine.o tm.o

all: tm

tm: $(TMOBJS)
	$(CXX) $(CXXFLAGS) $(TMOBJS) -o tm

TuringMachine.o: TuringMachine.h TuringMachine.cpp

clean   :
	rm -f tm core *.o *~
