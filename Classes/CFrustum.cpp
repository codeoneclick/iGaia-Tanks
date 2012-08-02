//
//  CFrustum.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/23/12.
//
//

#include "CFrustum.h"
#include "ICamera.h"

CFrustum::CPlane::CPlane(void)
{

}

CFrustum::CPlane::~CPlane(void)
{
    
}

float CFrustum::CPlane::Get_Distance(const glm::vec3 &_vPoint)
{
    float fDot = glm::dot(m_vNormal, _vPoint);
    return (m_fOffset + fDot) * -1.0f;
}

void CFrustum::CPlane::Update(const glm::vec3 &_vPoint_01, const glm::vec3 &_vPoint_02, const glm::vec3 &_vPoint_03)
{
    glm::vec3 vEdge_01, vEdge_02;
	vEdge_01 = _vPoint_01 - _vPoint_02;
	vEdge_02 = _vPoint_03 - _vPoint_02;
    
	m_vNormal = glm::normalize(glm::cross(vEdge_01, vEdge_02));
	m_fOffset = -glm::dot(m_vNormal, _vPoint_02);
}

CFrustum::CFrustum(ICamera* _pCameraRef)
{
    m_pCameraRef = _pCameraRef;
}

CFrustum::~CFrustum(void)
{
    
}

void CFrustum::Update(void)
{
    glm::vec3 vCameraPosition = m_pCameraRef->Get_Position();
    glm::vec3 vCameraLookAt = m_pCameraRef->Get_LookAt();
    glm::vec3 vCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    m_fNearOffset = m_pCameraRef->Get_NearPlane();
	m_fFarOffset = m_pCameraRef->Get_FarPlane();
    
	float fTan = tanf(glm::radians(m_pCameraRef->Get_FovY()) * 0.5f);
	m_fNearHeight = m_fNearOffset * fTan;
	m_fNearWidth = m_fNearHeight * m_pCameraRef->Get_AspectRatio();
	m_fFarHeight = m_fFarOffset  * fTan;
	m_fFarWidth = m_fFarHeight * m_pCameraRef->Get_AspectRatio();
    
    glm::vec3 vNearOffset, vFarOffset, vCameraBasis_X, vCameraBasis_Y, vCameraBasis_Z;
    
	vCameraBasis_Z = glm::normalize(vCameraPosition - vCameraLookAt);
	vCameraBasis_X = glm::normalize(glm::cross(vCameraUp, vCameraBasis_Z));
	vCameraBasis_Y = glm::cross(vCameraBasis_Z, vCameraBasis_X);
    
	vNearOffset = vCameraPosition - vCameraBasis_Z * m_fNearOffset;
	vFarOffset = vCameraPosition - vCameraBasis_Z * m_fFarOffset;
    
	m_vNearTopLeftPoint = vNearOffset + vCameraBasis_Y * m_fNearHeight - vCameraBasis_X * m_fNearWidth;
	m_vNearTopRightPoint = vNearOffset + vCameraBasis_Y * m_fNearHeight + vCameraBasis_X * m_fNearWidth;
	m_vNearBottomLeftPoint = vNearOffset - vCameraBasis_Y * m_fNearHeight - vCameraBasis_X * m_fNearWidth;
	m_vNearBottomRightPoint = vNearOffset - vCameraBasis_Y * m_fNearHeight + vCameraBasis_X * m_fNearWidth;
    
	m_vFarTopLeftPoint = vFarOffset + vCameraBasis_Y * m_fFarHeight - vCameraBasis_X * m_fFarWidth;
	m_vFarTopRightPoint = vFarOffset + vCameraBasis_Y * m_fFarHeight + vCameraBasis_X * m_fFarWidth;
	m_vFarBottomLeftPoint = vFarOffset - vCameraBasis_Y * m_fFarHeight - vCameraBasis_X * m_fFarWidth;
	m_vFarBottomRightPoint = vFarOffset - vCameraBasis_Y * m_fFarHeight + vCameraBasis_X * m_fFarWidth;
    
	m_pPlanes[E_FRUSTUM_PLANE_TOP].Update(m_vNearTopRightPoint,m_vNearTopLeftPoint,m_vFarTopLeftPoint);
	m_pPlanes[E_FRUSTUM_PLANE_BOTTOM].Update(m_vNearBottomLeftPoint,m_vNearBottomRightPoint,m_vFarBottomRightPoint);
	m_pPlanes[E_FRUSTUM_PLANE_LEFT].Update(m_vNearTopLeftPoint,m_vNearBottomLeftPoint,m_vFarBottomLeftPoint);
	m_pPlanes[E_FRUSTUM_PLANE_RIGHT].Update(m_vNearBottomRightPoint,m_vNearTopRightPoint,m_vFarBottomRightPoint);
	m_pPlanes[E_FRUSTUM_PLANE_NEAR].Update(m_vNearTopLeftPoint,m_vNearTopRightPoint,m_vNearBottomRightPoint);
	m_pPlanes[E_FRUSTUM_PLANE_FAR].Update(m_vFarTopRightPoint,m_vFarTopLeftPoint,m_vFarBottomLeftPoint);
}


