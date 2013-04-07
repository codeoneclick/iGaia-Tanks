//
//  CCollisionNavigator.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/25/13.
//
//

#ifndef CCollisionNavigator_h
#define CCollisionNavigator_h

#include "CNavigator.h"
#include "CCollisionCallback.h"

class CCollisionNavigator :
public CNavigator,
public CCollisionCallback_INTERFACE
{
private:

protected:

    void OnBox2dCollide(CCollisionCallback_INTERFACE* _collider);
    void OnBox2dPositionChanged(const glm::vec3& _position);
    void OnBox2dRotationChanged(f32 _angle);
    
    glm::vec3 Get_Box2dCenter(void);
    glm::vec3 Get_Box2dMaxBound(void);
    glm::vec3 Get_Box2dMinBound(void);
    
    glm::vec3 m_maxBound;
    glm::vec3 m_minBound;

public:

    CCollisionNavigator(f32 _moveForwardSpeed,
                        f32 _moveBackwardSpeed,
                        f32 _strafeSpeed,
                        f32 _steerSpeed,
                        f32* _heightmapData,
                        ui32 _heightmapWidth,
                        ui32 _heightmapHeight,
                        const glm::vec3& _maxBound,
                        const glm::vec3& _minBound);
    
    ~CCollisionNavigator(void);
    
    void Set_Position(const glm::vec3& _position);
    
    inline void Set_MaxBound(const glm::vec3& _maxBound)
    {
        m_maxBound = _maxBound;
    };
    
    inline void Set_MinBound(const glm::vec3& _minBound)
    {
        m_minBound = _minBound;
    };
    
    bool MoveForward(void);
    bool MoveBackward(void);
    bool MoveLeft(void);
    bool MoveRight(void);
};

#endif 
