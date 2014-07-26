//
//  NameTableStake.cpp
//  llvmfrontend
//
//  Created by h4x on 14-6-14.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#include "NameTableStack.h"

using namespace std;
using namespace llvm;

// ----------------
// -- NameTable

NameTable::NameTable()
{
    this->contextName = string("<anonymous>");
}

bool NameTable::NameExist(const char* name)
{
    string strname(name);
    auto cnt = this->table.count(strname);
    return (cnt > 0);
}

Value* NameTable::GetValue(const char* name)
{
    string strname(name);
    auto cnt = this->table.count(strname);
    if(cnt == 0)
        return nullptr;
    else
        return this->table[strname];
}

void NameTable::SetValue(const char* name, Value* value)
{
    string strname(name);
    this->table[strname] = value;
}

void NameTable::SetContextName(const char *ctxname)
{
    this->contextName = string(ctxname);
}


// ----------------
// -- NameTableStack


NameTableStack::NameTableStack()
{
    auto globalTable = new NameTable();
    globalTable->SetContextName("Global");
    
    this->stack.push_back(globalTable);
}

bool NameTableStack::NameExist(const char* name)
{
    for(int i = (int)this->stack.size()-1; i >= 0; i--)
        if(stack[i]->NameExist(name))
            return true;
    return false;
}

Value* NameTableStack::GetValue(const char* name)
{
    for(int i = (int)this->stack.size()-1; i >= 0; i--)
    {
        auto rtv = stack[i]->GetValue(name);
        if(rtv) return rtv;
    }
    return nullptr;
}

void NameTableStack::SetTopContextValue(const char* name, Value* value)
{
    NameTable& topCtx = *stack[stack.size() - 1];
    topCtx.SetValue(name, value);
}

NameTable& NameTableStack::GetTopContext()
{
    return *stack[stack.size() - 1];
}

NameTable& NameTableStack::GetGlobalContext()
{
    return *stack[0];
}

NameTable& NameTableStack::PushContext()
{
    auto newCtx = new NameTable();
    stack.push_back(newCtx);
    
    return *newCtx;
}

void NameTableStack::PopContext()
{
    if(stack.size() > 1)
        stack.pop_back();
}




