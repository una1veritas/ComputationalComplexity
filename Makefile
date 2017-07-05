CC = gcc
CXX = g++ -std=c++11

CFLAGS = -Wall -O0 -g3
CXXFLAGS = -Wall -O0 -g3
INCLUDES = -I./ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

all: tm.exe maker.exe

maker.exe: maker.o
	$(CC) $(CFLAGS) $(INCLUDES)  maker.o -o $@

tm.exe: tm.o TuringMachine.o
	$(CXX) $(CXXFLAGS) $(INCLUDES)  tm.o TuringMachine.o -o $@

tm.o: TuringMachine.h

TuringMachine.o: TuringMachine.h

clean:
	rm -f tm.exe tm.o TuringMachine.o
