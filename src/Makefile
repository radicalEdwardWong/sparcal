# Makefile for Main module

CC = g++ -std=c++0x

SUBDIR	=	main ctrl scanparse p_tree interp emitter symtab

DOTOHS	=	ctrl/ctrl.o scanparse/scanparse.o p_tree/p_tree.o \
			interp/interp.o emitter/emit.o symtab/symtab.o main/Main.o


PROGRAM:
			for i in ${SUBDIR}; do \
				(echo $$i;cd $$i make;); \
			done
			CC -o epc $(DOTOHS)

clean:
			for i in ${SUBDIR}; do \
				(echo $$i;cd $$i; make clean;); \
			done
			rm -f *.o tmp* a.out epc
print:
			/usr/bin/pr -n Main.C Makefile > comp.lst
			cat comp.lst
			rm -f *.lst
			for i in ${SUBDIR}; do \
				(echo $$i;cd $$i; make print;); \
			done

count:
			for i in ${SUBDIR}; do \
				(echo $$i;cd $$i; make count;); \
			done