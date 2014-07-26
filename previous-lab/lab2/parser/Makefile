#--------------------------------------------------------------------------------
#
# Makefile for the PCAT AST generation
#
#--------------------------------------------------------------------------------

# The GC directory (the garbage collector)

GCC = clang
CFLAGS = -O0 -g -fno-omit-frame-pointer
LDFLAGS = -lgc
YACC = bison
LEX = flex

all: parser

parser: main.c ast.h pcat.o ast.o
	$(GCC) $(CFLAGS) $(LDFLAGS) main.c pcat.o ast.o -o parser

ast.o:  ast.c ast.h
	$(GCC) $(CFLAGS) -c ast.c

pcat.c: pcat.y
	$(YACC) -d -v pcat.y
	mv pcat.tab.c pcat.c

pcat.o: pcat.c pcat.yy.c ast.h
	$(GCC) $(CFLAGS) -c pcat.c

pcat.yy.c: pcat.lex
	   $(LEX) pcat.lex
	   mv lex.yy.c pcat.yy.c

clean:
	/bin/rm -f *.o *~ pcat.yy.c pcat.c pcat.output parser core
