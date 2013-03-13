//
//  CNavigator.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CNavigator.h"
#include "CHeightmapHelper.h"

CNavigator::CNavigator(f32 _moveForwardSpeed, f32 _moveBackwardSpeed, f32 _strafeSpeed, f32 _steerSpeed)
{
    m_moveForwardSpeed = _moveForwardSpeed;
    m_moveBackwardSpeed = _moveBackwardSpeed;
    m_strafeSpeed = _strafeSpeed;
    m_steerSpeed = _steerSpeed;

    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    m_heightmapData = nullptr;
    m_heightmapWidth = 0;
    m_heightmapHeight = 0;
}

bool CNavigator::MoveForward(void)
{
    glm::vec3 precomputePosition = glm::vec3(m_position.x + cosf(-m_rotation.y) * m_moveForwardSpeed, 0.0f, m_position.z + sinf(-m_rotation.y) * m_moveForwardSpeed);
    if(floorf(precomputePosition.x) > m_heightmapWidth ||
       floorf(precomputePosition.x) < 0 ||
       floorf(precomputePosition.z) > m_heightmapHeight ||
       floorf(precomputePosition.z) < 0
       )
    {
        return false;
    }
    f32 height = CHeightmapHelper::Get_HeightValue(m_heightmapData, m_heightmapWidth, m_heightmapHeight, precomputePosition);
    m_position = glm::vec3(precomputePosition.x, height, precomputePosition.z);
    glm::vec2 rotationOnHeightmap = CHeightmapHelper::Get_RotationOnHeightmap(m_heightmapData, m_heightmapWidth, m_heightmapHeight, m_position);
    m_rotation = glm::vec3(rotationOnHeightmap.x, m_rotation.y, rotationOnHeightmap.y);
    return true;
}

bool CNavigator::MoveBackward(void)
{
    glm::vec3 precomputePosition = glm::vec3(m_position.x - cosf(-m_rotation.y) * m_moveBackwardSpeed, 0.0f, m_position.z - sinf(-m_rotation.y) * m_moveBackwardSpeed);
    if(floorf(precomputePosition.x) > m_heightmapWidth ||
       floorf(precomputePosition.x) < 0 ||
       floorf(precomputePosition.z) > m_heightmapHeight ||
       floorf(precomputePosition.z) < 0
       )
    {
        return false;
    }
    f32 height = CHeightmapHelper::Get_HeightValue(m_heightmapData, m_heightmapWidth, m_heightmapHeight, precomputePosition);
    m_position = glm::vec3(precomputePosition.x, height, precomputePosition.z);
    glm::vec2 rotationOnHeightmap = CHeightmapHelper::Get_RotationOnHeightmap(m_heightmapData, m_heightmapWidth, m_heightmapHeight, m_position);
    m_rotation = glm::vec3(rotationOnHeightmap.x, m_rotation.y, rotationOnHeightmap.y);
    return true;
}

bool CNavigator::MoveLeft(void)
{
    glm::vec3 precomputePosition = glm::vec3(m_position.x - sinf(m_rotation.y) * m_strafeSpeed, 0.0f, m_position.z - cosf(m_rotation.y) * m_strafeSpeed);
    if(floorf(precomputePosition.x) > m_heightmapWidth ||
       floorf(precomputePosition.x) < 0 ||
       floorf(precomputePosition.z) > m_heightmapHeight ||
       floorf(precomputePosition.z) < 0
       )
    {
        return false;
    }
    f32 height = CHeightmapHelper::Get_HeightValue(m_heightmapData, m_heightmapWidth, m_heightmapHeight, precomputePosition);
    m_position = glm::vec3(precomputePosition.x, height, precomputePosition.z);
    glm::vec2 rotationOnHeightmap = CHeightmapHelper::Get_RotationOnHeightmap(m_heightmapData, m_heightmapWidth, m_heightmapHeight, m_position);
    m_rotation = glm::vec3(rotationOnHeightmap.x, m_rotation.y, rotationOnHeightmap.y);
    return true;
}

bool CNavigator::MoveRight(void)
{
    glm::vec3 precomputePosition = glm::vec3(m_position.x + sinf(m_rotation.y) * m_strafeSpeed, 0.0f, m_position.z + cosf(m_rotation.y) * m_strafeSpeed);
    if(floorf(precomputePosition.x) > m_heightmapWidth ||
       floorf(precomputePosition.x) < 0 ||
       floorf(precomputePosition.z) > m_heightmapHeight ||
       floorf(precomputePosition.z) < 0
       )
    {
        return false;
    }
    f32 height = CHeightmapHelper::Get_HeightValue(m_heightmapData, m_heightmapWidth, m_heightmapHeight, precomputePosition);
    m_position = glm::vec3(precomputePosition.x, height, precomputePosition.z);
    glm::vec2 rotationOnHeightmap = CHeightmapHelper::Get_RotationOnHeightmap(m_heightmapData, m_heightmapWidth, m_heightmapHeight, m_position);
    m_rotation = glm::vec3(rotationOnHeightmap.x, m_rotation.y, rotationOnHeightmap.y);
    return true;
}

void CNavigator::SteerLeft(void)
{
    m_rotation.y += m_steerSpeed;
   glm:: vec2 rotationOnHeightmap = CHeightmapHelper::Get_RotationOnHeightmap(m_heightmapData, m_heightmapWidth, m_heightmapHeight, m_position);
    m_rotation = glm::vec3(rotationOnHeightmap.x, m_rotation.y, rotationOnHeightmap.y);
}

void CNavigator::SteerRight(void)
{
    m_rotation.y -= m_steerSpeed;
    glm::vec2 rotationOnHeightmap = CHeightmapHelper::Get_RotationOnHeightmap(m_heightmapData, m_heightmapWidth, m_heightmapHeight, m_position);
    m_rotation = glm::vec3(rotationOnHeightmap.x, m_rotation.y, rotationOnHeightmap.y);
}
