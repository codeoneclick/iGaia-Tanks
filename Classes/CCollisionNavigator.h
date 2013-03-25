//
//  CCollisionNavigator.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/25/13.
//
//

#ifndef __iGaia_CartoonPanzers__CCollisionNavigator__
#define __iGaia_CartoonPanzers__CCollisionNavigator__

#include "CNavigator.h"
#include "CCollisionCallback.h"

class CCollisionNavigator :
public CNavigator,
public CCollisionCallback_INTERFACE
{
private:

protected:

public:

    CCollisionNavigator(void);
    ~CCollisionNavigator(void);
};

#endif 
