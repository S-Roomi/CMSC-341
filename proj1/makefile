CXX = g++
CXXFLAGS = -Wall


proj1:	mytest.cpp csr.o
		$(CXX) $(CXXFLAGS) mytest.cpp csr.o -o proj1

csr.o:  csr.h csr.cpp
		$(CXX) $(CXXFLAGS) -c csr.cpp

clean:
	rm *.o* proj1
	

run:
	./proj1

val1:
	valgrind ./proj1