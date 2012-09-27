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
    struct SVertex
    {
        glm::vec3 m_vPosition;
        glm::vec2 m_vTexCoord;
        glm::vec3 m_vNormal;
        glm::vec3 m_vTangent;
    };
        
    SVertex* m_vertexData;
    unsigned short* m_indexData;
    unsigned int m_numVertexes;
    unsigned int m_numIndexes;
public:
    CParser_MDL(void);
    ~CParser_MDL(void);
    void Load(const std::string& _name);
    IResource* Commit(void);
};


#endif
