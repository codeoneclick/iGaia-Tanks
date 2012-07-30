//
//  CCamera.h
//  iGaia
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_ICamera_h
#define iGaia_ICamera_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

class ICamera
{
protected:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    glm::vec3 m_vLookAt;
    glm::vec3 m_vUp;
    
    glm::mat4x4 m_mView;
    glm::mat4x4 m_mProjection;
    
    float m_fFovY;
    float m_fAspectRatio;
    float m_fFarPlane;
    float m_fNearPlane;
    float m_fMoveSpeed;
    float m_fDistanceToLookAt;
    float m_fHeightFromLookAt;
    
public:
    ICamera(void);
    virtual ~ICamera(void);
    
    void Init(int _iScreenWidth, int _iScreenHeight, float _fFovY, float _fFarPlane, float _fNearPlane);
    virtual void Update(void) = 0;
    
    virtual void OnScreenMove(glm::vec2 _vMoveDirection) = 0;
    
    const glm::mat4x4 Get_Projection(void) { return m_mProjection; }
    const glm::mat4x4 Get_View(void) { return m_mView; }
    const void Set_Projection(glm::mat4x4 _mProjection) { m_mProjection = _mProjection; }
    const void Set_View(glm::mat4x4 _mView) { m_mView = _mView; }
    
    glm::mat4x4 Get_BillboardSphericalMatrix(glm::vec3 _vPosition);
    glm::mat4x4 Get_BillboardCylindricalMatrix(glm::vec3 _vPosition);
    
    void Set_FovY(float _fFovY);
    float Get_FovY(void) { return m_fFovY; }
    void Set_FarPlane(float _fFarPlane) { m_fFarPlane = _fFarPlane; }
    float Get_FarPlane(void) { return m_fFarPlane; }
    void Set_NearPlane(float _fNearPlane) { m_fNearPlane = _fNearPlane; }
    float Get_NearPlane(void) { return m_fNearPlane; }
    void Set_DistanceToLookAt(float _fDistanceToLookAt) { m_fDistanceToLookAt = _fDistanceToLookAt; }
    float Get_DistanceToLookAt(void) { return m_fDistanceToLookAt; }
    void Set_HeightFromLookAt(float _fHeightFromLookAt) { m_fHeightFromLookAt = _fHeightFromLookAt; }
    float Get_HeightFromLookAt(void) { return m_fHeightFromLookAt; }
    void Set_AspectRatio(float _fAspectRatio) { m_fAspectRatio = _fAspectRatio; }
    float Get_AspectRatio(void) { return m_fAspectRatio; }
    
    virtual glm::vec3 Get_Position(void) { return m_vPosition; }
    virtual void Set_Position(const glm::vec3& _vPosition) { m_vPosition = _vPosition; }
    
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    void Set_Rotation(const glm::vec3& _fRotation) { m_vRotation = _fRotation; }
    
    glm::vec3 Get_LookAt(void) { return m_vLookAt; }
    void Set_LookAt(const glm::vec3& _vLookAt) { m_vLookAt = _vLookAt; }
};


#endif
