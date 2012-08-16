//
//  ICollisionDelegate.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/7/12.
//
//

#include "ICollisionDelegate.h"

ICollisionDelegate::ICollisionDelegate(void)
{
    m_eDelegateType = E_DELEGATE_TYPE_COLLISION;
    m_sColliderIdStr = "none";
    m_pBox2dBody = NULL;
}

ICollisionDelegate::~ICollisionDelegate(void)
{
    
}

void ICollisionDelegate::Set_Box2dPosition(const glm::vec3 &vPosition)
{
    if(m_pBox2dBody != NULL)
    {
        m_pBox2dBody->SetTransform(b2Vec2(vPosition.x, vPosition.z),m_pBox2dBody->GetAngle());
    }
}

