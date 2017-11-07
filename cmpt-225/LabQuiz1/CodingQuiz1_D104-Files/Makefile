all: sltd

sltd: SomeList_Test_Driver.o SomeList.o Event.o 
	g++ -std=c++11 -o sltd SomeList_Test_Driver.o SomeList.o Event.o

SomeList_Test_Driver.o: SomeList_Test_Driver.cpp SomeList.h Event.h
	g++ -std=c++11 -c SomeList_Test_Driver.cpp

SomeList.o: SomeList.cpp SomeList.h Event.h
	g++ -std=c++11 -c SomeList.cpp

Event.o: Event.cpp Event.h
	g++ -std=c++11 -c Event.cpp

clean:
	rm -f sltd *.o