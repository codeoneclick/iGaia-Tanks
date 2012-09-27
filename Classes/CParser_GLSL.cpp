//
//  CParser_GLSL.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_GLSL.h"

CParser_GLSL::CParser_GLSL(void)
{
    
}

CParser_GLSL::~CParser_GLSL(void)
{
    
}

CShader* CParser_GLSL::Load(const char* _dataSourceVertexShader, const char* _dataSourceFragmentShader)
{
    unsigned int handleVertexShader = Compile(_dataSourceVertexShader, GL_VERTEX_SHADER);
    unsigned int handleFragmentShader = Compile(_dataSourceFragmentShader, GL_FRAGMENT_SHADER);
    
    unsigned int handle = glCreateProgram();
    glAttachShader(handle, handleVertexShader);
    glAttachShader(handle, handleFragmentShader);
    glLinkProgram(handle);
    
    int success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) 
    {
        char message[256];
        glGetProgramInfoLog(handle, sizeof(message), 0, &message[0]);
        std::cout<<message;
    }
    
    CShader* shader = new CShader(handle);
    return shader;
}

unsigned int CParser_GLSL::Compile(const char *_dataSource, GLenum _shader)
{
    unsigned int handle = glCreateShader(_shader);
    glShaderSource(handle, 1, &_dataSource, 0);
    glCompileShader(handle);
    
    int success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) 
    {
        GLchar message[256];
        glGetShaderInfoLog(handle, sizeof(message), 0, &message[0]);
        std::cout<<message;
        handle = 0;
    }
    return handle;
}