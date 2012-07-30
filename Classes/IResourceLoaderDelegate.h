//
//  IResourceLoaderDelegate.h
//  iGaia
//
//  Created by code_oneclick on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IResourceLoaderDelegate_h
#define iGaia_IResourceLoaderDelegate_h

#include "IDelegate.h"
#include "IResource.h"

class IResourceLoaderDelegate : public virtual IDelegate
{
public:
    IResourceLoaderDelegate(void);
    virtual ~IResourceLoaderDelegate(void);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource) = 0;
};


#endif
