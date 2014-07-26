//
//  irgen.cpp
//  llvmfrontend
//
//  Created by h4x on 14-6-14.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#include "irgen.h"

#include <cstdio>
#include <stack>
#include <unistd.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/IR/Argument.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/PassManager.h>
#include <llvm/Pass.h>


#include "ast.h"
#include "ASTKinds.h"
#include "NameTableStack.h"
#include "TypeTable.h"
#include "TypeToName.h"

using namespace llvm;
using namespace std;

static const ast_kind expkinds_array[] = {
    pos_exp, neg_exp, not_exp,
    plus_exp, minus_exp, times_exp, fdiv_exp, div_exp, mod_exp,
    or_exp, and_exp, gt_exp, lt_exp, eq_exp, ge_exp, le_exp, neq_exp,
    fcall_exp, finit_exp, ainit_exp,
    idx_exp, mem_exp,
};
static ASTKinds expkinds = ASTKinds(sizeof(expkinds_array)/sizeof(ast_kind), expkinds_array);

struct IRGenContext
{
    LLVMContext* ctx;
    IRBuilder<>* irb;
    Module* module;
    
    NameTableStack names;
    TypeTable typetable;
    stack<BasicBlock*> loopExitStack;   // for 'exit' statement in nested loops
    bool forceStop;
    
    // function from libc
    struct {
        Function* scanf;
        Function* printf;
    } libcfunc;
    
    struct {
        Function* memncpy;
        Function* readreal;
        Function* writereal;
        Function* writeint;
        Function* writestr;
    } pcatfunc;
    
    IRGenContext(LLVMContext& ctx) : typetable(ctx)
    {
        this->ctx = &ctx;
        forceStop = false;
    }
    
    char msgbuff[255];
    
    void PrintLocation(ast_loc* location);
    void Warning(ast_loc* location, const char* msg, ...);
    void Error(ast_loc* location, const char* msg, ...);
    void FatalError(ast_loc* location, const char* msg, ...);
    
    /// \brief Extract nodes from linked list to build an array.
    void extractNodeList(ast_list* lst, vector<ast*>& outArray);
    void extractNodeList(ast* node, vector<ast*>& outArray);
    
    void RegisterLibc();
    void CreateInternal_readreal();
    void CreateInternal_writereal();
    void CreateInternal_writeint();
    void CreateInternal_writestr();
    void CreateInternal_memncpy();
    
    /// \brief Generate IR code from an arbitrary node
    Value* GenerateNode(ast* node, ASTKinds expectNode, bool globaldecl = false);
    
    /// \brief Generate expression
    Value* GenerateExpression(ast* node);
    
    /// \brief Generate body code
    void GenerateBody(ast* body, bool globaldecl = true);
    
    /// \brief Generate assignment code with auto-casting (between int * double)
    void GenerateNumericAssign(Value* exprval, Value* varptr, ast_loc* loc);
    
    Constant* GetZeroinitializer(Type* Ty);
    
    void GenerateVarDeclares(ast* node, bool globaldecl = true);
    
    /// \brief Create types
    void GenerateTypeDeclares(ast* node);
    
    /// \brief Get the L-Value address
    Value* GenerateLvalue(ast* node);
    
    /// \brief Make sure the value having a proper type
    ///
    /// Otherwise the function will throw an error and return the
    /// default value of the given type.
    Value* SafelyGetValue(Value* value, Type* ty, ast_loc* location);
    
    /// \brief Get the value with proper type and do casting when needed (int->real)
    Value* SafelyGetValueAutoCast(Value* value, Type* ty, ast_loc* location);
    
    bool GenerateStatement(ast* node);
    void GenerateStatements(ast* node);
    
    void GenerateProcedure(ast* node, bool globaldecl = true);
    void GenerateProcedures(ast* node, bool globaldecl = true);
    
    void GenerateProgram(ast* root);
    
    
};

void IRGenContext::PrintLocation(ast_loc* location)
{
    if(location)
    {
        fprintf(stderr, "[%d.%d]:[%d.%d] ",
                location->first_line, location->first_column,
                location->last_line, location->last_column);
    }
}

void IRGenContext::Warning(ast_loc* location, const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    vsnprintf(msgbuff, sizeof(msgbuff), msg, ap);
    va_end(ap);
    
    PrintLocation(location);
    if(isatty(fileno(stdout)))
        fprintf(stderr, "\033[35mwarning:\033[39m %s\n", msgbuff);
    else
        fprintf(stderr, "warning: %s\n", msgbuff);
}

void IRGenContext::Error(ast_loc* location, const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    vsnprintf(msgbuff, sizeof(msgbuff), msg, ap);
    va_end(ap);
    
    PrintLocation(location);
    if(isatty(fileno(stdout)))
        fprintf(stderr, "\033[31merror:\033[39m %s\n", msgbuff);
    else
        fprintf(stderr, "error: %s\n", msgbuff);
}

void IRGenContext::FatalError(ast_loc* location, const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    vsnprintf(msgbuff, sizeof(msgbuff), msg, ap);
    va_end(ap);
    
    PrintLocation(location);
    if(isatty(fileno(stdout)))
        fprintf(stderr, "\033[31;1mfatal:\033[39;2m %s\n", msgbuff);
    else
        fprintf(stderr, "fatal: %s\n", msgbuff);
    
    forceStop = true;
}

/// \brief Extract nodes from linked list to build an array.
void IRGenContext::extractNodeList(ast_list* lst, vector<ast*>& outArray)
{
    outArray.clear();
    for(auto head = lst; head != nullptr; head = head->next)
        outArray.push_back(head->elem);
}
void IRGenContext::extractNodeList(ast* node, vector<ast*>& outArray)
{
    extractNodeList(node->info.node.arguments, outArray);
}

void IRGenContext::RegisterLibc()
{
    auto i8pTy = Type::getInt8PtrTy(*ctx);
    auto i32Ty = Type::getInt32Ty(*ctx);
    
    // -- int scanf(char*, ...)
    auto scanfTy = FunctionType::get(i32Ty, i8pTy, true);
    libcfunc.scanf = Function::Create(scanfTy, Function::ExternalLinkage, "scanf", module);
    
    // -- int printf(char*, ...)
    auto printfTy = FunctionType::get(i32Ty, i8pTy, true);
    libcfunc.printf = Function::Create(printfTy, Function::ExternalLinkage, "printf", module);
}

void IRGenContext::CreateInternal_readreal()
{
    // double __pcat_readreal()
    // {
    //     double x;
    //     scanf("%lf", &x);
    //     return x;
    // }
    
    auto doubleTy = Type::getDoubleTy(*ctx);
    auto i8pTy = Type::getInt8PtrTy(*ctx);
    
    auto readrealTy = FunctionType::get(doubleTy, false);
    auto readreal = Function::Create(readrealTy, Function::ExternalLinkage, "__pcat_readreal", module);
    
    auto b_entry = BasicBlock::Create(*ctx, "entry", readreal);
    irb->SetInsertPoint(b_entry);
    
    // arg: "%lf"
    auto fmt = irb->CreateGlobalStringPtr("%lf");
    
    // arg: &x
    auto x_var = irb->CreateAlloca(doubleTy);
    auto x_i8p = irb->CreateBitCast(x_var, i8pTy);
    
    // scanf("%lf", &x)
    irb->CreateCall2(libcfunc.scanf, fmt, x_i8p);
    
    auto x_val = irb->CreateLoad(x_var, "x");
    irb->CreateRet(x_val);
    
    verifyFunction(*readreal);
    
    pcatfunc.readreal = readreal;
}


