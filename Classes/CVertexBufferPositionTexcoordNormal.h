//
//  CVertexBufferPositionTexcoordNormal.h
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CVertexBufferPositionTexcoordNormal_h
#define iGaia_CVertexBufferPositionTexcoordNormal_h

#include "IVertexBuffer.h"

class CVertexBufferPositionTexcoordNormal : public IVertexBuffer
{
public:
    struct SVertex
    {
    public:
        glm::vec3 m_vPosition; // 12
        glm::vec2 m_vTexcoord; // 8
        glm::u8vec4 m_vNormal; // 4
    private:
        char padding[8];
    };
public:
    CVertexBufferPositionTexcoordNormal(unsigned int _iNumVertexes, unsigned int _eMode);
    ~CVertexBufferPositionTexcoordNormal(void);

    virtual void Enable(CShader::E_RENDER_MODE _eRenderMode);
    virtual void Disable(CShader::E_RENDER_MODE _eRenderMode);
};

#endif
