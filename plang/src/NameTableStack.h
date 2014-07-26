//
//  NameTableStake.h
//  llvmfrontend
//
//  Created by h4x on 14-6-14.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#ifndef __llvmfrontend__NameTableStack__
#define __llvmfrontend__NameTableStack__

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace llvm
{
    class Value;
    class Function;
    class BasicBlock;
}

class NameTable
{
    std::map<std::string, llvm::Value*> table;
    std::string contextName;
    
    llvm::Function* function;
    llvm::BasicBlock* block;
    
public:
    NameTable();
    
    bool NameExist(const char* name);
    llvm::Value* GetValue(const char* name);
    void SetValue(const char* name, llvm::Value* value);
    void SetContextName(const char* ctxname);
    
    // function context stuff
    inline void SetFunction(llvm::Function* func) { this->function = func; }
    inline void SetFuncBlock(llvm::BasicBlock* block) { this->block = block; }
    inline llvm::Function* GetFunction() { return this->function; }
    inline llvm::BasicBlock* GetFuncBlock() { return this->block; }
};

class NameTableStack
{
    std::vector<NameTable*> stack;
    
public:
    NameTableStack();
    
    bool NameExist(const char* name);
    llvm::Value* GetValue(const char* name);
    void SetTopContextValue(const char* name, llvm::Value* value);
    
    NameTable& GetTopContext();
    NameTable& GetGlobalContext();
    
    NameTable& PushContext();
    void PopContext();
};

#endif /* defined(__llvmfrontend__NameTableStack__) */
