//
//  CTexture.h
//  iGaia
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CTexture_h
#define CTexture_h

#include "IResource.h"

class CTexture : public IResource_INTERFACE
{   
private:
    
    ui32 m_width;
    ui32 m_height;
    ui32 m_handle;
    ui32 m_wrap;

protected:

    
public:
    
    CTexture(void);
    ~CTexture(void);
    
    void Link(ui32 _handle, ui32 _width, ui32 _height);
    
    inline ui32 Get_Handle(void)
    {
        return m_handle;
    };
    
    inline ui32 Get_Width(void)
    {
        return m_width;
    };
    
    inline ui32 Get_Height(void)
    {
        return m_height;
    };

    void Set_Wrap(ui32 _wrap);
    
    void Bind(void);
    void Unbind(void);
};

#endif
