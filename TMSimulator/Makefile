CC = gcc
CXX = g++ -std=c++11

CFLAGS = -Wall -O0 -g
CXXFLAGS = -Wall -O0 -g
INCLUDES = -I./ 


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

all: tm.exe 

tm.exe: tm.o TuringMachine.o
	$(CXX) $(CXXFLAGS) $(INCLUDES)  tm.o TuringMachine.o -o $@

tm.o: TuringMachine.h

TuringMachine.o: TuringMachine.h

clean:
	rm -f *.exe *.o
