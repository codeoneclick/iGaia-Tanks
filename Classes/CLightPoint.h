//
//  CLightPoint.h
//  iGaia
//
//  Created by sergey.sergeev on 1/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CLightPoint_h
#define iGaia_CLightPoint_h

#include "ILight.h"
#ifdef OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif EMULATION_GL
#include <GL/glew.h>
#ifndef GL_GLEXT_PROTOTYPES
#       define GL_GLEXT_PROTOTYPES 1
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include "CMesh.h"
#include "CShader.h"

class CLightPoint : public ILight
{
protected:
    static const glm::vec3 k_Size;
    glm::vec3 m_vMin;
    glm::vec3 m_vMax;
    glm::vec2 m_vDistanceToLightAt;
    CShader* m_pShader;
    CMesh* m_pMesh;
    bool m_bIsVisible;
public:
    CLightPoint(void);
    virtual ~CLightPoint(void);
    virtual void Update(void);
    virtual void Render(void);
    void Set_Visible(bool _bValue) { m_bIsVisible = _bValue; }
};


#endif