void IRGenContext::CreateInternal_writereal()
{
    // void __pcat_writereal(double x)
    // {
    //     printf("%lf", x);
    // }
    
    auto voidTy = Type::getVoidTy(*ctx);
    auto doubleTy = Type::getDoubleTy(*ctx);
    
    auto writerealTy = FunctionType::get(voidTy, doubleTy, false);
    auto writereal = Function::Create(writerealTy, Function::ExternalLinkage, "__pcat_writereal", module);
    
    auto b_entry = BasicBlock::Create(*ctx, "entry", writereal);
    irb->SetInsertPoint(b_entry);
    
    // arg: "%lf"
    auto fmt = irb->CreateGlobalStringPtr("%lf");
    
    // arg: x
    auto argx = writereal->arg_begin();
    
    irb->CreateCall2(libcfunc.printf, fmt, argx);
    irb->CreateRetVoid();
    
    verifyFunction(*writereal);
    pcatfunc.writereal = writereal;
}

void IRGenContext::CreateInternal_writeint()
{
    // void __pcat_writereal(double x)
    // {
    //     printf("%lf", x);
    // }
    
    auto voidTy = Type::getVoidTy(*ctx);
    auto intTy = TypeBuilder<int, false>::get(*ctx);
    
    auto writeintTy = FunctionType::get(voidTy, intTy, false);
    auto writeint = Function::Create(writeintTy, Function::ExternalLinkage, "__pcat_writeint", module);
    
    auto b_entry = BasicBlock::Create(*ctx, "entry", writeint);
    irb->SetInsertPoint(b_entry);
    
    // arg: "%lf"
    auto fmt = irb->CreateGlobalStringPtr("%d");
    
    // arg: x
    auto argx = writeint->arg_begin();
    
    irb->CreateCall2(libcfunc.printf, fmt, argx);
    irb->CreateRetVoid();
    
    verifyFunction(*writeint);
    pcatfunc.writeint = writeint;
}


void IRGenContext::CreateInternal_writestr()
{
    auto voidTy = Type::getVoidTy(*ctx);
    auto i8pTy = Type::getInt8PtrTy(*ctx);
    
    auto writestrTy = FunctionType::get(voidTy, i8pTy, false);
    auto writestr = Function::Create(writestrTy, Function::ExternalLinkage, "__pcat_writestr", module);
    
    auto b_entry = BasicBlock::Create(*ctx, "entry", writestr);
    irb->SetInsertPoint(b_entry);

    auto cont = writestr->arg_begin();
    
    irb->CreateCall(libcfunc.printf, cont);
    irb->CreateRetVoid();
    
    verifyFunction(*writestr);
    pcatfunc.writestr = writestr;
}

void IRGenContext::CreateInternal_memncpy()
{
    //  void __pcat_memncpy(void* tgt, void* src, size_t n, size_t sz)
    //  {
    //      int i = 0;
    //      while(i < n)
    //      {
    //          memcpy(tgt, src, sz);
    //          tgt += sz;
    //          i++;
    //      }
    //  }
    
    vector<Type*> memncpyArgTy;
    memncpyArgTy.push_back(Type::getInt8PtrTy(*ctx));
    memncpyArgTy.push_back(Type::getInt8PtrTy(*ctx));
    memncpyArgTy.push_back(TypeBuilder<size_t, false>::get(*ctx));
    memncpyArgTy.push_back(TypeBuilder<size_t, false>::get(*ctx));
    
    auto memncpyTy = FunctionType::get(Type::getVoidTy(*ctx), memncpyArgTy, false);
    auto memncpy = Function::Create(memncpyTy, Function::ExternalLinkage, "__pcat_memncpy", module);
    
    auto b_entry = BasicBlock::Create(*ctx, "entry", memncpy);
    auto b_cond = BasicBlock::Create(*ctx, "cond", memncpy);
    auto b_loop = BasicBlock::Create(*ctx, "loop", memncpy);
    auto b_fin = BasicBlock::Create(*ctx, "fin", memncpy);
    
    irb->SetInsertPoint(b_entry);
    
    auto sizeTy = TypeBuilder<size_t, false>::get(*ctx);
    auto int_0 = ConstantInt::get(sizeTy, 0);
    auto int_1 = ConstantInt::get(sizeTy, 1);
    
    auto argit = memncpy->arg_begin();
    auto ptr_tgt = argit++; ptr_tgt->setName("arg_tgt");
    auto ptr_src = argit++; ptr_src->setName("arg_src");
    auto int_n = argit++;   int_n->setName("arg_n");
    auto int_sz = argit++;  int_sz->setName("arg_sz");
    
    // i = 0
    auto var_i = irb->CreateAlloca(sizeTy, 0, "var_i");
    irb->CreateStore(int_0, var_i);
    
    // localtgt = tgt
    auto var_tgt = irb->CreateAlloca(Type::getInt8PtrTy(*ctx), 0, "var_tgt");
    irb->CreateStore(ptr_tgt, var_tgt);
    irb->CreateBr(b_cond);
    
    // while(i < n)
    irb->SetInsertPoint(b_cond);
    auto int_i = irb->CreateLoad(var_i, "i");
    auto cond = irb->CreateICmpSLT(int_i, int_n);
    irb->CreateCondBr(cond, b_loop, b_fin);
    
    {
        // memcpy(tgt, src, sz)
        irb->SetInsertPoint(b_loop);
        auto local_tgt = irb->CreateLoad(var_tgt, "val_tgt");
        irb->CreateMemCpy(local_tgt, ptr_src, int_sz, 1);
        
        // tgt += sz
        auto new_tgt = irb->CreateGEP(local_tgt, int_sz);
        irb->CreateStore(new_tgt, var_tgt);
        
        // i++
        auto new_i = irb->CreateAdd(int_i, int_1);
        irb->CreateStore(new_i, var_i);
        irb->CreateBr(b_cond);
    }
    
    // return
    irb->SetInsertPoint(b_fin);
    irb->CreateRetVoid();
    
    verifyFunction(*memncpy);
    pcatfunc.memncpy = memncpy;
}

void IRGenContext::GenerateBody(ast* body, bool globaldecl)
{
    vector<ast*> args;
    extractNodeList(body, args);
    
    auto declareLst = args[0];
    auto progblock = args[1];
    
    // gen declares
    vector<ast*> declares;
    extractNodeList(declareLst, declares);
    
    for(auto decl : declares)
    {
        // The declaration generator should ensure not moving the IRBuilder
        // insert point after calling.
        // Actually only procedure declaration needs to deal with this case.
        GenerateNode(decl, ASTKinds(var_decls, type_decls, proc_decls), globaldecl);
    }
    
    // gen program block (continue the function block)
    GenerateNode(progblock, ASTKinds(stat_node));
}

