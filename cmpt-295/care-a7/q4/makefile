
all:	x

x:	main.o dynamic.o
	gcc -o x main.o dynamic.o

main.o:	main.c
	gcc -c main.c

dynamic.o:	dynamic.c
	gcc -c dynamic.c

clean:	
	rm -f *.o x
