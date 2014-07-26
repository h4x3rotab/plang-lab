//
//  TypeToName.cpp
//  llvmfrontend
//
//  Created by h4x on 14-6-16.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#include "TypeToName.h"
#include <sstream>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

using namespace llvm;
using namespace std;

string TypeToName(llvm::Type* type)
{
    
    if(type->isIntegerTy())
    {
        int bits = type->getIntegerBitWidth();
        if(bits == 1)
            return "boolean";
        else
            return "integer";
    }
    else if(type->isDoubleTy())
    {
        return "real";
    }
    else if(type->isPointerTy())
    {
        auto elemty = TypeToName(type->getPointerElementType());
        return elemty + "[]";
    }
    else if(type->isStructTy())
    {
        return "record " + string(type->getStructName());
    }
    else if(type->isVoidTy())
    {
        return "void";
    }
    else if(type->isFunctionTy())
    {
        ostringstream sout;
        
        auto funcTy = cast<FunctionType>(type);
        auto retTy = funcTy->getReturnType();
        
        sout << "procedure(";
        for(int i=0, n=funcTy->getNumParams(); i<n ;i++)
        {
            if(i > 0) sout << ", ";
            
            auto argTy = funcTy->getParamType(i);
            auto argTyName = TypeToName(argTy);
            sout << argTyName;
        }
        sout << ")";
        
        if(!retTy->isVoidTy())
            sout << ":" << TypeToName(retTy);
        
        return sout.str();
    }
    
    return "<unknown>";
}