void IRGenContext::GenerateNumericAssign(Value* exprval, Value* varptr, ast_loc* loc)
{
    Value* castedValue = nullptr;
    auto xTy = exprval->getType();
    auto yTy = varptr->getType()->getPointerElementType();
    
    if(xTy == yTy)
    {
        castedValue = exprval;
    }
    else if(xTy->isDoubleTy() && yTy->isIntegerTy() && yTy->getIntegerBitWidth() != 1)
    {
        // double -> int
        auto intTy = TypeBuilder<int, false>::get(*ctx);
        castedValue = irb->CreateFPToSI(exprval, intTy);
    }
    else if(xTy->isIntegerTy() && xTy->getIntegerBitWidth() != 1 && yTy->isDoubleTy())
    {
        // int -> double
        auto doubleTy = TypeBuilder<double, false>::get(*ctx);
        castedValue = irb->CreateSIToFP(exprval, doubleTy);
    }
    else
    {
        auto xty_name = TypeToName(xTy);
        auto yty_name = TypeToName(yTy);
        Error(loc, "assigning to '%s' from incompatible type '%s'",
              yty_name.c_str(), xty_name.c_str());
        return;
    }

    // make assign
    irb->CreateStore(castedValue, varptr);
}

Constant* IRGenContext::GetZeroinitializer(Type* Ty)
{
    if(Ty->isStructTy() || Ty->isArrayTy() || Ty->isVectorTy())
        return ConstantAggregateZero::get(Ty);
    else if(Ty->isIntegerTy())
        return ConstantInt::get(Ty, 0);
    else if(Ty->isDoubleTy())
        return ConstantFP::get(Ty, 0.0);
    else if(Ty->isPointerTy())
        return ConstantPointerNull::get((PointerType*)Ty);
    else
    {
        FatalError(nullptr, "cannot find the zero-initializer for type '%s'",
                   TypeToName(Ty).c_str());
        return nullptr;
    }
}

void IRGenContext::GenerateVarDeclares(ast* node, bool globaldecl)
{
    vector<ast*> vardecs;
    extractNodeList(node, vardecs);
    
    for(auto vardec: vardecs)
    {
        vector<ast*> args;
        extractNodeList(vardec, args);
        
        auto vars = args[0];
        auto opt_type = args[1];
        auto expr = args[2];
        
        // init value
        auto exprval = GenerateExpression(expr);
        
        // type
        Type* varty = nullptr;
        if(opt_type)
            varty = typetable.FindType(opt_type->info.string);
        
        if(!varty)
        {
            //typetable.FindType("INTEGER");
            varty = exprval->getType();
        }
        
        // make declare
        vector<ast*> varlist;
        extractNodeList(vars, varlist);
        for(auto avar: varlist)
        {
            auto varname = avar->info.string;
            if(names.GetTopContext().NameExist(varname))
            {
                Error(&avar->location, "redefinition of '%s'", varname);
            }
            else
            {
                Value* varptr;
                
                if(globaldecl)
                {
                    // create global variable in data section
                    
                    // must specify the 'zeroinitializer' unless we want to
                    // introduce an external global variable.

                    auto zeroinit = GetZeroinitializer(varty);
                    varptr = new GlobalVariable(*module, varty, false, GlobalVariable::CommonLinkage, zeroinit, varname);
                }
                else
                {
                    // create local variable in stack
                    varptr = irb->CreateAlloca(varty, 0, varname);
                }
                
                // var <- [expr]
                GenerateNumericAssign(exprval, varptr, &avar->location);
                
                // store to context
                names.SetTopContextValue(varname, varptr);
            }
        }
    }
}

void IRGenContext::GenerateTypeDeclares(ast* node)
{
    vector<ast*> declares;
    extractNodeList(node, declares);
    
    for(auto declnode: declares)
    {
        vector<ast*> args;
        extractNodeList(declnode, args);
        
        // type name
        auto namenode = args[0];
        auto typebody = args[1];
        auto name_cstr = namenode->info.string;
        
        // body
        auto tag = typebody->info.node.tag;
        vector<ast*> bodyargs;
        extractNodeList(typebody, bodyargs);
        
        Type* type = nullptr;
        
        if(tag == arr_type)
        {
            // array type defination
            
            auto eletype = bodyargs[0];
            auto eleTy_cstr = eletype->info.string;
            
            auto eleTy = typetable.FindType(eleTy_cstr);
            if(!eleTy)
            {
                Error(&eletype->location, "unknown type name '%s'", eleTy_cstr);
            }
            else
            {
                // create array type
                type = eleTy->getPointerTo();
                typetable.AddType(name_cstr, type);
            }
        }
        else if(tag == rec_type)
        {
            // record type defination
            
            // get all field-declares
            
            // create struct
            bool badbody = false;
            StructDef sdef(name_cstr);
            vector<Type*> fieldsTy;
            
            // for each fields
            for(auto fdeclnode: bodyargs)
            {
                vector<ast*> fargs;
                extractNodeList(fdeclnode, fargs);
                
                auto fname_node = fargs[0];
                auto ftype_node = fargs[1];
                auto fname_cstr = fname_node->info.string;
                auto ftype_cstr = ftype_node->info.string;
                
                // find field type
                auto fieldTy = typetable.FindType(ftype_cstr);
                if(!fieldTy)
                {
                    Error(&ftype_node->location, "unknown type name '%s'", ftype_cstr);
                    badbody = true;
                    break;
                }
                else
                {
                    // append field
                    sdef.AppendMember(fname_cstr, fieldTy);
                    fieldsTy.push_back(fieldTy);
                }
            }
            
            if(!badbody)
            {
                // create sturcture type
                type = StructType::create(*ctx, fieldsTy, name_cstr);
                typetable.AddStruct(name_cstr, type, sdef);
            }
        }
        
        if(!type)
        {
            Warning(&declnode->location, "type '%s' is not created", name_cstr);
        }
    }
}

