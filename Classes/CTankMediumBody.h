//
//  CTankMediumBody.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankMediumBody__
#define __iGaia__CTankMediumBody__

#include <iostream>
#include "ITankBody.h"

class CTankMediumBody : public ITankBody
{
protected:
public:
    CTankMediumBody(void);
    ~CTankMediumBody(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankMediumBody__) */
