//
//  ITankPart.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#include "ISpare.h"

ISpare::ISpare(void)
{
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

ISpare::~ISpare(void)
{
    
}