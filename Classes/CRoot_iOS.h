//
//  CRoot_iOS.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#ifndef CRoot_iOS_h
#define CRoot_iOS_h

#include "CSceneFabricator.h"
#include "CSceneGraph.h"
#include "IGLContext.h"

class CRoot_iOS : public virtual CSceneFabricator, public virtual CSceneGraph
{
private:
    
    IGLContext_INTERFACE* m_glContext;
    
protected:
    
public:
    
    CRoot_iOS(void* _glView);
    ~CRoot_iOS(void);
};

#endif 
