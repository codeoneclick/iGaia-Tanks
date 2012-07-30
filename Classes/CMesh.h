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
public:
    struct SVertex 
    {
        glm::vec3    m_vPosition;
        glm::vec2    m_vTexCoord;
        glm::vec3    m_vNormal;
        glm::vec3    m_vTangent;
    };
    
    struct SSourceData
    {
        SVertex*        m_pData;
        IVertexBuffer*  m_pVertexBuffer;
        CIndexBuffer*   m_pIndexBuffer;
        int             m_iNumVertexes;
        int             m_iNumIndexes;
        glm::vec3       m_vMaxBound;
        glm::vec3       m_vMinBound;
    }; 
protected:
    SSourceData* m_pSourceData;
public:
    CMesh(E_CREATION_MODE _eCreationMode);
    virtual ~CMesh(void);
    IVertexBuffer*  Get_VertexBufferRef(void) { return m_pSourceData->m_pVertexBuffer; }
    CIndexBuffer*   Get_IndexBufferRef(void) { return m_pSourceData->m_pIndexBuffer; }
    virtual void Set_SourceData(void* _pSourceData);
    int Get_NumIndexes(void) { return m_pSourceData->m_iNumIndexes; }
    int Get_NumVertexes(void) { return m_pSourceData->m_iNumVertexes; }
    glm::vec3 Get_MaxBound(void) { return m_pSourceData->m_vMaxBound; }
    glm::vec3 Get_MinBound(void) { return m_pSourceData->m_vMinBound; }
};

#endif