Value* IRGenContext::GenerateLvalue(ast* node)
{
    if(node->tag == var_ast)
    {
        auto lvalue = names.GetValue(node->info.string);
        if(!lvalue)
        {
            Error(&node->location, "undefined symbol '%s'", node->info.string);
        }
        return lvalue;
    }
    else
    {
        vector<ast*> args;
        extractNodeList(node, args);
        
        auto tag = node->info.node.tag;
        Value* lvalptr = nullptr;
        bool badExpr = false;
        
        if(tag == idx_exp || tag == mem_exp)
        {
            auto lvalnode = args[0];
            lvalptr = GenerateLvalue(lvalnode);
            
            if(!lvalptr->getType()->isPointerTy())
            {
                badExpr = true;
                Error(&lvalnode->location, "expect lvalue expression");
            }
        }
        
        if(tag == idx_exp)
        {
            // array index exresssion
            
            // get idx expr
            auto idxnode = args[1];
            auto idx = GenerateExpression(idxnode);
            
            if(!idx->getType()->isIntegerTy())
            {
                badExpr = true;
                Error(&idxnode->location, "expect offset (integer) expression");
            }
            
            // return offset pointer
            if(!badExpr)
            {
                auto lval = irb->CreateGEP(lvalptr, idx);
                return lval;
            }
#warning return null?
        }
        else if(tag == mem_exp)
        {
            // struct member expression
            
            // get member name
            auto memnode = args[1];
            auto mem_cstr = memnode->info.string;
            
            // verify variable (lvalue) type
            auto lvalTy = lvalptr->getType();
            if(!(lvalTy->isPointerTy() && lvalTy->getPointerElementType()->isStructTy()))
            {
                badExpr = true;
                Error(&args[0]->location, "expect struct member lvalue expression");
            }
            
            if(!badExpr)
            {
                // search struct type
                auto structName = lvalptr->getType()->getPointerElementType()->getStructName();
                auto name_cstr = structName.data();
                
                StructDef* structDef;
                typetable.FindStructure(name_cstr, &structDef);
                
                // search struct member index
                string strmem(mem_cstr);
                if(structDef->memberIndex.count(strmem) == 0)
                {
                    Error(&memnode->location, "no member named '%s' in 'record %s'",
                          mem_cstr, name_cstr);
                }
                else
                {
                    // calculate offset
                    auto memidx = structDef->memberIndex[strmem];
                    
                    auto intTy = TypeBuilder<int, false>::get(*ctx);
                    auto i0 = ConstantInt::get(intTy, 0);
                    auto validx = ConstantInt::get(intTy, memidx);
                    
                    // &obj[0] + idx
                    vector<Value*> offsets;
                    offsets.push_back(i0);
                    offsets.push_back(validx);
                    
                    // array variable is actually a pointer to the first element
                    // thus we should load the pointer from the varialbe firstly
                    auto elemPos = irb->CreateLoad(lvalptr, "elepos");
                    
                    // then calculate the offset
                    auto lval = irb->CreateGEP(elemPos, offsets);
                    return lval;
                }
            }
        }
        else
        {
            Error(&node->location, "expect idx_exp or mem_exp, but only found %s",
                  ast_names[node->info.node.tag]);
        }
    }
    
    return nullptr;
}

Value* IRGenContext::SafelyGetValue(Value* value, Type* ty, ast_loc* location)
{
    auto valueTy = value->getType();
    
    if (valueTy == ty)
        return value;
    else
    {
        Error(location, "statement requires expression of %s type ('%s' invalid)",
              TypeToName(ty).c_str(), TypeToName(valueTy).c_str());
        
        // dummy values
        if(ty->isIntegerTy())
        {
            return ConstantInt::get(ty, 0);
        }
        else if(ty->isDoubleTy())
        {
            return ConstantFP::get(ty, 0);
        }
        else if(ty->isPointerTy())
        {
            return ConstantInt::getNullValue(ty);
        }
        else
        {
            // structure or other strang things
            return nullptr;
        }
    }
}

Value* IRGenContext::SafelyGetValueAutoCast(Value* value, Type* ty, ast_loc* location)
{
    auto valueTy = value->getType();
    auto intTy = TypeBuilder<int, false>::get(*ctx);
    
    if (valueTy == ty)
        return value;
    else
    {
        if(ty->isDoubleTy() && valueTy == intTy)
        {
            return irb->CreateSIToFP(value, ty);
        }
        else
        {
            return SafelyGetValue(value, ty, location);
        }
    }
}

