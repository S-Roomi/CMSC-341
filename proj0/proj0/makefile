CXX = g++
CXXFLAGS = -Wall


proj0:	mytest.cpp bingo.o
		$(CXX) $(CXXFLAGS) mytest.cpp bingo.o -o proj0

bingo.o:  bingo.h bingo.cpp
		$(CXX) $(CXXFLAGS) -c bingo.cpp

clean:
	rm *.o* proj0
	

run:
	./proj0

val1:
	valgrind ./proj0 