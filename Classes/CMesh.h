//
//  CMesh.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CMesh_h
#define CMesh_h

#include "IResource.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CMesh : public IResource_INTERFACE
{   
private:

protected:

    std::unique_ptr<CVertexBuffer> m_vertexBuffer;
    std::unique_ptr<CIndexBuffer> m_indexBuffer;

    glm::vec3 m_maxBound;
    glm::vec3 m_minBound;

public:

    CMesh(void);
    ~CMesh(void);
    
    void Link(std::unique_ptr<CVertexBuffer> _vertexBuffer, std::unique_ptr<CIndexBuffer> _indexBuffer);
    void Link(std::unique_ptr<CVertexBuffer> _vertexBuffer, std::unique_ptr<CIndexBuffer> _indexBuffer, const glm::vec3& _maxBound, const glm::vec3& _minBound);

    inline CVertexBuffer* Get_VertexBuffer(void)
    {
        assert(m_vertexBuffer != nullptr);
        return m_vertexBuffer.get();
    };
    
    inline CIndexBuffer* Get_IndexBuffer(void)
    {
        assert(m_indexBuffer != nullptr);
        return m_indexBuffer.get();
    };

    inline ui32 Get_NumVertexes(void)
    {
        assert(m_vertexBuffer != nullptr);
        return m_vertexBuffer->Get_NumVertexes();
    };

    inline ui32 Get_NumIndexes(void)
    {
        assert(m_indexBuffer != nullptr);
        return m_indexBuffer->Get_NumIndexes();
    };

    inline glm::vec3 Get_MaxBound(void)
    {
        return m_maxBound;
    }

    inline glm::vec3 Get_MinBound(void)
    {
        return m_minBound;
    }

    void Bind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots);
    void Draw(void);
    void Unbind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots);
};

#endif
