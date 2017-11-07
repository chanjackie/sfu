
all:	x bonux

x:	main.o dot_prod.o 
	gcc -o x main.o dot_prod.o

bonux:	bonux.o dot_prod.o 
	gcc -o bonux bonux.o dot_prod.o

main.o:	main.s
	gcc -c main.s

main.s:	main.c
	gcc -O2 -S main.c

dot_prod.o:	dot_prod.s
	gcc -g -c dot_prod.s

bonux.o:	bonux.s
	gcc -c bonux.s

bonux.s:	bonux.c
	gcc -O2 -S bonux.c

clean:	
	rm -f bonux x *.o main.s bonux.s
