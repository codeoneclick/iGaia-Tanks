//
//  ITankPart.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "ITankPart.h"

ITankPart::ITankPart(void)
{
    m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    
    m_vCachedPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vCachedRotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

ITankPart::~ITankPart(void)
{
    
}