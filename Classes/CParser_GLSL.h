//
//  CParser_GLSL.h
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CParser_GLSL_h
#define CParser_GLSL_h

#include "HCommon.h"

struct SGLSLData
{
    ui32 m_linkedShaderHandle;
    ui32 m_vertexShaderHandle;
    ui32 m_fragmentShaderHandle;
};

class CParser_GLSL
{
private:
    
protected:
    
    ui32 Build(const char* _source, GLenum _shader);
    
public:
    
    CParser_GLSL(void);
    ~CParser_GLSL(void);
    
    SGLSLData Load(const char *_vertexShaderSource, const char*_fragmentShaderSource);
};

#endif
