//
//  CParser_GLSL.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_GLSL.h"

CParser_GLSL::CParser_GLSL()
{
    
}

CParser_GLSL::~CParser_GLSL()
{
    
}

CParser_GLSL::SGLSLData CParser_GLSL::Load(const char *_vSource, const char *_fSource)
{
    SGLSLData data;
    data.s_vHandle = Build(_vSource, GL_VERTEX_SHADER);
    data.s_fHandle = Build(_fSource, GL_FRAGMENT_SHADER);
    
    data.s_pHandle = glCreateProgram();
    glAttachShader(data.s_pHandle, data.s_vHandle);
    glAttachShader(data.s_pHandle, data.s_fHandle);
    glLinkProgram(data.s_pHandle);
    
    GLint success;
    glGetProgramiv(data.s_pHandle, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) 
    {
        GLchar messages[256];
        glGetProgramInfoLog(data.s_pHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
    }
    return data;
}

GLuint CParser_GLSL::Build(const char *_pSource, GLenum _eShader) 
{
    GLuint handle = glCreateShader(_eShader);
    glShaderSource(handle, 1, &_pSource, 0);
    glCompileShader(handle);
    
    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    
    if (success == GL_FALSE) 
    {
        GLchar messages[256];
        glGetShaderInfoLog(handle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        handle = 0;
    }
    return handle;
}