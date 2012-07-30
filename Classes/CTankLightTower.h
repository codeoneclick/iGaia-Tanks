//
//  CTankLightTower.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankLightTower__
#define __iGaia__CTankLightTower__

#include <iostream>
#include "ITankTower.h"

class CTankLightTower : public ITankTower
{
protected:
public:
    CTankLightTower(void);
    ~CTankLightTower(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankLightTower__) */
