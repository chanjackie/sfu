all: test

test: test.o Node.o BpTree.o
	g++ -std=c++11 test.o BpTree.o Node.o -o test

test.o: test.cpp Node.h
	g++ -std=c++11 -c test.cpp

BpTree.o: BpTree.h BpTree.cpp Node.h
	g++ -std=c++11 -c BpTree.cpp

Node.o: Node.h Node.cpp
	g++ -std=c++11 -c Node.cpp

clean:
	rm -f test *.o