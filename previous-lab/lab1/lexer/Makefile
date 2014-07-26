#--------------------------------------------------------------------------------
#
# Makefile for the PCAT scanner
#
#--------------------------------------------------------------------------------

# The GC directory (the garbage collector)
GCDIR = /usr/local/Cellar/bdw-gc/7.2e

GCC = g++
CXXFLAGS = -g
YACC = bison
LEX = flex
INCLUDE = basic.h basic.templates

lexer:	main.cc basic.o pcat.yy.c
	$(GCC) $(CXXFLAGS) main.cc basic.o $(GCDIR)/gc.a -o lexer

basic.o: basic.cc $(INCLUDE)
	 $(GCC) $(CXXFLAGS) -c basic.cc

pcat.yy.c: pcat.lex
	   $(LEX) pcat.lex
	   mv lex.yy.c pcat.yy.c

clean: 
	/bin/rm -f *.o *~ pcat.yy.c lexer core