bool IRGenContext::GenerateStatement(ast* node)
{
    auto curblock = irb->GetInsertBlock();
    auto terminator = curblock->getTerminator();
    if(terminator)
    {
        Warning(&node->location, "unreachable code");
        return false;
    }
    
    if(!expkinds.Verify(node))
    {
        // normal expression calculation
        GenerateExpression(node);
        return true;
    }
    
    vector<ast*> args;
    extractNodeList(node, args);
    
    switch(node->info.node.tag)
    {
        case asgn_stat:
        {
            auto lval_node = args[0];
            auto expr_node = args[1];
            
            auto lval_var = GenerateLvalue(lval_node);
            auto expr_val = GenerateExpression(expr_node);
            auto lvalTy = lval_var->getType()->getPointerElementType();
            
            expr_val = SafelyGetValue(expr_val, lvalTy, &expr_node->location);
            
            if(expr_val)
            {
                // type safe
                irb->CreateStore(expr_val, lval_var);
            }

            break;
        }
        case read_stat:
        {
            vector<ast*> ionodes;
            extractNodeList(args[0], ionodes);
            for(auto lval_node: ionodes)
            {
                auto lval_var = GenerateLvalue(lval_node);
                auto lvalTy = lval_var->getType()->getPointerElementType();
                
                auto input_val = irb->CreateCall(pcatfunc.readreal);
                
                if(lvalTy->isDoubleTy())
                {
                    irb->CreateStore(input_val, lval_var);
                }
                else if(lvalTy->isIntegerTy())
                {
                    // double -> int
                    auto intTy = TypeBuilder<int, false>::get(*ctx);
                    auto input_int = irb->CreateFPToSI(input_val, intTy);
                    
                    irb->CreateStore(input_int, lval_var);
                }
                else
                {
                    Error(&lval_node->location, "statement requires expression of numeric type ('%s' invalid)",
                          TypeToName(lvalTy).c_str());
                }
            }
            
            break;
        }
        case write_stat:
        {
            vector<ast*> ionodes;
            extractNodeList(args[0], ionodes);
            
            for(auto out_node: ionodes)
            {
                if(out_node->tag == str_ast)
                {
                    // string
                    auto str = irb->CreateGlobalStringPtr(out_node->info.string);
                    irb->CreateCall(pcatfunc.writestr, str);
                }
                else
                {
                    // expr
                    auto expr_val = GenerateExpression(out_node);
                    auto exprTy = expr_val->getType();
                    
                    if(exprTy->isDoubleTy())
                    {
                        irb->CreateCall(pcatfunc.writereal, expr_val);
                    }
                    else if(exprTy->isIntegerTy())
                    {
                        irb->CreateCall(pcatfunc.writeint, expr_val);
                    }
                    else
                    {
                        Error(&out_node->location, "statement requires expression of numeric type ('%s' invalid)",
                              TypeToName(exprTy).c_str());
                    }
                }
            }
            
            auto newline = irb->CreateGlobalStringPtr("\n");
            irb->CreateCall(pcatfunc.writestr, newline);
            
            break;
        }
        case if_stat:
        {
            auto bfin = BasicBlock::Create(*ctx, "if.fin", names.GetTopContext().GetFunction());
            
            vector<ast*> iflst;
            extractNodeList(args[1], iflst);
            iflst.insert(iflst.begin(), args[0]);
            
            for(auto ifnode: iflst)
            {
                auto btrue = BasicBlock::Create(*ctx, "if.true", names.GetTopContext().GetFunction(), bfin);
                auto bfalse = BasicBlock::Create(*ctx, "if.false", names.GetTopContext().GetFunction(), bfin);
                
                vector<ast*> ifargs;
                extractNodeList(ifnode, ifargs);
                
                auto condnode = ifargs[0];
                auto statnode = ifargs[1];
                
                auto cond = GenerateExpression(condnode);
                cond = SafelyGetValue(cond, Type::getInt1Ty(*ctx), &condnode->location);
                
                irb->CreateCondBr(cond, btrue, bfalse);
                
                // true
                irb->SetInsertPoint(btrue);
                GenerateStatements(statnode);
                
                // be careful of terminated block
                if(!irb->GetInsertBlock()->getTerminator())
                    irb->CreateBr(bfin);
                
                // false
                irb->SetInsertPoint(bfalse);
            }
            
            auto elsenode = args[2];
            if(elsenode)
            {
                GenerateStatements(elsenode);
            }
            
            // be careful of terminated block
            if(!irb->GetInsertBlock()->getTerminator())
                irb->CreateBr(bfin);
            
            irb->SetInsertPoint(bfin);
            
            break;
        }
        case while_stat:
        {
            auto bbegin = BasicBlock::Create(*ctx, "while.begin", names.GetTopContext().GetFunction());
            auto bloop = BasicBlock::Create(*ctx, "while.loop", names.GetTopContext().GetFunction());
            auto bfin = BasicBlock::Create(*ctx, "while.fin", names.GetTopContext().GetFunction());
            
            // create context
            loopExitStack.push(bfin);
            irb->CreateBr(bbegin);
            
            // begin:
            irb->SetInsertPoint(bbegin);
            auto cond = GenerateExpression(args[0]);
            cond = SafelyGetValue(cond, Type::getInt1Ty(*ctx), &args[0]->location);
            if(!cond) goto while_restore;
            
            irb->CreateCondBr(cond, bloop, bfin);
            
            // loop:
            irb->SetInsertPoint(bloop);
            GenerateNode(args[1], ASTKinds(stat_node));
            
            if(!irb->GetInsertBlock()->getTerminator())
                irb->CreateBr(bbegin);
            
            // restore context
        while_restore:
            irb->SetInsertPoint(bfin);
            loopExitStack.pop();
            
            break;
        }
        case loop_stat:
        {
            auto bloop = BasicBlock::Create(*ctx, "loop.begin", names.GetTopContext().GetFunction());
            auto bfin = BasicBlock::Create(*ctx, "loop.fin", names.GetTopContext().GetFunction());
            
            // create context
            loopExitStack.push(bfin);
            irb->CreateBr(bloop);
            
            // build loop
            irb->SetInsertPoint(bloop);
            GenerateNode(args[0], ASTKinds(stat_node));
            
            if(!irb->GetInsertBlock()->getTerminator())
                irb->CreateBr(bloop);
            
            // restore context
            irb->SetInsertPoint(bfin);
            loopExitStack.pop();
            
            break;
        }
        case for_stat:
        {
            auto idx_node = args[0];
            auto frm_node = args[1];
            auto end_node = args[2];
            auto stp_node = args[3];
            auto stm_node = args[4];
            auto intTy = TypeBuilder<int, false>::get(*ctx);
            
            auto bbegin = BasicBlock::Create(*ctx, "for.begin", names.GetTopContext().GetFunction());
            auto bcondi = BasicBlock::Create(*ctx, "for.cond.inc", names.GetTopContext().GetFunction());
            auto bcondd = BasicBlock::Create(*ctx, "for.cond.dec", names.GetTopContext().GetFunction());
            auto bloop = BasicBlock::Create(*ctx, "for.loop", names.GetTopContext().GetFunction());
            auto bfin = BasicBlock::Create(*ctx, "for.fin", names.GetTopContext().GetFunction());

            Value *end_val, *idx_val, *condit1, *condit2, *conditn, *step_val, *idx_new, *condinc;
            
            // create context
            loopExitStack.push(bfin);
            
            // prepare:
            auto idx_var = GenerateLvalue(idx_node);
            auto frm_val = GenerateExpression(frm_node);
            
            idx_var = SafelyGetValue(idx_var, intTy->getPointerTo(), &idx_node->location);
            frm_val = SafelyGetValue(frm_val, intTy, &frm_node->location);
            if(!idx_var || !frm_val) goto for_restore;
            
            irb->CreateStore(frm_val, idx_var);
            irb->CreateBr(bbegin);
            
            // begin:
            irb->SetInsertPoint(bbegin);
            end_val = GenerateExpression(end_node);
            end_val = SafelyGetValue(end_val, intTy, &end_node->location);
            if(!end_val) goto for_restore;
            
            idx_val = irb->CreateLoad(idx_var, "idx");
            condinc = irb->CreateICmpSLE(frm_val, end_val);
            irb->CreateCondBr(condinc, bcondi, bcondd);
            
            // cond.inc: (begin < end)
            irb->SetInsertPoint(bcondi);
            condit1 = irb->CreateICmpSLE(idx_val, end_val);
            condit2 = irb->CreateICmpSLE(frm_val, idx_val);
            conditn = irb->CreateAnd(condit1, condit2);
            irb->CreateCondBr(conditn, bloop, bfin);
            
            // cond.dec: (begin > end)
            irb->SetInsertPoint(bcondd);
            condit1 = irb->CreateICmpSGE(idx_val, end_val);
            condit2 = irb->CreateICmpSGE(frm_val, idx_val);
            conditn = irb->CreateAnd(condit1, condit2);
            irb->CreateCondBr(conditn, bloop, bfin);
            
            // loop:
            irb->SetInsertPoint(bloop);
            GenerateNode(stm_node, ASTKinds(stat_node));
            
            // tail:
            // generate index step
            step_val = ConstantInt::get(intTy, 1);;
            if(stp_node)
            {
                step_val = GenerateExpression(stp_node);
                step_val = SafelyGetValue(step_val, intTy, &stp_node->location);
                if(!step_val) goto for_restore;
            }
            // idx <- idx + step
            idx_new = irb->CreateAdd(idx_val, step_val);
            irb->CreateStore(idx_new, idx_var);
            irb->CreateBr(bbegin);
            
            // restore context
        for_restore:
            irb->SetInsertPoint(bfin);
            loopExitStack.pop();
            break;
        }
        case exit_stat:
        {
            if(loopExitStack.empty())
            {
                Error(&node->location, "'exit' statement not in loop statement");
            }
            else
            {
                // In PCAT it's not possible to jump out of several variable context
                // since all the variable declarations are before the statements. In
                // other words, there's no new variable between scopes. Thus we can
                // jump to the exit directly.
                irb->CreateBr(loopExitStack.top());
            }
            break;
        }
        case retn_stat:
        {
            auto rtv_node = args[0];
            if(rtv_node)
            {
                auto rtv_val = GenerateExpression(rtv_node);
                irb->CreateRet(rtv_val);
            }
            else
            {
#warning check return type
                irb->CreateRetVoid();
            }
            
            break;
        }
        default: break;
    }
    
    return true;
}

