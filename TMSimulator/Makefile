CC = gcc
CXX = g++ -std=c++11

CFLAGS = -Wall -O -g3
CXXFLAGS = -Wall -O -g3
INCLUDES = -I./ 


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

all: tm.exe nc++test.exe

nc++test.exe: ./cprog/nc++test.o
	$(CXX) $(CFLAGS) $(INCLUDES) nc++test.o -o $@

nc++test.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

maker.exe: maker.o
	$(CC) $(CFLAGS) $(INCLUDES)  maker.o -o $@

tm.exe: tm.o TuringMachine.o
	$(CXX) $(CXXFLAGS) $(INCLUDES)  tm.o TuringMachine.o -o $@

tm.o: TuringMachine.h

TuringMachine.o: TuringMachine.h

clean:
	rm -f *.exe *.o
