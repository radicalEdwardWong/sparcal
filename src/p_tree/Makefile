CC = g++ -c

# Makefile for parse tree
PROGRAM: p_tree.o

p_tree.o:	../scanparse/scanparse.h ../symtab/symtab.h\
			p_tree.h p_tree.C
			$(CC) p_tree.C

clean:
		rm -f *.o a.out

print:
		cat p_tree.h p_tree.C Makefile

count:
		wc *.h *.C Makefile
