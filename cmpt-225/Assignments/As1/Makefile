all: wicps

wicps: WICPS.o List.o Patient.o
	g++ -Wall -o wicps WICPS.o List.o Patient.o

WICPS.o: WICPS.cpp List.h Patient.h
	g++ -Wall -c WICPS.cpp

List.o: List.h List.cpp
	g++ -Wall -c List.cpp

Patient.o: Patient.h Patient.cpp
	g++ -Wall -c Patient.cpp

clean:
	rm -f wicps *.o
