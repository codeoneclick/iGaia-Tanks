//
//  CFrustum.h
//  iGaia
//
//  Created by sergey sergeev on 5/23/12.
//
//

#ifndef __iGaia__CFrustum__
#define __iGaia__CFrustum__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define k_MAX_FRUSTUM_PLANES 6

class ICamera;
class CFrustum
{
public:
    enum E_FRUSTUM_RESULT
    {
        E_FRUSTUM_RESULT_OUTSIDE = 0,
        E_FRUSTUM_RESULT_INTERSECT,
        E_FRUSTUM_RESULT_INSIDE
    };
protected:
    class CPlane
    {
    protected:
        glm::vec3 m_vNormal;
        float m_fOffset;
    public:
        CPlane(void);
        ~CPlane(void);
        void Update(const glm::vec3& _vPoint_01, const glm::vec3& _vPoint_02, const glm::vec3& _vPoint_03);
        float Get_Distance(const glm::vec3& _vPoint);
        inline glm::vec3 Get_Normal(void) { return m_vNormal; }
        inline float Get_Offset(void) { return m_fOffset; }
    };
    enum E_FRUSTUM_PLANE
    {
        E_FRUSTUM_PLANE_TOP = 0,
        E_FRUSTUM_PLANE_BOTTOM,
        E_FRUSTUM_PLANE_LEFT,
        E_FRUSTUM_PLANE_RIGHT,
        E_FRUSTUM_PLANE_NEAR,
        E_FRUSTUM_PLANE_FAR
    };
    CPlane m_pPlanes[k_MAX_FRUSTUM_PLANES];
    glm::vec3 m_vNearTopLeftPoint,m_vNearTopRightPoint, m_vNearBottomLeftPoint, m_vNearBottomRightPoint, m_vFarTopLeftPoint,m_vFarTopRightPoint, m_vFarBottomLeftPoint, m_vFarBottomRightPoint;
    float m_fNearOffset, m_fFarOffset;
	float m_fNearWidth, m_fNearHeight, m_fFarWidth, m_fFarHeight;
    ICamera* m_pCameraRef;
public:
    CFrustum(ICamera* _pCameraRef);
    ~CFrustum(void);
    void Update(void);
    int IsPointInFrustum(const glm::vec3& _vPoint);
    int IsSphereInFrustum(const glm::vec3& _vPoint, float _fRadius);
    int IsBoxInFrustum(const glm::vec3& _vMaxBound, const glm::vec3& _vMinBound);
    
};

#endif /* defined(__iGaia__CFrustum__) */
