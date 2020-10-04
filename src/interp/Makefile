CC = g++ -c

PROGRAM: interp.o

interp.o:	../symtab/symtab.h ../p_tree/p_tree.h interp.C
			$(CC) -c interp.C

clean:
			rm -f *.o tmp* a.out

print:
			cat interp.C Makefile

count:
			wc *.C Makefile
