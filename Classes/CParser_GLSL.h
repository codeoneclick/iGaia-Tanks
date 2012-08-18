//
//  CParser_GLSL.h
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CParser_GLSL_h
#define iGaia_CParser_GLSL_h

#ifdef OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif EMULATION_GL
#include <GL/glew.h>
#ifndef GL_GLEXT_PROTOTYPES
#       define GL_GLEXT_PROTOTYPES 1
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
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
