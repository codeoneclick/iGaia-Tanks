//
//  CMathHelper.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/6/12.
//
//

#include "CMathHelper.h"
#include "CSceneMgr.h"
#include <cmath>
#include <limits>

CMathHelper* CMathHelper::m_pInstance = NULL;

float CMathHelper::k_PI = 3.14159265359f;
float CMathHelper::k_HALF_PI = k_PI / 2.0f;

CMathHelper::CMathHelper(void)
{
    
}

CMathHelper::~CMathHelper(void)
{
    
}

CMathHelper* CMathHelper::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CMathHelper();
    }
    
    return m_pInstance;
}

bool CMathHelper::IsFloatEqual(float _fValue_01, float _fValue_02)
{
    return std::fabs(_fValue_01 - _fValue_02) < std::numeric_limits<float>::epsilon();
}

bool CMathHelper::IsFloatEqualWithDelta(float _fValue_01, float _fValue_02, float _fDelta)
{
    return std::fabs(_fValue_01 - _fValue_02) < _fDelta;
}

float CMathHelper::Get_RotationForPlane(const glm::vec3& _vPoint_01,const glm::vec3& _vPoint_02, const glm::vec3& _vPoint_03)
{
    float fVectorLength_01 = sqrt(pow(_vPoint_02.x - _vPoint_01.x,2) + pow(_vPoint_02.y - _vPoint_01.y,2) + pow(_vPoint_02.z - _vPoint_01.z,2));
    float fVectorLength_02 = sqrt(pow(_vPoint_03.x - _vPoint_01.x,2) + pow(_vPoint_03.y - _vPoint_01.y,2) + pow(_vPoint_03.z - _vPoint_01.z,2));
    float fScalar = (_vPoint_02.x - _vPoint_01.x)*(_vPoint_03.x - _vPoint_01.x) + (_vPoint_02.y - _vPoint_01.y)*(_vPoint_03.y - _vPoint_01.y) + (_vPoint_02.z - _vPoint_01.z)*(_vPoint_03.z - _vPoint_01.z);
    return fScalar / (fVectorLength_01 * fVectorLength_02);
}

glm::vec2 CMathHelper::Get_RotationOnHeightmap(const glm::vec3& _vPosition)
{
    glm::vec3 vPoint_01 = _vPosition;
    glm::vec3 vPoint_02 = glm::vec3(_vPosition.x, _vPosition.y + 0.25f, _vPosition.z);
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(_vPosition.x + 0.25f, _vPosition.z);
    glm::vec3 vPoint_03 = glm::vec3(_vPosition.x + 0.25f, fHeight, _vPosition.z);
    fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(_vPosition.x, _vPosition.z + 0.25f);
    glm::vec3 vPoint_04 = glm::vec3(_vPosition.x, fHeight, _vPosition.z + 0.25f);
    
    float fAngle_01 = Get_RotationForPlane(vPoint_01, vPoint_02, vPoint_03);
    float fAngle_02 = Get_RotationForPlane(vPoint_01, vPoint_02, vPoint_04);
    
    return glm::vec2(-acos(fAngle_02) + k_HALF_PI, -acos(fAngle_01) + k_HALF_PI);
}

float CMathHelper::Get_RotationBetweenPoints(const glm::vec3& _vPoint_01,const glm::vec3& _vPoint_02)
{
    /*float fVectorLength = glm::length(glm::vec2(_vPoint_02.x, _vPoint_02.z) - glm::vec2(_vPoint_01.x, _vPoint_01.z));
    //sqrtf(powf(_vPoint_02.x - _vPoint_01.x, 2.0f) + powf(_vPoint_02.z - _vPoint_01.z, 2.0f));
    float fAngle_01 = k_PI * (_vPoint_02.x - _vPoint_01.x) / fVectorLength;
    float fAngle_02 = k_PI * (_vPoint_02.z - _vPoint_01.z) / fVectorLength;
    float fAngle_03 = 0.0f;
    if (fAngle_01 >= 0.0f)
        fAngle_03 =  fAngle_02 / 2.0f;
    if (fAngle_01 < 0.0f)
        fAngle_03 = -fAngle_02 / 2.0f - k_PI;
    return -fAngle_03;*/
    
    float fAngle = 0.0f;
    glm::vec3 vFromSeekerToTarget = _vPoint_02 - _vPoint_01;
    
    fAngle = glm::degrees(atan2f(vFromSeekerToTarget.x, vFromSeekerToTarget.z));
    
    if (fAngle < 0.0f)
        fAngle += 360.0f;
    if (fAngle >= 360.0f)
        fAngle -= 360.0f;
    
    
    return fAngle;
    
    /*const f64 z1 = core::squareroot(X*X + Z*Z);
    
    angle.X = (T)(atan2((f64)z1, (f64)Y) * RADTODEG64 - 90.0);
    
    if (angle.X < 0)
        angle.X += 360;
    if (angle.X >= 360)
        angle.X -= 360;
    
    return angle;*/
}

float CMathHelper::Get_RotationBetweenPointsDot(const glm::vec2& _vPoint_01, const glm::vec2& _vPoint_02)
{
    float fDot = glm::dot(_vPoint_01, _vPoint_02);
    return acosf(fDot);
}

float CMathHelper::Get_RotationBetweenPointsDot(const glm::vec3& _vPoint_01, const glm::vec3& _vPoint_02)
{
    float fDot = glm::dot(glm::vec2(_vPoint_01.x, _vPoint_01.z), glm::vec2(_vPoint_02.x, _vPoint_02.z));
    return acosf(fDot);
}

