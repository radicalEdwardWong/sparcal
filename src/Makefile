# Makefile for Main module

OUT = sparcal
CC = g++ -Wall -Wextra -pedantic

SUBDIR	=	main ctrl scanparse p_tree symtab interp emit

DOTOHS	=	symtab/symtab.o ctrl/ctrl.o scanparse/scanparse.o p_tree/p_tree.o \
			interp/interp.o emit/emit.o main/Main.o

PROGRAM:
			for i in ${SUBDIR}; do \
				(echo $$i; cd $$i; make;); \
			done
			$(CC) -o $(OUT) $(DOTOHS)
			mv $(OUT) ../

clean:
			for i in ${SUBDIR}; do \
				(echo $$i; cd $$i; make clean;); \
			done
			rm -f *.o tmp* a.out ../$(OUT)
print:
			/usr/bin/pr -n Main.C Makefile > comp.lst
			cat comp.lst
			rm -f *.lst
			for i in ${SUBDIR}; do \
				(echo $$i; cd $$i; make print;); \
			done

count:
			for i in ${SUBDIR}; do \
				(echo $$i; cd $$i; make count;); \
			done

test:
			../$(OUT) -l toast.p

demo:
			cat toast.p
			../$(OUT) -ea toast.p
