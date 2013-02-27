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

extern "C" class IResource_INTERFACE;

typedef std::function<void(IResource_INTERFACE* _resource)> __RESOURCE_DID_LOAD_LISTENER;

class CResourceLoadCallback final
{
    
private:

    friend class CResourceLoadCallback_INTERFACE;
    
    __RESOURCE_DID_LOAD_LISTENER m_resourceDidLoadListener;

protected:
    
    CResourceLoadCallback(void) = default;

    void ConnectResourceDidLoadListener(const __RESOURCE_DID_LOAD_LISTENER& _listener);
    
public:
    
    ~CResourceLoadCallback(void) = default;

    void DispatchResourceDidLoad(IResource_INTERFACE* _resource);
};

class CResourceLoadCallback_INTERFACE
{
private:

    CResourceLoadCallback m_resourceLoadCallback;
    void ConnectResourceLoadCallback(void);
    
protected:

    CResourceLoadCallback_INTERFACE(void);

    virtual void OnResourceDidLoad(IResource_INTERFACE* _resource) = 0;
    
public:

    virtual ~CResourceLoadCallback_INTERFACE(void) = default;

    inline CResourceLoadCallback* Get_Commands(void)
    {
        return &m_resourceLoadCallback;
    }
};

#endif 
