PROGRAM:	ctrl.h ctrl.o

ctrl.o: ../scanparse/scanparse.h ../p_tree/p_tree.h \
		../symtab/symtab.h ctrl.h ctrl.C
		CC -c -g ctrl.C

clean:
		rm -f *.o a.out

print:
		cat ctrl.h ctrl.C Makefile

count:
		wc *.h *.C Makefile
