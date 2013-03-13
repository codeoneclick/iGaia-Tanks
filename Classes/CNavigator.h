//
//  CNavigator.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CNavigator_h
#define CNavigator_h

#include "HCommon.h"

class CNavigator
{
private:

    f32 m_moveForwardSpeed;
    f32 m_moveBackwardSpeed;
    f32 m_strafeSpeed;
    f32 m_steerSpeed;

    glm::vec3 m_position;
    glm::vec3 m_rotation;

    f32* m_heightmapData;
    ui32 m_heightmapWidth;
    ui32 m_heightmapHeight;

protected:

public:

    CNavigator(f32 _moveForwardSpeed, f32 _moveBackwardSpeed, f32 _strafeSpeed, f32 _steerSpeed);
    ~CNavigator(void) = default;

    inline void Set_Heightmap(f32* _heightmapData, ui32 _heightmapWidth, ui32 _heightmapHeight)
    {
        assert(_heightmapData != nullptr);
        assert(_heightmapHeight != 0);
        assert(_heightmapWidth != 0);
        m_heightmapData = _heightmapData;
        m_heightmapWidth = _heightmapWidth;
        m_heightmapHeight = _heightmapHeight;
    };

    bool MoveForward(void);
    bool MoveBackward(void);
    bool MoveLeft(void);
    bool MoveRight(void);

    void SteerLeft(void);
    void SteerRight(void);

    inline glm::vec3 Get_Position(void)
    {
        return m_position;
    };
    
    inline void Set_Position(const glm::vec3& _position)
    {
        m_position = _position;
    };

    inline glm::vec3 Get_Rotation(void)
    {
        return m_rotation;
    };
    
    inline void Set_Rotation(const glm::vec3& _rotation)
    {
        m_rotation = _rotation;
    };

    inline void Set_MoveForwardSpeed(f32 _speed)
    {
        m_moveForwardSpeed = _speed;
    };
    
    inline void Set_MoveBackwardSpeed(f32 _speed)
    {
        m_moveBackwardSpeed = _speed;
    };
    
    inline void Set_StrafeSpeed(f32 _speed)
    {
        m_strafeSpeed = _speed;
    };
    
    inline void Set_SteerSpeed(f32 _speed)
    {
        m_steerSpeed = _speed;
    };
};

#endif 
