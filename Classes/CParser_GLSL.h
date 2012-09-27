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

#include "CShader.h"

class CParser_GLSL
{
private:
    unsigned int Compile(const char* _dataSource, GLenum _shader);
public:
    CParser_GLSL(void);
    ~CParser_GLSL(void);
    CShader* Load(const char* _dataSourceVertexShader, const char* _dataSourceFragmentShader);
};

#endif
