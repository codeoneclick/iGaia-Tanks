//
//  ICharacter.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#include "ICharacter.h"

ICharacter::ICharacter(void)
{
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

ICharacter::~ICharacter(void)
{

}