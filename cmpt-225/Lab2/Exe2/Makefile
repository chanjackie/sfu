all: ca

ca: circle_array.o Circle.o
	g++ -Wall circle_array.o Circle.o -o ca

Circle.o: Circle.h Circle.cpp
	g++ -Wall -c Circle.cpp

CircleApp.o: circle_array.cpp Circle.h
	g++ -Wall -c circle_array.cpp

clean:
	rm -f ca *.o
