//
//  INavigationDelegate.h
//  iGaia
//
//  Created by sergey sergeev on 8/15/12.
//
//

#ifndef __iGaia__INavigationDelegate__
#define __iGaia__INavigationDelegate__

#include <iostream>
#include <iostream>
#include "IDelegate.h"
#include "box2d.h"

class INavigationDelegate : public virtual IDelegate
{
public:
    INavigationDelegate(void);
    virtual ~INavigationDelegate(void);
    virtual void OnNavigationPositionChanged(const glm::vec3& _vPosition) = 0;
    virtual void OnNavigationRotationChanged(const glm::vec3& _vRotation) = 0;
};

#endif /* defined(__iGaia__INavigationDelegate__) */
