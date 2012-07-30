//
//  ITankBody.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__ITankBody__
#define __iGaia__ITankBody__

#include <iostream>
#include "ITankPart.h"

class ITankBody : public ITankPart
{
protected:
    CModel* m_pBody;
    
    CParticleEmitter* m_pLeftExhaustSmokeEmitter;
    CParticleEmitter* m_pRightExhaustSmokeEmitter;
    
    float m_fBodyCurrentHealth;
    float m_fBodyTotalHealth;
    
    glm::vec3 m_vLeftExhaustEmitterOffset;
    glm::vec3 m_vRightExhaustEmitterOffset;
    
    glm::vec3 m_vMaxBound;
    glm::vec3 m_vMinBound;
    glm::vec3 m_vCenterBound;
    
public:
    ITankBody(void);
    virtual ~ITankBody(void);
    
    virtual void Load(void);
    virtual void Update(void);
    
    void Set_BodyHealth(float _fHealth);
    float Get_BodyHealth(void);
    
    void Set_Position(const glm::vec3& _vPosition);
    void Set_Rotation(const glm::vec3& _vRotation);
    
    inline glm::vec3 Get_BodyMaxBound(void)    { return m_vMaxBound; }
    inline glm::vec3 Get_BodyMinBound(void)    { return m_vMinBound; }
    inline glm::vec3 Get_BodyCenterBound(void) { return m_vCenterBound; }
    
    void StartExhaust(bool _bValue);
    
    INode* Get_BasisNode(void) { return m_pBody; };
};

#endif /* defined(__iGaia__ITankBody__) */
