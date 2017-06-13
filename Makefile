CC = gcc
CXX = g++

CFLAGS = -Wall -O0 -g3
CXXFLAGS = -Wall -O0 -g3
INCLUDES = -I./ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

all: tm.exe

tm.exe: tm.o TuringMachine.o
	$(CXX) $(CXXFLAGS) $(INCLUDES)  tm.o TuringMachine.o -o $@
	
tm.o: TuringMachine.h

TuringMachine.o: TuringMachine.h

clean:
	¥rm tm.exe tm.o TuringMachine.o
	