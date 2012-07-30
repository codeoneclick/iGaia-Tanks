//
//  CCameraTarget.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCameraTarget.h"

CCameraTarget::CCameraTarget(void)
{
    
}

CCameraTarget::~CCameraTarget(void)
{
    m_pTarget = NULL;
}

void CCameraTarget::Update()
{
    if(m_pTarget != NULL)
    {
        m_vLookAt = m_pTarget->Get_Position();
    }
    m_vLookAt.y += 2.0f;
    m_vPosition.y = m_fHeightFromLookAt;
    m_vPosition.x = m_vLookAt.x + cos(-m_vRotation.y) * -m_fDistanceToLookAt;
    m_vPosition.z = m_vLookAt.z + sin(-m_vRotation.y) * -m_fDistanceToLookAt;
	m_mView = glm::lookAt(m_vPosition, m_vLookAt, m_vUp); 
}

void CCameraTarget::OnScreenMove(glm::vec2 _vMoveDirection)
{
    
}
