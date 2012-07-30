//
//  CVertexBufferPositionTexcoordColor.h
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#ifndef __iGaia__CVertexBufferPositionTexcoordColor__
#define __iGaia__CVertexBufferPositionTexcoordColor__

#include <iostream>
#include "IVertexBuffer.h"

class CVertexBufferPositionTexcoordColor : public IVertexBuffer
{
public:
    struct SVertex
    {
    public:
        glm::vec3 m_vPosition; // 12
        glm::vec2 m_vTexcoord; // 8
        glm::u8vec4 m_vColor; // 4
    private:
        char padding[8];
};
public:
    CVertexBufferPositionTexcoordColor(unsigned int _iNumVertexes, unsigned int _eMode);
    ~CVertexBufferPositionTexcoordColor(void);

    virtual void Enable(CShader::E_RENDER_MODE _eRenderMode);
    virtual void Disable(CShader::E_RENDER_MODE _eRenderMode);
};


#endif /* defined(__iGaia__CVertexBufferPositionTexcoordColor__) */
