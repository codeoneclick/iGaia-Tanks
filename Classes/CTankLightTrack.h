//
//  CTankLightTrack.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankLightTrack__
#define __iGaia__CTankLightTrack__

#include <iostream>
#include "ITankTrack.h"

class CTankLightTrack : public ITankTrack
{
protected:
public:
    CTankLightTrack(void);
    ~CTankLightTrack(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankLightTrack__) */
