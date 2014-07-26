//
//  TypeTable.cpp
//  llvmfrontend
//
//  Created by h4x on 14-6-15.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#include "TypeTable.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/TypeBuilder.h>

using namespace std;
using namespace llvm;

void StructDef::AppendMember(const char* name, Type* type)
{
    string strname(name);
    int index = (int)this->memberTypes.size();
    
    this->memberTypes.push_back(type);
    this->memberIndex[strname] = index;
}

void StructDef::Clean()
{
    this->memberIndex.clear();
    this->memberTypes.clear();
}

TypeTable::TypeTable(LLVMContext& ctx)
{
    // built-in types
    this->types[string("INTEGER")] = TypeBuilder<int, false>::get(ctx);
    this->types[string("INT")] = TypeBuilder<int, false>::get(ctx);
    this->types[string("REAL")] = TypeBuilder<double, false>::get(ctx);
    this->types[string("BOOLEAN")] = Type::getInt1Ty(ctx);
}

void TypeTable::AddType(const char* name, Type* type)
{
    string strname(name);
    
    if(this->types.count(name) > 0)
        fprintf(stderr, "warning: type '%s' has already declared", name);
    
    this->types[strname] = type;
}

void TypeTable::AddStruct(const char* name, Type* type, StructDef& structDef)
{
    StructDef* copyedDef = new StructDef(structDef);
    
    AddType(name, type);
    this->structs[string(name)] = copyedDef;
}

Type* TypeTable::FindType(const char* name)
{
    string strname(name);
    
    auto cnt = this->types.count(strname);
    if(cnt == 0)
        return nullptr;
    else
        return this->types[strname];
}

Type* TypeTable::FindStructure(const char* name, StructDef** outDef)
{
    string strname(name);
    auto type = this->FindType(name);
    
    if(this->structs.count(strname) == 1)
    {
        if(outDef) *outDef = structs[strname];
        return type;
    }
    return  nullptr;
}

TypeTable::~TypeTable()
{
    for(auto it = structs.begin(); it != structs.end(); it++)
        delete it->second;
}
