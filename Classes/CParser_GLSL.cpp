//
//  CParser_GLSL.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CParser_GLSL.h"

CParser_GLSL::CParser_GLSL(void)
{
    
}

CParser_GLSL::~CParser_GLSL(void)
{
    
}

SGLSLData CParser_GLSL::Load(const char *_vertexShaderSource, const char *_fragmentShaderSource)
{
    SGLSLData data;
    data.m_vertexShaderHandle = Build(_vertexShaderSource, GL_VERTEX_SHADER);
    data.m_fragmentShaderHandle = Build(_fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    data.m_linkedShaderHandle = glCreateProgram();
    glAttachShader(data.m_linkedShaderHandle, data.m_vertexShaderHandle);
    glAttachShader(data.m_linkedShaderHandle, data.m_fragmentShaderHandle);
    glLinkProgram(data.m_linkedShaderHandle);
    
    i32 success;
    glGetProgramiv(data.m_linkedShaderHandle, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) 
    {
        GLchar messages[256];
        glGetProgramInfoLog(data.m_linkedShaderHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
    }
    return data;
}

GLuint CParser_GLSL::Build(const char *_source, GLenum _shader)
{
    ui32 handle = glCreateShader(_shader);
    glShaderSource(handle, 1, &_source, 0);
    glCompileShader(handle);
    
    i32 success;
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