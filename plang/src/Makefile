#--------------------------------------------------------------------------------
#
# Makefile for the PCAT AST generation
#
#--------------------------------------------------------------------------------

# The GC directory (the garbage collector)

GCC = clang
CXX = clang++
CFLAGS = -O0 -g -fno-omit-frame-pointer
LDFLAGS = -lgc
YACC = bison
LEX = flex

# * LLVM_PREFIX should be the installation path of LLVM
# * LLVM_LIBFILE is the dynamic library file of the whole LLVM engine
#
# For LLVM from Homebrew in OS X, the installation path is
#     `/usr/local/opt/llvm/bin`
# 
# And in the `lib` directory in LLVM path, we can find a dynamic 
# library file that contains all the components of LLVM. Link it 
# against our program. 
#
# For example, if we've found `libLLVM-3.4.dylib` in `lib` directory,
# set `LLVM_LIBFILE` to it.

LLVM_PREFIX = /usr/local/opt/llvm/bin
LLVM_LIBFILE = libLLVM-3.4.dylib

LLVM_DYLIB = `$(LLVM_PREFIX)/llvm-config --libdir`/$(LLVM_LIBFILE)
LLVM_CXXFLAGS = `$(LLVM_PREFIX)/llvm-config --cxxflags`
LLVM_LDFLAGS = `$(LLVM_PREFIX)/llvm-config --ldflags` $(LLVM_DYLIB)

all: plang

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

plang: pcat.o ast.o irgen.o TypeToName.o TypeTable.o NameTableStack.o ASTKinds.o llvmbackend.cpp
	$(CXX) $(LLVM_CXXFLAGS) -std=c++11 llvmbackend.cpp pcat.o ast.o irgen.o TypeToName.o TypeTable.o NameTableStack.o ASTKinds.o $(LLVM_DYLIB) -o plang

irgen.o: irgen.cpp
	$(CXX) $(LLVM_CXXFLAGS) -c -std=c++11 irgen.cpp

TypeToName.o: TypeToName.cpp
	$(CXX) $(LLVM_CXXFLAGS) -c -std=c++11 TypeToName.cpp

TypeTable.o: TypeTable.cpp
	$(CXX) $(LLVM_CXXFLAGS) -c -std=c++11 TypeTable.cpp

NameTableStack.o: NameTableStack.cpp
	$(CXX) $(LLVM_CXXFLAGS) -c -std=c++11 NameTableStack.cpp

ASTKinds.o: ASTKinds.cpp
	$(CXX) $(LLVM_CXXFLAGS) -c -std=c++11 ASTKinds.cpp








clean:
	/bin/rm -f *.o *~ pcat.yy.c pcat.c pcat.output parser core backend plang $(LLVM_LIBFILE)
