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
#include "ICamera.h"
#include "CBoundingBox.h"

class CFrustum
{
public:
    class CFrustumPlane
    {
    public:
        glm::vec3 m_vNormal, m_vPoint;
        float d;
        CFrustumPlane(void);
        ~CFrustumPlane(void);
        void Set_Points(const glm::vec3& _vPoint_01, const glm::vec3& _vPoint_02, const glm::vec3& _vPoint_03);
        float Get_Distance(const glm::vec3& _vPoint);
    };
    enum E_FRUSTUM_RESULT { E_FRUSTUM_RESULT_OUTSIDE = 0, E_FRUSTUM_RESULT_INTERSECT, E_FRUSTUM_RESULT_INSIDE };
protected:
    ICamera* m_pCameraRef;
    enum { TOP = 0, BOTTOM, LEFT, RIGHT, NEAR, FAR };
    CFrustumPlane m_pPlanes[6];
    glm::vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
    float m_fAngle, m_fAspectRation, m_fNearD, m_fFarD, m_fTan;
	float nw,nh,fw,fh;
public:
    CFrustum(void);
    ~CFrustum(void);
    void Update(void);
    void Set_CameraRef(ICamera* _pCameraRef);
    void Set_InternalParams(float _fAngle, float _fAspectRation, float _fNearD, float _fFarD);
    int IsPointInFrustum(const glm::vec3& _vPoint);
    int IsSphereInFrustum(const glm::vec3& _vPoint, float _fRadius);
    int IsBoxInFrustum(const glm::vec3& _vMaxBound, const glm::vec3& _vMinBound);
    
};

#endif /* defined(__iGaia__CFrustum__) */
