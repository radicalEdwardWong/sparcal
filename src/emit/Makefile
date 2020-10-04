CC = g++ -c

PROGRAM: emit.o

interp.o:	../symtab/symtab.h ../p_tree/p_tree.h emit.C
			$(CC) -c emit.C

clean:
			rm -f *.o tmp* a.out

print:
			cat emit.C Makefile

count:
			wc *.C Makefile
