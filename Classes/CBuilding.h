//
//  CBuilding.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 4/6/13.
//
//

#ifndef CBuilding_h
#define CBuilding_h

#include "HCommon.h"
#include "IRoot.h"
#include "HGameSettings_DTO.h"
#include "CShape3d.h"
#include "CCollisionCallback.h"

class CBuilding :
public CCollisionCallback_INTERFACE
{
private:
    
    CShape3d* m_shape3d;
    
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    
protected:
    
    void OnBox2dCollide(CCollisionCallback_INTERFACE* _collider);
    void OnBox2dPositionChanged(const glm::vec3& _position);
    void OnBox2dRotationChanged(f32 _angle);
    
    glm::vec3 Get_Box2dCenter(void);
    glm::vec3 Get_Box2dMaxBound(void);
    glm::vec3 Get_Box2dMinBound(void);
    
public:
    
    CBuilding(void);
    ~CBuilding(void);
    
    void Load(IRoot* _root, SBuildingSettings* _settings);
    
    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);
};

#endif 
