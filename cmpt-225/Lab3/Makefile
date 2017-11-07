all: test

test: test.o List.o Node.o
	g++ -Wall test.o List.o Node.o -o test

test.o: test.cpp List.h
	g++ -Wall -c test.cpp

List.o: List.h List.cpp Node.h
	g++ -Wall -c List.cpp

Node.o: Node.h Node.cpp
	g++ -Wall -c Node.cpp

clean:
	rm -f test *.o