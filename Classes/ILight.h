//
//  ILight.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_ILight_h
#define iGaia_ILight_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

class ILight
{
public:
    enum E_LIGHT_MODE { E_LIGHT_MODE_DIRECTION = 0, E_LIGHT_MODE_POINT };
protected:
    glm::vec3   m_vPosition;
    glm::vec3   m_vLightAt;
    glm::vec3   m_vRotation;
    glm::vec3   m_vDirection;
    glm::mat4x4 m_mWorld;
public:
    ILight(void);
    ~ILight(void);
    virtual void Update(void);
    virtual void Render(void);
    virtual void Set_Position(glm::vec3 _vPosition) { m_vPosition = _vPosition; }
    virtual glm::vec3 Get_Position() { return m_vPosition; }
    virtual void Set_Rotation(glm::vec3 _vRotation) { m_vRotation = _vRotation; }
    virtual glm::vec3 Get_Rotation() { return m_vRotation; }
    virtual void Set_LightAt(glm::vec3 _vLightAt) { m_vLightAt = _vLightAt; }
    virtual glm::vec3 Get_LightAt() { return m_vLightAt; }
    virtual glm::vec3 Get_Direction() { return m_vDirection; }
};

#endif
