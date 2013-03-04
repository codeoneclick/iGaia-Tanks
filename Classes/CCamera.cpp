//
//  CCamera.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CCamera.h"

CCamera::CCamera(f32 _fov, f32 _near, f32 _far, glm::vec4 _viewport)
{
    m_fov = _fov;
    m_aspect = static_cast<f32>(_viewport.z) / static_cast<f32>(_viewport.w);
    m_near = _near;
    m_far = _far;
    m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
    m_altitude = 0;
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_frustum = new CFrustum(this);
}

CCamera::~CCamera(void)
{

}

void CCamera::OnUpdate(f32 _deltatime)
{
    m_position.y = m_look.y + 64.0f;
    m_position.x = m_look.x + cosf(-m_rotation) * -32.0f;
    m_position.z = m_look.z + sinf(-m_rotation) * -32.0f;
    m_view = lookAt(m_position, m_look, m_up);

    vec3 position = m_position;
    position.y = -position.y + m_altitude * 2.0f;
    vec3 look = m_look;
    look.y = -look.y + m_altitude * 2.0f;
    m_reflection = lookAt(position, look, m_up * -1.0f);

    m_frustum->OnUpdate();
}

mat4x4 iGaiaCamera::Get_CylindricalMatrixForPosition(const vec3 &_position)
{
    vec3 direction = m_position - _position;
    direction = normalize(direction);

    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    vec3 right = cross(direction, up);
    right = normalize(right);
    direction = cross(right, direction);

    mat4x4 cylindricalMatrix;
    cylindricalMatrix[0][0] = right.x;
    cylindricalMatrix[0][1] = right.y;
    cylindricalMatrix[0][2] = right.z;
    cylindricalMatrix[0][3] = 0.0f;
    cylindricalMatrix[1][0] = up.x;
    cylindricalMatrix[1][1] = up.y;
    cylindricalMatrix[1][2] = up.z;
    cylindricalMatrix[1][3] = 0.0f;
    cylindricalMatrix[2][0] = direction.x;
    cylindricalMatrix[2][1] = direction.y;
    cylindricalMatrix[2][2] = direction.z;
    cylindricalMatrix[2][3] = 0.0f;

    cylindricalMatrix[3][0] = _position.x;
    cylindricalMatrix[3][1] = _position.y;
    cylindricalMatrix[3][2] = _position.z;
    cylindricalMatrix[3][3] = 1.0f;

    return cylindricalMatrix;
}

mat4x4 iGaiaCamera::Get_SphericalMatrixForPosition(const vec3 &_position)
{
    vec3 direction = _position - m_position;
    direction = normalize(direction);

    vec3 up = vec3(m_view[1][0], m_view[1][1], m_view[1][2]);
    up = normalize(up);

    vec3 right = cross(direction, up);
    right = normalize(right);

    up = cross(direction, right);
    up = normalize(up);

    mat4x4 sphericalMatrix;
    sphericalMatrix[0][0] = right.x;
    sphericalMatrix[0][1] = right.y;
    sphericalMatrix[0][2] = right.z;
    sphericalMatrix[0][3] = 0.0f;
    sphericalMatrix[1][0] = up.x;
    sphericalMatrix[1][1] = up.y;
    sphericalMatrix[1][2] = up.z;
    sphericalMatrix[1][3] = 0.0f;
    sphericalMatrix[2][0] = direction.x;
    sphericalMatrix[2][1] = direction.y;
    sphericalMatrix[2][2] = direction.z;
    sphericalMatrix[2][3] = 0.0f;

    sphericalMatrix[3][0] = _position.x;
    sphericalMatrix[3][1] = _position.y;
    sphericalMatrix[3][2] = _position.z;
    sphericalMatrix[3][3] = 1.0f;
    
    return sphericalMatrix;
}
