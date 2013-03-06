//
//  CFrustum.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/23/12.
//
//
#include "CFrustum.h"
#include "CCamera.h"

void CFrustumPlane::OnUpdate(const glm::vec3 &_point_01, const glm::vec3 &_point_02, const glm::vec3 &_point_03)
{
    glm::vec3 edge_01, edge_02;
	edge_01 = _point_01 - _point_02;
	edge_02 = _point_03 - _point_02;
	m_normal = glm::normalize(glm::cross(edge_01, edge_02));
	m_offset = -glm::dot(m_normal, _point_02);
}

CFrustum::CFrustum(CCamera* _camera)
{
    m_camera = _camera;
}

CFrustum::~CFrustum(void)
{
    m_camera = nullptr;
}

void CFrustum::OnUpdate(void)
{
    f32 tan = tanf(glm::radians(m_camera->Get_Fov()) * 0.5f);
	f32 nearHeight = m_camera->Get_Near() * tan;
	f32 nearWidth = nearHeight * m_camera->Get_Aspect();
	f32 farHeight = m_camera->Get_Far()  * tan;
	f32 farWidth = farHeight * m_camera->Get_Aspect();
    
    glm::vec3 basis_Z = glm::normalize(m_camera->Get_Position() - m_camera->Get_LookAt());
    glm::vec3 basis_X = glm::normalize(glm::cross(m_camera->Get_Up(), basis_Z));
    glm::vec3 basis_Y = glm::cross(basis_Z, basis_X);
    
    glm::vec3 nearOffset = m_camera->Get_Position() - basis_Z * m_camera->Get_Near();
	glm::vec3 farOffset = m_camera->Get_Position() - basis_Z * m_camera->Get_Far();
    
	glm::vec3 nearTopLeftPoint = nearOffset + basis_Y * nearHeight - basis_X * nearWidth;
	glm::vec3 nearTopRightPoint = nearOffset + basis_Y * nearHeight + basis_X * nearWidth;
	glm::vec3 nearBottomLeftPoint = nearOffset - basis_Y * nearHeight - basis_X * nearWidth;
	glm::vec3 nearBottomRightPoint = nearOffset - basis_Y * nearHeight + basis_X * nearWidth;
    
	glm::vec3 farTopLeftPoint = farOffset + basis_Y * farHeight - basis_X * farWidth;
	glm::vec3 farTopRightPoint = farOffset + basis_Y * farHeight + basis_X * farWidth;
	glm::vec3 farBottomLeftPoint = farOffset - basis_Y * farHeight - basis_X * farWidth;
	glm::vec3 farBottomRightPoint = farOffset - basis_Y * farHeight + basis_X * farWidth;
    
	m_planes[E_FRUSTUM_PLANE_TOP].OnUpdate(nearTopRightPoint, nearTopLeftPoint, farTopLeftPoint);
	m_planes[E_FRUSTUM_PLANE_BOTTOM].OnUpdate(nearBottomLeftPoint, nearBottomRightPoint, farBottomRightPoint);
	m_planes[E_FRUSTUM_PLANE_LEFT].OnUpdate(nearTopLeftPoint, nearBottomLeftPoint, farBottomLeftPoint);
	m_planes[E_FRUSTUM_PLANE_RIGHT].OnUpdate(nearBottomRightPoint, nearTopRightPoint, farBottomRightPoint);
	m_planes[E_FRUSTUM_PLANE_NEAR].OnUpdate(nearTopLeftPoint, nearTopRightPoint, nearBottomRightPoint);
	m_planes[E_FRUSTUM_PLANE_FAR].OnUpdate(farTopRightPoint, farTopLeftPoint, farBottomLeftPoint);
}

E_FRUSTUM_BOUND_RESULT CFrustum::IsPointInFrustum(const glm::vec3& _point)
{
    for(ui32 i = 0; i < E_FRUSTUM_PLANE_MAX; ++i)
    {
		if (m_planes[i].Get_Distance(_point) < 0.0f)
        {
			return E_FRUSTUM_BOUND_RESULT_OUTSIDE;
        }
	}
	return E_FRUSTUM_BOUND_RESULT_INSIDE;
}

E_FRUSTUM_BOUND_RESULT CFrustum::IsSphereInFrumstum(const glm::vec3& _center, f32 _radius)
{
    E_FRUSTUM_BOUND_RESULT result = E_FRUSTUM_BOUND_RESULT_INSIDE;
	for(ui32 i = 0; i < E_FRUSTUM_PLANE_MAX; ++i)
    {
		f32 distance = m_planes[i].Get_Distance(_center);
		if (distance < -_radius)
        {
			return E_FRUSTUM_BOUND_RESULT_OUTSIDE;
        }
		else if (distance < _radius)
        {
			result =  E_FRUSTUM_BOUND_RESULT_INTERSECT;
        }
	}
	return result;
}

E_FRUSTUM_BOUND_RESULT CFrustum::IsBoundBoxInFrustum(const glm::vec3& _maxBound, const glm::vec3& _minBound)
{
    glm::vec3 points[8];
    
    points[0] = _minBound;
    points[1] = glm::vec3(_minBound.x, _minBound.y, _maxBound.z);
    points[2] = glm::vec3(_maxBound.x, _minBound.y, _minBound.z);
    points[3] = glm::vec3(_maxBound.x, _minBound.y, _maxBound.z);
    
    points[4] = _maxBound;
    points[5] = glm::vec3(_maxBound.x, _maxBound.y, _minBound.z);
    points[6] = glm::vec3(_minBound.x, _maxBound.y, _maxBound.z);
    points[7] = glm::vec3(_minBound.x, _maxBound.y, _minBound.z);
    
    E_FRUSTUM_BOUND_RESULT result = E_FRUSTUM_BOUND_RESULT_INSIDE;
    ui32 pointsIn, pointsOut;
    
	for(ui32 i = 0; i < E_FRUSTUM_PLANE_MAX; ++i)
    {
        pointsIn = 0;
        pointsOut = 0;

		for (ui32 k = 0; k < 8 && (pointsIn == 0 || pointsOut == 0); ++k)
        {
			if (m_planes[i].Get_Distance(points[k]) < 0)
            {
				pointsOut++;
            }
			else
            {
				pointsIn++;
            }
		}

		if (!pointsIn)
        {
			return E_FRUSTUM_BOUND_RESULT_OUTSIDE;
        }
		else if (pointsOut)
        {
			result = E_FRUSTUM_BOUND_RESULT_INTERSECT;
        }
	}
	return result;
}









