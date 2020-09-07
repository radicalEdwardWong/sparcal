#Makefile for Pascal-to-SPARC compiler
PROGRAM:		scanparse.o

scanparse.o:	./p_tree/p_tree.h scanparse. scanparse.C\
				scanparse.fct
				CC -c -g scanparse.C

scanparse.fct:	parser.tmp scanner.tmp
				cat scanner.tmp parser.tmp > scanparse.fct

scanner.tmp:	scanner.h scanner.specs scanner.fcts parser.gram
				lex scanner.specs
				sed - scanner.cmd lex.yy.c  scanner.tmp
				rm lex.yy.c

parser.tmp:		parser.h parser.gram parser.fcts
				bison -vd parser.gram
				sed -f parser.cmd y.tab.c > parser.tmp
				rm y.tab.c

clean:
				rm -f *.o lex.yy.c y.tab.c y.o* *tmp*\
				scanparse.fct y.tab.h a.out

print:
				cat scanparse.h scanparse.C\
				scanner.scecs parser.gram Makefile

count:
				wc *.cmd *.fcts *.specs *.gram *.h *.C Makefile
