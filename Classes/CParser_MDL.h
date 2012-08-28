//
//  CParser_MDL.h
//  iGaia
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CParser_MDL_h
#define iGaia_CParser_MDL_h

#include "stdlib.h"
#include <string>
#include "CMesh.h"
#include "IParser.h"

class CParser_MDL : public IParser
{
protected:
    struct SData
    {
        struct SVertex
        {
            glm::vec3 m_vPosition;
            glm::vec2 m_vTexCoord;
            glm::vec3 m_vNormal;
            glm::vec3 m_vTangent;
        };
        
        SVertex* m_pVertexData;
        unsigned short* m_pIndexData;
        unsigned int m_iNumVertexes;
        unsigned int m_iNumIndexes;
        glm::vec3       m_vMaxBound;
        glm::vec3       m_vMinBound;
        SData(void)
        {
            m_pVertexData = nullptr;
            m_pIndexData = nullptr;
            m_iNumVertexes = 0;
            m_iNumIndexes = 0;
            m_vMaxBound = glm::vec3(-4096.0f, -4096.0f, -4096.0f);
            m_vMinBound = glm::vec3(4096.0f, 4096.0f, 4096.0f);
        };
        ~SData(void)
        {
            SAFE_DELETE_ARRAY(m_pVertexData);
            SAFE_DELETE_ARRAY(m_pIndexData);
        };
    };
    
    SData* m_pData;
public:
    CParser_MDL(void);
    ~CParser_MDL(void);
    void Load(const std::string& _sName);
    IResource* Commit(void);
};


#endif
