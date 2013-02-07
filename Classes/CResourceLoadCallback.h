//
//  CResourceLoadCallback.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/7/13.
//
//

#ifndef CResourceLoadCallback_h
#define CResourceLoadCallback_h

#include "HCommon.h"
#include "IResource.h"

typedef std::function<void(IResource* _pResource, E_RESOURCE_TYPE _eResourceType)> __RESOURCE_DID_LOAD_LISTENER;

class CResourceLoadCallback final
{
    
private:

    friend class CResourceLoadCallback_INTERFACE;
    
    __RESOURCE_DID_LOAD_LISTENER m_tResourceDidLoadListener;

protected:
    
    CResourceLoadCallback(void) = default;

    void ConnectResourceDidLoadListener(const __RESOURCE_DID_LOAD_LISTENER& _tListener);
    
public:
    
    ~CResourceLoadCallback(void) = default;

    void NotifyResourceDidLoadListener(IResource* _pResource, E_RESOURCE_TYPE _eResourceType);
};

class CResourceLoadCallback_INTERFACE
{
private:

    CResourceLoadCallback m_tResourceLoadCallback;
    void ConnectResourceLoadCallback(void);
    
protected:

    CResourceLoadCallback_INTERFACE(void);

    virtual void OnResourceDidLoad(IResource* _pResource, E_RESOURCE_TYPE _eResourceType) = 0;
    
public:

    virtual ~CResourceLoadCallback_INTERFACE(void) = default;
};

#endif 
