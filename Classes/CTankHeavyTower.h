//
//  CTankHeavyTower.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankHeavyTower__
#define __iGaia__CTankHeavyTower__

#include <iostream>
#include "ITankTower.h"

class CTankHeavyTower : public ITankTower
{
protected:
public:
    CTankHeavyTower(void);
    ~CTankHeavyTower(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankHeavyTower__) */
