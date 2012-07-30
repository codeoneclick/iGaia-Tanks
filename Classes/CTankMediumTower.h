//
//  CTankMediumTower.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankMediumTower__
#define __iGaia__CTankMediumTower__

#include <iostream>
#include "ITankTower.h"

class CTankMediumTower : public ITankTower
{
protected:
public:
    CTankMediumTower(void);
    ~CTankMediumTower(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankMediumTower__) */
