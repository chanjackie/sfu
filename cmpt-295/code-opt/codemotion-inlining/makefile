
all:	x	
	
x:	main.o str_alnum.o
	gcc -o x main.o str_alnum.o

main.o:	main.s
	gcc -c main.s

main.s:	main.c 
	gcc -S -O2 main.c

str_alnum.o:	str_alnum.s
	gcc -c str_alnum.s

str_alnum.s:	str_alnum.c 
	gcc -S -O2 str_alnum.c

clean:	
	rm -f *.o *.s x
