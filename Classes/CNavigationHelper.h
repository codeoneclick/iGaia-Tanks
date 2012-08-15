//
//  CNavigationHelper.h
//  iGaia
//
//  Created by sergey sergeev on 8/15/12.
//
//

#ifndef __iGaia__CNavigationHelper__
#define __iGaia__CNavigationHelper__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "INavigationDelegate.h"

#define k_NAVIGATION_HELPER_BOUND_MAX_MIN 4096

class CNavigationHelper
{
protected:
    float m_fMoveForwardSpeed;
    float m_fMoveBackwardSpeed;
    float m_fStrafeSpeed;
    float m_fSteerSpeed;
    glm::vec3 m_vMaxBound;
    glm::vec3 m_vMinBound;
    bool m_bIsUseHeightMap;
    
    glm::vec3 m_vCurrentPosition;
    glm::vec3 m_vCurrentRotation;
    
    INavigationDelegate* m_pOwner;
    
    float _Get_HeightForPosition(const glm::vec3& _vPosition);
public:
    CNavigationHelper(void);
    ~CNavigationHelper(void);
    
    inline void Set_MoveForwardSpeed(float _fMoveForwardSpeed) { m_fMoveForwardSpeed = _fMoveForwardSpeed; }
    inline void Set_MoveBackwardSpeed(float _fMoveBackwardSpeed) { m_fMoveBackwardSpeed = _fMoveBackwardSpeed; }
    inline void Set_StrafeSpeed(float _fStrafeSpeed) { m_fStrafeSpeed = _fStrafeSpeed; }
    inline void Set_SteerSpeed(float _fSteerSpeed) { m_fSteerSpeed = _fSteerSpeed; }
    inline void Set_MaxBound(const glm::vec3& _vMaxBound) { m_vMaxBound = _vMaxBound; }
    inline void Set_MinBound(const glm::vec3& _vMinBound) { m_vMinBound = _vMinBound; }
    inline void Set_UseHeightMap(bool _bValue) { m_bIsUseHeightMap = _bValue; }
    
    inline void Set_CurrentPosition(const glm::vec3& _vPosition) { m_vCurrentPosition = _vPosition; }
    inline glm::vec3 Get_CurrentPosition(void) { return m_vCurrentPosition; }
    inline void Set_CurrentRotation(const glm::vec3& _vRotation) { m_vCurrentRotation = _vRotation; }
    inline glm::vec3 Get_CurrentRotation(void) { return m_vCurrentRotation; }
    
    bool MoveForward(void);
    bool MoveBackward(void);
    bool MoveLeft(void);
    bool MoveRight(void);
    
    void SteerLeft(void);
    void SteerRight(void);
    
    glm::vec3 Get_MoveForwardForceOffset(void);
    glm::vec3 Get_MoveBackwardForceOffset(void);
    glm::vec3 Get_MoveLeftForceOffset(void);
    glm::vec3 Get_MoveRightForceOffset(void);
    
    inline void Set_Owner(INavigationDelegate* _pOwner) { m_pOwner = _pOwner; }
};

#endif /* defined(__iGaia__CNavigationHelper__) */
