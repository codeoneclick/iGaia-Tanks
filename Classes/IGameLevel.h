//
//  IGameLevel.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__IGameLevel__
#define __iGaia__IGameLevel__

#include "CLandscape.h"
#include "CGrass.h"
#include "COcean.h"
#include "CSkyBox.h"
#include "CBuilding.h"
#include "ITouchDelegate.h"

class IGameLevel : public ITouchDelegate
{
protected:
    CLandscape* m_pLandscape;
    CGrass* m_pGrass;
    COcean* m_pOcean;
    CSkyBox* m_pSkyBox;
    std::vector<CBuilding*> m_lBuildings;
public:
    IGameLevel(void);
    virtual ~IGameLevel(void);
    CLandscape* Get_Landscape(void) { return m_pLandscape; }
    CGrass* Get_Grass(void) { return m_pGrass; }
    COcean* Get_Ocean(void) { return m_pOcean; }
    CSkyBox* Get_SkyBox(void) { return m_pSkyBox; }
    
    virtual void Load(void);
    virtual void Unload(void);
    virtual void Update(void);
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__ILevel__) */
