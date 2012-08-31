//
//  CMathHelper.h
//  iGaia
//
//  Created by sergey sergeev on 6/6/12.
//
//

#ifndef __iGaia__CMathHelper__
#define __iGaia__CMathHelper__

#include "CCommon.h"

class CMathHelper
{
public:
    static float k_PI;
    static float k_HALF_PI;
    CMathHelper(void) = default;
    ~CMathHelper(void) = default;
    static bool IsFloatEqual(float _fValue_01, float _fValue_02);
    static bool IsFloatEqualWithDelta(float _fValue_01, float _fValue_02, float _fDelta);
    
    static float Get_RotationForPlane(const glm::vec3& _vPoint_01, const glm::vec3& _vPoint_02, const glm::vec3& _vPoint_03);
    static glm::vec2 Get_RotationOnHeightmap(const glm::vec3& _vPosition);
    static float Get_RotationBetweenPoints(const glm::vec3& _vPoint_01,const glm::vec3& _vPoint_02);
    static float Get_RotationBetweenPointsDot(const glm::vec2& _vPoint_01, const glm::vec2& _vPoint_02);
    static float Get_RotationBetweenPointsDot(const glm::vec3& _vPoint_01, const glm::vec3& _vPoint_02);
    static float Get_WrapAngle(float _fValue, float _fMin, float _fMax);
};

#endif /* defined(__iGaia__CMathHelper__) */
