
x:	main.o mul.o
	gcc -o x mul.o main.o

main.o:	main.s
	gcc -c main.s

mul.o:	mul.s
	gcc -c mul.s

main.s:	main.c
	gcc -O2 -S main.c

clean:	
	rm -f x *.o main.s
