
x:	main.o sum.o
	gcc -o x sum.o main.o

main.o:	main.s
	gcc -c main.s

main.s:	main.c
	gcc -fno-builtin -O2 -S main.c

sum.o:	sum.s
	gcc -g -c sum.s


clean:
	rm -f x *.o main.s
