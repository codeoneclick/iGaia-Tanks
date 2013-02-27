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

protected:

    ui32 m_width;
    ui32 m_height;
    ui32 m_handle;
    ui32 m_wrapMode;
    
public:
    
    CTexture(ui32 _handle, ui32 _width, ui32 _height);
    ~CTexture(void);
    
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

    void Set_WrapMode(ui32 _mode);
};

#endif
