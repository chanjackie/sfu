all: ltd

ltd: List_Test_Driver.o ListADT.o Profile.o Node.o
	g++ -Wall -o ltd List_Test_Driver.o ListADT.o Profile.o Node.o

List_Test_Driver.o: List_Test_Driver.cpp ListADT.h Profile.h Node.h
	g++ -Wall -c List_Test_Driver.cpp

ListADT.o: ListADT.h Node.h ListADT.cpp
	g++ -Wall -c ListADT.cpp

Node.o: Node.h Node.cpp
	g++ -Wall -c Node.cpp
	
Profile.o: Profile.h Profile.cpp
	g++ -Wall -c Profile.cpp

clean:
	rm -f ltd *.o