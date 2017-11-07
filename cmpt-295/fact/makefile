
x:	main.o fact.o
	gcc -o x fact.o main.o

main.o:	main.s
	gcc -c main.s

fact.o:	fact.s
	gcc -c fact.s

clean:
	rm -f x *.o 
