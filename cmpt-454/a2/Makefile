all: test

test: test.o Node.o
	g++ -std=c++11 test.o Node.o -o test

test.o: test.cpp Node.h
	g++ -std=c++11 -c test.cpp

# List.o: List.h List.cpp Node.h
# 	g++ -std=c++11 -c List.cpp

Node.o: Node.h Node.cpp
	g++ -std=c++11 -c Node.cpp

clean:
	rm -f test *.o