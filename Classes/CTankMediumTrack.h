//
//  CTankMediumTrack.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankMediumTrack__
#define __iGaia__CTankMediumTrack__

#include <iostream>
#include "ITankTrack.h"

class CTankMediumTrack : public ITankTrack
{
protected:
public:
    CTankMediumTrack(void);
    ~CTankMediumTrack(void);
    
    void Load(void);
    void Update(void);
};


#endif /* defined(__iGaia__CTankMediumTrack__) */
