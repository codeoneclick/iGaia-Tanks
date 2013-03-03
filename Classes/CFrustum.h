//
//  CFrustum.h
//  iGaia
//
//  Created by sergey sergeev on 5/23/12.
//
//

#ifndef CFrustum_h
#define CFrustum_h

#include "HCommon.h"

class CFrustumPlane
{
private: 
    
protected:
    
    glm::vec3 m_normal;
    f32 m_offset;
    
public:
    
    CFrustumPlane(void) = default;
    ~CFrustumPlane(void) = default;
    
    void OnUpdate(const glm::vec3& _point_01, const glm::vec3& _point_02, const glm::vec3& _point_03);
    
    inline f32 Get_Distance(const glm::vec3& _point)
    {
        return (m_offset + glm::dot(m_normal, _point)) * -1.0f;
    }
    
    inline glm::vec3 Get_Normal(void)
    {
        return m_normal;
    };
    
    inline f32 Get_Offset(void)
    {
        return m_offset;
    }
};

class CCamera;
class CFrustum
{
private:
        
    CFrustumPlane m_planes[E_FRUSTUM_PLANE_MAX];
    CCamera* m_camera;
    
protected:
    
public:
    
    CFrustum(CCamera* _camera);
    ~CFrustum(void);
    
    inline void Set_Camera(CCamera* _camera)
    {
        m_camera = _camera;
    }
    
    void OnUpdate(void);
    
    E_FRUSTUM_BOUND_RESULT IsPointInFrustum(const glm::vec3& _point);
    E_FRUSTUM_BOUND_RESULT IsSphereInFrumstum(const glm::vec3& _center, f32 _radius);
    E_FRUSTUM_BOUND_RESULT IsBoundBoxInFrustum(const glm::vec3& _maxBound, const glm::vec3& _minBound);
};

#endif
