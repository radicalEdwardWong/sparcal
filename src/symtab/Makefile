CC = g++ -c

PROGRAM:	symtab.h symtab.o

ctrl.o: symtab.h symtab.C
		$(CC) symtab.C

clean:
		rm -f *.o a.out

print:
		cat symtab.h symtab.C Makefile

count:
		wc *.h *.C Makefile
