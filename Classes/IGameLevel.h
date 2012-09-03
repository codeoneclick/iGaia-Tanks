//
//  IGameLevel.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__IGameLevel__
#define __iGaia__IGameLevel__

#include "CEnvironment.h"
#include "CBuilding.h"
#include "ITouchDelegate.h"

class IGameLevel : public ITouchDelegate
{
protected:
    std::vector<CBuilding*> m_lBuildings;
public:
    IGameLevel(void);
    virtual ~IGameLevel(void);
    
    virtual void Load(void);
    virtual void Unload(void);
    virtual void Update(void);
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__ILevel__) */
