//
//  CTexture.h
//  iGaia
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CTexture_h
#define iGaia_CTexture_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "PVRTTexture.h"
#include "IResource.h"

class CTexture : public IResource
{   
public:
    enum E_WRAP_MODE { E_WRAP_MODE_REPEAT = 0, E_WRAP_MODE_CLAMP };
protected:
    GLuint m_iHandle;
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    E_WRAP_MODE m_eWrapMode;
public:
    CTexture(void);
    virtual ~CTexture(void);
    inline GLuint Get_Handle(void) { return m_iHandle; }
    void Set_Handle(GLuint _iHandle);
    inline unsigned int Get_Width(void) { return m_iWidth; }
    inline unsigned int Get_Height(void) { return m_iHeight; }
    inline void Set_Width(unsigned int _iWidth) { m_iWidth = _iWidth; }
    inline void Set_Height(unsigned int _iHeight) { m_iHeight = _iHeight; }
    void Set_WrapMode(E_WRAP_MODE _eWrapMode);
};

#endif
