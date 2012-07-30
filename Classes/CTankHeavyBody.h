//
//  CTankHeavyBody.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankHeavyBody__
#define __iGaia__CTankHeavyBody__

#include <iostream>
#include "ITankBody.h"

class CTankHeavyBody : public ITankBody
{
protected:
public:
    CTankHeavyBody(void);
    ~CTankHeavyBody(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankHeavyBody__) */
