//
//  CVertexBufferPositionColor.h
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CVertexBufferPositionColor_h
#define iGaia_CVertexBufferPositionColor_h

#include "IVertexBuffer.h"

class CVertexBufferPositionColor : public IVertexBuffer
{
public:
    struct SVertex
    {
    public:
        glm::vec3 m_vPosition; // 12
        glm::u8vec4 m_vColor; // 4
    private:
        char padding[16];
    };
public:
    CVertexBufferPositionColor(unsigned int _iNumVertexes, unsigned int _eMode);
    ~CVertexBufferPositionColor(void);
    
    virtual void Enable(CShader::E_RENDER_MODE _eRenderMode);
    virtual void Disable(CShader::E_RENDER_MODE _eRenderMode);
};

#endif
