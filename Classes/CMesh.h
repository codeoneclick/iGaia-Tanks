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

    CVertexBuffer* m_vertexBuffer;
    CIndexBuffer* m_indexBuffer;

    glm::vec3 m_maxBound;
    glm::vec3 m_minBound;

public:

    CMesh(CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer, const glm::vec3& _maxBound, const glm::vec3& _minBound);
    ~CMesh(void);

    inline CVertexBuffer* Get_VertexBuffer(void)
    {
        assert(m_vertexBuffer != nullptr);
        return m_vertexBuffer;
    };
    
    inline CIndexBuffer* Get_IndexBuffer(void)
    {
        assert(m_indexBuffer != nullptr);
        return m_indexBuffer;
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
