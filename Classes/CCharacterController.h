//
//  CCharacterController.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#ifndef CCharacterController_h
#define CCharacterController_h

#include "HCommon.h"
#include "HGameEnum.h"
#include "CCamera.h"
#include "ICharacter.h"
#include "CNavigator.h"
#include "CMoveControllerCallback.h"
#include "CRotateControllerCallback.h"
#include "CMainLoopUpdateCallback.h"
#include "CLandscapeDecal.h"

class CCharacterController :
    public virtual CMoveControllerCallback_INTERFACE,
    public virtual CMainLoopUpdateCallback_INTERFACE,
    public virtual CRotateControllerCallback_INTERFACE
{
private:

protected:

    CCamera* m_camera;
    ICharacter* m_character;
    CLandscapeDecal* m_shadow;
    CNavigator* m_navigator;

    E_MOVE_CONTROLLER_DIRECTION m_moveDirection;
    E_ROTATE_CONTROLLER_DIRECTION m_rotateDirection;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    f32 m_lookAtHeight;

    void OnMoveControllerUpdate(ui32 _direction);
    void OnRotateControllerUpdate(ui32 _direction);
    void OnUpdate(f32 _deltatime);

    glm::vec3 SmoothRotation(const glm::vec3& _oldRotation, const glm::vec3& _newRotation);
    
    glm::vec3 Get_CameraLookAt(void);
    glm::vec3 Get_CharacterRotation(void);

public:

    CCharacterController(void);
    ~CCharacterController(void);

    inline void Set_Camera(CCamera* _camera)
    {
        m_camera = _camera;
    };

    inline void Set_Character(ICharacter* _character)
    {
        m_character = _character;
    };

    inline void Set_Shadow(CLandscapeDecal* _shadow)
    {
        m_shadow = _shadow;
    };

	inline void Set_Navigator(CNavigator* _navigator)
	{
		m_navigator = _navigator;
	};

    inline void Set_Position(const glm::vec3& _position)
    {
        assert(m_navigator != nullptr);
        m_position = _position;
        m_navigator->Set_Position(m_position);
    };

    inline glm::vec3 Get_Position(void)
    {
        return m_position;
    };

    inline void Set_Rotation(const glm::vec3& _rotation)
    {
        assert(m_navigator != nullptr);
        m_rotation = _rotation;
        m_navigator->Set_Rotation(m_rotation);
    };

    inline glm::vec3 Get_Rotation(void)
    {
        return m_rotation;
    };
    
    inline void Set_LookAtHeight(f32 _lookAtHeight)
    {
        m_lookAtHeight = _lookAtHeight;
    }
};

#endif 
