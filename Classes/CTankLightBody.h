//
//  CTankLightBody.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankLightBody__
#define __iGaia__CTankLightBody__

#include <iostream>
#include "ITankBody.h"

class CTankLightBody : public ITankBody
{
protected:
public:
    CTankLightBody(void);
    ~CTankLightBody(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankLightBody__) */
