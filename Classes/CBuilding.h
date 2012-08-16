//
//  CBuilding.h
//  iGaia
//
//  Created by sergey sergeev on 8/7/12.
//
//

#ifndef __iGaia__CBuilding__
#define __iGaia__CBuilding__

#include <iostream>
#include "CSceneMgr.h"

class CBuilding : public ICollisionDelegate
{
protected:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    
    INode* m_pModel;
    
    glm::vec3 m_vMaxBound;
    glm::vec3 m_vMinBound;
public:
    CBuilding(void);
    ~CBuilding(void);
    void Load(const std::string& _sModelName, const std::string& _sTextureName);
    void Update(void);
    
    void Set_Position(const glm::vec3& _vPosition);
    glm::vec3 Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(const glm::vec3& _vRotation);
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    void OnCollision(ICollisionDelegate* _pCollider);
    void OnBox2dPositionChanged(const glm::vec3& _vPosition);
    void OnBox2dRotationChanged(float _fAngleY);
    glm::vec3 Get_Box2dPosition(void) { return m_vPosition; }
    glm::vec3 Get_Box2dMaxBound(void) { return m_vMaxBound; }
    glm::vec3 Get_Box2dMinBound(void) { return m_vMinBound; }
};

#endif /* defined(__iGaia__CBuilding__) */