int CFrustum::IsPointInFrustum(const glm::vec3 &_vPoint)
{
    int iResult = E_FRUSTUM_RESULT_INSIDE;
	for(unsigned int i = 0; i < k_MAX_FRUSTUM_PLANES; i++)
    {
		if (m_pPlanes[i].Get_Distance(_vPoint) < 0.0f)
        {
			return E_FRUSTUM_RESULT_OUTSIDE;
        }
	}
	return iResult;
}

int CFrustum::IsSphereInFrustum(const glm::vec3& _vPoint, float _fRadius)
{
    int iRresult = E_FRUSTUM_RESULT_INSIDE;
	float fDistance;
    
	for(int i = 0; i < k_MAX_FRUSTUM_PLANES; i++)
    {
		fDistance = m_pPlanes[i].Get_Distance(_vPoint);
		if (fDistance < -_fRadius)
			return E_FRUSTUM_RESULT_OUTSIDE;
		else if (fDistance < _fRadius)
			iRresult =  E_FRUSTUM_RESULT_INTERSECT;
	}
	return(iRresult);
}

int CFrustum::IsBoxInFrustum(const glm::vec3& _vMaxBound, const glm::vec3& _vMinBound)
{
    int iResult = E_FRUSTUM_RESULT_INSIDE; 
    glm::vec3 vMin, vMax;
    
    for(int i = 0; i < k_MAX_FRUSTUM_PLANES; ++i)
    {
        glm::vec3 vNormal = m_pPlanes[i].Get_Normal();
        // X axis
        if(vNormal.x > 0)
        {
            vMin.x = _vMinBound.x; 
            vMax.x = _vMaxBound.x; 
        }
        else
        {
            vMin.x = _vMaxBound.x; 
            vMax.x = _vMinBound.x; 
        } 
        // Y axis 
        if(vNormal.y > 0)
        {
            vMin.y = _vMinBound.y; 
            vMax.y = _vMaxBound.y; 
        }
        else
        {
            vMin.y = _vMaxBound.y; 
            vMax.y = _vMinBound.y; 
        } 
        // Z axis 
        if(vNormal.z > 0)
        {
            vMin.z = _vMinBound.z; 
            vMax.z = _vMaxBound.z; 
        }
        else
        {
            vMin.z = _vMaxBound.z; 
            vMax.z = _vMinBound.z; 
        } 
        if(glm::dot(vNormal, vMin) + m_pPlanes[i].Get_Offset() > 0)
            return E_FRUSTUM_RESULT_OUTSIDE; 
        if(glm::dot(vNormal, vMax) + m_pPlanes[i].Get_Offset() >= 0)
            iResult = E_FRUSTUM_RESULT_INTERSECT; 
    } 
    return iResult;
}









