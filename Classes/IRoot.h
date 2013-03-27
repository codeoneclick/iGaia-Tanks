//
//  HRoot.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/21/13.
//
//

#ifndef HRoot_h
#define HRoot_h

#include "CSceneFabricator.h"
#include "CSceneGraph.h"
#include "IInputContext.h"

class IRoot :
public virtual CSceneFabricator,
public virtual CSceneGraph,
public virtual IInputContext_INTERFACE
{
    
};

#endif
