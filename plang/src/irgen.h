//
//  irgen.h
//  llvmfrontend
//
//  Created by h4x on 14-6-14.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#ifndef __llvmfrontend__irgen__
#define __llvmfrontend__irgen__

#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

struct ast;
void GenerateIR(ast* root, llvm::LLVMContext& ctx, llvm::IRBuilder<>& builder, llvm::Module* module);

#endif /* defined(__llvmfrontend__irgen__) */
