//
//  ITouchDelegate.h
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#ifndef __iGaia__ITouchDelegate__
#define __iGaia__ITouchDelegate__

#include <iostream>
#include "IDelegate.h"

class ITouchDelegate : public virtual IDelegate
{
public:
    ITouchDelegate(void);
    virtual ~ITouchDelegate(void);
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner) = 0;
};


#endif /* defined(__iGaia__ITouchDelegate__) */
