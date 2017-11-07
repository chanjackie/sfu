
x:	main.o dot.o
	gcc -o x dot.o main.o

main.o:	main.s
	gcc -c main.s

main.s:	main.c
	gcc -fno-builtin -O2 -S main.c

dot.o:	dot.s
	gcc -g -c dot.s


clean:
	rm -f x *.o main.s
