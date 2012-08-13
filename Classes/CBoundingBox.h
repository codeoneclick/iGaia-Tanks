//
//  CBoundingBox.h
//  iGaia
//
//  Created by sergey.sergeev on 1/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBoundingBox_h
#define iGaia_CBoundingBox_h
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CMesh.h"
#include "CShader.h"
#include "CMaterial.h"

class CBoundingBox
{
protected:
    glm::vec3   m_vMax;
    glm::vec3   m_vMin;
    glm::vec3   m_vCenter;
    glm::vec3   m_vScale;
    glm::mat4x4 m_mWorld;
    static CMaterial* m_pMaterial;
    static CMesh* m_pMesh;
public:
    static const float k_MAX_VALUE;
    static const float k_MIN_VALUE;
    
    static CMesh* Get_BoundingBoxMesh(void);
    
    CBoundingBox(const glm::vec3 &_vMax, const glm::vec3 &_vMin);
    ~CBoundingBox();
    
    void Set_WorldMatrix(const glm::mat4x4 &_mWorld);
    glm::mat4x4 Get_WorldMatrix(void) { return m_mWorld; }
    CMesh* Get_Mesh(void) { return m_pMesh; }
    void Set_MaxMinPoints(const glm::vec3 &_vMax, const glm::vec3 &_vMin);
    
    inline glm::vec3 Get_Center(void)   { return m_vCenter; }
    inline glm::vec3 Get_MaxBound(void) { return m_vMax; }
    inline glm::vec3 Get_MinBound(void) { return m_vMin; }
    
    void Render(void);
};

#endif