/// \brief Create IR for array of statements (stat_node)
void IRGenContext::GenerateStatements(ast* node)
{
    vector<ast*> statlst;
    extractNodeList(node, statlst);
    
    //print_ast(node); <- for debug
    
    for(auto statnode: statlst)
    {
        bool reachable = GenerateStatement(statnode);
        if(!reachable) break;
    }
}

void IRGenContext::GenerateProcedure(ast* node, bool globaldecl)
{
    // backup the block
    auto origBlock = irb->GetInsertBlock();
    
    vector<ast*> nodes;
    extractNodeList(node, nodes);
    
    auto name_node = nodes[0];
    auto parm_node = nodes[1];
    auto type_node = nodes[2];
    auto body_node = nodes[3];
    
    auto name_cstr = name_node->info.string;
    
    vector<ast*> args; // formal_params = formal_section[]
    extractNodeList(parm_node, args);
    
    vector<Type*> argTyTable;  // arg tables for build function
    vector<const char*> argNmTable;
    
    // enum args
    for(auto arg_node: args)
    {
        vector<ast*> items;
        extractNodeList(arg_node, items);
        
        auto id_nodes = items[0];
        auto ty_node = items[1];
        auto ty_cstr = ty_node->info.string;
        auto type = typetable.FindType(ty_cstr);
        
        if(!type)
        {
            Error(&ty_node->location, "unknown type name '%s'", ty_cstr);
        }
        else
        {
            vector<ast*> id_list;
            extractNodeList(id_nodes, id_list);
            
            for(auto id_node: id_list)
            {
                auto id_cstr = id_node->info.string;
                argTyTable.push_back(type);
                argNmTable.push_back(id_cstr);
            }
        }
    }

    // get return type
    Type* retTy = Type::getVoidTy(*ctx);
    if(type_node)
    {
        auto type_cstr = type_node->info.string;
        auto returnTy = typetable.FindType(type_cstr);
        
        if(!returnTy)
            Error(&type_node->location, "unknown type name '%s'", type_cstr);
        else
            retTy = returnTy;
    }
    
    // build function
    auto funcTy = FunctionType::get(retTy, argTyTable, false);
    auto func = Function::Create(funcTy, Function::ExternalLinkage, name_cstr, module);
    auto funcBlock = BasicBlock::Create(*ctx, "func_entry", func);
    
    // register the function itself (in outer context)
    names.GetTopContext().SetValue(name_cstr, func);
    
    // create context
    NameTable& curctx = names.PushContext();
    curctx.SetContextName(name_cstr);
    curctx.SetFunction(func);
    curctx.SetFuncBlock(funcBlock);
    
    
    // store all arguments
    irb->SetInsertPoint(funcBlock);
    auto arg_it = func->arg_begin();
    for(int i=0; i<argNmTable.size(); i++)
    {
        auto argnm_cstr = argNmTable[i];
        auto arg_val = arg_it++;
        auto argTy = arg_val->getType();
        
        // alloc local variable in stack or global
        Value* arg_var;
        if(globaldecl)
        {
            auto zeroinit = GetZeroinitializer(argTy);
            arg_var = new GlobalVariable(*module, argTy, false, GlobalVariable::CommonLinkage, zeroinit, argnm_cstr);
        }
        else
        {
            arg_var = irb->CreateAlloca(argTy);
        }
        
        // var <- [val]
        irb->CreateStore(arg_val, arg_var);
        
        // declare local variable
        arg_val->setName(argnm_cstr);
        curctx.SetValue(argnm_cstr, arg_var);
    }
    
    GenerateBody(body_node);
    
    if(retTy->isVoidTy())
        irb->CreateRetVoid();
    else
        irb->CreateRet(GetZeroinitializer(retTy));
    
    // resotre context
    names.PopContext();
    
    //verifyFunction(*func);
    // func->dump();
    
    // resotre the block
    irb->SetInsertPoint(origBlock);
}

void IRGenContext::GenerateProcedures(ast* node, bool globaldecl)
{
    vector<ast*> proclst;
    extractNodeList(node, proclst);
    
    for(auto procnode: proclst)
    {
        GenerateProcedure(procnode, globaldecl);
    }
}

void IRGenContext::GenerateProgram(ast* root)
{
    // create main function
    auto intTy = TypeBuilder<int, false>::get(*ctx);
    auto mainTy = FunctionType::get(intTy, false);
    
    auto mainFunc = Function::Create(mainTy, Function::ExternalLinkage, "main", module);
    auto mainBlock = BasicBlock::Create(*ctx, "main_entry", mainFunc);
    
    // create & push context
    NameTable& mainCtx = names.GetGlobalContext();
    mainCtx.SetFunction(mainFunc);
    mainCtx.SetFuncBlock(mainBlock);
    
    // set insert point
    irb->SetInsertPoint(mainBlock);
    
    // begin generate ir (no args needed for generating function)
    GenerateBody(root, true);
    
    // generate 'return 0'
    
    if(!irb->GetInsertBlock()->getTerminator())
    {
        Warning(&root->location, "control reaches end of non-void function (main)");
        
        auto i0 = ConstantInt::get(intTy, 0);
        irb->CreateRet(i0);
    }

    // verify function (for debug)
    verifyFunction(*mainFunc);
}

Value* IRGenContext::GenerateNode(ast* node, ASTKinds expectkinds, bool globaldecl)
{
    if(forceStop) return nullptr;
    
    // preprocess

    const char* expects = expectkinds.GetNames();
    if(node->tag != node_ast)
    {
        // not a node
        Error(&node->location, "expects %s.", expects);
        return nullptr;
    }
    
    expects = expectkinds.Verify(node);
    if(expects)
    {
        // not expected node
        Error(&node->location, "expects %s, but found %s.",
              expects, ast_names[node->info.node.tag]);
    }
    
    // generate ir
    
    Value* resultValue = nullptr;
    switch(node->info.node.tag)
    {
        case body_node: GenerateBody(node); break;
        case var_decls: GenerateVarDeclares(node, globaldecl); break;
        case type_decls: GenerateTypeDeclares(node); break;
        case stat_node: GenerateStatements(node); break;
        case proc_decls: GenerateProcedures(node); break;
    }
    
    return resultValue;
}

