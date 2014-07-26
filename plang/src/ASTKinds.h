//
//  ASTKinds.h
//  llvmfrontend
//
//  Created by h4x on 14-6-15.
//  Copyright (c) 2014年 h4x. All rights reserved.
//

#ifndef __llvmfrontend__ASTKinds__
#define __llvmfrontend__ASTKinds__

#include <iostream>
#include <vector>
#include "ast.h"

using namespace std;

struct ASTKinds
{
    vector<ast_kind> kinds;
    
    ASTKinds() { }
    ASTKinds(ast_kind k1)
    {
        kinds.push_back(k1);
    }
    ASTKinds(ast_kind k1, ast_kind k2)
    {
        kinds.push_back(k1);
        kinds.push_back(k2);
    }
    ASTKinds(ast_kind k1, ast_kind k2, ast_kind k3)
    {
        kinds.push_back(k1);
        kinds.push_back(k2);
        kinds.push_back(k3);
    }
    ASTKinds(ast_kind k1, ast_kind k2, ast_kind k3, ast_kind k4)
    {
        kinds.push_back(k1);
        kinds.push_back(k2);
        kinds.push_back(k3);
        kinds.push_back(k4);
    }
    ASTKinds(int n, const ast_kind kk[])
    {
        for(int i=0; i<n ; i++)
        {
            kinds.push_back(kk[i]);
        }
    }
    
    const char* GetNames()
    {
        static char tmpbuff[255];
        string expect;
        for(int i=0; i<kinds.size(); i++)
        {
            expect += ast_names[kinds[i]];
            if(i > 0 && i == kinds.size() - 1)
                expect += ", or ";
            else
                expect += ", ";
        }
        
        sprintf(tmpbuff, "%s", expect.c_str());
        return tmpbuff;
        
    }
    
    const char* Verify(ast* node)
    {
        
        if(kinds.size() == 0)
            return nullptr;
        
        for(int i=0; i<kinds.size(); i++)
            if(node->info.node.tag == kinds[i])
                return nullptr;
        
        return GetNames();
    }
};


#endif /* defined(__llvmfrontend__ASTKinds__) */
