#include <iostream>
#include <fstream>
#include <vector>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/IR/Argument.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/PassManager.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/CommandLine.h>

#include "ast.h"
#include "irgen.h"

using namespace std;
using namespace llvm;

// -------------------------
// setup for parser

extern "C"
{
    int lineno = 1;
    int columnno = 1;
    int show_ast = 0;
    ast* ast_root = NULL;

    extern FILE* yyin;
    void yyparse();
    
    extern int parse_error;
}


// --------------------------
// backend main

void printVersion()
{
    printf("plang - PCAT LLVM compiler 1.0 (based on LLVM 3.4.1)\n");
}

void hideUnusefulCmd()
{
    StringMap<cl::Option*> Map;
    cl::getRegisteredOptions(Map);
    
    for(auto& it: Map)
    {
        if(it.first() != StringRef("help")
           && it.first() != StringRef("version"))
            it.second->setHiddenFlag(cl::Hidden);
    }
}


int main(int argc, char* argv[])
{
    // ----------------------
    // Command line parsing
    
    hideUnusefulCmd();
    
    // create commands
    cl::opt<string> inputFilename(cl::Positional, cl::desc("<input file>"), cl::init(""));
    cl::opt<string> outputFilename("o", cl::desc("Specify output filename"), cl::value_desc("filename"));
    cl::opt<bool> showAST("show-ast", cl::desc("Output abstract syntax tree to stdout"));
    cl::opt<bool> emitLLVM("emit-llvm", cl::desc("Output LLVM IR code"));
    cl::opt<bool> emitLLVMStdout("emit-llvm-stdout", cl::desc("Output LLVM IR to stdout"));
    cl::opt<bool> emitObject("c", cl::desc("Output object file"));
    cl::opt<bool> emitASM("S", cl::desc("Output assembly file"));
    cl::SetVersionPrinter(printVersion);
    
    // parse
    cl::ParseCommandLineOptions(argc, argv);
    
    
    // ----------------------
    // Compile
    
    // read file
    bool fromFile = false;
    if (inputFilename.length() > 0)
    {
        auto fin = fopen(inputFilename.c_str() ,"r");
        if(fin)
        {
            yyin = fin;
            fromFile = true;
        }
        else fprintf(stderr, "Fatal: cannot open file '%s'\n", inputFilename.c_str());
    }
    
#if 0
    yyin = fopen("/Users/h4x/Desktop/hw/Compile/labs/project/Project-3/src/test/test08.pcat", "r");
    fromFile = true;
#endif
    
    // configure ast tree printing
    if(showAST)
        show_ast = 1;
    
    // do parse, ast stored in ast_root
    yyparse();
    
    // close file if nessersary
    if(fromFile)
        fclose(yyin);
    
    if(parse_error)
    {
        // stop IR generating
        fprintf(stderr, "Info: found errors, IR generating stopped\n");
    }
    else
    {
        // generate IR
        LLVMContext& ctx = getGlobalContext();
        auto builder = IRBuilder<>(ctx);
        auto m = new Module("theModule", ctx);
        
        GenerateIR(ast_root, ctx, builder, m);
        
        // store IR
        string ircode;
        raw_string_ostream sout(ircode);
        m->print(sout, nullptr);
        
        // create a buffer for filename
        char cmdbuff[255];
        
        // output ir to stdout
        if(emitLLVMStdout)
            cout << ircode << endl;
        
        // output ir to file
        auto filename_ll = outputFilename + ".ll";
        {
            ofstream llout(filename_ll);
            llout << ircode << endl;
            llout.close();
        }
        
        // create asm file
        auto filename_S = outputFilename + ".S";
        snprintf(cmdbuff, sizeof(cmdbuff), "llc %s -o %s", filename_ll.c_str(), filename_S.c_str());
        int llc = system(cmdbuff);
        
        if(llc)
        {
            fprintf(stderr, "Error: llc exited with %d\n", llc);
            return llc;
        }
        
        // create executable file
        snprintf(cmdbuff, sizeof(cmdbuff), "clang -O3 %s -o %s", filename_S.c_str(), outputFilename.c_str());
        int clang = system(cmdbuff);
        
        if(clang)
        {
            fprintf(stderr, "Error: clang exited with %d\n", clang);
            return clang;
        }
        
        // clean up .ll file
        if(!emitLLVM)
            remove(filename_ll.c_str());
        
        // clean up .S file
        if(!emitASM)
            remove(filename_S.c_str());
    }
    
    return 0;
}