// fin
Value* IRGenContext::GenerateExpression(ast* node)
{
#warning for an error expression, we should generate a dummy value, rather than return nullptr
    
    Value* result = nullptr;
    
    switch (node->tag)
    {
        case int_ast:
        {
            // integer constant
            auto intTy = TypeBuilder<int, false>::get(*ctx);
            result = ConstantInt::get(intTy, node->info.integer);
            break;
        }
        case real_ast:
        {
            // real constant
            auto realTy = TypeBuilder<double, false>::get(*ctx);
            result = ConstantFP::get(realTy, node->info.real);
            break;
        }
        case var_ast:
        {
            // variable id
            auto varname = node->info.string;
            auto varptr = names.GetValue(varname);
            
            if(!varptr)
            {
                Error(&node->location, "use of undeclared identifier '%s'", varname);
            }
            else
            {
                result = irb->CreateLoad(varptr, "var");
            }
            break;
        }
        case node_ast:
        {
            // for node expression
            
            // verify expression kinds
            auto expects = expkinds.Verify(node);
            if(expects)
            {
                Error(&node->location, "expect %s, but found %s",
                      expects, ast_names[node->info.node.tag]);
                break;
            }
            
            // extarct operands
            vector<ast*> ops;
            extractNodeList(node, ops);
            
            auto nodetag = node->info.node.tag;
            
            if(nodetag == fcall_exp)
            {
                // function call
                auto funcId = ops[0];                
                auto funcObj = names.GetValue(funcId->info.string);
                
                if(!funcObj)
                {
                    Error(&funcId->location, "undefined procedure '%s'", funcId->info.string);
                }
                else
                {
                    auto funcPtrTy = funcObj->getType();
                    
                    if(!(funcPtrTy->isPointerTy() && funcPtrTy->getPointerElementType()->isFunctionTy()))
                    {
                        auto funcTy = funcObj->getType()->getPointerElementType();
                        bool isfunc = funcTy->isFunctionTy();
                        cout << isfunc << endl;
                        Error(&funcId->location, "called object type '%s' is not a function",
                              TypeToName(funcPtrTy).c_str());
                    }
                    else
                    {
                        auto funcTy = funcPtrTy->getPointerElementType();
                        
                        vector<ast*> arglist;
                        vector<Value*> argValues;
                        
                        extractNodeList(ops[1], arglist);
                        
                        if(arglist.size() != funcTy->getFunctionNumParams())
                        {
                            int expected = (int)arglist.size();
                            int have = funcTy->getFunctionNumParams();
                            Error(&node->location, "too %s arguments to procedure call, expected %d, have %d",
                                  (have < expected) ? "few" : "many", expected, have);
                        }
                        else
                        {
                            // valid argument count
                            int i = 0;
                            for(auto arg: arglist)
                            {
                                auto fargty = funcTy->getFunctionParamType(i++);
                                auto argval = GenerateExpression(arg);
                                argValues.push_back(argval);
                                
                                // auto casting if nessesary
                                argval = SafelyGetValueAutoCast(argval, fargty, &arg->location);
                            }
                            
                            result = irb->CreateCall(funcObj, argValues);
                        }
                    }
                }
            }
            else if(nodetag == finit_exp)
            {
                // field init
                
                auto tyname = ops[0];
                auto tyname_cstr = tyname->info.string;
                
                // find struct type
                StructDef* structDef;
                auto structTy = typetable.FindStructure(tyname_cstr, &structDef);
                if(!structTy)
                {
                    Error(&tyname->location, "unknown type '%d'", tyname_cstr);
                }
                else
                {
                    // alloc struct in stack
                    auto structPtr = irb->CreateAlloca(structTy, 0, "rec");
                    
                    // do assignments
                    auto finit_exprs = ops[1];
                    
                    vector<ast*> fasglist;
                    extractNodeList(finit_exprs, fasglist);
                    
                    for(auto fasgnode: fasglist)
                    {
                        vector<ast*> args;
                        extractNodeList(fasgnode, args);
                        
                        auto memnode = args[0];
                        auto expnode = args[1];
                        auto mem_cstr = memnode->info.string;
                        auto exprval = GenerateExpression(expnode);
                        
                        // find member idx
                        string strmem(mem_cstr);
                        if(structDef->memberIndex.count(strmem) == 0)
                        {
                            Error(&memnode->location, "no member named '%s' in 'record %s'",
                                 mem_cstr, mem_cstr);
                        }
                        else
                        {
                            // member index
                            auto memidx = structDef->memberIndex[strmem];
                            
                            // perpare for GEP
                            auto intTy = TypeBuilder<int, false>::get(*ctx);
                            auto i0 = ConstantInt::get(intTy, 0);
                            auto validx = ConstantInt::get(intTy, memidx);
                            
                            // GEP @struct ptr, i64 0, i64 idx
                            vector<Value*> idxlst;
                            idxlst.push_back(i0);
                            idxlst.push_back(validx);
                            auto memptr = irb->CreateGEP(structPtr, idxlst);
                            
                            // do assign
                            irb->CreateStore(exprval, memptr);
                        }
                    }
                    
                    auto structValue = irb->CreateLoad(structPtr, "objval");
                    result = structValue;
                }
            }
            else if(nodetag == ainit_exp)
            {
                // array init
                auto tyname = ops[0];
                auto arrayexpr = ops[1];
                
                auto tyname_cstr = tyname->info.string;
                auto elemTy = typetable.FindType(tyname_cstr);
                if(!elemTy)
                {
                    Error(&tyname->location, "unknown type name '%s'", tyname_cstr);
                }
                else
                {
                    // dynamic create array (on stack)
                    
                    vector<Value*> values;
                    vector<Value*> valuerep;
                    vector<ast*> arrvals;
                    extractNodeList(arrayexpr, arrvals);
                    
                    auto intTy = TypeBuilder<int, false>::get(*ctx);
                    Value* arraysz = ConstantInt::get(intTy, 0);
                    
                    for(auto aval: arrvals)
                    {
                        // calc repetition count & value
                        Value* valcnt = ConstantInt::get(intTy, 1);
                        Value* val = nullptr;
                        
                        vector<ast*> aval_arg;
                        extractNodeList(aval, aval_arg);
                        if(aval_arg.size() == 2)
                        {
                            // { [n of] x, }
                            auto expcnt = GenerateExpression(aval_arg[0]);
                            if(expcnt) valcnt = expcnt;
                            val = GenerateExpression(aval_arg[1]);
                        }
                        else
                        {
                            // { x, }
                            val = GenerateExpression(aval_arg[0]);
                        }
                        
                        // sum up the element count
                        arraysz = irb->CreateAdd(arraysz, valcnt);
                        
                        // store
                        values.push_back(val);
                        valuerep.push_back(valcnt);
                    }
                    
                    // create array with size 'arraysz'
                    auto var_arr = irb->CreateAlloca(elemTy, arraysz, "array");
                    auto var_idx = irb->CreateAlloca(intTy, 0, "var_idx");
                    auto var_j = irb->CreateAlloca(intTy, 0, "var_j");
                    
                    // load values
                    
                    // i = 0
                    auto i0 = ConstantInt::get(intTy, 0);
                    auto i1 = ConstantInt::get(intTy, 1);
                    irb->CreateStore(i0, var_idx);
                    
                    for(int i=0; i<values.size(); i++)
                    {
                        
                        auto b_cond = BasicBlock::Create(*ctx, "b_ainit_cond", names.GetTopContext().GetFunction());
                        auto b_loop = BasicBlock::Create(*ctx, "b_ainit_loop", names.GetTopContext().GetFunction());
                        auto b_fin = BasicBlock::Create(*ctx, "b_ainit_fin", names.GetTopContext().GetFunction());
                        
                        // j = 0
                        irb->CreateStore(i0, var_j);
                        irb->CreateBr(b_cond);
                        
                        // while(j < valuerep[i])
                        // {
                        irb->SetInsertPoint(b_cond);
                        auto val_j = irb->CreateLoad(var_j, "val_j");
                        auto cond = irb->CreateICmpSLT(val_j, valuerep[i]);
                        irb->CreateCondBr(cond, b_loop, b_fin);
                        
                        //     arr[idx] = values[i]
                        irb->SetInsertPoint(b_loop);
                        auto val_idx = irb->CreateLoad(var_idx, "idx");
                        auto curpos = irb->CreateGEP(var_arr, val_idx);
                        irb->CreateStore(values[i], curpos);
                        
                        //     idx++, j++
                        auto new_idx = irb->CreateAdd(val_idx, i1);
                        auto new_j = irb->CreateAdd(val_j, i1);
                        irb->CreateStore(new_idx, var_idx);
                        irb->CreateStore(new_j, var_j);
                        irb->CreateBr(b_cond);
                        
                        // }
                        irb->SetInsertPoint(b_fin);
                    }
                    
                    // return the pointer to the elements
                    result = var_arr;
                }
            }
            else if(nodetag == idx_exp || nodetag == mem_exp)
            {
                // get value from lvalue
                
                auto valptr = GenerateLvalue(node);
                auto val = irb->CreateLoad(valptr, "val");
                result = val;
            }
            else
            {
                // arithmetic expression
                
                Value* x = nullptr;
                Value* y = nullptr;
                Type* xTy = nullptr;
                Type* yTy = nullptr;
                bool valueType = false;
                bool booleanType = false;
                bool integerType = false;
                auto doubleTy = TypeBuilder<double, false>::get(*ctx);
                
                // preprocess the operands
                
                if(ops.size() >= 1)
                {
                    // first operand
                    x = GenerateExpression(ops[0]);
                    xTy = x->getType();
                    
                    valueType = (xTy->isDoubleTy() || xTy->isIntegerTy());
                    integerType = xTy->isIntegerTy();
                    booleanType = integerType && (xTy->getIntegerBitWidth() == 1);
                }
                if(ops.size() >= 2)
                {
                    // second operand
                    y = GenerateExpression(ops[1]);
                    yTy = y->getType();
                    
                    valueType = valueType && (yTy->isDoubleTy() || yTy->isIntegerTy());
                    integerType = integerType && yTy->isIntegerTy();
                    booleanType = booleanType && integerType && (yTy->getIntegerBitWidth() == 1);
                    
                    if(!integerType)
                    {
                        // if result is real type, cast operands from integer to real
                        if(xTy->isIntegerTy()) x = irb->CreateSIToFP(x, doubleTy);
                        if(yTy->isIntegerTy()) y = irb->CreateSIToFP(y, doubleTy);
                    }
                }
                
                // error type (placeholder?)
                if(!valueType) break;
                
#define TypeName(ty) ((ty)->isIntegerTy() ? (((ty)->getIntegerBitWidth() == 1)? "boolean" : "integer" ) : "real")
#define InvalidOpUnary(node, xTy) Error(&((node)->location), "invalid operands to unary expression (%s)", TypeName(xTy))
#define InvalidOpBinary(node, xTy, yTy) Error(&((node)->location), "invalid operands to binary expression (%s, %s)", TypeName(xTy), TypeName(yTy))
                
                switch (node->info.node.tag)
                {
                    // unary operator
                    // pos_exp, neg_exp, not_exp,
                    case pos_exp:
                    {
                        result = x;
                        break;
                    }
                    case neg_exp:
                    {
                        if(booleanType) InvalidOpUnary(node, xTy);
                        else if(integerType) result = irb->CreateNeg(x, "tmpneg");
                        else result = irb->CreateFNeg(x, "tmpfneg");
                        break;
                    }
                    case not_exp:
                    {
                        if(booleanType) InvalidOpUnary(node, xTy);
                        else if(integerType) result = irb->CreateNot(x, "tmpnot");
                        else InvalidOpUnary(node, xTy);
                        break;
                    }
                    // binary operator
                    // plus_exp, minus_exp, times_exp, fdiv_exp, div_exp, mod_exp,
                    case plus_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateAdd(x, y, "tmpadd");
                        else result = irb->CreateFAdd(x, y, "tmpfadd");
                        break;
                    }
                    case minus_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateSub(x, y, "tmpsub");
                        else result = irb->CreateFSub(x, y, "tmpsub");
                        break;
                    }
                    case times_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateMul(x, y, "tmpmul");
                        else result = irb->CreateFMul(x, y, "tmpmul");
                        break;
                    }
                    case fdiv_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) InvalidOpBinary(node, xTy, yTy);
                        else result = irb->CreateFDiv(x, y, "tmpfdiv");
                        break;
                    }
                    case div_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateSDiv(x, y, "tmpdiv");
                        else InvalidOpBinary(node, xTy, yTy);
                        break;
                    }
                    case mod_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateSRem(x, y, "tmpmod");
                        else InvalidOpBinary(node, xTy, yTy);
                        break;
                    }
                    // condition operator
                    // or_exp, and_exp, gt_exp, lt_exp, eq_exp, ge_exp, le_exp, neq_exp,
                    case or_exp:
                    {
                        if(booleanType) result = irb->CreateOr(x, y, "tmpor");
                        else InvalidOpBinary(node, xTy, yTy);
                        break;
                    }
                    case and_exp:
                    {
                        if(booleanType) result = irb->CreateAnd(x, y, "tmpand");
                        else  InvalidOpBinary(node, xTy, yTy);
                        break;
                    }
                    case gt_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateICmpSGT(x, y, "tmpgt");
                        else result = irb->CreateFCmpOEQ(x, y, "tmpgt");
                        break;
                    }
                    case lt_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateICmpSLT(x, y, "tmplt");
                        else result = irb->CreateFCmpOLT(x, y, "tmplt");
                        break;
                    }
                    case eq_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateICmpEQ(x, y, "tmpeq");
                        else result = irb->CreateFCmpOEQ(x, y, "tmpeq");
                        break;
                    }
                    case ge_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateICmpSGE(x, y, "tmpge");
                        else result = irb->CreateFCmpOGE(x, y, "tmpge");
                        break;
                    }
                    case le_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateICmpSLE(x, y, "tmple");
                        else result = irb->CreateFCmpOLE(x, y, "tmple");
                        break;
                    }
                    case neq_exp:
                    {
                        if(booleanType) InvalidOpBinary(node, xTy, yTy);
                        else if(integerType) result = irb->CreateICmpNE(x, y, "tmpneq");
                        else result = irb->CreateFCmpONE(x, y, "tmpneq");
                        break;
                    }
                    default: break;
                }
            }
            break;
        }
        default: break;
    }
    
    return result;
}


void GenerateIR(ast* root, llvm::LLVMContext& ctx, llvm::IRBuilder<>& builder, llvm::Module* module)
{
    auto irgen = IRGenContext(ctx);
    irgen.ctx = &ctx;
    irgen.irb = &builder;
    irgen.module = module;
    
    irgen.RegisterLibc();
    irgen.CreateInternal_readreal();
    irgen.CreateInternal_writereal();
    irgen.CreateInternal_writeint();
    irgen.CreateInternal_writestr();
    // irgen.CreateInternal_memncpy(); -- not used
    
    irgen.GenerateProgram(root);
}