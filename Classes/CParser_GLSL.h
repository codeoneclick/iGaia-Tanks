//
//  CParser_GLSL.h
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CParser_GLSL_h
#define iGaia_CParser_GLSL_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "stdlib.h"
#include <string>

class CParser_GLSL
{
public:
    struct SGLSLData
    {
        GLuint s_pHandle;
        GLuint s_vHandle;
        GLuint s_fHandle;
    };
private:
    GLuint Build(const char* _pSource, GLenum _eShader);
public:
    CParser_GLSL();
    ~CParser_GLSL();
    SGLSLData Load(const char *_vSource, const char*_fSource);
};

#endif
