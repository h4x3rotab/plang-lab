//
//  TypeTable.h
//  llvmfrontend
//
//  Created by h4x on 14-6-15.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#ifndef __llvmfrontend__TypeTable__
#define __llvmfrontend__TypeTable__

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace llvm
{
    class Type;
    class LLVMContext;
}

/// \brief Defination of a structure (record) including names and types
struct StructDef
{
    std::string structName;
    std::vector<llvm::Type*> memberTypes;
    std::map<std::string, int> memberIndex;
    
    StructDef() {}
    StructDef(const char* name) : structName(name) {}
    void AppendMember(const char* name, llvm::Type* type);
    void Clean();
};

/// \brief The table of types in PCAT
class TypeTable
{
    std::map<std::string, llvm::Type*> types;
    std::map<std::string, StructDef*> structs;

public:
    TypeTable(llvm::LLVMContext& ctx);
    
    /// \brief To add normal types or array
    void AddType(const char* name, llvm::Type* type);
    
    /// \brief To add user defined structures
    void AddStruct(const char* name, llvm::Type* type, StructDef& structDef);
    
    llvm::Type* FindType(const char* name);
    llvm::Type* FindStructure(const char* name, StructDef** outDef);
    
    virtual ~TypeTable();
};


#endif /* defined(__llvmfrontend__TypeTable__) */
