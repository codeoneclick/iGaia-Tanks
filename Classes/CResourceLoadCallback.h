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
typedef std::shared_ptr<IResource_INTERFACE> TSharedPtrResource;

typedef std::function<void(TSharedPtrResource _resource)> __ON_RESOURCE_DID_LOAD_CALLBACK;

class CResourceLoadCallback final
{
private:

    friend class CResourceLoadCallback_INTERFACE;
    
    __ON_RESOURCE_DID_LOAD_CALLBACK m_onResourceDidLoadCallback;

protected:
    
    CResourceLoadCallback(void) {};

    void Register_OnResourceLoadCallback(const __ON_RESOURCE_DID_LOAD_CALLBACK& _listener);
    
public:
    
    ~CResourceLoadCallback(void) {};

    void Execute_OnResourceDidLoadCallback(TSharedPtrResource _resource);
};

class CResourceLoadCallback_INTERFACE
{
private:

    CResourceLoadCallback m_commands;
    void RegisterCommands(void);
    
protected:

    CResourceLoadCallback_INTERFACE(void);

    virtual void OnResourceDidLoad(TSharedPtrResource _resource) = 0;
    
public:

    virtual ~CResourceLoadCallback_INTERFACE(void) {};

    inline CResourceLoadCallback* Get_Commands(void)
    {
		return &m_commands;
    };
};

#endif 
