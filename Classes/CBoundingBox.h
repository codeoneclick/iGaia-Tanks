//
//  CBoundingBox.h
//  iGaia
//
//  Created by sergey.sergeev on 1/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBoundingBox_h
#define iGaia_CBoundingBox_h

#include "CCommon.h"
#include "CMesh.h"
#include "CShader.h"
#include "CMaterial.h"

class CBoundingBox
{
protected:
    glm::vec3   m_vMaxBound;
    glm::vec3   m_vMinBound;
    glm::vec3   m_vCenter;
    glm::vec3   m_vScale;
    glm::mat4x4 m_mWorld;
    static CMaterial* m_pMaterial;
    static CMesh* m_pMesh;
    static CMesh* _Get_DefaultBoxMesh(void);
    void _UpdateBounds(void);
public:
    static const float k_MAX_VALUE;
    static const float k_MIN_VALUE;
    
    CBoundingBox(const glm::vec3 &_vMaxBound, const glm::vec3 &_vMinBound);
    ~CBoundingBox(void);
    
    void Set_WorldMatrix(const glm::mat4x4 &_mWorld);
    glm::mat4x4 Get_WorldMatrix(void) { return m_mWorld; }
    
    CMesh* Get_Mesh(void) { return m_pMesh; }
    
    void Set_MaxBound(const glm::vec3 &_vMaxBound);
    void Set_MinBound(const glm::vec3 &_vMinBound);
    
    inline glm::vec3 Get_Center(void)   { return m_vCenter; }
    inline glm::vec3 Get_MaxBound(void) { return m_vMaxBound; }
    inline glm::vec3 Get_MinBound(void) { return m_vMinBound; }
    
    void Render(void);
};

#endif
