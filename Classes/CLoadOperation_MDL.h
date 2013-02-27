//
//  CLoadOperation_MDL.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#ifndef CLoadOperation_MDL_h
#define CLoadOperation_MDL_h

#include "ILoadOperation.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CLoadOperation_MDL : public ILoadOperation_INTERFACE
{
private:

protected:

    SVertex* m_vertexData;
    ui16* m_indexData;
    ui32 m_numVertexes;
    ui32 m_numIndexes;

    glm::vec3 m_maxBound;
    glm::vec3 m_minBound;

public:

    CLoadOperation_MDL(void);
    ~CLoadOperation_MDL(void);

    void Load(const std::string& _filename);
    IResource_INTERFACE* Build(void);
};

#endif 
