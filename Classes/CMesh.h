//
//  CMesh.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CMesh_h
#define iGaia_CMesh_h

#include "IVertexBuffer.h"
#include "CIndexBuffer.h"
#include "IResource.h"
#include <vector>

class CMesh : public IResource
{   
protected:
    IVertexBuffer* m_pVertexBuffer;
    CIndexBuffer* m_pIndexBuffer;
    
    glm::vec3       m_vMaxBound;
    glm::vec3       m_vMinBound;
public:
    CMesh(E_CREATION_MODE _eCreationMode);
    ~CMesh(void);
    inline IVertexBuffer* Get_VertexBufferRef(void) { return m_pVertexBuffer; }
    inline CIndexBuffer* Get_IndexBufferRef(void) { return m_pIndexBuffer; }
    inline void Set_VertexBufferRef(IVertexBuffer* _pVertexBufferRef) { m_pVertexBuffer = _pVertexBufferRef; }
    inline void Set_IndexBufferRef(CIndexBuffer* _pIndexBufferRef) { m_pIndexBuffer = _pIndexBufferRef; }
    inline glm::vec3 Get_MaxBound(void) { return m_vMaxBound; }
    inline glm::vec3 Get_MinBound(void) { return m_vMinBound; }
    inline void Set_MaxBound(const glm::vec3& _vMaxBound) { m_vMaxBound = _vMaxBound; }
    inline void Set_MinBound(const glm::vec3& _vMinBound) { m_vMinBound = _vMinBound; }
};

#endif
