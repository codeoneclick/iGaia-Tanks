//
//  ITankPart.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__ITankPart__
#define __iGaia__ITankPart__

#include <iostream>
#include "CModel.h"
#include "CMathHelper.h"
#include "CParticleEmitterFire.h"

class ITankPart
{
protected:
    glm::vec3 m_vBoundPositionHelper;
    glm::vec4 m_vTransformHelper;
    glm::mat4x4 m_mTransformHelper;
    
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    glm::vec3 m_vCachedPosition;
    glm::vec3 m_vCachedRotation;
public:
    ITankPart(void);
    virtual ~ITankPart(void);

    virtual void Load(void) = 0;
    virtual void Update(void) = 0;
    
    virtual void Set_Position(const glm::vec3& _vPosition) = 0;
    virtual void Set_Rotation(const glm::vec3& _vRotation) = 0;
};

#endif /* defined(__iGaia__ITankPart__) */
