//
//  CCamera.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CCamera_h
#define CCamera_h

#include "HCommon.h"
#include "CFrustum.h"
#include "CSceneUpdateCallback.h"

class CCamera : public CSceneUpdateCallback_INTERFACE
{
private:
    
    glm::mat4x4 m_view;
    glm::mat4x4 m_reflection;
    glm::mat4x4 m_projection;

    glm::vec3 m_position;
    glm::vec3 m_look;
    glm::vec3 m_up;
    f32 m_rotation;
    f32 m_altitude;
    f32 m_distance;
    f32 m_height;
    f32 m_fov;
    f32 m_aspect;

    f32 m_near;
    f32 m_far;

    CFrustum* m_frustum;

protected:

    void OnUpdate(f32 _deltatime);
    
public:

    CCamera(f32 _fov, f32 _near, f32 _far, glm::vec4 _viewport);
    ~CCamera(void);

    inline glm::mat4x4 Get_ViewMatrix(void)
    {
        return m_view;
    };

    inline glm::mat4x4 Get_ProjectionMatrix(void)
    {
        return m_projection;
    };

    inline glm::mat4x4 Get_ViewReflectionMatrix(void)
    {
        return m_reflection;
    };

    inline void Set_Position(const glm::vec3& _position)
    {
        m_position = _position;
    };
    
    inline glm::vec3 Get_Position(void)
    {
        return m_position;
    };

    inline void Set_LookAt(const glm::vec3& _look)
    {
        m_look = _look;
    };

    inline glm::vec3 Get_LookAt(void)
    {
        return m_look;
    };

    inline glm::vec3 Get_Up(void)
    {
        return m_up;
    };

    inline void Set_Rotation(f32 _rotation)
    {
        m_rotation = _rotation;
    };

    inline f32 Get_Rotation(void)
    {
        return m_rotation;
    };

    inline void Set_Altitude(f32 _altitude)
    {
        m_altitude = _altitude;
    };

    inline f32 Get_Altitude(void)
    {
        return m_altitude;
    };

    inline void Set_Distance(f32 _distance)
    {
        m_distance = _distance;
    };
    
    inline f32 Get_Distance(void)
    {
        return m_distance;
    };

    inline void Set_Height(f32 _height)
    {
        m_height = _height;
    }

    inline f32 Get_Height(void)
    {
        return m_height;
    }

    inline f32 Get_Fov(void)
    {
        return m_fov;
    };

    inline f32 Get_Aspect(void)
    {
        return m_aspect;
    };

    inline f32 Get_Near(void)
    {
        return m_near;
    };

    inline f32 Get_Far(void)
    {
        return m_far;
    };

    inline CFrustum* Get_Frustum(void)
    {
        return m_frustum;
    };

    glm::mat4x4 Get_SphericalMatrixForPosition(const glm::vec3& _position);
    glm::mat4x4 Get_CylindricalMatrixForPosition(const glm::vec3& _position);
};

#endif
