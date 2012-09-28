//
//  CMesh.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CMesh_h
#define iGaia_CMesh_h

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "IResource.h"
#include <vector>

class CMesh : public IResource
{   
protected:
    CVertexBuffer* m_vertexBuffer;
    CIndexBuffer* m_indexBuffer;
    
    glm::vec3       m_maxBound;
    glm::vec3       m_minBound;

    void _CreateBounds(void);
public:
    CMesh(E_CREATION_MODE _eCreationMode, CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer);
    ~CMesh(void);
    inline CVertexBuffer* Get_VertexBuffer(void)
    {
        return m_vertexBuffer;
    }
    inline CIndexBuffer* Get_IndexBuffer(void)
    {
        return m_indexBuffer;
    }
    inline glm::vec3 Get_MaxBound(void)
    {
        return m_maxBound;
    }
    inline glm::vec3 Get_MinBound(void)
    {
        return m_minBound;
    }
    
    void PutInstance(IResource* _resource);
};

#endif
