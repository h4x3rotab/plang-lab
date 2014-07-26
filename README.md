plang-lab
=========

PCAT LLVM compiler 1.0 (based on LLVM)

*This is the lab of the course "Compile" in Fudan University.*

# PCAT

"The **PCAT** language (**P**ascal **C**lone with an **AT**titude) is a small imperative
programming language with nested functions, record values with implicit pointers, arrays, 
integer and real variables, and a few simple structured control constructs." [[1]]

# PLANG

Plang is an compiler based on LLVM. It can compile, link, and eventually generate an 
executable file of your PCAT code.

# Build

Prepare the dependency (OS X):

    brew install llvm bdw-gc

or (Ubuntu):

    apt-get install llvm libgc

Configure the `Makefile` in `plang/src`. Make sure `LLVM_PREFIX` and `LLVM_LIBFILE` are
set correctly. Finally, run `make` command and you will get an executable `plang`.

# Usage

Try `plang --help`.

    USAGE: plang [options] <input file>

    OPTIONS:
      -S                - Output assembly file
      -c                - Output object file
      -emit-llvm        - Output LLVM IR code
      -emit-llvm-stdout - Output LLVM IR to stdout
      -help             - Display available options (-help-hidden for more)
      -o=<filename>     - Specify output filename
      -show-ast         - Output abstract syntax tree to stdout
      -version          - Display the version of this program

Example:

    plang -o hello HelloWorld.pcat

# Documents

The repository has documents in `doc` directory. However, only Chinese versions are available.



[1]: http://web.cecs.pdx.edu/~apt/cs302_1999/pcat99/pcat99.html
