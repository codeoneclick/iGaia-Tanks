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
}

ICollisionDelegate::~ICollisionDelegate(void)
{
    
}