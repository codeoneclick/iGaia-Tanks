//
//  CFrustum.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/23/12.
//
//

#include "CFrustum.h"

CFrustum::CFrustumPlane::CFrustumPlane(void)
{
    
}

CFrustum::CFrustumPlane::~CFrustumPlane(void)
{
    
}

void CFrustum::CFrustumPlane::Set_Points(const glm::vec3 &_vPoint_01, const glm::vec3 &_vPoint_02, const glm::vec3 &_vPoint_03)
{
    glm::vec3 vEdge_01, vEdge_02;
    
	vEdge_01 = _vPoint_01 - _vPoint_02;
	vEdge_02 = _vPoint_03 - _vPoint_02;
    
	m_vNormal = glm::normalize(glm::cross(vEdge_01, vEdge_02));
    m_vPoint = _vPoint_02;
	d = -glm::dot(m_vNormal, m_vPoint);
}

float CFrustum::CFrustumPlane::Get_Distance(const glm::vec3 &_vPoint)
{
    float fDot = glm::dot(m_vNormal, _vPoint);
    return (d + fDot) * -1.0f;
}

CFrustum::CFrustum(void)
{
    m_pCameraRef = NULL;
}

CFrustum::~CFrustum(void)
{
    
}

void CFrustum::Update(void)
{
    if(m_pCameraRef == NULL)
    {
        return;
    }
    
    glm::vec3 vCameraPosition = m_pCameraRef->Get_Position();
    glm::vec3 vCameraLookAt = m_pCameraRef->Get_LookAt();
    glm::vec3 vCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 dir, nc, fc, X, Y, Z;
    
	Z = glm::normalize(vCameraPosition - vCameraLookAt);
	X = glm::normalize(glm::cross(vCameraUp, Z));
	Y = glm::cross(Z, X);
    
	nc = vCameraPosition - Z * m_fNearD;
	fc = vCameraPosition - Z * m_fFarD;
    
	ntl = nc + Y * nh - X * nw;
	ntr = nc + Y * nh + X * nw;
	nbl = nc - Y * nh - X * nw;
	nbr = nc - Y * nh + X * nw;
    
	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;
    
	m_pPlanes[TOP].Set_Points(ntr,ntl,ftl);
	m_pPlanes[BOTTOM].Set_Points(nbl,nbr,fbr);
	m_pPlanes[LEFT].Set_Points(ntl,nbl,fbl);
	m_pPlanes[RIGHT].Set_Points(nbr,ntr,fbr);
	m_pPlanes[NEAR].Set_Points(ntl,ntr,nbr);
	m_pPlanes[FAR].Set_Points(ftr,ftl,fbl);
}

void CFrustum::Set_CameraRef(ICamera *_pCameraRef)
{
    m_pCameraRef = _pCameraRef;
}

void CFrustum::Set_InternalParams(float _fAngle, float _fAspectRation, float _fNearD, float _fFarD)
{
    m_fAspectRation = _fAspectRation;
	m_fAngle = _fAngle;
	m_fNearD = _fNearD;
	m_fFarD = _fFarD;
    
	m_fTan = tanf(glm::radians(m_fAngle) * 0.5f);
	nh = m_fNearD * m_fTan;
	nw = nh * m_fAspectRation;
	fh = m_fFarD  * m_fTan;
	fw = fh * m_fAspectRation;
}

int CFrustum::IsPointInFrustum(const glm::vec3 &_vPoint)
{
    int iResult = E_FRUSTUM_RESULT_INSIDE;
	for(int i=0; i < 6; i++)
    {
		if (m_pPlanes[i].Get_Distance(_vPoint) < 0.0f)
        {
			return E_FRUSTUM_RESULT_OUTSIDE;
        }
	}
	return(iResult);
}

int CFrustum::IsSphereInFrustum(const glm::vec3& _vPoint, float _fRadius)
{
    int iRresult = E_FRUSTUM_RESULT_INSIDE;
	float fDistance;
    
	for(int i=0; i < 6; i++)
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
    
    for(int i = 0; i < 6; ++i) {
        // X axis 
        if(m_pPlanes[i].m_vNormal.x > 0)
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
        if(m_pPlanes[i].m_vNormal.y > 0)
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
        if(m_pPlanes[i].m_vNormal.z > 0)
        {
            vMin.z = _vMinBound.z; 
            vMax.z = _vMaxBound.z; 
        }
        else
        {
            vMin.z = _vMaxBound.z; 
            vMax.z = _vMinBound.z; 
        } 
        if(glm::dot(m_pPlanes[i].m_vNormal, vMin) + m_pPlanes[i].d > 0)
            return E_FRUSTUM_RESULT_OUTSIDE; 
        if(glm::dot(m_pPlanes[i].m_vNormal, vMax) + m_pPlanes[i].d >= 0) 
            iResult = E_FRUSTUM_RESULT_INTERSECT; 
    } 
    return iResult;
}









