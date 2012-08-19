//
//  CTexture.h
//  iGaia
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CTexture_h
#define iGaia_CTexture_h

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
#include <PVRTTexture.h>
#include "IResource.h"

class CTexture : public IResource
{   
public:
    struct SSourceData
    {
        GLuint m_hTextureHanlde;
        int m_iWidth;
        int m_iHeight;
    };
    enum E_WRAP_MODE { E_WRAP_MODE_REPEAT = 0, E_WRAP_MODE_CLAMP };
protected:
    SSourceData* m_pSourceData;
public:
    CTexture(void);
    virtual ~CTexture(void);
    inline GLuint Get_Handle(void) { return m_pSourceData->m_hTextureHanlde; }
    inline unsigned int Get_Width(void) { return m_pSourceData->m_iWidth; }
    inline unsigned int Get_Height(void) { return m_pSourceData->m_iHeight; }
    virtual void Set_SourceData(void* _pSourceData);
};

#endif
