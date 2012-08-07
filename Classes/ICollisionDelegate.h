//
//  ICollisionDelegate.h
//  iGaia
//
//  Created by sergey sergeev on 8/7/12.
//
//

#ifndef __iGaia__ICollisionDelegate__
#define __iGaia__ICollisionDelegate__

#include <iostream>
#include "IDelegate.h"

class ICollisionDelegate : public virtual IDelegate
{
protected:
    std::string m_sColliderIdStr;
public:
    ICollisionDelegate(void);
    virtual ~ICollisionDelegate(void);
    virtual void OnCollision(ICollisionDelegate* _pCollider) = 0;
    std::string Get_ColliderIdStr(void) { return m_sColliderIdStr; }
};


#endif /* defined(__iGaia__ICollisionDelegate__) */
