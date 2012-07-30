//
//  CCamera.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ICamera.h"
#include "CWindow.h"
#include "CInput.h"

ICamera::ICamera()
{
	m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

ICamera::~ICamera()
{

}

void ICamera::Init(int _iScreenWidth, int _iScreenHeight, float _fFovY, float _fFarPlane, float _fNearPlane)
{
    m_fAspectRatio = static_cast<float>(CWindow::Get_OffScreenWidth()) / static_cast<float>(CWindow::Get_OffScreenHeight());
    m_fFovY = _fFovY;
    m_fFarPlane = _fFarPlane;
    m_fNearPlane = _fNearPlane;
    m_mProjection = glm::perspective(m_fFovY, m_fAspectRatio, m_fNearPlane, m_fFarPlane);
}

void ICamera::Set_FovY(float _fFovY)
{
    m_fFovY = _fFovY;
    m_mProjection = glm::perspective(m_fFovY, m_fAspectRatio, m_fNearPlane, m_fFarPlane);
}

glm::mat4x4 ICamera::Get_BillboardSphericalMatrix(glm::vec3 _vPosition)
{
    glm::vec3 vLook = m_vPosition - _vPosition;
    vLook = glm::normalize(vLook);
    glm::vec3 vUp = glm::vec3(m_mView[1][0], m_mView[1][1], m_mView[1][2]);
    glm::vec3 vRight = glm::cross(vLook, vUp);
    vRight = glm::normalize(vRight);
    vUp = glm::cross(vRight, vLook);

    glm::mat4x4 mBillboardMatrix; 
    
    mBillboardMatrix[0][0] = vRight.x;
    mBillboardMatrix[0][1] = vRight.y;
    mBillboardMatrix[0][2] = vRight.z;
    mBillboardMatrix[0][3] = 0.0f;
    mBillboardMatrix[1][0] = vUp.x;
    mBillboardMatrix[1][1] = vUp.y;
    mBillboardMatrix[1][2] = vUp.z;
    mBillboardMatrix[1][3] = 0.0f;
    mBillboardMatrix[2][0] = vLook.x;
    mBillboardMatrix[2][1] = vLook.y;
    mBillboardMatrix[2][2] = vLook.z;
    mBillboardMatrix[2][3] = 0.0f;
    
    mBillboardMatrix[3][0] = _vPosition.x;
    mBillboardMatrix[3][1] = _vPosition.y;
    mBillboardMatrix[3][2] = _vPosition.z;
    mBillboardMatrix[3][3] = 1.0f;
    return mBillboardMatrix;
}

glm::mat4x4 ICamera::Get_BillboardCylindricalMatrix(glm::vec3 _vPosition)
{
    glm::vec3 vLook = m_vPosition - _vPosition;
    vLook = glm::normalize(vLook);
    glm::vec3 vUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 vRight = glm::cross(vLook, vUp);
    vRight = glm::normalize(vRight);
    vLook = glm::cross(vRight, vLook);
    
    glm::mat4x4 mBillboardMatrix; 
    
    mBillboardMatrix[0][0] = vRight.x;
    mBillboardMatrix[0][1] = vRight.y;
    mBillboardMatrix[0][2] = vRight.z;
    mBillboardMatrix[0][3] = 0.0f;
    mBillboardMatrix[1][0] = vUp.x;
    mBillboardMatrix[1][1] = vUp.y;
    mBillboardMatrix[1][2] = vUp.z;
    mBillboardMatrix[1][3] = 0.0f;
    mBillboardMatrix[2][0] = vLook.x;
    mBillboardMatrix[2][1] = vLook.y;
    mBillboardMatrix[2][2] = vLook.z;
    mBillboardMatrix[2][3] = 0.0f;
    
    mBillboardMatrix[3][0] = _vPosition.x;
    mBillboardMatrix[3][1] = _vPosition.y;
    mBillboardMatrix[3][2] = _vPosition.z;
    mBillboardMatrix[3][3] = 1.0f;
    return mBillboardMatrix;
}








