//
//  IDelegate.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IDelegate_h
#define iGaia_IDelegate_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class IDelegate
{
public:
    enum E_DELEGATE_TYPE { E_DELEGATE_TYPE_NONE = 0, E_DELEGATE_TYPE_RESOURCE_LOAD, E_DELEGATE_TYPE_TOUCH };
protected:
    E_DELEGATE_TYPE m_eDelegateType;
public:
    IDelegate(void);
    virtual ~IDelegate(void);
    E_DELEGATE_TYPE Get_DelegateType(void) { return m_eDelegateType; }
};

#endif
