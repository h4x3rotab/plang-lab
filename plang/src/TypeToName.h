//
//  TypeToName.h
//  llvmfrontend
//
//  Created by h4x on 14-6-16.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#ifndef __llvmfrontend__TypeToName__
#define __llvmfrontend__TypeToName__

#include <iostream>
#include <string>

namespace llvm
{
    class Type;
}

std::string TypeToName(llvm::Type* type);

#endif /* defined(__llvmfrontend__TypeToName__) */
