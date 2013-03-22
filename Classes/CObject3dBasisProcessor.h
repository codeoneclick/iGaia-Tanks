//
//  CObject3dBasisProcessor.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/14/13.
//
//

#ifndef CObject3dBasisProcessor_h
#define CObject3dBasisProcessor_h

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CObject3dBasisProcessor final
{
private:
    
    static void ProcessTriangleBasis(const glm::vec3& E, const glm::vec3& F, const glm::vec3& G, f32 sE, f32 tE, f32 sF, f32 tF, f32 sG, f32 tG, glm::vec3& tangentX, glm::vec3& tangentY);
    static glm::vec3 ClosestPointOnLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
    static glm::vec3 Ortogonalize(const glm::vec3& v1, const glm::vec3& v2);
    
protected:

public:
    
    CObject3dBasisProcessor(void) {};
    ~CObject3dBasisProcessor(void) {};

    static void ProcessNormals(CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer);
    static void ProcessTangentsAndBinormals(CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer);
};

#endif 
