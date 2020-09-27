CC = g++

#Makefile for SPARCal (Pascal-to-SPARC) compiler
PROGRAM:		scanparse.o

scanparse.o:	../p_tree/p_tree.h scanparse.h scanparse.C\
				scanparse.fct
				$(CC) scanparse.C

scanparse.fct:	parser.tmp scanner.tmp
				cat scanner.tmp parser.tmp > scanparse.fct

scanner.tmp:	scanner.h scanner.specs scanner.fcts parser.gram
				lex scanner.specs
				sed -f scanner.cmd lex.yy.c > scanner.tmp

parser.tmp:		parser.gram parser.fcts
				yacc -vd parser.gram
				mv y.tab.h y.tab.h.tmp
				mv y.tab.c y.tab.c.tmp
				sed '/extern YYSTYPE yylval;/d' y.tab.h.tmp > y.tab.h
				sed -f parser.cmd y.tab.c.tmp > y.tab.c
				cp y.tab.c parser.tmp
				rm y.tab.h.tmp y.tab.c.tmp

clean:
				rm -f *.o lex.yy.c y.tab.c y.o* *tmp*\
				scanparse.fct y.tab.h a.out

print:
				cat scanparse.h scanparse.C\
				scanner.specs parser.gram Makefile

count:
				wc *.cmd *.fcts *.specs *.gram *.h *.C Makefile
