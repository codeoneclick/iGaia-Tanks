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
    enum E_WRAP_MODE
    {
        E_WRAP_MODE_REPEAT = 0,
        E_WRAP_MODE_CLAMP
    };
protected:
    unsigned int m_handle;
    unsigned int m_width;
    unsigned int m_height;
public:
    CTexture(unsigned int _handle, unsigned int _width, unsigned int _height);
    ~CTexture(void);
    inline unsigned int Get_Handle(void)
    {
        return m_handle;
    }
    
    inline unsigned int Get_Width(void)
    {
        return m_width;
    }
    inline unsigned int Get_Height(void)
    {
        return m_height;
    }

    void Set_WrapMode(E_WRAP_MODE _wrapMode);
    
    void PutInstance(IResource* _resource);
};

#endif
