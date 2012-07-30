//
//  CTankHeavyTrack.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__CTankHeavyTrack__
#define __iGaia__CTankHeavyTrack__

#include <iostream>
#include "ITankTrack.h"

class CTankHeavyTrack : public ITankTrack
{
protected:
public:
    CTankHeavyTrack(void);
    ~CTankHeavyTrack(void);
    
    void Load(void);
    void Update(void);
};

#endif /* defined(__iGaia__CTankHeavyTrack__) */
