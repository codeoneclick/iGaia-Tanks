//
//  ILight.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/2/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ILight.h"

ILight::ILight(void)
{
    m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vLightAt  = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

ILight::~ILight(void)
{
    
}

void ILight::Update(void)
{
    glm::mat4x4 mRotationX = glm::rotate(glm::mat4(1.0f), m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4x4 mRotationY = glm::rotate(glm::mat4(1.0f), m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4x4 mRotationZ = glm::rotate(glm::mat4(1.0f), m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    glm::mat4x4 mRotation = mRotationX * mRotationY * mRotationZ;
    
    glm::mat4x4 mTranslation = glm::translate(glm::mat4(1.0f), m_vPosition);
    
    m_mWorld = mTranslation * mRotation;
}

void ILight::Render(void)
{
    
}